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

#include "mainwindow.h"
#include "music.h"
#include "authentication.h"
#include "aboutdialog.h"
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QRegExpValidator>
#include <QPushButton>
#include <QFormLayout>
#include <QGridLayout>
#include <QComboBox>
#include <QSlider>
#include <QTime>
#include <QSpacerItem>
#ifndef Q_WS_MAEMO_5
#include <QMenuBar>
#include <QMenu>
#include <QCoreApplication>
#endif
#include <QDebug>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_consumerKeyEdit(new QLineEdit(this)),
    m_consumerSecretEdit(new QLineEdit(this)),
    m_tokenKeyEdit(new QLineEdit(this)),
    m_tokenSecretEdit(new QLineEdit(this)),
    m_methodSelector(new QComboBox(this)),
    m_paramsEdit(new QLineEdit(this)),
    m_actionButton(new QPushButton(tr("Get result"), this)),
    m_cancelButton(new QPushButton(tr("Cancel"), this)),
    m_resultEdit(new QTextEdit(this)),
    m_positionLabel(new QLabel("--:--", this)),
    m_durationLabel(new QLabel("--:--", this)),
    m_artworkLabel(new QLabel(this)),
    m_slider(new QSlider(Qt::Horizontal, this)),
    m_playPauseButton(new QPushButton(tr("Play"), this)),
    m_stopButton(new QPushButton(tr("Stop"), this)),
    m_mediaPlayer(new QMediaPlayer(this, QMediaPlayer::StreamPlayback)),
    m_stream(0)
{
    this->setMinimumSize(400, 400);
    this->setWindowTitle(tr("QUbuntuOne Music Example"));
    this->setCentralWidget(new QWidget(this));
#ifdef Q_WS_MAEMO_5
    this->menuBar()->addAction(tr("About"), this, SLOT(showAboutDialog()));
#else
    QMenu *fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(tr("Quit"), QCoreApplication::instance(), SLOT(quit()), Qt::CTRL + Qt::Key_Q);

    QMenu *helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(tr("About"), this, SLOT(showAboutDialog()));

    this->menuBar()->addMenu(fileMenu);
    this->menuBar()->addMenu(helpMenu);
#endif
    QRegExpValidator *validator = new QRegExpValidator(QRegExp("[\\S]+"), this);
    m_consumerKeyEdit->setValidator(validator);
    m_consumerSecretEdit->setValidator(validator);
    m_tokenKeyEdit->setValidator(validator);
    m_tokenSecretEdit->setValidator(validator);
    m_paramsEdit->setPlaceholderText(tr("Comma separated parameters"));
    m_resultEdit->setReadOnly(true);
    m_actionButton->setEnabled(false);
    m_cancelButton->setEnabled(false);
    m_slider->setEnabled(false);
    m_playPauseButton->setEnabled(false);
    m_stopButton->setEnabled(false);

    m_methodSelector->addItems(QStringList()
                               << "getArtists"
                               << "getAlbums"
                               << "getArtistAlbums"
                               << "getSongs"
                               << "getAlbumSongs"
                               << "getPlaylistSongs"
                               << "getPlaylists"
                               << "createPlaylist"
                               << "updatePlaylist"
                               << "getArtwork"
                               << "getMusicStream");

    QWidget *formWidget = new QWidget(this);
    QFormLayout *formLayout = new QFormLayout(formWidget);
    formLayout->setContentsMargins(0, 0, 0, 0);
    formLayout->addRow(tr("&Consumer key:"), m_consumerKeyEdit);
    formLayout->addRow(tr("&Consumer secret:"), m_consumerSecretEdit);
    formLayout->addRow(tr("&Token key:"), m_tokenKeyEdit);
    formLayout->addRow(tr("&Token secret:"), m_tokenSecretEdit);
    formLayout->addRow(tr("&Method:"), m_methodSelector);
    formLayout->addRow(tr("&Params:"), m_paramsEdit);

    QGridLayout *grid = new QGridLayout(this->centralWidget());
    grid->setColumnStretch(3, 1);
    grid->addWidget(formWidget, 0, 0, 1, 4);
    grid->addItem(new QSpacerItem(10, 10, QSizePolicy::Expanding), 1, 0);
    grid->addWidget(m_actionButton, 1, 3, Qt::AlignRight);
    grid->addWidget(m_cancelButton, 2, 3, Qt::AlignRight);
    grid->addWidget(new QLabel(tr("Result:"), this), 3, 0);
    grid->addWidget(m_resultEdit, 4, 0, 1, 4);
    grid->addWidget(m_artworkLabel, 5, 0);
    grid->addWidget(m_positionLabel, 5, 1);
    grid->addWidget(m_durationLabel, 5, 2);
    grid->addWidget(m_slider, 5, 3);
    grid->addWidget(m_playPauseButton, 6, 0);
    grid->addWidget(m_stopButton, 6, 1);

    this->connect(m_consumerKeyEdit, SIGNAL(textEdited(QString)), this, SLOT(onCredentialsChanged()));
    this->connect(m_consumerSecretEdit, SIGNAL(textEdited(QString)), this, SLOT(onCredentialsChanged()));
    this->connect(m_tokenKeyEdit, SIGNAL(textEdited(QString)), this, SLOT(onCredentialsChanged()));
    this->connect(m_tokenSecretEdit, SIGNAL(textEdited(QString)), this, SLOT(onCredentialsChanged()));
    this->connect(m_actionButton, SIGNAL(clicked()), this, SLOT(getResult()));
    this->connect(m_slider, SIGNAL(sliderReleased()), this, SLOT(onSliderReleased()));
    this->connect(m_playPauseButton, SIGNAL(clicked()), this, SLOT(togglePlayPause()));
    this->connect(m_stopButton, SIGNAL(clicked()), this, SLOT(stop()));
    this->connect(m_mediaPlayer, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(onMediaStateChanged(QMediaPlayer::State)));
    this->connect(m_mediaPlayer, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(onMediaError(QMediaPlayer::Error)));
    this->connect(m_mediaPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(onMediaPositionChanged(qint64)));
    this->connect(m_mediaPlayer, SIGNAL(durationChanged(qint64)), this, SLOT(onMediaDurationChanged(qint64)));
}

