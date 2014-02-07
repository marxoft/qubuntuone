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
 * \file artwork.h
 */

#ifndef ARTWORK_H
#define ARTWORK_H

#include "qubuntuone_global.h"
#include <QObject>
#include <QImage>
#include <QUrl>
#include <QNetworkReply>

namespace QtUbuntuOne {

class ArtworkPrivate;

/**
 * \class Artwork
 * \brief Contains the metadata of an UbuntuOne music arwork image.
 *
 * Artwork contains the metadata of an UbuntuOne music arwork image.
 * The metadata is read-only.
 */
class QUBUNTUONESHARED_EXPORT Artwork : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QUrl url
               READ url)
    Q_PROPERTY(QSize size
               READ size)
    Q_PROPERTY(QImage image
               READ image
               NOTIFY ready)
    Q_PROPERTY(Error error
               READ error
               NOTIFY ready)
    Q_PROPERTY(QString errorString
               READ errorString
               NOTIFY ready)

    Q_ENUMS(Error)

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

    ~Artwork();

    /**
     * Returns the unique URL of the image.
     *
     * \return QUrl
     */
    QUrl url() const;

    /**
     * Returns the requested size of the image.
     * The image will be scaled to this size, once
     * it has been retrieved.
     *
     * \return QSize
     */
    QSize size() const;

    /**
     * Returns the image.
     *
     * \return QImage
     */
    QImage image() const;

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
     * \param list The Artwork object.
     */
    void ready(Artwork *artwork);

    /**
     * Emitted when the request is cancelled.
     *
     * \param list The Artwork object.
     */
    void cancelled(Artwork *artwork);

private:
    explicit Artwork(QNetworkReply *reply, const QSize &size, QObject *parent = 0);
    explicit Artwork(ArtworkPrivate &d, QObject *parent = 0);

    QScopedPointer<ArtworkPrivate> d_ptr;

    Q_DECLARE_PRIVATE(Artwork)

    Q_PRIVATE_SLOT(d_func(), void _q_onReplyFinished())
};

}

Q_DECLARE_METATYPE(QtUbuntuOne::Artwork::Error)

#endif // ARTWORK_H
