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

#include "song_p.h"
#include "json.h"

namespace QtUbuntuOne {

SongPrivate::SongPrivate(Song *parent) :
    q_ptr(parent),
    m_year(1970),
    m_trackNumber(1),
    m_discNumber(1),
    m_bitRate(0),
    m_duration(0),
    m_size(0)
{
}

SongPrivate::SongPrivate(Song *otherSong, Song *parent) :
    q_ptr(parent),
    m_id(otherSong->id()),
    m_title(otherSong->title()),
    m_artist(otherSong->artist()),
    m_artistId(otherSong->artistId()),
    m_albumTitle(otherSong->albumTitle()),
    m_albumArtist(otherSong->albumArtist()),
    m_albumId(otherSong->albumId()),
    m_genre(otherSong->genre()),
    m_filePath(otherSong->filePath()),
    m_fileSuffix(otherSong->fileSuffix()),
    m_mimeType(otherSong->mimeType()),
    m_url(otherSong->url()),
    m_artworkUrl(otherSong->artworkUrl()),
    m_streamUrl(otherSong->streamUrl()),
    m_year(otherSong->year()),
    m_trackNumber(otherSong->trackNumber()),
    m_discNumber(otherSong->discNumber()),
    m_bitRate(otherSong->bitRate()),
    m_duration(otherSong->duration()),
    m_size(otherSong->size())
{
    Q_Q(Song);

    emit q->ready(q);
}

SongPrivate::~SongPrivate() {}

void SongPrivate::loadSong(Song *otherSong) {
    Q_Q(Song);

    this->setId(otherSong->id());
    this->setTitle(otherSong->title());
    this->setArtist(otherSong->artist());
    this->setArtistId(otherSong->artistId());
    this->setAlbumTitle(otherSong->albumTitle());
    this->setAlbumArtist(otherSong->albumArtist());
    this->setAlbumId(otherSong->albumId());
    this->setGenre(otherSong->genre());
    this->setFilePath(otherSong->filePath());
    this->setFileSuffix(otherSong->fileSuffix());
    this->setMimeType(otherSong->mimeType());
    this->setUrl(otherSong->url());
    this->setArtworkUrl(otherSong->artworkUrl());
    this->setStreamUrl(otherSong->streamUrl());
    this->setYear(otherSong->year());
    this->setTrackNumber(otherSong->trackNumber());
    this->setDiscNumber(otherSong->discNumber());
    this->setBitRate(otherSong->bitRate());
    this->setDuration(otherSong->duration());
    this->setSize(otherSong->size());

    emit q->ready(q);
}

void SongPrivate::loadSong(const QVariantMap &song) {
    Q_Q(Song);

    this->setId(song.value("id").toString());
    this->setTitle(song.value("title").toString());
    this->setArtist(song.value("artist").toString());
    this->setArtistId(song.value("artist_id").toString());
    this->setAlbumTitle(song.value("album").toString());
    this->setAlbumArtist(song.value("album_artist").toString());
    this->setAlbumId(song.value("album_id").toString());
    this->setGenre(song.value("genre").toString());
    this->setFilePath(song.value("path").toString());
    this->setFileSuffix(song.value("suffix").toString());
    this->setMimeType(song.value("content_type").toString());
    this->setUrl(song.value("song_url").toUrl());
    this->setArtworkUrl(song.value("song_art_url").toUrl());
    this->setStreamUrl(song.value("song_stream_url").toUrl());
    this->setYear(song.value("year").toInt());
    this->setTrackNumber(song.value("track").toInt());
    this->setDiscNumber(song.value("disc_number").toInt());
    this->setBitRate(song.value("bit_rate").toInt());
    this->setDuration(song.value("duration").toLongLong());
    this->setSize(song.value("size").toLongLong());

    emit q->ready(q);
}

QString SongPrivate::id() const {
    return m_id;
}

void SongPrivate::setId(const QString &id) {
    m_id = id;
}

QString SongPrivate::title() const {
    return m_title;
}

void SongPrivate::setTitle(const QString &title) {
    m_title = title;
}

QString SongPrivate::artist() const {
    return m_artist;
}

void SongPrivate::setArtist(const QString &artist) {
    m_artist = artist;
}

QString SongPrivate::artistId() const {
    return m_artistId;
}

void SongPrivate::setArtistId(const QString &id) {
    m_artistId = id;
}

QString SongPrivate::albumTitle() const {
    return m_albumTitle;
}

void SongPrivate::setAlbumTitle(const QString &title) {
    m_albumTitle = title;
}

QString SongPrivate::albumArtist() const {
    return m_albumArtist;
}

void SongPrivate::setAlbumArtist(const QString &artist) {
    m_albumArtist = artist;
}

QString SongPrivate::albumId() const {
    return m_albumId;
}

void SongPrivate::setAlbumId(const QString &id) {
    m_albumId = id;
}

QString SongPrivate::genre() const {
    return m_genre;
}

void SongPrivate::setGenre(const QString &genre) {
    m_genre = genre;
}

QString SongPrivate::filePath() const {
    return m_filePath;
}

void SongPrivate::setFilePath(const QString &path) {
    m_filePath = path;
}

QString SongPrivate::fileSuffix() const {
    return m_fileSuffix;
}

void SongPrivate::setFileSuffix(const QString &suffix) {
    m_fileSuffix = suffix;
}

QString SongPrivate::mimeType() const {
    return m_mimeType;
}

void SongPrivate::setMimeType(const QString &type) {
    m_mimeType = type;
}

QUrl SongPrivate::url() const {
    return m_url;
}

void SongPrivate::setUrl(const QUrl &url) {
    m_url = url;
}

QUrl SongPrivate::artworkUrl() const {
    return m_artworkUrl;
}

void SongPrivate::setArtworkUrl(const QUrl &url) {
    m_artworkUrl = url;
}

QUrl SongPrivate::streamUrl() const {
    return m_streamUrl;
}

void SongPrivate::setStreamUrl(const QUrl &url) {
    m_streamUrl = url;
}

int SongPrivate::year() const {
    return m_year;
}

void SongPrivate::setYear(int year) {
    m_year = year;
}

int SongPrivate::trackNumber() const {
    return m_trackNumber;
}

void SongPrivate::setTrackNumber(int number) {
    m_trackNumber = number;
}

int SongPrivate::discNumber() const {
    return m_discNumber;
}

void SongPrivate::setDiscNumber(int number) {
    m_discNumber = number;
}

int SongPrivate::bitRate() const {
    return m_bitRate;
}

void SongPrivate::setBitRate(int rate) {
    m_bitRate = rate;
}

qint64 SongPrivate::duration() const {
    return m_duration;
}

void SongPrivate::setDuration(qint64 duration) {
    m_duration = duration;
}

qint64 SongPrivate::size() const {
    return m_size;
}

void SongPrivate::setSize(qint64 size) {
    m_size = size;
}

}

