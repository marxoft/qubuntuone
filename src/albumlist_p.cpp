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

#include "albumlist_p.h"
#include "album_p.h"
#include "json.h"

namespace QtUbuntuOne {

AlbumListPrivate::AlbumListPrivate(QNetworkReply *reply, AlbumList *parent) :
    q_ptr(parent),
    m_reply(reply),
    m_error(AlbumList::NoError)
{
    Q_Q(AlbumList);

    if (m_reply) {
        q->connect(m_reply, SIGNAL(finished()), q, SLOT(_q_onReplyFinished()));
    }
}

AlbumListPrivate::~AlbumListPrivate() {
    if (m_reply) {
        delete m_reply;
        m_reply = 0;
    }
}

int AlbumListPrivate::count() const {
    return m_albums.size();
}

QList<Album*> AlbumListPrivate::albums() const {
    return m_albums;
}

AlbumList::Error AlbumListPrivate::error() const {
    return m_error;
}

void AlbumListPrivate::setError(AlbumList::Error error) {
    m_error = error;
}

QString AlbumListPrivate::errorString() const {
    return m_errorString;
}

void AlbumListPrivate::setErrorString(const QString &errorstring) {
    m_errorString = errorstring;
}

void AlbumListPrivate::loadAlbums(const QVariantList &albums) {
    Q_Q(AlbumList);

    foreach (QVariant album, albums) {
        Album *a = new Album;
        a->d_func()->loadAlbum(album.toMap());
        m_albums.append(a);
    }

    emit q->ready(q);
}

void AlbumListPrivate::cancel() {
    if (m_reply) {
        m_reply->abort();
    }
}

void AlbumListPrivate::_q_onReplyFinished() {
    Q_Q(AlbumList);

    if (m_reply) {
        switch (m_reply->error()) {
        case QNetworkReply::NoError:
            break;
        case QNetworkReply::OperationCanceledError:
            emit q->cancelled(q);
            return;
        default:
            this->setError(AlbumList::Error(m_reply->error()));
            this->setErrorString(m_reply->errorString());
            emit q->ready(q);
            return;
        }

        QString response(m_reply->readAll());
        QVariant result = QtJson::Json::parse(response);

        switch (result.type()) {
        case QVariant::Map:
            this->loadAlbums(result.toMap().value("response").toMap().value("albums").toList());
            break;
        case QVariant::List:
            this->loadAlbums(result.toList());
            break;
        default:
            this->setError(AlbumList::ParserError);
            this->setErrorString(QObject::tr("Cannot parse server response"));
            emit q->ready(q);
            break;
        }

        m_reply->deleteLater();
        m_reply = 0;
    }
}

}

