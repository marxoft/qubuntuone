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
 * \file token.h
 */

#ifndef TOKEN_H
#define TOKEN_H

#include "qubuntuone_global.h"
#include <QObject>
#include <QNetworkReply>

namespace QtUbuntuOne {

class TokenPrivate;

/**
 * \class Token
 * \brief Contains data for an Authentication request.
 *
 * Token contains metadata that results from a request made using the Authentication class.
 * The metadata takes the form of a QVariant. Token also provides convenience methods for
 * accessing the credentials returned by the request.
 */
class QUBUNTUONESHARED_EXPORT Token : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString tokenName
               READ tokenName
               NOTIFY ready)
    Q_PROPERTY(QString consumerKey
               READ consumerKey
               NOTIFY ready)
    Q_PROPERTY(QString consumerSecret
               READ consumerSecret
               NOTIFY ready)
    Q_PROPERTY(QString tokenKey
               READ tokenKey
               NOTIFY ready)
    Q_PROPERTY(QString tokenSecret
               READ tokenSecret
               NOTIFY ready)
    Q_PROPERTY(Error error
               READ error
               NOTIFY ready)
    Q_PROPERTY(QString errorString
               READ errorString
               NOTIFY ready)

    Q_ENUMS(Error)

    friend class Authentication;

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

    ~Token();

    /**
     * Returns the token name.
     *
     * \return QString The token name.
     */
    QString tokenName() const;

    /**
     * Returns the consumer key.
     *
     * \return QString The consumer key.
     */
    QString consumerKey() const;

    /**
     * Returns the consumer secret.
     *
     * \return QString The consumer secret.
     */
    QString consumerSecret() const;

    /**
     * Returns the token key.
     *
     * \return QString The token key.
     */
    QString tokenKey() const;

    /**
     * Returns the token secret.
     *
     * \return QString The token secret.
     */
    QString tokenSecret() const;

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
     * \param token The Token object.
     */
    void ready(Token *token);

    /**
     * Emitted when the request is completed.
     *
     * \param token The Token object.
     */
    void cancelled(Token *token);

private:
    explicit Token(QNetworkReply *reply, QObject *parent = 0);
    explicit Token(TokenPrivate &d, QObject *parent = 0);

    QScopedPointer<TokenPrivate> d_ptr;

    Q_DECLARE_PRIVATE(Token)

    Q_PRIVATE_SLOT(d_func(), void _q_onReplyFinished())
};

}

Q_DECLARE_METATYPE(QtUbuntuOne::Token::Error)

#endif // TOKEN_H
