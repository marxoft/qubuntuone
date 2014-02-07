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
 * \file artistlist.cpp
 */

#include "artistlist.h"
#include "artistlist_p.h"

namespace QtUbuntuOne {

ArtistList::ArtistList(QNetworkReply *reply, QObject *parent) :
    QObject(parent),
    d_ptr(new ArtistListPrivate(reply, this))
{
}

ArtistList::~ArtistList() {}

/**
 * count
 */
int ArtistList::count() const {
    Q_D(const ArtistList);

    return d->count();
}

/**
 * artists
 */
QList<Artist*> ArtistList::artists() const {
    Q_D(const ArtistList);

    return d->artists();
}

/**
 * error
 */
ArtistList::Error ArtistList::error() const {
    Q_D(const ArtistList);

    return d->error();
}

/**
 * errorString
 */
QString ArtistList::errorString() const {
    Q_D(const ArtistList);

    return d->errorString();
}

/**
 * cancel
 */
void ArtistList::cancel() {
    Q_D(ArtistList);

    d->cancel();
}

#include "moc_artistlist.cpp"

}
