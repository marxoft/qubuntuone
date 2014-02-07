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

#ifndef PLAYLIST_P_H
#define PLAYLIST_P_H

#include "playlist.h"

namespace QtUbuntuOne {

class PlaylistPrivate
{

public:
    PlaylistPrivate(Playlist *parent);
    PlaylistPrivate(Playlist *otherPlaylist, Playlist *parent);
    PlaylistPrivate(QNetworkReply *reply, Playlist *parent);
    virtual ~PlaylistPrivate();

    void loadPlaylist(Playlist *otherPlaylist);
    void loadPlaylist(const QVariantMap &playlist);

    QString id() const;

    QString name() const;

    QUrl url() const;

    int songCount() const;

    Playlist::Error error() const;
    QString errorString() const;

    void cancel();

private:
    void setId(const QString &id);

    void setName(const QString &name);

    void setUrl(const QUrl &url);

    void setSongCount(int count);

    void setError(Playlist::Error error);
    void setErrorString(const QString &errorString);

    void _q_onReplyFinished();

    Playlist *q_ptr;

    QNetworkReply *m_reply;

    QString m_id;

    QString m_name;

    QUrl m_url;

    int m_songCount;

    Playlist::Error m_error;
    QString m_errorString;

    Q_DECLARE_PUBLIC(Playlist)
};

}

#endif // PLAYLIST_P_H
