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

#include "playlist_p.h"
#include "json.h"
#include <QNetworkReply>

namespace QtUbuntuOne {

PlaylistPrivate::PlaylistPrivate(Playlist *parent) :
    q_ptr(parent),
    m_reply(0),
    m_songCount(0),
    m_error(Playlist::NoError)
{
}

PlaylistPrivate::PlaylistPrivate(Playlist *otherPlaylist, Playlist *parent) :
    q_ptr(parent),
    m_reply(0),
    m_id(otherPlaylist->id()),
    m_name(otherPlaylist->name()),
    m_url(otherPlaylist->url()),
    m_songCount(otherPlaylist->songCount()),
    m_error(otherPlaylist->error())
{
    Q_Q(Playlist);

    emit q->ready(q);
}

PlaylistPrivate::PlaylistPrivate(QNetworkReply *reply, Playlist *parent) :
    q_ptr(parent),
    m_reply(reply),
    m_songCount(0),
    m_error(Playlist::NoError)
{
    Q_Q(Playlist);

    if (m_reply) {
        q->connect(m_reply, SIGNAL(finished()), q, SLOT(_q_onReplyFinished()));
    }
}

PlaylistPrivate::~PlaylistPrivate() {
    if (m_reply) {
        delete m_reply;
        m_reply = 0;
    }
}

void PlaylistPrivate::loadPlaylist(Playlist *otherPlaylist) {
    Q_Q(Playlist);

    this->setId(otherPlaylist->id());
    this->setName(otherPlaylist->name());
    this->setUrl(otherPlaylist->url());
    this->setSongCount(otherPlaylist->songCount());
    this->setError(otherPlaylist->error());

    emit q->ready(q);
}

void PlaylistPrivate::loadPlaylist(const QVariantMap &playlist) {
    Q_Q(Playlist);

    this->setId(playlist.value("id").toString());
    this->setName(playlist.value("name").toString());
    this->setUrl(playlist.value("playlist_url").toUrl());
    this->setSongCount(playlist.value("song_count").toInt());

    emit q->ready(q);
}

QString PlaylistPrivate::id() const {
    return m_id;
}

void PlaylistPrivate::setId(const QString &id) {
    m_id = id;
}

QString PlaylistPrivate::name() const {
    return m_name;
}

void PlaylistPrivate::setName(const QString &name) {
    m_name = name;
}

QUrl PlaylistPrivate::url() const {
    return m_url;
}

void PlaylistPrivate::setUrl(const QUrl &url) {
    m_url = url;
}

int PlaylistPrivate::songCount() const {
    return m_songCount;
}

void PlaylistPrivate::setSongCount(int count) {
    m_songCount = count;
}

Playlist::Error PlaylistPrivate::error() const {
    return m_error;
}

void PlaylistPrivate::setError(Playlist::Error error) {
    m_error = error;
}

QString PlaylistPrivate::errorString() const {
    return m_errorString;
}

void PlaylistPrivate::setErrorString(const QString &errorString) {
    m_errorString = errorString;
}

void PlaylistPrivate::cancel() {
    if (m_reply) {
        m_reply->abort();
    }
}

void PlaylistPrivate::_q_onReplyFinished() {
    Q_Q(Playlist);

    if (m_reply) {
        switch (m_reply->error()) {
        case QNetworkReply::NoError:
            break;
        case QNetworkReply::OperationCanceledError:
            emit q->cancelled(q);
            return;
        default:
            this->setError(Playlist::Error(m_reply->error()));
            this->setErrorString(m_reply->errorString());
            emit q->ready(q);
            return;
        }

        QString response(m_reply->readAll());
        QVariantMap result = QtJson::Json::parse(response).toMap();

        if (!result.isEmpty()) {
            this->loadPlaylist(result.value("response").toMap());
        }
        else {
            this->setError(Playlist::ParserError);
            this->setErrorString(QObject::tr("Cannot parse server response"));
            emit q->ready(q);
        }

        m_reply->deleteLater();
        m_reply = 0;
    }
}

}

