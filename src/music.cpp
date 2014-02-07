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

#include "music.h"
#include "authentication.h"
#include "urls.h"
#include "networkaccessmanager.h"
#include "reply.h"
#include "artwork.h"
#include "musicstream.h"
#include "artistlist.h"
#include "albumlist.h"
#include "playlistlist.h"
#include "songlist.h"
#include <QUrl>
#include <QStringList>
#include <QDir>
#include <QSize>
#if QT_VERSION >= 0x050000
#include <QUrlQuery>
#endif

namespace QtUbuntuOne {

Music::Music(QObject *parent) :
    QObject(parent)
{
}

Music::~Music() {}

ArtistList* Music::getArtists() {
    QUrl url(BASE_URL_MUSIC + "/artists/");
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", Authentication::getOAuthHeader("GET", url.toString(QUrl::RemoveQuery), QMap<QString, QString>()));
    request.setRawHeader("Accept", "application/json");
    request.setRawHeader("User-Agent", "QUbuntuOne (Qt)");

    return new ArtistList(NetworkAccessManager::instance()->get(request));
}

ArtistList* Music::getArtists(int offset, int limit) {
    QUrl url(BASE_URL_MUSIC + "/artists/");
#if QT_VERSION >= 0x050000
    QUrlQuery query(url);
    query.addQueryItem("offset", QString::number(offset));
    query.addQueryItem("limit", QString::number(limit));
    url.setQuery(query);
#else
    url.addQueryItem("offset", QString::number(offset));
    url.addQueryItem("limit", QString::number(limit));
#endif
    QMap<QString, QString> params;
    params["offset"] = QString::number(offset);
    params["limit"] = QString::number(limit);
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", Authentication::getOAuthHeader("GET", url.toString(QUrl::RemoveQuery), params));
    request.setRawHeader("Accept", "application/json");
    request.setRawHeader("User-Agent", "QUbuntuOne (Qt)");

    return new ArtistList(NetworkAccessManager::instance()->get(request));
}

AlbumList* Music::getAlbums() {
    QUrl url(BASE_URL_MUSIC + "/albums/");
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", Authentication::getOAuthHeader("GET", url.toString(QUrl::RemoveQuery), QMap<QString, QString>()));
    request.setRawHeader("Accept", "application/json");
    request.setRawHeader("User-Agent", "QUbuntuOne (Qt)");

    return new AlbumList(NetworkAccessManager::instance()->get(request));
}

AlbumList* Music::getAlbums(int offset, int limit) {
    QUrl url(BASE_URL_MUSIC + "/albums/");
#if QT_VERSION >= 0x050000
    QUrlQuery query(url);
    query.addQueryItem("offset", QString::number(offset));
    query.addQueryItem("limit", QString::number(limit));
    url.setQuery(query);
#else
    url.addQueryItem("offset", QString::number(offset));
    url.addQueryItem("limit", QString::number(limit));
#endif
    QMap<QString, QString> params;
    params["offset"] = QString::number(offset);
    params["limit"] = QString::number(limit);
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", Authentication::getOAuthHeader("GET", url.toString(QUrl::RemoveQuery), params));
    request.setRawHeader("Accept", "application/json");
    request.setRawHeader("User-Agent", "QUbuntuOne (Qt)");

    return new AlbumList(NetworkAccessManager::instance()->get(request));
}

AlbumList* Music::getArtistAlbums(const QString &artistId) {
    QUrl url(BASE_URL_MUSIC + "/artists/" + artistId + "/");
#if QT_VERSION >= 0x050000
    QUrlQuery query(url);
    query.addQueryItem("artist_id", artistId);
    url.setQuery(query);
#else
    url.addQueryItem("artist_id", artistId);
#endif
    QMap<QString, QString> params;
    params["artist_id"] = artistId;
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", Authentication::getOAuthHeader("GET", url.toString(QUrl::RemoveQuery), params));
    request.setRawHeader("Accept", "application/json");
    request.setRawHeader("User-Agent", "QUbuntuOne (Qt)");

    return new AlbumList(NetworkAccessManager::instance()->get(request));
}

SongList* Music::getSongs() {
    QUrl url(BASE_URL_MUSIC + "/songs/");
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", Authentication::getOAuthHeader("GET", url.toString(QUrl::RemoveQuery), QMap<QString, QString>()));
    request.setRawHeader("Accept", "application/json");
    request.setRawHeader("User-Agent", "QUbuntuOne (Qt)");

    return new SongList(NetworkAccessManager::instance()->get(request));
}

SongList* Music::getSongs(int offset, int limit) {
    QUrl url(BASE_URL_MUSIC + "/songs/");
#if QT_VERSION >= 0x050000
    QUrlQuery query(url);
    query.addQueryItem("offset", QString::number(offset));
    query.addQueryItem("limit", QString::number(limit));
    url.setQuery(query);
#else
    url.addQueryItem("offset", QString::number(offset));
    url.addQueryItem("limit", QString::number(limit));
#endif
    QMap<QString, QString> params;
    params["offset"] = QString::number(offset);
    params["limit"] = QString::number(limit);
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", Authentication::getOAuthHeader("GET", url.toString(QUrl::RemoveQuery), params));
    request.setRawHeader("Accept", "application/json");
    request.setRawHeader("User-Agent", "QUbuntuOne (Qt)");

    return new SongList(NetworkAccessManager::instance()->get(request));
}

SongList* Music::getAlbumSongs(const QString &albumId) {
    QUrl url(BASE_URL_MUSIC + "/albums/" + albumId + "/");
#if QT_VERSION >= 0x050000
    QUrlQuery query(url);
    query.addQueryItem("album_id", albumId);
    url.setQuery(query);
#else
    url.addQueryItem("album_id", albumId);
#endif
    QMap<QString, QString> params;
    params["album_id"] = albumId;
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", Authentication::getOAuthHeader("GET", url.toString(QUrl::RemoveQuery), params));
    request.setRawHeader("Accept", "application/json");
    request.setRawHeader("User-Agent", "QUbuntuOne (Qt)");

    return new SongList(NetworkAccessManager::instance()->get(request));
}

SongList* Music::getPlaylistSongs(const QString &playlistId) {
    QUrl url(BASE_URL_MUSIC + "/playlists/" + playlistId + "/");
#if QT_VERSION >= 0x050000
    QUrlQuery query(url);
    query.addQueryItem("playlist_id", playlistId);
    url.setQuery(query);
#else
    url.addQueryItem("playlist_id", playlistId);
#endif
    QMap<QString, QString> params;
    params["playlist_id"] = playlistId;
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", Authentication::getOAuthHeader("GET", url.toString(QUrl::RemoveQuery), params));
    request.setRawHeader("Accept", "application/json");
    request.setRawHeader("User-Agent", "QUbuntuOne (Qt)");

    return new SongList(NetworkAccessManager::instance()->get(request));
}

PlaylistList* Music::getPlaylists() {
    QUrl url(BASE_URL_MUSIC + "/playlists/");
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", Authentication::getOAuthHeader("GET", url.toString(QUrl::RemoveQuery), QMap<QString, QString>()));
    request.setRawHeader("Accept", "application/json");
    request.setRawHeader("User-Agent", "QUbuntuOne (Qt)");

    return new PlaylistList(NetworkAccessManager::instance()->get(request));
}

PlaylistList* Music::getPlaylists(int offset, int limit) {
    QUrl url(BASE_URL_MUSIC + "/playlists/");
#if QT_VERSION >= 0x050000
    QUrlQuery query(url);
    query.addQueryItem("offset", QString::number(offset));
    query.addQueryItem("limit", QString::number(limit));
    url.setQuery(query);
#else
    url.addQueryItem("offset", QString::number(offset));
    url.addQueryItem("limit", QString::number(limit));
#endif
    QMap<QString, QString> params;
    params["offset"] = QString::number(offset);
    params["limit"] = QString::number(limit);
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", Authentication::getOAuthHeader("GET", url.toString(QUrl::RemoveQuery), params));
    request.setRawHeader("Accept", "application/json");
    request.setRawHeader("User-Agent", "QUbuntuOne (Qt)");

    return new PlaylistList(NetworkAccessManager::instance()->get(request));
}

Playlist* Music::createPlaylist(const QString &title) {
    QUrl url(BASE_URL_MUSIC + "/playlists/");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", Authentication::getOAuthHeader("POST", url.toString(QUrl::RemoveQuery), QMap<QString, QString>()));
    request.setRawHeader("Accept", "application/json");
    request.setRawHeader("User-Agent", "QUbuntuOne (Qt)");

    return new Playlist(NetworkAccessManager::instance()->put(request, "{ \"name\": \"" + title.toUtf8() + "\" }"));
}

Playlist* Music::createPlaylist(const QString &title, const QStringList &songIds) {
    QUrl url(BASE_URL_MUSIC + "/playlists/");
    QString json = QString("{ \"name\": \"%1\", \"song_id_list\": [ %2 ] }").arg(title).arg(songIds.join(", "));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", Authentication::getOAuthHeader("PUT", url.toString(QUrl::RemoveQuery), QMap<QString, QString>()));
    request.setRawHeader("Accept", "application/json");
    request.setRawHeader("User-Agent", "QUbuntuOne (Qt)");

    return new Playlist(NetworkAccessManager::instance()->put(request, json.toUtf8()));
}

Reply* Music::updatePlaylist(const QString &id, const QString &title) {
    QUrl url(BASE_URL_MUSIC + "/playlists/" + id + "/");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", Authentication::getOAuthHeader("PUT", url.toString(QUrl::RemoveQuery), QMap<QString, QString>()));
    request.setRawHeader("Accept", "application/json");
    request.setRawHeader("User-Agent", "QUbuntuOne (Qt)");

    return new Reply(NetworkAccessManager::instance()->put(request, "{ \"name\": \"" + title.toUtf8() + "\" }"));
}

Reply* Music::updatePlaylist(const QString &id, const QStringList &songIds) {
    QUrl url(BASE_URL_MUSIC + "/playlists/" + id + "/");
    QString json = QString("{ \"song_id_list\": [ %1 ] }").arg(songIds.join(", "));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", Authentication::getOAuthHeader("PUT", url.toString(QUrl::RemoveQuery), QMap<QString, QString>()));
    request.setRawHeader("Accept", "application/json");
    request.setRawHeader("User-Agent", "QUbuntuOne (Qt)");

    return new Reply(NetworkAccessManager::instance()->put(request, json.toUtf8()));
}

Artwork* Music::getArtwork(const QUrl &artworkUrl) {
    return Music::getArtwork(artworkUrl, QSize());
}

Artwork* Music::getArtwork(const QUrl &artworkUrl, const QSize &size) {
    QNetworkRequest request(artworkUrl);
    request.setRawHeader("Authorization", Authentication::getOAuthHeader("GET", artworkUrl.toString(), QMap<QString, QString>()));
    request.setRawHeader("User-Agent", "QUbuntuOne (Qt)");

    return new Artwork(NetworkAccessManager::instance()->get(request), size);
}

MusicStream* Music::getMusicStream(const QUrl &url, const QString &localPath) {
    return new MusicStream(url, localPath);
}

}
