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
 * \file account.h
 */

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "qubuntuone_global.h"
#include <QObject>

namespace QtUbuntuOne {

class StorageQuota;
class UserAccount;

/**
 * \class Account
 * \brief Ubuntu One account retriever.
 *
 * Account retrieves account details for the currently autheticated user.
 */
class QUBUNTUONESHARED_EXPORT Account : public QObject
{
    Q_OBJECT

public:
    Account(QObject *parent = 0);
    ~Account();

    /**
     * Requests account information of the currently authenticated user and returns instance of UserAccount.
     *
     * \return UserAccount* A UserAccount containing the result of the request.
     */
    Q_INVOKABLE static UserAccount* getAccount();

    /**
     * Requests the storage quota of the currently authenticated user and returns an instance of StorageQuota.
     *
     * \return StorageQuota* A StorageQuota containing the result of the request.
     */
    Q_INVOKABLE static StorageQuota* getStorageQuota();
};

}

#endif // ACCOUNT_H
