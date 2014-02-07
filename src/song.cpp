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
 * song
 */

#include "song.h"
#include "song_p.h"

namespace QtUbuntuOne {

Song::Song(QObject *parent) :
    QObject(parent),
    d_ptr(new SongPrivate(this))
{
}

Song::Song(Song *otherSong, QObject *parent) :
    QObject(parent),
    d_ptr(new SongPrivate(otherSong, this))
{
}

Song::Song(SongPrivate &d, QObject *parent) :
    QObject(parent),
    d_ptr(&d)
{
}

Song::~Song() {}

/**
 * loadSong
 */
void Song::loadSong(Song *otherSong) {
    Q_D(Song);

    d->loadSong(otherSong);
}

/**
 * id
 */
QString Song::id() const {
    Q_D(const Song);

    return d->id();
}

/**
 * title
 */
QString Song::title() const {
    Q_D(const Song);

    return d->title();
}

/**
 * artist
 */
QString Song::artist() const {
    Q_D(const Song);

    return d->artist();
}

/**
 * artistId
 */
QString Song::artistId() const {
    Q_D(const Song);

    return d->artistId();
}

/**
 * albumTitle
 */
QString Song::albumTitle() const {
    Q_D(const Song);

    return d->albumTitle();
}

/**
 * albumArtist
 */
QString Song::albumArtist() const {
    Q_D(const Song);

    return d->albumArtist();
}

/**
 * albumId
 */
QString Song::albumId() const {
    Q_D(const Song);

    return d->albumId();
}

/**
 * genre
 */
QString Song::genre() const {
    Q_D(const Song);

    return d->genre();
}

/**
 * filePath
 */
QString Song::filePath() const {
    Q_D(const Song);

    return d->filePath();
}

/**
 * fileSuffix
 */
QString Song::fileSuffix() const {
    Q_D(const Song);

    return d->fileSuffix();
}

/**
 * mimeType
 */
QString Song::mimeType() const {
    Q_D(const Song);

    return d->mimeType();
}

/**
 * url
 */
QUrl Song::url() const {
    Q_D(const Song);

    return d->url();
}

/**
 * artworkUrl
 */
QUrl Song::artworkUrl() const {
    Q_D(const Song);

    return d->artworkUrl();
}

/**
 * streamUrl
 */
QUrl Song::streamUrl() const {
    Q_D(const Song);

    return d->streamUrl();
}

/**
 * year
 */
int Song::year() const {
    Q_D(const Song);

    return d->year();
}

/**
 * trackNumber
 */
int Song::trackNumber() const {
    Q_D(const Song);

    return d->trackNumber();
}

/**
 * discNumber
 */
int Song::discNumber() const {
    Q_D(const Song);

    return d->discNumber();
}

/**
 * bitRate
 */
int Song::bitRate() const {
    Q_D(const Song);

    return d->bitRate();
}

/**
 * duration
 */
qint64 Song::duration() const {
    Q_D(const Song);

    return d->duration();
}

/**
 * size
 */
qint64 Song::size() const {
    Q_D(const Song);

    return d->size();
}

#include "moc_song.cpp"

}