MainWindow::~MainWindow() {
    if (m_stream) {
        delete m_stream;
        m_stream = 0;
    }
}

void MainWindow::onCredentialsChanged() {
    m_actionButton->setEnabled((m_consumerKeyEdit->hasAcceptableInput())
                               && (m_consumerSecretEdit->hasAcceptableInput())
                               && (m_tokenKeyEdit->hasAcceptableInput())
                               && (m_tokenSecretEdit->hasAcceptableInput()));
}

void MainWindow::getResult() {
    Authentication::setCredentials(m_consumerKeyEdit->text(),
                                   m_consumerSecretEdit->text(),
                                   m_tokenKeyEdit->text(),
                                   m_tokenSecretEdit->text());

    m_resultEdit->setText(tr("Calling method %1...").arg(m_methodSelector->currentText()));
    m_actionButton->setEnabled(false);
    m_cancelButton->setEnabled(true);

    QMetaObject::invokeMethod(this, m_methodSelector->currentText().toUtf8());
}

void MainWindow::getArtists() {
    ArtistList *artists = Music::getArtists(m_paramsEdit->text().toInt(), 30);
    this->connect(m_cancelButton, SIGNAL(clicked()), artists, SLOT(cancel()));
    this->connect(artists, SIGNAL(ready(ArtistList*)), this, SLOT(onArtistsReady(ArtistList*)));
    this->connect(artists, SIGNAL(cancelled(ArtistList*)), this, SLOT(onArtistsCancelled(ArtistList*)));
}

void MainWindow::getAlbums() {
    AlbumList *albums = Music::getAlbums(m_paramsEdit->text().toInt(), 30);
    this->connect(m_cancelButton, SIGNAL(clicked()), albums, SLOT(cancel()));
    this->connect(albums, SIGNAL(ready(AlbumList*)), this, SLOT(onAlbumsReady(AlbumList*)));
    this->connect(albums, SIGNAL(cancelled(AlbumList*)), this, SLOT(onAlbumsCancelled(AlbumList*)));
}

