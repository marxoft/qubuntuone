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
 * \file useraccount.h
 */

#include "useraccount.h"
#include "useraccount_p.h"

namespace QtUbuntuOne {

UserAccount::UserAccount(QNetworkReply *reply, QObject *parent) :
    QObject(parent),
    d_ptr(new UserAccountPrivate(reply, this))
{
}

UserAccount::UserAccount(UserAccountPrivate &d, QObject *parent) :
    QObject(parent),
    d_ptr(&d)
{
}

UserAccount::~UserAccount() {}

/**
 * id
 */
QString UserAccount::id() const {
    Q_D(const UserAccount);

    return d->id();
}

/**
 * username
 */
QString UserAccount::username() const {
    Q_D(const UserAccount);

    return d->username();
}

/**
 * nickname
 */
QString UserAccount::nickname() const {
    Q_D(const UserAccount);

    return d->nickname();
}

/**
 * firstName
 */
QString UserAccount::firstName() const {
    Q_D(const UserAccount);

    return d->firstName();
}

/**
 * lastName
 */
QString UserAccount::lastName() const {
    Q_D(const UserAccount);

    return d->lastName();
}

/**
 * email
 */
QString UserAccount::email() const {
    Q_D(const UserAccount);

    return d->email();
}

/**
 * openId
 */
QString UserAccount::openId() const {
    Q_D(const UserAccount);

    return d->openId();
}

/**
 * totalStorage
 */
qint64 UserAccount::totalStorage() const {
    Q_D(const UserAccount);

    return d->totalStorage();
}

/**
 * currentPlan
 */
QString UserAccount::currentPlan() const {
    Q_D(const UserAccount);

    return d->currentPlan();
}

/**
 * detailedPlans
 */
QVariantList UserAccount::detailedPlans() const {
    Q_D(const UserAccount);

    return d->detailedPlans();
}

/**
 * features
 */
QStringList UserAccount::features() const {
    Q_D(const UserAccount);

    return d->features();
}

/**
 * subscription
 */
QVariantMap UserAccount::subscription() const {
    Q_D(const UserAccount);

    return d->subscription();
}

/**
 * error
 */
UserAccount::Error UserAccount::error() const {
    Q_D(const UserAccount);

    return d->error();
}

/**
 * errorString
 */
QString UserAccount::errorString() const {
    Q_D(const UserAccount);

    return d->errorString();
}

/**
 * cancel
 */
void UserAccount::cancel() {
    Q_D(UserAccount);

    d->cancel();
}

#include "moc_useraccount.cpp"

}
