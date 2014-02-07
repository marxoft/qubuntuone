/*
 * Copyright (C) 2014 Stuart Howarth <showarth@marxoft.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU Lesser General Public License,
 * version 3, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "nodelist_p.h"
#include "node_p.h"
#include "json.h"

namespace QtUbuntuOne {

NodeListPrivate::NodeListPrivate(QNetworkReply *reply, NodeList *parent) :
    q_ptr(parent),
    m_reply(reply),
    m_error(NodeList::NoError)
{
    Q_Q(NodeList);

    if (m_reply) {
        q->connect(m_reply, SIGNAL(finished()), q, SLOT(_q_onReplyFinished()));
    }
}

NodeListPrivate::~NodeListPrivate() {
    if (m_reply) {
        delete m_reply;
        m_reply = 0;
    }
}

int NodeListPrivate::count() const {
    return m_nodes.size();
}

QList<Node*> NodeListPrivate::nodes() const {
    return m_nodes;
}

NodeList::Error NodeListPrivate::error() const {
    return m_error;
}

void NodeListPrivate::setError(NodeList::Error error) {
    m_error = error;
}

QString NodeListPrivate::errorString() const {
    return m_errorString;
}

void NodeListPrivate::setErrorString(const QString &errorstring) {
    m_errorString = errorstring;
}

void NodeListPrivate::loadNodes(const QVariantList &nodes) {
    Q_Q(NodeList);

    foreach (QVariant node, nodes) {
        Node *n = new Node;
        n->d_func()->loadNode(node.toMap());
        m_nodes.append(n);
    }

    emit q->ready(q);
}

void NodeListPrivate::cancel() {
    if (m_reply) {
        m_reply->abort();
    }
}

void NodeListPrivate::_q_onReplyFinished() {
    Q_Q(NodeList);

    if (m_reply) {
        switch (m_reply->error()) {
        case QNetworkReply::NoError:
            break;
        case QNetworkReply::OperationCanceledError:
            emit q->cancelled(q);
            return;
        default:
            this->setError(NodeList::Error(m_reply->error()));
            this->setErrorString(m_reply->errorString());
            emit q->ready(q);
            return;
        }

        QString response(m_reply->readAll());
        QVariant result = QtJson::Json::parse(response);

        switch (result.type()) {
        case QVariant::Map:
            this->loadNodes(result.toMap().value("children").toList());
            break;
        case QVariant::List:
            this->loadNodes(result.toList());
            break;
        default:
            this->setError(NodeList::ParserError);
            this->setErrorString(QObject::tr("Cannot parse server response"));
            emit q->ready(q);
            break;
        }

        m_reply->deleteLater();
        m_reply = 0;
    }
}

}
