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

/**
 * \file song.h
 */

#ifndef SONG_H
#define SONG_H

#include "qubuntuone_global.h"
#include <QObject>
#include <QUrl>
#include <QVariantMap>

namespace QtUbuntuOne {

class SongPrivate;

/**
 * \class Song
 * \brief Contains the metadata of an UbuntuOne music song.
 *
 * Song contains the metadata of an UbuntuOne music song.
 * The metadata is read-only.
 */
class QUBUNTUONESHARED_EXPORT Song : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString id
               READ id
               NOTIFY ready)
    Q_PROPERTY(QString title
               READ title
               NOTIFY ready)
    Q_PROPERTY(QString artist
               READ artist
               NOTIFY ready)
    Q_PROPERTY(QString artistId
               READ artistId
               NOTIFY ready)
    Q_PROPERTY(QString albumTitle
               READ albumTitle
               NOTIFY ready)
    Q_PROPERTY(QString albumArtist
               READ albumArtist
               NOTIFY ready)
    Q_PROPERTY(QString albumId
               READ albumId
               NOTIFY ready)
    Q_PROPERTY(QString genre
               READ genre
               NOTIFY ready)
    Q_PROPERTY(QString filePath
               READ filePath
               NOTIFY ready)
    Q_PROPERTY(QString fileSuffix
               READ fileSuffix
               NOTIFY ready)
    Q_PROPERTY(QString mimeType
               READ mimeType
               NOTIFY ready)
    Q_PROPERTY(QUrl url
               READ url
               NOTIFY ready)
    Q_PROPERTY(QUrl artworkUrl
               READ artworkUrl
               NOTIFY ready)
    Q_PROPERTY(QUrl streamUrl
               READ streamUrl
               NOTIFY ready)
    Q_PROPERTY(int year
               READ year
               NOTIFY ready)
    Q_PROPERTY(int trackNumber
               READ trackNumber
               NOTIFY ready)
    Q_PROPERTY(int discNumber
               READ discNumber
               NOTIFY ready)
    Q_PROPERTY(int bitRate
               READ bitRate
               NOTIFY ready)
    Q_PROPERTY(qint64 duration
               READ duration
               NOTIFY ready)
    Q_PROPERTY(qint64 size
               READ size
               NOTIFY ready)

    friend class SongListPrivate;

public:
    explicit Song(QObject *parent = 0);
    explicit Song(Song *otherSong, QObject *parent = 0);
    ~Song();

    /**
     * Loads metadata from another instance of Song.
     *
     * \param Song*
     */
    Q_INVOKABLE void loadSong(Song *otherSong);

    /**
     * Returns the unique id of the Song.
     *
     * \return QString
     */
    QString id() const;

    /**
     * Returns the title of the Song.
     *
     * \return QString
     */
    QString title() const;

    /**
     * Returns the artist of the Song.
     *
     * \return QString
     */
    QString artist() const;

    /**
     * Returns the unique id of the artist of the Song.
     *
     * \return QString
     */
    QString artistId() const;

    /**
     * Returns the album title of the Song.
     *
     * \return QString
     */
    QString albumTitle() const;

    /**
     * Returns the album artist of the Song.
     *
     * \return QString
     */
    QString albumArtist() const;

    /**
     * Returns the unique id of the album of the Song.
     *
     * \return QString
     */
    QString albumId() const;

    /**
     * Returns the genre of the Song.
     *
     * \return QString
     */
    QString genre() const;

    /**
     * Returns the file path of the Song.
     *
     * \return QString
     */
    QString filePath() const;

    /**
     * Returns the file suffix of the Song.
     *
     * \return QString
     */
    QString fileSuffix() const;

    /**
     * Returns the mime type of the Song.
     *
     * \return QString
     */
    QString mimeType() const;

    /**
     * Returns the unique URL of the Song.
     *
     * \return QUrl
     */
    QUrl url() const;

    /**
     * Returns the artwork URL of the Song.
     *
     * \return QUrl
     */
    QUrl artworkUrl() const;

    /**
     * Returns the stream URL of the Song.
     *
     * \return QUrl
     */
    QUrl streamUrl() const;

    /**
     * Returns the year of the Song.
     *
     * \return int
     */
    int year() const;

    /**
     * Returns the track number of the Song.
     *
     * \return int
     */
    int trackNumber() const;

    /**
     * Returns the disc number of the Song.
     *
     * \return int
     */
    int discNumber() const;

    /**
     * Returns the bitrate of the Song.
     *
     * \return int
     */
    int bitRate() const;

    /**
     * Returns the duration of the Song in seconds.
     *
     * \return qint64
     */
    qint64 duration() const;

    /**
     * Returns the file size of the Song.
     *
     * \return qint64
     */
    qint64 size() const;

signals:
    /**
     * Emitted when new artist metadata has been loaded.
     *
     * \param song
     */
    void ready(Song *song);

private:
    explicit Song(SongPrivate &d, QObject *parent = 0);

    QScopedPointer<SongPrivate> d_ptr;

    Q_DECLARE_PRIVATE(Song)
};

}

#endif // SONG_H
