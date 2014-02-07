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
 * \file user.h
 */

#ifndef USER_H
#define USER_H

#include "qubuntuone_global.h"
#include <QObject>
#include <QDateTime>
#include <QUrl>
#include <QVariantMap>
#include <QNetworkReply>

namespace QtUbuntuOne {

class UserPrivate;

/**
 * \class User
 * \brief Contains the metadata of an UbuntuOne user representation.
 *
 * User contains the metadata of an UbuntuOne user representation.
 * The metadata is read-only.
 */
class QUBUNTUONESHARED_EXPORT User : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString id
               READ id
               NOTIFY ready)
    Q_PROPERTY(QString name
               READ name
               NOTIFY ready)
    Q_PROPERTY(QString resourcePath
               READ resourcePath
               NOTIFY ready)
    Q_PROPERTY(QString rootNodePath
               READ rootNodePath
               NOTIFY ready)
    Q_PROPERTY(QStringList userNodePaths
               READ userNodePaths
               NOTIFY ready)
    Q_PROPERTY(qint64 maxBytes
               READ maxBytes
               NOTIFY ready)
    Q_PROPERTY(qint64 usedBytes
               READ usedBytes
               NOTIFY ready)
    Q_PROPERTY(Error error
               READ error
               NOTIFY ready)
    Q_PROPERTY(QString errorString
               READ errorString
               NOTIFY ready)

    Q_ENUMS(Error)

    friend class Files;

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

    ~User();

    /**
     * Returns the unique id of the User.
     *
     * \return QString
     */
    QString id() const;

    /**
     * Returns the name of the User.
     *
     * \return QString
     */
    QString name() const;

    /**
     * Returns the resource path of the User.
     *
     * \return QString
     */
    QString resourcePath() const;

    /**
     * Returns the root node path of the User.
     *
     * \return QString
     */
    QString rootNodePath() const;

    /**
     * Returns a list of user node paths of the User.
     *
     * \return QStringList
     */
    QStringList userNodePaths() const;

    /**
     * Returns the maximum storage of the User.
     *
     * \return qint64
     */
    qint64 maxBytes() const;

    /**
     * Returns the used storage of the User.
     *
     * \return qint64
     */
    qint64 usedBytes() const;

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
     * \param user The User object.
     */
    void ready(User *user);

    /**
     * Emitted when the request is cancelled.
     *
     * \param user The User object.
     */
    void cancelled(User *user);

private:
    explicit User(QNetworkReply *reply, QObject *parent = 0);
    explicit User(UserPrivate &d, QObject *parent = 0);

    QScopedPointer<UserPrivate> d_ptr;

    Q_DECLARE_PRIVATE(User)

    Q_PRIVATE_SLOT(d_func(), void _q_onReplyFinished())
};

}

Q_DECLARE_METATYPE(QtUbuntuOne::User::Error)

#endif // USER_H
