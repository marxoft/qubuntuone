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
 * \file music.h
 */

#ifndef MUSIC_H
#define MUSIC_H

#include "qubuntuone_global.h"
#include <QObject>

class QUrl;
class QSize;

namespace QtUbuntuOne {

class ArtistList;
class AlbumList;
class PlaylistList;
class Playlist;
class SongList;
class Reply;
class Artwork;
class MusicStream;

/**
 * \class Music
 * \brief Handles requests to the Ubuntu One music streaming API.
 *
 * Music handles all requests to the Ubuntu One music streaming API.
 */
class QUBUNTUONESHARED_EXPORT Music : public QObject
{
    Q_OBJECT

public:
    Music(QObject *parent = 0);
    ~Music();

    /**
     * Requests a list of artists for the currently authenticated user,
     * and returns an ArtistList instance that handles the response.
     *
     * \return ArtistList* An instance of ArtistList that contains the response metadata.
     */
    Q_INVOKABLE static ArtistList* getArtists();

    /**
     * Requests a list of artists for the currently authenticated user,
     * and returns an ArtistList instance that handles the response.
     *
     * \param offset
     * \param limit
     *
     * \return ArtistList* An instance of ArtistList that contains the response metadata.
     */
    Q_INVOKABLE static ArtistList* getArtists(int offset, int limit);

    /**
     * Requests a list of albums for the currently authenticated user,
     * and returns an AlbumList instance that handles the response.
     *
     * \return AlbumList* An instance of AlbumList that contains the response metadata.
     */
    Q_INVOKABLE static AlbumList* getAlbums();

    /**
     * Requests a list of albums for the currently authenticated user,
     * and returns an AlbumList instance that handles the response.
     *
     * \param offset
     * \param limit
     *
     * \return AlbumList* An instance of AlbumList that contains the response metadata.
     */
    Q_INVOKABLE static AlbumList* getAlbums(int offset, int limit);

    /**
     * Requests the albums from the specified artist for the currently authenticated user,
     * and returns an AlbumList instance that handles the response.
     *
     * \param artistId
     *
     * \return AlbumList* An instance of AlbumList that contains the response metadata.
     */
    Q_INVOKABLE static AlbumList* getArtistAlbums(const QString &artistId);

    /**
     * Requests a list of songs for the currently authenticated user,
     * and returns a SongList instance that handles the response.
     *
     * \return SongList* An instance of SongList that contains the response metadata.
     */
    Q_INVOKABLE static SongList* getSongs();

    /**
     * Requests a list of songs for the currently authenticated user,
     * and returns a SongList instance that handles the response.
     *
     * \param offset
     * \param limit
     *
     * \return SongList* An instance of SongList that contains the response metadata.
     */
    Q_INVOKABLE static SongList* getSongs(int offset, int limit);

    /**
     * Requests the songs from the specified album for the currently authenticated user,
     * and returns a SongList instance that handles the response.
     *
     * \param albumId
     *
     * \return SongList* An instance of SongList that contains the response metadata.
     */
    Q_INVOKABLE static SongList* getAlbumSongs(const QString &albumId);

    /**
     * Requests the songs from the specified playlist for the currently authenticated user,
     * and returns a SongList instance that handles the response.
     *
     * \param playlistId
     *
     * \return SongList* An instance of SongList that contains the response metadata.
     */
    Q_INVOKABLE static SongList* getPlaylistSongs(const QString &playlistId);

    /**
     * Requests a list of playlists for the currently authenticated user,
     * and returns a PlaylistList instance that handles the response.
     *
     * \return PlaylistList* An instance of Reply that contains the response metadata.
     */
    Q_INVOKABLE static PlaylistList* getPlaylists();

    /**
     * Requests a list of playlists for the currently authenticated user,
     * and returns a PlaylistList instance that handles the response.
     *
     * \param offset
     * \param limit
     *
     * \return PlaylistList* An instance of Reply that contains the response metadata.
     */
    Q_INVOKABLE static PlaylistList* getPlaylists(int offset, int limit);

    /**
     * Creates a playlist for the currently authenticated user,
     * and returns a Playlist instance that handles the response.
     *
     * \param title
     *
     * \return Playlist* An instance of Reply that contains the response metadata.
     */
    Q_INVOKABLE static Playlist* createPlaylist(const QString &title);

    /**
     * Creates a playlist for the currently authenticated user,
     * and returns a Playlist instance that handles the response.
     *
     * \param title
     * \param songIds
     *
     * \return Playlist* An instance of Playlist that contains the response metadata.
     */
    Q_INVOKABLE static Playlist* createPlaylist(const QString &title, const QStringList &songIds);

    /**
     * Updates the title of the specified playlist for the currently authenticated user,
     * and returns a Reply instance that handles the response.
     *
     * \param playlistId
     * \param title
     *
     * \return Reply* An instance of Reply that contains the response metadata.
     */
    Q_INVOKABLE static Reply* updatePlaylist(const QString &playlistId, const QString &title);

    /**
     * Updates the song list of the specified playlist for the currently authenticated user,
     * and returns a Reply instance that handles the response.
     *
     * \param playlistId
     * \param songIds
     *
     * \return Reply* An instance of Reply that contains the response metadata.
     */
    Q_INVOKABLE static Reply* updatePlaylist(const QString &playlistId, const QStringList &songIds);

    /**
     * Requests the requested artwork image, and returns an Artwork instance that handles the repsonse.
     *
     * \param artworkUrl
     *
     * \return Artwork* An instance of Artwork that contains the response metadata.
     */
    Q_INVOKABLE static Artwork* getArtwork(const QUrl &artworkUrl);

    /**
     * Requests the requested artwork image, and returns an Artwork instance that handles the repsonse.
     * The image is scaled to the requested size.
     *
     * \param artworkUrl
     * \param size
     *
     * \return Artwork* An instance of Artwork that contains the response metadata.
     */
    Q_INVOKABLE static Artwork* getArtwork(const QUrl &artworkUrl, const QSize &size);

    /**
     * Creates a MusicStream instance that performs streaming of the song specified by the stream URL.
     * The stream is cached to the specified local file path.
     *
     * \param streamUrl
     * \param localPath
     *
     * \return MusicStream*.
     */
    Q_INVOKABLE static MusicStream* getMusicStream(const QUrl &streamUrl, const QString &localPath);
};

}

#endif
