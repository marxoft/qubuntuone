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
 * \file account.cpp
 */

#include "account.h"
#include "storagequota.h"
#include "useraccount.h"
#include "authentication.h"
#include "networkaccessmanager.h"
#include "urls.h"

namespace QtUbuntuOne {

Account::Account(QObject *parent) :
    QObject(parent)
{
}

Account::~Account() {}

/**
 * getAccount
 */
UserAccount* Account::getAccount() {
    QUrl url(BASE_URL_ACCOUNT);
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", Authentication::getOAuthHeader("GET", BASE_URL_ACCOUNT, QMap<QString, QString>()));
    request.setRawHeader("Accept", "application/json");
    request.setRawHeader("User-Agent", "QUbuntuOne (Qt)");

    return new UserAccount(NetworkAccessManager::instance()->get(request));
}

/**
 * getStorageQuota
 */
StorageQuota* Account::getStorageQuota() {
    QUrl url(BASE_URL_QUOTA);
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", Authentication::getOAuthHeader("GET", BASE_URL_QUOTA, QMap<QString, QString>()));
    request.setRawHeader("Accept", "application/json");
    request.setRawHeader("User-Agent", "QUbuntuOne (Qt)");

    return new StorageQuota(NetworkAccessManager::instance()->get(request));
}

}
