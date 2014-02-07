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

#include "album_p.h"
#include "json.h"

namespace QtUbuntuOne {

AlbumPrivate::AlbumPrivate(Album *parent) :
    q_ptr(parent),
    m_year(1970)
{
}

AlbumPrivate::AlbumPrivate(Album *otherAlbum, Album *parent) :
    q_ptr(parent),
    m_id(otherAlbum->id()),
    m_title(otherAlbum->title()),
    m_artist(otherAlbum->artist()),
    m_artistId(otherAlbum->artistId()),
    m_url(otherAlbum->url()),
    m_artworkUrl(otherAlbum->artworkUrl()),
    m_year(otherAlbum->year()),
    m_date(otherAlbum->date())
{
    Q_Q(Album);

    emit q->ready(q);
}

AlbumPrivate::~AlbumPrivate() {}

void AlbumPrivate::loadAlbum(Album *otherAlbum) {
    Q_Q(Album);

    this->setId(otherAlbum->id());
    this->setTitle(otherAlbum->title());
    this->setArtist(otherAlbum->artist());
    this->setArtistId(otherAlbum->artistId());
    this->setUrl(otherAlbum->url());
    this->setArtworkUrl(otherAlbum->artworkUrl());
    this->setYear(otherAlbum->year());
    this->setDate(otherAlbum->date());

    emit q->ready(q);
}

void AlbumPrivate::loadAlbum(const QVariantMap &album) {
    Q_Q(Album);

    this->setId(album.value("id").toString());
    this->setTitle(album.value("title").toString());
    this->setArtist(album.value("artist").toString());
    this->setArtistId(album.value("artist_id").toString());
    this->setUrl(album.value("album_url").toUrl());
    this->setArtworkUrl(album.value("album_art_url").toUrl());
    this->setYear(album.value("year").toInt());
    this->setDate(QDateTime::fromTime_t(album.value("parsed_date").toLongLong()));

    emit q->ready(q);
}

QString AlbumPrivate::id() const {
    return m_id;
}

void AlbumPrivate::setId(const QString &id) {
    m_id = id;
}

QString AlbumPrivate::title() const {
    return m_title;
}

void AlbumPrivate::setTitle(const QString &title) {
    m_title = title;
}

QString AlbumPrivate::artist() const {
    return m_artist;
}

void AlbumPrivate::setArtist(const QString &artist) {
    m_artist = artist;
}

QString AlbumPrivate::artistId() const {
    return m_artistId;
}

void AlbumPrivate::setArtistId(const QString &id) {
    m_artistId = id;
}

QUrl AlbumPrivate::url() const {
    return m_url;
}

void AlbumPrivate::setUrl(const QUrl &url) {
    m_url = url;
}

QUrl AlbumPrivate::artworkUrl() const {
    return m_artworkUrl;
}

void AlbumPrivate::setArtworkUrl(const QUrl &url) {
    m_artworkUrl = url;
}

int AlbumPrivate::year() const {
    return m_year;
}

void AlbumPrivate::setYear(int year) {
    m_year = year;
}

QDateTime AlbumPrivate::date() const {
    return m_date;
}

void AlbumPrivate::setDate(const QDateTime &date) {
    m_date = date;
}

}

