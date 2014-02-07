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

#include "artwork_p.h"
#include <QImageReader>

namespace QtUbuntuOne {

ArtworkPrivate::ArtworkPrivate(QNetworkReply *reply, const QSize &size, Artwork *parent) :
    q_ptr(parent),
    m_reply(reply),
    m_url(!reply ? QUrl() : reply->request().url()),
    m_size(size),
    m_error(Artwork::NoError)
{
    Q_Q(Artwork);

    if (m_reply) {
        q->connect(m_reply, SIGNAL(finished()), q, SLOT(_q_onReplyFinished()));
    }
}

ArtworkPrivate::~ArtworkPrivate() {
    if (m_reply) {
        delete m_reply;
        m_reply = 0;
    }
}

QUrl ArtworkPrivate::url() const {
    return m_url;
}

void ArtworkPrivate::setUrl(const QUrl &url) {
    m_url = url;
}

QSize ArtworkPrivate::size() const {
    return m_size;
}

void ArtworkPrivate::setSize(const QSize &size) {
    m_size = size;
}

QImage ArtworkPrivate::image() const {
    return m_image;
}

void ArtworkPrivate::setImage(const QImage &image) {
    m_image = image;
}

Artwork::Error ArtworkPrivate::error() const {
    return m_error;
}

void ArtworkPrivate::setError(Artwork::Error error) {
    m_error = error;
}

QString ArtworkPrivate::errorString() const {
    return m_errorString;
}

void ArtworkPrivate::setErrorString(const QString &errorString) {
    m_errorString = errorString;
}

void ArtworkPrivate::cancel() {
    if (m_reply) {
        m_reply->abort();
    }
}

void ArtworkPrivate::_q_onReplyFinished() {
    Q_Q(Artwork);

    if (m_reply) {
        switch (m_reply->error()) {
        case QNetworkReply::NoError:
            break;
        case QNetworkReply::OperationCanceledError:
            emit q->cancelled(q);
            return;
        default:
            this->setError(Artwork::Error(m_reply->error()));
            this->setErrorString(m_reply->errorString());
            emit q->ready(q);
            return;
        }

        QImageReader reader(m_reply);

        if (!this->size().isNull()) {
            reader.setScaledSize(this->size());
        }

        if (reader.canRead()) {
            this->setImage(reader.read());
        }
        else {
            this->setError(Artwork::ParserError);
            this->setErrorString(QObject::tr("Cannot load image"));
        }

        emit q->ready(q);

        m_reply->deleteLater();
        m_reply = 0;
    }
}

}
