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
 * artist.cpp
 */

#include "artist.h"
#include "artist_p.h"

namespace QtUbuntuOne {

Artist::Artist(QObject *parent) :
    QObject(parent),
    d_ptr(new ArtistPrivate(this))
{
}

Artist::Artist(Artist *otherArtist, QObject *parent) :
    QObject(parent),
    d_ptr(new ArtistPrivate(otherArtist, this))
{
}

Artist::Artist(ArtistPrivate &d, QObject *parent) :
    QObject(parent),
    d_ptr(&d)
{
}

Artist::~Artist() {}

/**
 * loadArtist
 */
void Artist::loadArtist(Artist *otherArtist) {
    Q_D(Artist);

    d->loadArtist(otherArtist);
}

/**
 * id
 */
QString Artist::id() const {
    Q_D(const Artist);

    return d->id();
}

/**
 * name
 */
QString Artist::name() const {
    Q_D(const Artist);

    return d->name();
}

/**
 * url
 */
QUrl Artist::url() const {
    Q_D(const Artist);

    return d->url();
}

/**
 * artworkUrl
 */
QUrl Artist::artworkUrl() const {
    Q_D(const Artist);

    return d->artworkUrl();
}

/**
 * songCount
 */
int Artist::songCount() const {
    Q_D(const Artist);

    return d->songCount();
}

/**
 * albumCount
 */
int Artist::albumCount() const {
    Q_D(const Artist);

    return d->albumCount();
}

/**
 * albumIds
 */
QStringList Artist::albumIds() const {
    Q_D(const Artist);

    return d->albumIds();
}

#include "moc_artist.cpp"

}
