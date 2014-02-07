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

#ifndef USERACCOUNT_H
#define USERACCOUNT_H

#include "qubuntuone_global.h"
#include <QObject>
#include <QVariantMap>
#include <QNetworkReply>

namespace QtUbuntuOne {

class UserAccountPrivate;

/**
 * \class UserAccount
 * \brief Contains the metadata of an UbuntuOne account.
 *
 * UserAccount contains the metadata of an UbuntuOne account.
 * The metadata is read-only.
 */
class QUBUNTUONESHARED_EXPORT UserAccount : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString id
               READ id
               NOTIFY ready)
    Q_PROPERTY(QString username
               READ username
               NOTIFY ready)
    Q_PROPERTY(QString nickname
               READ nickname
               NOTIFY ready)
    Q_PROPERTY(QString firstName
               READ firstName
               NOTIFY ready)
    Q_PROPERTY(QString lastName
               READ lastName
               NOTIFY ready)
    Q_PROPERTY(QString email
               READ email
               NOTIFY ready)
    Q_PROPERTY(QString openId
               READ openId
               NOTIFY ready)
    Q_PROPERTY(qint64 totalStorage
               READ totalStorage
               NOTIFY ready)
    Q_PROPERTY(QString currentPlan
               READ currentPlan
               NOTIFY ready)
    Q_PROPERTY(QVariantList detailedPlans
               READ detailedPlans
               NOTIFY ready)
    Q_PROPERTY(QStringList features
               READ features
               NOTIFY ready)
    Q_PROPERTY(QVariantMap subscription
               READ subscription
               NOTIFY ready)
    Q_PROPERTY(Error error
               READ error
               NOTIFY ready)
    Q_PROPERTY(QString errorString
               READ errorString
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

    ~UserAccount();

    /**
     * Returns the unique id of the UserAccount.
     *
     * \return QString
     */
    QString id() const;

    /**
     * Returns the username of the UserAccount.
     *
     * \return QString
     */
    QString username() const;

    /**
     * Returns the nickname of the UserAccount.
     *
     * \return QString
     */
    QString nickname() const;

    /**
     * Returns the first name of the UserAccount.
     *
     * \return QString
     */
    QString firstName() const;

    /**
     * Returns the last name of the UserAccount.
     *
     * \return QString
     */
    QString lastName() const;

    /**
     * Returns the email address of the UserAccount.
     *
     * \return QString
     */
    QString email() const;

    /**
     * Returns the open id of the UserAccount.
     *
     * \return QString
     */
    QString openId() const;

    /**
     * Returns the total storage of the UserAccount.
     *
     * \return qint64
     */
    qint64 totalStorage() const;

    /**
     * Returns the current plan of the UserAccount.
     *
     * \return QString
     */
    QString currentPlan() const;

    /**
     * Returns a list of plans of the UserAccount.
     *
     * \return QVariantList
     */
    QVariantList detailedPlans() const;

    /**
     * Returns a list of features of the UserAccount.
     *
     * \return QStringList
     */
    QStringList features() const;

    /**
     * Returns the subscription of the UserAccount.
     *
     * \return QVariantMap
     */
    QVariantMap subscription() const;

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
     * \param account The UserAccount object.
     */
    void ready(UserAccount *account);

    /**
     * Emitted when the request is cancelled.
     *
     * \param account The UserAccount object.
     */
    void cancelled(UserAccount *account);

private:
    explicit UserAccount(QNetworkReply *reply, QObject *parent = 0);
    explicit UserAccount(UserAccountPrivate &d, QObject *parent = 0);

    QScopedPointer<UserAccountPrivate> d_ptr;

    Q_DECLARE_PRIVATE(UserAccount)

    Q_PRIVATE_SLOT(d_func(), void _q_onReplyFinished())
};

}

Q_DECLARE_METATYPE(QtUbuntuOne::UserAccount::Error)

#endif // USERACCOUNT_H
