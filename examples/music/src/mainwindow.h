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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "reply.h"
#include "artwork.h"
#include "musicstream.h"
#include "albumlist.h"
#include "artistlist.h"
#include "playlistlist.h"
#include "songlist.h"
#include <QMainWindow>
#include <QMediaPlayer>

class QPushButton;
class QLineEdit;
class QTextEdit;
class QComboBox;
class QLabel;
class QSlider;

using namespace QtUbuntuOne;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onCredentialsChanged();
    void getResult();
    void getArtists();
    void getAlbums();
    void getArtistAlbums();
    void getSongs();
    void getAlbumSongs();
    void getPlaylistSongs();
    void getPlaylists();
    void createPlaylist();
    void updatePlaylist();
    void getArtwork();
    void getMusicStream();
    void onArtistsReady(ArtistList *artists);
    void onArtistsCancelled(ArtistList *artists);
    void onAlbumsReady(AlbumList *albums);
    void onAlbumsCancelled(AlbumList *albums);
    void onPlaylistReady(Playlist *playlist);
    void onPlaylistCancelled(Playlist *playlist);
    void onPlaylistsReady(PlaylistList *playlists);
    void onPlaylistsCancelled(PlaylistList *playlists);
    void onSongsReady(SongList *songs);
    void onSongsCancelled(SongList *songs);
    void onReplyFinished(Reply *reply);
    void onReplyCancelled(Reply *reply);
    void onArtworkReady(Artwork *artwork);
    void onArtworkCancelled(Artwork *artwork);
    void onMusicStreamStatusChanged(MusicStream::Status status);
    void onMediaStateChanged(QMediaPlayer::State state);
    void onMediaError(QMediaPlayer::Error error);
    void onMediaPositionChanged(qint64 position);
    void onMediaDurationChanged(qint64 duration);
    void onSliderReleased();
    void togglePlayPause();
    void stop();
    void showAboutDialog();

private:
    QString msecsToString(qint64 msecs) const;

private:
    QLineEdit *m_consumerKeyEdit;
    QLineEdit *m_consumerSecretEdit;
    QLineEdit *m_tokenKeyEdit;
    QLineEdit *m_tokenSecretEdit;
    QComboBox *m_methodSelector;
    QLineEdit *m_paramsEdit;
    QPushButton *m_actionButton;
    QPushButton *m_cancelButton;
    QTextEdit *m_resultEdit;
    QLabel *m_positionLabel;
    QLabel *m_durationLabel;
    QLabel *m_artworkLabel;
    QSlider *m_slider;
    QPushButton *m_playPauseButton;
    QPushButton *m_stopButton;
    QMediaPlayer *m_mediaPlayer;
    MusicStream *m_stream;
};

#endif // MAINWINDOW_H