void MainWindow::getArtistAlbums() {
    AlbumList *albums = Music::getArtistAlbums(m_paramsEdit->text());
    this->connect(m_cancelButton, SIGNAL(clicked()), albums, SLOT(cancel()));
    this->connect(albums, SIGNAL(ready(AlbumList*)), this, SLOT(onAlbumsReady(AlbumList*)));
    this->connect(albums, SIGNAL(cancelled(AlbumList*)), this, SLOT(onAlbumsCancelled(AlbumList*)));
}

void MainWindow::getSongs() {
    SongList *songs = Music::getSongs(m_paramsEdit->text().toInt(), 30);
    this->connect(m_cancelButton, SIGNAL(clicked()), songs, SLOT(cancel()));
    this->connect(songs, SIGNAL(ready(SongList*)), this, SLOT(onSongsReady(SongList*)));
    this->connect(songs, SIGNAL(cancelled(SongList*)), this, SLOT(onSongsCancelled(SongList*)));
}

void MainWindow::getAlbumSongs() {
    SongList *songs = Music::getAlbumSongs(m_paramsEdit->text());
    this->connect(m_cancelButton, SIGNAL(clicked()), songs, SLOT(cancel()));
    this->connect(songs, SIGNAL(ready(SongList*)), this, SLOT(onSongsReady(SongList*)));
    this->connect(songs, SIGNAL(cancelled(SongList*)), this, SLOT(onSongsCancelled(SongList*)));
}

void MainWindow::getPlaylistSongs() {
    SongList *songs = Music::getPlaylistSongs(m_paramsEdit->text());
    this->connect(m_cancelButton, SIGNAL(clicked()), songs, SLOT(cancel()));
    this->connect(songs, SIGNAL(ready(SongList*)), this, SLOT(onSongsReady(SongList*)));
    this->connect(songs, SIGNAL(cancelled(SongList*)), this, SLOT(onSongsCancelled(SongList*)));
}

void MainWindow::getPlaylists() {
    PlaylistList *playlists = Music::getPlaylists(m_paramsEdit->text().toInt(), 30);
    this->connect(m_cancelButton, SIGNAL(clicked()), playlists, SLOT(cancel()));
    this->connect(playlists, SIGNAL(ready(PlaylistList*)), this, SLOT(onPlaylistsReady(PlaylistList*)));
    this->connect(playlists, SIGNAL(cancelled(PlaylistList*)), this, SLOT(onPlaylistsCancelled(PlaylistList*)));
}

void MainWindow::createPlaylist() {
    Playlist *playlist = Music::createPlaylist(m_paramsEdit->text());
    this->connect(m_cancelButton, SIGNAL(clicked()), playlist, SLOT(cancel()));
    this->connect(playlist, SIGNAL(ready(Playlist*)), this, SLOT(onPlaylistReady(Playlist*)));
    this->connect(playlist, SIGNAL(cancelled(Playlist*)), this, SLOT(onPlaylistCancelled(Playlist*)));
}

void MainWindow::updatePlaylist() {
    Reply *reply = Music::updatePlaylist(m_paramsEdit->text().section(',', 0, 0).trimmed(), m_paramsEdit->text().section(',', -1).trimmed());
    this->connect(m_cancelButton, SIGNAL(clicked()), reply, SLOT(cancel()));
    this->connect(reply, SIGNAL(finished(Reply*)), this, SLOT(onReplyFinished(Reply*)));
    this->connect(reply, SIGNAL(cancelled(Reply*)), this, SLOT(onReplyCancelled(Reply*)));
}

void MainWindow::getArtwork() {
    Artwork *artwork = Music::getArtwork(QUrl::fromUserInput(m_paramsEdit->text()), QSize(64, 64));
    this->connect(m_cancelButton, SIGNAL(clicked()), artwork, SLOT(cancel()));
    this->connect(artwork, SIGNAL(ready(Artwork*)), this, SLOT(onArtworkReady(Artwork*)));
    this->connect(artwork, SIGNAL(cancelled(Artwork*)), this, SLOT(onArtworkCancelled(Artwork*)));
}

