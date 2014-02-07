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
 * \file reply.h
 */

#ifndef REPLY_H
#define REPLY_H

#include "qubuntuone_global.h"
#include <QObject>
#include <QNetworkReply>

namespace QtUbuntuOne {

class ReplyPrivate;

/**
 * \class Reply
 * \brief Contains data for a request.
 *
 * Reply contains metadata that results from a request made using the  class.
 * The metadata takes the form of a QVariant.
 */
class QUBUNTUONESHARED_EXPORT Reply : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QUrl url
               READ url)
    Q_PROPERTY(int status
               READ status
               NOTIFY finished)
    Q_PROPERTY(QVariant result
               READ result
               NOTIFY finished)
    Q_PROPERTY(QString resultString
               READ resultString
               NOTIFY finished)
    Q_PROPERTY(QString resultType
               READ resultTypeString
               NOTIFY finished)
    Q_PROPERTY(Error error
               READ error
               NOTIFY finished)
    Q_PROPERTY(QString errorString
               READ errorString
               NOTIFY finished)

    Q_ENUMS(Error)

    friend class Account;
    friend class Files;
    friend class Music;

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

    ~Reply();

    /**
     * Returns the request URL.
     *
     * \return QUrl The request URL.
     */
    QUrl url() const;

    /**
     * Returns the HTTP status code of the request.
     *
     * \return int The request status.
     */
    int status() const;

    /**
     * Returns the metadata obtained from the request.
     *
     * \return QVariant The request result.
     */
    QVariant result() const;

    /**
     * Returns the result, serialised as a string.
     *
     * \return QString The serialised result.
     */
    QString resultString() const;

    /**
     * Returns the data type of the result. See QVariant documentation for details.
     *
     * \return QVariant::Type The result type.
     */
    QVariant::Type resultType() const;

    /**
     * Returns the data type of the result, cast to a string. See QVariant documentation for details.
     *
     * \return QString The result type.
     */
    QString resultTypeString() const;

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
     * \param reply The Reply object.
     */
    void finished(Reply *reply);

    /**
     * Emitted when the request is cancelled.
     *
     * \param reply The Reply object.
     */
    void cancelled(Reply *reply);

private:
    explicit Reply(QNetworkReply *reply, QObject *parent = 0);
    explicit Reply(ReplyPrivate &d, QObject *parent = 0);

    QScopedPointer<ReplyPrivate> d_ptr;

    Q_DECLARE_PRIVATE(Reply)

    Q_PRIVATE_SLOT(d_func(), void _q_onReplyFinished())
};

}

Q_DECLARE_METATYPE(QtUbuntuOne::Reply::Error)

#endif // REPLY_H
