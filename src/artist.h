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
 * \file artist.h
 */

#ifndef ARTIST_H
#define ARTIST_H

#include "qubuntuone_global.h"
#include <QObject>
#include <QUrl>
#include <QVariantMap>

namespace QtUbuntuOne {

class ArtistPrivate;

/**
 * \class Artist
 * \brief Contains the metadata of an UbuntuOne music artist.
 *
 * Artist contains the metadata of an UbuntuOne music artist.
 * The metadata is read-only.
 */
class QUBUNTUONESHARED_EXPORT Artist : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString id
               READ id
               NOTIFY ready)
    Q_PROPERTY(QString name
               READ name
               NOTIFY ready)
    Q_PROPERTY(QUrl url
               READ url
               NOTIFY ready)
    Q_PROPERTY(QUrl artworkUrl
               READ artworkUrl
               NOTIFY ready)
    Q_PROPERTY(int songCount
               READ songCount
               NOTIFY ready)
    Q_PROPERTY(int albumCount
               READ albumCount
               NOTIFY ready)
    Q_PROPERTY(QStringList albumIds
               READ albumIds
               NOTIFY ready)

    friend class ArtistListPrivate;

public:
    explicit Artist(QObject *parent = 0);
    explicit Artist(Artist *otherArtist, QObject *parent = 0);
    ~Artist();

    /**
     * Loads metadata from another instance of Artist.
     *
     * \param Artist*
     */
    Q_INVOKABLE void loadArtist(Artist *otherArtist);

    /**
     * Returns the unique id of the Artist.
     *
     * \return QString
     */
    QString id() const;

    /**
     * Returns the name of the Artist.
     *
     * \return QString
     */
    QString name() const;

    /**
     * Returns the unique URL of the Artist.
     *
     * \return QUrl
     */
    QUrl url() const;

    /**
     * Returns the artwork URL of the Artist.
     *
     * \return QUrl
     */
    QUrl artworkUrl() const;

    /**
     * Returns the song count of the Artist.
     *
     * \return int
     */
    int songCount() const;

    /**
     * Returns the album count of the Artist.
     *
     * \return int
     */
    int albumCount() const;

    /**
     * Returns a list of the unique albums ids of the Artist.
     *
     * \return QStringList
     */
    QStringList albumIds() const;

signals:
    /**
     * Emitted when new artist metadata has been loaded.
     *
     * \param artist
     */
    void ready(Artist *artist);

private:
    explicit Artist(ArtistPrivate &d, QObject *parent = 0);

    QScopedPointer<ArtistPrivate> d_ptr;

    Q_DECLARE_PRIVATE(Artist)
};

}

#endif // ARTIST_H
