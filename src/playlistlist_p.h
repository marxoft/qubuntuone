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

#ifndef PLAYLISTLIST_P_H
#define PLAYLISTLIST_P_H

#include "playlistlist.h"

namespace QtUbuntuOne {

class PlaylistListPrivate
{

public:
    PlaylistListPrivate(QNetworkReply *reply, PlaylistList *parent);
    virtual ~PlaylistListPrivate();

    int count() const;

    QList<Playlist*> playlists() const;

    PlaylistList::Error error() const;
    QString errorString() const;

    void cancel();

private:
    void setError(PlaylistList::Error error);
    void setErrorString(const QString &errorstring);

    void loadPlaylists(const QVariantList &playlists);

    void _q_onReplyFinished();

    PlaylistList *q_ptr;

    QNetworkReply *m_reply;

    QList<Playlist*> m_playlists;

    PlaylistList::Error m_error;
    QString m_errorString;

    Q_DECLARE_PUBLIC(PlaylistList)
};

}

#endif // PLAYLISTLIST_P_H
