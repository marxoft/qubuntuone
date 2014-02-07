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
 * \file playlistlist.cpp
 */

#include "playlistlist.h"
#include "playlistlist_p.h"

namespace QtUbuntuOne {

PlaylistList::PlaylistList(QNetworkReply *reply, QObject *parent) :
    QObject(parent),
    d_ptr(new PlaylistListPrivate(reply, this))
{
}

PlaylistList::PlaylistList(PlaylistListPrivate &d, QObject *parent) :
    QObject(parent),
    d_ptr(&d)
{
}

PlaylistList::~PlaylistList() {}

/**
 * count
 */
int PlaylistList::count() const {
    Q_D(const PlaylistList);

    return d->count();
}

/**
 * playlists
 */
QList<Playlist*> PlaylistList::playlists() const {
    Q_D(const PlaylistList);

    return d->playlists();
}

/**
 * error
 */
PlaylistList::Error PlaylistList::error() const {
    Q_D(const PlaylistList);

    return d->error();
}

/**
 * errorString
 */
QString PlaylistList::errorString() const {
    Q_D(const PlaylistList);

    return d->errorString();
}

/**
 * cancel
 */
void PlaylistList::cancel() {
    Q_D(PlaylistList);

    d->cancel();
}

#include "moc_playlistlist.cpp"

}
