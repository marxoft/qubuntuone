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
 * album.cpp
 */

#include "album.h"
#include "album_p.h"

namespace QtUbuntuOne {

Album::Album(QObject *parent) :
    QObject(parent),
    d_ptr(new AlbumPrivate(this))
{
}

Album::Album(Album *otherAlbum, QObject *parent) :
    QObject(parent),
    d_ptr(new AlbumPrivate(otherAlbum, this))
{
}

Album::Album(AlbumPrivate &d, QObject *parent) :
    QObject(parent),
    d_ptr(&d)
{
}

Album::~Album() {}

/**
 * loadAlbum
 */
void Album::loadAlbum(Album *otherAlbum) {
    Q_D(Album);

    d->loadAlbum(otherAlbum);
}

/**
 * id
 */
QString Album::id() const {
    Q_D(const Album);

    return d->id();
}

/**
 * title
 */
QString Album::title() const {
    Q_D(const Album);

    return d->title();
}

/**
 * artist
 */
QString Album::artist() const {
    Q_D(const Album);

    return d->artist();
}

/**
 * artistId
 */
QString Album::artistId() const {
    Q_D(const Album);

    return d->artistId();
}

/**
 * url
 */
QUrl Album::url() const {
    Q_D(const Album);

    return d->url();
}

/**
 * artworkUrl
 */
QUrl Album::artworkUrl() const {
    Q_D(const Album);

    return d->artworkUrl();
}

/**
 * year
 */
int Album::year() const {
    Q_D(const Album);

    return d->year();
}

/**
 * date
 */
QDateTime Album::date() const {
    Q_D(const Album);

    return d->date();
}

#include "moc_album.cpp"

}
