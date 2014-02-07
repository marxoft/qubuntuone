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
 * playlist.cpp
 */

#include "playlist.h"
#include "playlist_p.h"

namespace QtUbuntuOne {

Playlist::Playlist(QObject *parent) :
    QObject(parent),
    d_ptr(new PlaylistPrivate(this))
{
}

Playlist::Playlist(Playlist *otherPlaylist, QObject *parent) :
    QObject(parent),
    d_ptr(new PlaylistPrivate(otherPlaylist, this))
{
}

Playlist::Playlist(QNetworkReply *reply, QObject *parent) :
    QObject(parent),
    d_ptr(new PlaylistPrivate(reply, this))
{
}

Playlist::Playlist(PlaylistPrivate &d, QObject *parent) :
    QObject(parent),
    d_ptr(&d)
{
}

Playlist::~Playlist() {}

/**
 * loadPlaylist
 */
void Playlist::loadPlaylist(Playlist *otherPlaylist) {
    Q_D(Playlist);

    d->loadPlaylist(otherPlaylist);
}

/**
 * id
 */
QString Playlist::id() const {
    Q_D(const Playlist);

    return d->id();
}

/**
 * name
 */
QString Playlist::name() const {
    Q_D(const Playlist);

    return d->name();
}

/**
 * url
 */
QUrl Playlist::url() const {
    Q_D(const Playlist);

    return d->url();
}

/**
 * songCount
 */
int Playlist::songCount() const {
    Q_D(const Playlist);

    return d->songCount();
}

/**
 * error
 */
Playlist::Error Playlist::error() const {
    Q_D(const Playlist);

    return d->error();
}

/**
 * errorString
 */
QString Playlist::errorString() const {
    Q_D(const Playlist);

    return d->errorString();
}

/**
 * cancel
 */
void Playlist::cancel() {
    Q_D(Playlist);

    d->cancel();
}

#include "moc_playlist.cpp"

}
