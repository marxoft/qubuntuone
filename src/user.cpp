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
 * \file user.cpp
 */

#include "user.h"
#include "user_p.h"

namespace QtUbuntuOne {

User::User(QNetworkReply *reply, QObject *parent) :
    QObject(parent),
    d_ptr(new UserPrivate(reply, this))
{
}

User::User(UserPrivate &d, QObject *parent) :
    QObject(parent),
    d_ptr(&d)
{
}

User::~User() {}

/**
 * id
 */
QString User::id() const {
    Q_D(const User);

    return d->id();
}

/**
 * name
 */
QString User::name() const {
    Q_D(const User);

    return d->name();
}

/**
 * resourcePath
 */
QString User::resourcePath() const {
    Q_D(const User);

    return d->resourcePath();
}

/**
 * rootNodePath
 */
QString User::rootNodePath() const {
    Q_D(const User);

    return d->rootNodePath();
}

/**
 * userNodePaths
 */
QStringList User::userNodePaths() const {
    Q_D(const User);

    return d->userNodePaths();
}

/**
 * maxBytes
 */
qint64 User::maxBytes() const {
    Q_D(const User);

    return d->maxBytes();
}

/**
 * usedBytes
 */
qint64 User::usedBytes() const {
    Q_D(const User);

    return d->usedBytes();
}

/**
 * error
 */
User::Error User::error() const {
    Q_D(const User);

    return d->error();
}

/**
 * errorString
 */
QString User::errorString() const {
    Q_D(const User);

    return d->errorString();
}

/**
 * cancel
 */
void User::cancel() {
    Q_D(User);

    d->cancel();
}

#include "moc_user.cpp"

}