void MainWindow::getMusicStream() {
    if (m_stream) {
        m_stream->stop();
        m_stream->deleteLater();
        m_stream = 0;
    }

    m_playPauseButton->setEnabled(false);
    m_stopButton->setEnabled(false);
    m_slider->setEnabled(false);

    m_stream = Music::getMusicStream(QUrl::fromUserInput(m_paramsEdit->text().section(',', 0, 0).trimmed()), m_paramsEdit->text().section(',', -1).trimmed());
    this->connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(stop()));
    this->connect(m_stream, SIGNAL(statusChanged(MusicStream::Status)), this, SLOT(onMusicMusicStreamChanged(MusicStream::Status)));

    m_stream->start();
}

void MainWindow::onArtistsReady(ArtistList *artists) {
    m_actionButton->setEnabled(true);
    m_cancelButton->setEnabled(false);
    m_resultEdit->clear();

    switch (artists->error()) {
    case ArtistList::NoError:
        foreach (Artist *artist, artists->artists()) {
            m_resultEdit->append(tr("Id: %1").arg(artist->id()));
            m_resultEdit->append(tr("Name: %1").arg(artist->name()));
            m_resultEdit->append(tr("Url: %1").arg(artist->url().toString()));
            m_resultEdit->append(tr("Artwork Url %1").arg(artist->artworkUrl().toString()));
            m_resultEdit->append(tr("Song count: %1").arg(artist->songCount()));
            m_resultEdit->append(tr("Album count: %1").arg(artist->albumCount()));
            m_resultEdit->append(tr("Album Ids: %1").arg(artist->albumIds().join(", ")));
            m_resultEdit->append("\n");
        }

        break;
    default:
        m_resultEdit->append(tr("Error: %1").arg(artists->errorString()));
        break;
    }

    qDeleteAll(artists->artists());
    artists->deleteLater();
}

void MainWindow::onArtistsCancelled(ArtistList *artists) {
    m_actionButton->setEnabled(true);
    m_cancelButton->setEnabled(false);
    m_resultEdit->append(tr("Operation cancelled."));
    qDeleteAll(artists->artists());
    artists->deleteLater();
}

void MainWindow::onAlbumsReady(AlbumList *albums) {
    m_actionButton->setEnabled(true);
    m_cancelButton->setEnabled(false);
    m_resultEdit->clear();

    switch (albums->error()) {
    case AlbumList::NoError:
        foreach (Album *album, albums->albums()) {
            m_resultEdit->append(tr("Id: %1").arg(album->id()));
            m_resultEdit->append(tr("Title: %1").arg(album->title()));
            m_resultEdit->append(tr("Artist: %1").arg(album->artist()));
            m_resultEdit->append(tr("Artist id: %1").arg(album->artistId()));
            m_resultEdit->append(tr("Url: %1").arg(album->url().toString()));
            m_resultEdit->append(tr("Artwork Url %1").arg(album->artworkUrl().toString()));
            m_resultEdit->append(tr("Year: %1").arg(album->year()));
            m_resultEdit->append(tr("Date: %1").arg(album->date().toString()));
            m_resultEdit->append("\n");
        }

        break;
    default:
        m_resultEdit->append(tr("Error: %1").arg(albums->errorString()));
        break;
    }

    qDeleteAll(albums->albums());
    albums->deleteLater();
}

void MainWindow::onAlbumsCancelled(AlbumList *albums) {
    m_actionButton->setEnabled(true);
    m_cancelButton->setEnabled(false);
    m_resultEdit->append(tr("Operation cancelled."));
    qDeleteAll(albums->albums());
    albums->deleteLater();
}

void MainWindow::onPlaylistReady(Playlist *playlist) {
    m_actionButton->setEnabled(true);
    m_cancelButton->setEnabled(false);
    m_resultEdit->clear();

    switch (playlist->error()) {
    case Playlist::NoError:
        m_resultEdit->append(tr("Id: %1").arg(playlist->id()));
        m_resultEdit->append(tr("Name: %1").arg(playlist->name()));
        m_resultEdit->append(tr("Url: %1").arg(playlist->url().toString()));
        m_resultEdit->append(tr("Song count: %1").arg(playlist->songCount()));
        break;
    default:
        m_resultEdit->append(tr("Error: %1").arg(playlist->errorString()));
        break;
    }

    playlist->deleteLater();
}

