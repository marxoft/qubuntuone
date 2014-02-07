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

#include "playlistlist_p.h"
#include "playlist_p.h"
#include "json.h"

namespace QtUbuntuOne {

PlaylistListPrivate::PlaylistListPrivate(QNetworkReply *reply, PlaylistList *parent) :
    q_ptr(parent),
    m_reply(reply),
    m_error(PlaylistList::NoError)
{
    Q_Q(PlaylistList);

    if (m_reply) {
        q->connect(m_reply, SIGNAL(finished()), q, SLOT(_q_onReplyFinished()));
    }
}

PlaylistListPrivate::~PlaylistListPrivate() {
    if (m_reply) {
        delete m_reply;
        m_reply = 0;
    }
}

int PlaylistListPrivate::count() const {
    return m_playlists.size();
}

QList<Playlist*> PlaylistListPrivate::playlists() const {
    return m_playlists;
}

PlaylistList::Error PlaylistListPrivate::error() const {
    return m_error;
}

void PlaylistListPrivate::setError(PlaylistList::Error error) {
    m_error = error;
}

QString PlaylistListPrivate::errorString() const {
    return m_errorString;
}

void PlaylistListPrivate::setErrorString(const QString &errorstring) {
    m_errorString = errorstring;
}

void PlaylistListPrivate::loadPlaylists(const QVariantList &playlists) {
    Q_Q(PlaylistList);

    foreach (QVariant playlist, playlists) {
        Playlist *p = new Playlist;
        p->d_func()->loadPlaylist(playlist.toMap());
        m_playlists.append(p);
    }

    emit q->ready(q);
}

void PlaylistListPrivate::cancel() {
    if (m_reply) {
        m_reply->abort();
    }
}

void PlaylistListPrivate::_q_onReplyFinished() {
    Q_Q(PlaylistList);

    if (m_reply) {
        switch (m_reply->error()) {
        case QNetworkReply::NoError:
            break;
        case QNetworkReply::OperationCanceledError:
            emit q->cancelled(q);
            return;
        default:
            this->setError(PlaylistList::Error(m_reply->error()));
            this->setErrorString(m_reply->errorString());
            emit q->ready(q);
            return;
        }

        QString response(m_reply->readAll());
        QVariant result = QtJson::Json::parse(response);

        switch (result.type()) {
        case QVariant::Map:
            this->loadPlaylists(result.toMap().value("response").toMap().value("playlists").toList());
            break;
        case QVariant::List:
            this->loadPlaylists(result.toList());
            break;
        default:
            this->setError(PlaylistList::ParserError);
            this->setErrorString(QObject::tr("Cannot parse server response"));
            emit q->ready(q);
            break;
        }

        m_reply->deleteLater();
        m_reply = 0;
    }
}

}

