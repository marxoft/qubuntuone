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

/**
 * \file nodelist.cpp
 */

#include "nodelist.h"
#include "nodelist_p.h"

namespace QtUbuntuOne {

NodeList::NodeList(QNetworkReply *reply, QObject *parent) :
    QObject(parent),
    d_ptr(new NodeListPrivate(reply, this))
{
}

NodeList::NodeList(NodeListPrivate &d, QObject *parent) :
    QObject(parent),
    d_ptr(&d)
{
}

NodeList::~NodeList() {}

/**
 * count
 */
int NodeList::count() const {
    Q_D(const NodeList);

    return d->count();
}

/**
 * nodes
 */
QList<Node*> NodeList::nodes() const {
    Q_D(const NodeList);

    return d->nodes();
}

/**
 * error
 */
NodeList::Error NodeList::error() const {
    Q_D(const NodeList);

    return d->error();
}

/**
 * errorString
 */
QString NodeList::errorString() const {
    Q_D(const NodeList);

    return d->errorString();
}

/**
 * cancel
 */
void NodeList::cancel() {
    Q_D(NodeList);

    d->cancel();
}

#include "moc_nodelist.cpp"

}
