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

#ifndef SONG_P_H
#define SONG_P_H

#include "song.h"

namespace QtUbuntuOne {

class SongPrivate
{

public:
    SongPrivate(Song *parent);
    SongPrivate(Song *otherSong, Song *parent);
    virtual ~SongPrivate();

    void loadSong(Song *otherSong);
    void loadSong(const QVariantMap &song);

    QString id() const;

    QString title() const;

    QString artist() const;

    QString artistId() const;

    QString albumTitle() const;

    QString albumArtist() const;

    QString albumId() const;

    QString genre() const;

    QString filePath() const;

    QString fileSuffix() const;

    QString mimeType() const;

    QUrl url() const;

    QUrl artworkUrl() const;

    QUrl streamUrl() const;

    int year() const;

    int trackNumber() const;

    int discNumber() const;

    int bitRate() const;

    qint64 duration() const;

    qint64 size() const;

private:
    void setId(const QString &id);

    void setTitle(const QString &title);

    void setArtist(const QString &artist);

    void setArtistId(const QString &id);

    void setAlbumTitle(const QString &title);

    void setAlbumArtist(const QString &artist);

    void setAlbumId(const QString &id);

    void setGenre(const QString &genre);

    void setFilePath(const QString &path);

    void setFileSuffix(const QString &suffix);

    void setMimeType(const QString &type);

    void setUrl(const QUrl &url);

    void setArtworkUrl(const QUrl &url);

    void setStreamUrl(const QUrl &url);

    void setYear(int year);

    void setTrackNumber(int number);

    void setDiscNumber(int number);

    void setBitRate(int rate);

    void setDuration(qint64 duration);

    void setSize(qint64 size);

    Song *q_ptr;

    QString m_id;

    QString m_title;

    QString m_artist;

    QString m_artistId;

    QString m_albumTitle;

    QString m_albumArtist;

    QString m_albumId;

    QString m_genre;

    QString m_filePath;

    QString m_fileSuffix;

    QString m_mimeType;

    QUrl m_url;

    QUrl m_artworkUrl;

    QUrl m_streamUrl;

    int m_year;

    int m_trackNumber;

    int m_discNumber;

    int m_bitRate;

    qint64 m_duration;

    qint64 m_size;

    Q_DECLARE_PUBLIC(Song)
};

}

#endif // SONG_P_H
