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

#include "artist_p.h"
#include "json.h"

namespace QtUbuntuOne {

ArtistPrivate::ArtistPrivate(Artist *parent) :
    q_ptr(parent),
    m_songCount(0),
    m_albumCount(0)
{
}

ArtistPrivate::ArtistPrivate(Artist *otherArtist, Artist *parent) :
    q_ptr(parent),
    m_id(otherArtist->id()),
    m_name(otherArtist->name()),
    m_url(otherArtist->url()),
    m_artworkUrl(otherArtist->artworkUrl()),
    m_songCount(otherArtist->songCount()),
    m_albumIds(otherArtist->albumIds()),
    m_albumCount(otherArtist->albumCount())
{
    Q_Q(Artist);

    emit q->ready(q);
}

ArtistPrivate::~ArtistPrivate() {}

void ArtistPrivate::loadArtist(Artist *otherArtist) {
    Q_Q(Artist);

    this->setId(otherArtist->id());
    this->setName(otherArtist->name());
    this->setUrl(otherArtist->url());
    this->setArtworkUrl(otherArtist->artworkUrl());
    this->setSongCount(otherArtist->songCount());
    this->setAlbumIds(otherArtist->albumIds());
    this->setAlbumCount(otherArtist->albumCount());

    emit q->ready(q);
}

void ArtistPrivate::loadArtist(const QVariantMap &artist) {
    Q_Q(Artist);

    this->setId(artist.value("id").toString());
    this->setName(artist.value("artist").toString());
    this->setUrl(artist.value("artist_url").toUrl());
    this->setArtworkUrl(artist.value("artist_art_url").toUrl());
    this->setSongCount(artist.value("song_count").toInt());
    this->setAlbumIds(artist.value("album_ids").toStringList());
    this->setAlbumCount(this->albumIds().size());

    emit q->ready(q);
}

QString ArtistPrivate::id() const {
    return m_id;
}

void ArtistPrivate::setId(const QString &id) {
    m_id = id;
}

QString ArtistPrivate::name() const {
    return m_name;
}

void ArtistPrivate::setName(const QString &name) {
    m_name = name;
}

QUrl ArtistPrivate::url() const {
    return m_url;
}

void ArtistPrivate::setUrl(const QUrl &url) {
    m_url = url;
}

QUrl ArtistPrivate::artworkUrl() const {
    return m_artworkUrl;
}

void ArtistPrivate::setArtworkUrl(const QUrl &url) {
    m_artworkUrl = url;
}

int ArtistPrivate::songCount() const {
    return m_songCount;
}

void ArtistPrivate::setSongCount(int count) {
    m_songCount = count;
}

int ArtistPrivate::albumCount() const {
    return m_albumCount;
}

void ArtistPrivate::setAlbumCount(int count) {
    m_albumCount = count;
}

QStringList ArtistPrivate::albumIds() const {
    return m_albumIds;
}

void ArtistPrivate::setAlbumIds(const QStringList &ids) {
    m_albumIds = ids;
}

}

