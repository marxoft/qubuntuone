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
 * \file storagequota.cpp
 */

#include "storagequota.h"
#include "storagequota_p.h"

namespace QtUbuntuOne {

StorageQuota::StorageQuota(QNetworkReply *reply, QObject *parent) :
    QObject(parent),
    d_ptr(new StorageQuotaPrivate(reply, this))
{
}

StorageQuota::StorageQuota(StorageQuotaPrivate &d, QObject *parent) :
    QObject(parent),
    d_ptr(&d)
{
}

StorageQuota::~StorageQuota() {}

/**
 * totalStorage
 */
qint64 StorageQuota::totalStorage() const {
    Q_D(const StorageQuota);

    return d->totalStorage();
}

/**
 * usedStorage
 */
qint64 StorageQuota::usedStorage() const {
    Q_D(const StorageQuota);

    return d->usedStorage();
}

/**
 * error
 */
StorageQuota::Error StorageQuota::error() const {
    Q_D(const StorageQuota);

    return d->error();
}

/**
 * errorString
 */
QString StorageQuota::errorString() const {
    Q_D(const StorageQuota);

    return d->errorString();
}

/**
 * cancel
 */
void StorageQuota::cancel() {
    Q_D(StorageQuota);

    d->cancel();
}

#include "moc_storagequota.cpp"

}
