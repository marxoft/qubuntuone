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
 * \file storagequota.h
 */

#ifndef STORAGEQUOTA_H
#define STORAGEQUOTA_H

#include "qubuntuone_global.h"
#include <QObject>
#include <QNetworkReply>

namespace QtUbuntuOne {

class StorageQuotaPrivate;

/**
 * \class StorageQuota
 * \brief Contains the total/used storage of an UbuntuOne account.
 *
 * UserAccount contains the total/used storage of an UbuntuOne account.
 * The metadata is read-only.
 */
class QUBUNTUONESHARED_EXPORT StorageQuota : public QObject
{
    Q_OBJECT

    Q_PROPERTY(qint64 totalStorage
               READ totalStorage
               NOTIFY ready)
    Q_PROPERTY(qint64 usedStorage
               READ usedStorage
               NOTIFY ready)
    Q_PROPERTY(Error error
               READ error
               NOTIFY ready)

    Q_ENUMS(Error)

    friend class Account;

public:
    /**
     * \enum Error
     */
    enum Error {
        NoError = QNetworkReply::NoError,
        ConnectionRefusedError = QNetworkReply::ConnectionRefusedError,
        RemoteHostClosedError = QNetworkReply::RemoteHostClosedError,
        HostNotFoundError = QNetworkReply::HostNotFoundError,
        TimeoutError = QNetworkReply::TimeoutError,
        OperationCanceledError = QNetworkReply::OperationCanceledError,
        SslHandshakeFailedError = QNetworkReply::SslHandshakeFailedError,
        TemporaryNetworkFailureError = QNetworkReply::TemporaryNetworkFailureError,
        ProxyConnectionRefusedError = QNetworkReply::ProxyConnectionRefusedError,
        ProxyConnectionClosedError = QNetworkReply::ProxyConnectionClosedError,
        ProxyNotFoundError = QNetworkReply::ProxyNotFoundError,
        ProxyTimeoutError = QNetworkReply::ProxyTimeoutError,
        ProxyAuthenticationRequiredError = QNetworkReply::ProxyAuthenticationRequiredError,
        ContentAccessDenied = QNetworkReply::ContentAccessDenied,
        ContentOperationNotPermittedError = QNetworkReply::ContentOperationNotPermittedError,
        ContentNotFoundError = QNetworkReply::ContentNotFoundError,
        AuthenticationRequiredError = QNetworkReply::AuthenticationRequiredError,
        ContentReSendError = QNetworkReply::ContentReSendError,
        ProtocolUnknownError = QNetworkReply::ProtocolUnknownError,
        ProtocolInvalidOperationError = QNetworkReply::ProtocolInvalidOperationError,
        UnknownNetworkError = QNetworkReply::UnknownNetworkError,
        UnknownProxyError = QNetworkReply::UnknownProxyError,
        UnknownContentError = QNetworkReply::UnknownContentError,
        ProtocolFailure = QNetworkReply::ProtocolFailure,
        ParserError = 1001
    };

    ~StorageQuota();

    /**
     * Returns the total available storage.
     *
     * \return qint64
     */
    qint64 totalStorage() const;

    /**
     * Returns the used storage.
     *
     * \return qint64
     */
    qint64 usedStorage() const;

    /**
     * Returns the error resulting from the request, or NoError if no error was reported.
     *
     * \return Error The request error.
     */
    Error error() const;

    /**
     * Returns a human-readable string detailing the error resulting from the request, or an empty string if no error was reported.
     *
     * \return QString The request error string.
     */
    QString errorString() const;

public slots:
    /**
     * Cancels the request.
     */
    void cancel();

signals:
    /**
     * Emitted when the request is completed.
     *
     * \param quota The StorageQuota object.
     */
    void ready(StorageQuota *quota);

    /**
     * Emitted when the request is completed.
     *
     * \param quota The StorageQuota object.
     */
    void cancelled(StorageQuota *quota);

private:
    explicit StorageQuota(QNetworkReply *reply, QObject *parent = 0);
    explicit StorageQuota(StorageQuotaPrivate &d, QObject *parent = 0);

    QScopedPointer<StorageQuotaPrivate> d_ptr;

    Q_DECLARE_PRIVATE(StorageQuota)

    Q_PRIVATE_SLOT(d_func(), void _q_onReplyFinished())
};

}

Q_DECLARE_METATYPE(QtUbuntuOne::StorageQuota::Error)

#endif // STORAGEQUOTA_H
