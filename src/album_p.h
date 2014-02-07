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

#ifndef ALBUM_P_H
#define ALBUM_P_H

#include "album.h"

namespace QtUbuntuOne {

class AlbumPrivate
{

public:
    AlbumPrivate(Album *parent);
    AlbumPrivate(Album *otherAlbum, Album *parent);
    virtual ~AlbumPrivate();

    void loadAlbum(Album *otherAlbum);
    void loadAlbum(const QVariantMap &album);

    QString id() const;

    QString title() const;

    QString artist() const;

    QString artistId() const;

    QUrl url() const;

    QUrl artworkUrl() const;

    int year() const;

    QDateTime date() const;

private:
    void setId(const QString &id);

    void setTitle(const QString &title);

    void setArtist(const QString &artist);

    void setArtistId(const QString &id);

    void setUrl(const QUrl &url);

    void setArtworkUrl(const QUrl &url);

    void setYear(int year);

    void setDate(const QDateTime &date);

    Album *q_ptr;

    QString m_id;

    QString m_title;

    QString m_artist;

    QString m_artistId;

    QUrl m_url;

    QUrl m_artworkUrl;

    int m_year;

    QDateTime m_date;

    Q_DECLARE_PUBLIC(Album)
};

}

#endif // ALBUM_P_H
