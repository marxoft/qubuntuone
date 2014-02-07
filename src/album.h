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
 * \file album.h
 */

#ifndef ALBUM_H
#define ALBUM_H

#include "qubuntuone_global.h"
#include <QObject>
#include <QDateTime>
#include <QUrl>
#include <QVariantMap>

namespace QtUbuntuOne {

class AlbumPrivate;

/**
 * \class Album
 * \brief Contains the metadata of an UbuntuOne music album.
 *
 * Album contains the metadata of an UbuntuOne music album.
 * The metadata is read-only.
 */
class QUBUNTUONESHARED_EXPORT Album : public QObject
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
    Q_PROPERTY(QUrl url
               READ url
               NOTIFY ready)
    Q_PROPERTY(QUrl artworkUrl
               READ artworkUrl
               NOTIFY ready)
    Q_PROPERTY(int year
               READ year
               NOTIFY ready)
    Q_PROPERTY(QDateTime date
               READ date
               NOTIFY ready)

    friend class AlbumListPrivate;

public:
    explicit Album(QObject *parent = 0);
    explicit Album(Album *otherAlbum, QObject *parent = 0);
    ~Album();

    /**
     * Loads metadata from another instance of Album.
     *
     * \param Album*
     */
    Q_INVOKABLE void loadAlbum(Album *otherAlbum);

    /**
     * Returns the unique id of the Album.
     *
     * \return QString
     */
    QString id() const;

    /**
     * Returns the title of the Album.
     *
     * \return QString
     */
    QString title() const;

    /**
     * Returns the artist of the Album.
     *
     * \return QString
     */
    QString artist() const;

    /**
     * Returns the unique id of the Album artist.
     *
     * \return QString
     */
    QString artistId() const;

    /**
     * Returns the unique URL of the Album.
     *
     * \return QUrl
     */
    QUrl url() const;

    /**
     * Returns the artwork URL of the Album.
     *
     * \return QUrl
     */
    QUrl artworkUrl() const;

    /**
     * Returns the year of the Album.
     *
     * \return int
     */
    int year() const;

    /**
     * Returns the date of the Album.
     *
     * \return QDateTime
     */
    QDateTime date() const;

signals:
    /**
     * Emitted when new album metadata has been loaded.
     *
     * \param album
     */
    void ready(Album *album);

private:
    explicit Album(AlbumPrivate &d, QObject *parent = 0);

    QScopedPointer<AlbumPrivate> d_ptr;

    Q_DECLARE_PRIVATE(Album)
};

}

#endif // ALBUM_H