void MainWindow::onPlaylistCancelled(Playlist *playlist) {
    m_actionButton->setEnabled(true);
    m_cancelButton->setEnabled(false);
    m_resultEdit->append(tr("Operation cancelled."));
    playlist->deleteLater();
}

void MainWindow::onPlaylistsReady(PlaylistList *playlists) {
    m_actionButton->setEnabled(true);
    m_cancelButton->setEnabled(false);
    m_resultEdit->clear();

    switch (playlists->error()) {
    case PlaylistList::NoError:
        foreach (Playlist *playlist, playlists->playlists()) {
            m_resultEdit->append(tr("Id: %1").arg(playlist->id()));
            m_resultEdit->append(tr("Name: %1").arg(playlist->name()));
            m_resultEdit->append(tr("Url: %1").arg(playlist->url().toString()));
            m_resultEdit->append(tr("Song count: %1").arg(playlist->songCount()));
            m_resultEdit->append("\n");
        }

        break;
    default:
        m_resultEdit->append(tr("Error: %1").arg(playlists->errorString()));
        break;
    }

    qDeleteAll(playlists->playlists());
    playlists->deleteLater();
}

void MainWindow::onPlaylistsCancelled(PlaylistList *playlists) {
    m_actionButton->setEnabled(true);
    m_cancelButton->setEnabled(false);
    m_resultEdit->append(tr("Operation cancelled."));
    qDeleteAll(playlists->playlists());
    playlists->deleteLater();
}

void MainWindow::onSongsReady(SongList *songs) {
    m_actionButton->setEnabled(true);
    m_cancelButton->setEnabled(false);
    m_resultEdit->clear();

    switch (songs->error()) {
    case SongList::NoError:
        foreach (Song *song, songs->songs()) {
            m_resultEdit->append(tr("Id: %1").arg(song->id()));
            m_resultEdit->append(tr("Title: %1").arg(song->title()));
            m_resultEdit->append(tr("Artist: %1").arg(song->artist()));
            m_resultEdit->append(tr("Artist id: %1").arg(song->artistId()));
            m_resultEdit->append(tr("Album title: %1").arg(song->albumTitle()));
            m_resultEdit->append(tr("Album artist: %1").arg(song->albumArtist()));
            m_resultEdit->append(tr("Album id: %1").arg(song->albumId()));
            m_resultEdit->append(tr("Genre: %1").arg(song->genre()));
            m_resultEdit->append(tr("File path: %1").arg(song->filePath()));
            m_resultEdit->append(tr("File suffix: %1").arg(song->fileSuffix()));
            m_resultEdit->append(tr("Mime type: %1").arg(song->mimeType()));
            m_resultEdit->append(tr("Url: %1").arg(song->url().toString()));
            m_resultEdit->append(tr("Artwork Url: %1").arg(song->artworkUrl().toString()));
            m_resultEdit->append(tr("Stream Url: %1").arg(song->streamUrl().toString()));
            m_resultEdit->append(tr("Year: %1").arg(song->year()));
            m_resultEdit->append(tr("Track number: %1").arg(song->trackNumber()));
            m_resultEdit->append(tr("Disc number: %1").arg(song->discNumber()));
            m_resultEdit->append(tr("Bitrate: %1").arg(song->bitRate()));
            m_resultEdit->append(tr("Duration: %1").arg(song->duration()));
            m_resultEdit->append(tr("Size: %1").arg(song->size()));
            m_resultEdit->append("\n");
        }

        break;
    default:
        m_resultEdit->append(tr("Error: %1").arg(songs->errorString()));
        break;
    }

    qDeleteAll(songs->songs());
    songs->deleteLater();
}

void MainWindow::onSongsCancelled(SongList *songs) {
    m_actionButton->setEnabled(true);
    m_cancelButton->setEnabled(false);
    m_resultEdit->append(tr("Operation cancelled."));
    qDeleteAll(songs->songs());
    songs->deleteLater();
}

