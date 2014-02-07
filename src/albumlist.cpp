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
 * \file albumlist.cpp
 */

#include "albumlist.h"
#include "albumlist_p.h"

namespace QtUbuntuOne {

AlbumList::AlbumList(QNetworkReply *reply, QObject *parent) :
    QObject(parent),
    d_ptr(new AlbumListPrivate(reply, this))
{
}

AlbumList::AlbumList(AlbumListPrivate &d, QObject *parent) :
    QObject(parent),
    d_ptr(&d)
{
}

AlbumList::~AlbumList() {}

/**
 * count
 */
int AlbumList::count() const {
    Q_D(const AlbumList);

    return d->count();
}

/**
 * albums
 */
QList<Album*> AlbumList::albums() const {
    Q_D(const AlbumList);

    return d->albums();
}

/**
 * error
 */
AlbumList::Error AlbumList::error() const {
    Q_D(const AlbumList);

    return d->error();
}

/**
 * errorString
 */
QString AlbumList::errorString() const {
    Q_D(const AlbumList);

    return d->errorString();
}

/**
 * cancel
 */
void AlbumList::cancel() {
    Q_D(AlbumList);

    d->cancel();
}

#include "moc_albumlist.cpp"

}
