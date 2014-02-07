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

#include "artistlist_p.h"
#include "artist_p.h"
#include "json.h"

namespace QtUbuntuOne {

ArtistListPrivate::ArtistListPrivate(QNetworkReply *reply, ArtistList *parent) :
    q_ptr(parent),
    m_reply(reply),
    m_error(ArtistList::NoError)
{
    Q_Q(ArtistList);

    if (m_reply) {
        q->connect(m_reply, SIGNAL(finished()), q, SLOT(_q_onReplyFinished()));
    }
}

ArtistListPrivate::~ArtistListPrivate() {
    if (m_reply) {
        delete m_reply;
        m_reply = 0;
    }
}

int ArtistListPrivate::count() const {
    return m_artists.size();
}

QList<Artist*> ArtistListPrivate::artists() const {
    return m_artists;
}

ArtistList::Error ArtistListPrivate::error() const {
    return m_error;
}

void ArtistListPrivate::setError(ArtistList::Error error) {
    m_error = error;
}

QString ArtistListPrivate::errorString() const {
    return m_errorString;
}

void ArtistListPrivate::setErrorString(const QString &errorstring) {
    m_errorString = errorstring;
}

void ArtistListPrivate::loadArtists(const QVariantList &artists) {
    Q_Q(ArtistList);

    foreach (QVariant artist, artists) {
        Artist *a = new Artist;
        a->d_func()->loadArtist(artist.toMap());
        m_artists.append(a);
    }

    emit q->ready(q);
}

void ArtistListPrivate::cancel() {
    if (m_reply) {
        m_reply->abort();
    }
}

void ArtistListPrivate::_q_onReplyFinished() {
    Q_Q(ArtistList);

    if (m_reply) {
        switch (m_reply->error()) {
        case QNetworkReply::NoError:
            break;
        case QNetworkReply::OperationCanceledError:
            emit q->cancelled(q);
            return;
        default:
            this->setError(ArtistList::Error(m_reply->error()));
            this->setErrorString(m_reply->errorString());
            emit q->ready(q);
            return;
        }

        QString response(m_reply->readAll());
        QVariant result = QtJson::Json::parse(response);

        switch (result.type()) {
        case QVariant::Map:
            this->loadArtists(result.toMap().value("response").toMap().value("artists").toList());
            break;
        case QVariant::List:
            this->loadArtists(result.toList());
            break;
        default:
            this->setError(ArtistList::ParserError);
            this->setErrorString(QObject::tr("Cannot parse server response"));
            emit q->ready(q);
            break;
        }

        m_reply->deleteLater();
        m_reply = 0;
    }
}

}
