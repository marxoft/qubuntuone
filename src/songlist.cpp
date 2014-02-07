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
 * \file songlist.cpp
 */

#include "songlist.h"
#include "songlist_p.h"

namespace QtUbuntuOne {

SongList::SongList(QNetworkReply *reply, QObject *parent) :
    QObject(parent),
    d_ptr(new SongListPrivate(reply, this))
{
}

SongList::SongList(SongListPrivate &d, QObject *parent) :
    QObject(parent),
    d_ptr(&d)
{
}

SongList::~SongList() {}

/**
 * count
 */
int SongList::count() const {
    Q_D(const SongList);

    return d->count();
}

/**
 * songs
 */
QList<Song*> SongList::songs() const {
    Q_D(const SongList);

    return d->songs();
}

/**
 * error
 */
SongList::Error SongList::error() const {
    Q_D(const SongList);

    return d->error();
}

/**
 * errorString
 */
QString SongList::errorString() const {
    Q_D(const SongList);

    return d->errorString();
}

/**
 * cancel
 */
void SongList::cancel() {
    Q_D(SongList);

    d->cancel();
}

#include "moc_songlist.cpp"

}
