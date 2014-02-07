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
 * \file albumlist.h
 */

#ifndef ALBUMLIST_H
#define ALBUMLIST_H

#include "qubuntuone_global.h"
#include "album.h"
#include <QObject>
#include <QNetworkReply>

class QNetworkReply;

namespace QtUbuntuOne {

class AlbumListPrivate;

/**
 * \class AlbumList
 * \brief Contains a list of UbuntuOne music albums.
 *
 * AlbumList contains a list of UbuntuOne music albums
 * resulting from a request to the Ubuntu One API.
 */
class QUBUNTUONESHARED_EXPORT AlbumList : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int count
               READ count
               NOTIFY ready)
    Q_PROPERTY(QList<Album*> albums
               READ albums
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

    ~AlbumList();

    /**
     * Returns the number of albums in the list.
     *
     * \return int
     */
    int count() const;

    /**
     * Returns the list of albums.
     *
     * \return QList<Album*>
     */
    QList<Album*> albums() const;

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
     * \param list The AlbumList object.
     */
    void ready(AlbumList *list);

    /**
     * Emitted when the request is cancelled.
     *
     * \param list The AlbumList object.
     */
    void cancelled(AlbumList *list);

private:
    explicit AlbumList(QNetworkReply *reply, QObject *parent = 0);
    explicit AlbumList(AlbumListPrivate &d, QObject *parent = 0);

    QScopedPointer<AlbumListPrivate> d_ptr;

    Q_DECLARE_PRIVATE(AlbumList)

    Q_PRIVATE_SLOT(d_func(), void _q_onReplyFinished())
};

}

Q_DECLARE_METATYPE(QtUbuntuOne::Album*)
Q_DECLARE_METATYPE(QtUbuntuOne::AlbumList::Error)

#endif // ALBUMLIST_H
