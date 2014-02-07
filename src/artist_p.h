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

#ifndef ARTIST_P_H
#define ARTIST_P_H

#include "artist.h"
#include <QStringList>

namespace QtUbuntuOne {

class ArtistPrivate
{

public:
    ArtistPrivate(Artist *parent);
    ArtistPrivate(Artist *otherArtist, Artist *parent);
    virtual ~ArtistPrivate();

    void loadArtist(Artist *otherArtist);
    void loadArtist(const QVariantMap &artist);

    QString id() const;

    QString name() const;

    QUrl url() const;

    QUrl artworkUrl() const;

    int songCount() const;

    int albumCount() const;

    QStringList albumIds() const;

private:
    void setId(const QString &id);

    void setName(const QString &name);

    void setUrl(const QUrl &url);

    void setArtworkUrl(const QUrl &url);

    void setSongCount(int count);

    void setAlbumCount(int count);

    void setAlbumIds(const QStringList &ids);

    Artist *q_ptr;

    QString m_id;

    QString m_name;

    QUrl m_url;

    QUrl m_artworkUrl;

    int m_songCount;

    QStringList m_albumIds;

    int m_albumCount;

    Q_DECLARE_PUBLIC(Artist)
};

}

#endif // ARTIST_P_H
