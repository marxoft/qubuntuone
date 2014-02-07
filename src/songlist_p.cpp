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

#include "songlist_p.h"
#include "song_p.h"
#include "json.h"

namespace QtUbuntuOne {

SongListPrivate::SongListPrivate(QNetworkReply *reply, SongList *parent) :
    q_ptr(parent),
    m_reply(reply),
    m_error(SongList::NoError)
{
    Q_Q(SongList);

    if (m_reply) {
        q->connect(m_reply, SIGNAL(finished()), q, SLOT(_q_onReplyFinished()));
    }
}

SongListPrivate::~SongListPrivate() {
    if (m_reply) {
        delete m_reply;
        m_reply = 0;
    }
}

int SongListPrivate::count() const {
    return m_songs.size();
}

QList<Song*> SongListPrivate::songs() const {
    return m_songs;
}

SongList::Error SongListPrivate::error() const {
    return m_error;
}

void SongListPrivate::setError(SongList::Error error) {
    m_error = error;
}

QString SongListPrivate::errorString() const {
    return m_errorString;
}

void SongListPrivate::setErrorString(const QString &errorstring) {
    m_errorString = errorstring;
}

void SongListPrivate::loadSongs(const QVariantList &songs) {
    Q_Q(SongList);

    foreach (QVariant song, songs) {
        Song *s = new Song;
        s->d_func()->loadSong(song.toMap());
        m_songs.append(s);
    }

    emit q->ready(q);
}

void SongListPrivate::cancel() {
    if (m_reply) {
        m_reply->abort();
    }
}

void SongListPrivate::_q_onReplyFinished() {
    Q_Q(SongList);

    if (m_reply) {
        switch (m_reply->error()) {
        case QNetworkReply::NoError:
            break;
        case QNetworkReply::OperationCanceledError:
            emit q->cancelled(q);
            return;
        default:
            this->setError(SongList::Error(m_reply->error()));
            this->setErrorString(m_reply->errorString());
            emit q->ready(q);
            return;
        }

        QString response(m_reply->readAll());
        QVariant result = QtJson::Json::parse(response);

        switch (result.type()) {
        case QVariant::Map:
            this->loadSongs(result.toMap().value("response").toMap().value("songs").toList());
            break;
        case QVariant::List:
            this->loadSongs(result.toList());
            break;
        default:
            this->setError(SongList::ParserError);
            this->setErrorString(QObject::tr("Cannot parse server response"));
            emit q->ready(q);
            break;
        }

        m_reply->deleteLater();
        m_reply = 0;
    }
}

}