void MainWindow::onReplyFinished(Reply *reply) {
    m_actionButton->setEnabled(true);
    m_cancelButton->setEnabled(false);
    m_resultEdit->clear();
    m_resultEdit->append(tr("Status: %1").arg(reply->status()));

    switch (reply->error()) {
    case Reply::NoError:
        m_resultEdit->append(reply->resultString());
        break;
    default:
        m_resultEdit->append(tr("Error: %1").arg(reply->errorString()));
        break;
    }

    reply->deleteLater();
}

void MainWindow::onReplyCancelled(Reply *reply) {
    m_actionButton->setEnabled(true);
    m_cancelButton->setEnabled(false);
    m_resultEdit->append(tr("Operation cancelled."));
    reply->deleteLater();
}

void MainWindow::onArtworkReady(Artwork *artwork) {
    m_actionButton->setEnabled(true);
    m_cancelButton->setEnabled(false);
    m_resultEdit->clear();

    switch (artwork->error()) {
    case Artwork::NoError:
        m_artworkLabel->setPixmap(QPixmap::fromImage(artwork->image()));
        m_resultEdit->append(tr("Artwork loaded from Url: %1").arg(artwork->url().toString()));
        break;
    default:
        m_resultEdit->append(tr("Error: %1").arg(artwork->errorString()));
        break;
    }

    artwork->deleteLater();
}

void MainWindow::onArtworkCancelled(Artwork *artwork) {
    m_actionButton->setEnabled(true);
    m_cancelButton->setEnabled(false);
    m_resultEdit->append(tr("Operation cancelled."));
    artwork->deleteLater();
}

void MainWindow::onMusicStreamStatusChanged(MusicStream::Status status) {
    switch (status) {
    case MusicStream::Ready:
        m_playPauseButton->setEnabled(true);
        m_stopButton->setEnabled(true);
        m_slider->setEnabled(true);
        return;
    case MusicStream::Finished:
        m_resultEdit->append(tr("Music stream finished. Size: %1").arg(m_stream->streamPosition()));
        return;
    case MusicStream::Failed:
        m_resultEdit->append(tr("Music stream error. Error: %1").arg(m_stream->errorString()));
        return;
    default:
        return;
    }
}

void MainWindow::onMediaStateChanged(QMediaPlayer::State state) {
    switch (state) {
    case QMediaPlayer::PlayingState:
        m_playPauseButton->setText(tr("Pause"));
        return;
    default:
        m_playPauseButton->setText(tr("Play"));
        return;
    }
}

void MainWindow::onMediaError(QMediaPlayer::Error error) {
    Q_UNUSED(error)

    m_resultEdit->append(tr("Media error: %1").arg(m_mediaPlayer->errorString()));
}

void MainWindow::onMediaPositionChanged(qint64 position) {
    m_positionLabel->setText(this->msecsToString(position));

    if (!m_slider->isSliderDown()) {
        m_slider->setValue(position);
    }
}

void MainWindow::onMediaDurationChanged(qint64 duration) {
    m_durationLabel->setText(this->msecsToString(duration));
    m_slider->setMaximum(duration);
}

void MainWindow::onSliderReleased() {
    m_mediaPlayer->setPosition(qint64(m_slider->value()));
}

void MainWindow::togglePlayPause() {
    switch (m_mediaPlayer->state()) {
    case QMediaPlayer::PlayingState:
        m_mediaPlayer->pause();
        return;
    default:
        m_stream->open(QIODevice::ReadOnly);
        m_mediaPlayer->setMedia(QMediaContent(), m_stream);

        switch (m_stream->status()) {
        case MusicStream::Stopped:
            m_stream->start();
            break;
        default:
            break;
        }

        m_mediaPlayer->play();
        return;
    }
}

void MainWindow::stop() {
    m_mediaPlayer->stop();
    m_stream->stop();
    m_actionButton->setEnabled(true);
    m_cancelButton->setEnabled(false);
    this->disconnect(m_cancelButton, SIGNAL(clicked()), this, SLOT(stop()));
}

void MainWindow::showAboutDialog() {
    AboutDialog *dialog = new AboutDialog(this);
    dialog->open();
}

QString MainWindow::msecsToString(qint64 msecs) const {
    QTime time;
    QString format = msecs >= 3600000 ? "hh:mm:ss" : "mm:ss";

    return time.addMSecs(msecs).toString(format);
}
