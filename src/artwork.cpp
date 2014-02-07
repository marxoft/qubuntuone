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
 * \file artwork.cpp
 */

#include "artwork.h"
#include "artwork_p.h"

namespace QtUbuntuOne {

Artwork::Artwork(QNetworkReply *reply, const QSize &size, QObject *parent) :
    QObject(parent),
    d_ptr(new ArtworkPrivate(reply, size, this))
{
}

Artwork::Artwork(ArtworkPrivate &d, QObject *parent) :
    QObject(parent),
    d_ptr(&d)
{
}

Artwork::~Artwork() {}

/**
 * url
 */
QUrl Artwork::url() const {
    Q_D(const Artwork);

    return d->url();
}

/**
 * size
 */
QSize Artwork::size() const {
    Q_D(const Artwork);

    return d->size();
}

/**
 * image
 */
QImage Artwork::image() const {
    Q_D(const Artwork);

    return d->image();
}

/**
 * error
 */
Artwork::Error Artwork::error() const {
    Q_D(const Artwork);

    return d->error();
}

/**
 * errorString
 */
QString Artwork::errorString() const {
    Q_D(const Artwork);

    return d->errorString();
}

/**
 * cancel
 */
void Artwork::cancel() {
    Q_D(Artwork);

    d->cancel();
}

#include "moc_artwork.cpp"

}
