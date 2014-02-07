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
 * \file playlist.h
 */

#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "qubuntuone_global.h"
#include <QObject>
#include <QUrl>
#include <QVariantMap>
#include <QNetworkReply>

class QNetworkReply;

namespace QtUbuntuOne {

class PlaylistPrivate;

/**
 * \class Playlist
 * \brief Contains the metadata of an UbuntuOne music playlist.
 *
 * Playlist contains the metadata of an UbuntuOne music playlist.
 * The metadata is read-only.
 */
class QUBUNTUONESHARED_EXPORT Playlist : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString id
               READ id
               NOTIFY ready)
    Q_PROPERTY(QString name
               READ name
               NOTIFY ready)
    Q_PROPERTY(QUrl url
               READ url
               NOTIFY ready)
    Q_PROPERTY(int songCount
               READ songCount
               NOTIFY ready)
    Q_PROPERTY(Error error
               READ error
               NOTIFY ready)
    Q_PROPERTY(QString errorString
               READ errorString
               NOTIFY ready)

    Q_ENUMS(Error)

    friend class Music;
    friend class PlaylistListPrivate;

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

    explicit Playlist(QObject *parent = 0);
    explicit Playlist(Playlist *otherPlaylist, QObject *parent = 0);
    ~Playlist();

    /**
     * Loads metadata from another instance of Playlist.
     *
     * \param Playlist*
     */
    Q_INVOKABLE void loadPlaylist(Playlist *otherPlaylist);

    /**
     * Returns the unique id of the Playlist.
     *
     * \return QString
     */
    QString id() const;

    /**
     * Returns the name of the Playlist.
     *
     * \return QString
     */
    QString name() const;

    /**
     * Returns the unique URL of the Playlist.
     *
     * \return QUrl
     */
    QUrl url() const;

    /**
     * Returns the song count of the Playlist.
     *
     * \return int
     */
    int songCount() const;

    Error error() const;
    QString errorString() const;

public slots:
    /**
     * Cancels the request.
     */
    void cancel();

signals:
    /**
     * Emitted when new artist metadata has been loaded.
     *
     * \param playlist
     */
    void ready(Playlist *playlist);

    /**
     * Emitted when the request is cancelled.
     *
     * \param playlist.
     */
    void cancelled(Playlist *playlist);

private:
    explicit Playlist(QNetworkReply *reply, QObject *parent = 0);
    explicit Playlist(PlaylistPrivate &d, QObject *parent = 0);

    QScopedPointer<PlaylistPrivate> d_ptr;

    Q_DECLARE_PRIVATE(Playlist)

    Q_PRIVATE_SLOT(d_func(), void _q_onReplyFinished())
};

}

Q_DECLARE_METATYPE(QtUbuntuOne::Playlist::Error)

#endif // PLAYLIST_H
