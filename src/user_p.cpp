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

#include "user_p.h"
#include "json.h"

namespace QtUbuntuOne {

UserPrivate::UserPrivate(QNetworkReply *reply, User *parent) :
    q_ptr(parent),
    m_reply(reply),
    m_maxBytes(0),
    m_usedBytes(0),
    m_error(User::NoError)
{
    Q_Q(User);

    if (m_reply) {
        q->connect(m_reply, SIGNAL(finished()), q, SLOT(_q_onReplyFinished()));
    }
}

UserPrivate::~UserPrivate() {
    if (m_reply) {
        delete m_reply;
        m_reply = 0;
    }
}

void UserPrivate::loadUser(const QVariantMap &user) {
    Q_Q(User);

    this->setId(user.value("id").toString());
    this->setName(user.value("visible_name").toString());
    this->setResourcePath(user.value("resource_path").toString());
    this->setRootNodePath(user.value("root_node_path").toString());
    this->setUserNodePaths(user.value("user_node_paths").toStringList());
    this->setMaxBytes(user.value("max_bytes").toLongLong());
    this->setUsedBytes(user.value("used_bytes").toLongLong());
    this->setError(User::NoError);
    this->setErrorString(QString());

    emit q->ready(q);
}

QString UserPrivate::id() const {
    return m_id;
}

void UserPrivate::setId(const QString &id) {
    m_id = id;
}

QString UserPrivate::name() const {
    return m_name;
}

void UserPrivate::setName(const QString &name) {
    m_name = name;
}

QString UserPrivate::resourcePath() const {
    return m_resourcePath;
}

void UserPrivate::setResourcePath(const QString &path) {
    m_resourcePath = path;
}

QString UserPrivate::rootNodePath() const {
    return m_rootNodePath;
}

void UserPrivate::setRootNodePath(const QString &path) {
    m_rootNodePath = path;
}

QStringList UserPrivate::userNodePaths() const {
    return m_userNodePaths;
}

void UserPrivate::setUserNodePaths(const QStringList &paths) {
    m_userNodePaths = paths;
}

qint64 UserPrivate::maxBytes() const {
    return m_maxBytes;
}

void UserPrivate::setMaxBytes(qint64 bytes) {
    m_maxBytes = bytes;
}

qint64 UserPrivate::usedBytes() const {
    return m_usedBytes;
}

void UserPrivate::setUsedBytes(qint64 bytes) {
    m_usedBytes = bytes;
}

User::Error UserPrivate::error() const {
    return m_error;
}

void UserPrivate::setError(User::Error error) {
    m_error = error;
}

QString UserPrivate::errorString() const {
    return m_errorString;
}

void UserPrivate::setErrorString(const QString &errorString) {
    m_errorString = errorString;
}

void UserPrivate::cancel() {
    if (m_reply) {
        m_reply->abort();
    }
}

void UserPrivate::_q_onReplyFinished() {
    Q_Q(User);

    if (m_reply) {
        switch (m_reply->error()) {
        case QNetworkReply::NoError:
            break;
        case QNetworkReply::OperationCanceledError:
            emit q->cancelled(q);
            return;
        default:
            this->setError(User::Error(m_reply->error()));
            this->setErrorString(m_reply->errorString());
            emit q->ready(q);
            return;
        }

        QString response(m_reply->readAll());
        QVariantMap result = QtJson::Json::parse(response).toMap();

        if (!result.isEmpty()) {
            this->loadUser(result);
        }
        else {
            this->setError(User::ParserError);
            this->setErrorString(QObject::tr("Cannot parse server response"));
            emit q->ready(q);
        }

        m_reply->deleteLater();
        m_reply = 0;
    }
}

}
