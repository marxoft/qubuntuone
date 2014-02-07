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

#ifndef ARTWORK_P_H
#define ARTWORK_P_H

#include "artwork.h"

namespace QtUbuntuOne {

class ArtworkPrivate
{

public:
    ArtworkPrivate(QNetworkReply *reply, const QSize &size, Artwork *parent);
    virtual ~ArtworkPrivate();

    QUrl url() const;

    QSize size() const;

    QImage image() const;

    Artwork::Error error() const;
    QString errorString() const;

    void cancel();

private:
    void setUrl(const QUrl &url);

    void setSize(const QSize &size);

    void setImage(const QImage &image);

    void setError(Artwork::Error error);
    void setErrorString(const QString &errorString);

    void _q_onReplyFinished();

    Artwork *q_ptr;

    QNetworkReply *m_reply;

    QUrl m_url;

    QSize m_size;

    QImage m_image;

    Artwork::Error m_error;
    QString m_errorString;

    Q_DECLARE_PUBLIC(Artwork)
};

}

#endif // ARTWORK_P_H
