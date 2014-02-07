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

#ifndef SONGLIST_P_H
#define SONGLIST_P_H

#include "songlist.h"

namespace QtUbuntuOne {

class SongListPrivate
{

public:
    SongListPrivate(QNetworkReply *reply, SongList *parent);
    virtual ~SongListPrivate();

    int count() const;

    QList<Song*> songs() const;

    SongList::Error error() const;
    QString errorString() const;

    void cancel();

private:
    void setError(SongList::Error error);
    void setErrorString(const QString &errorstring);

    void loadSongs(const QVariantList &songs);

    void _q_onReplyFinished();

    SongList *q_ptr;

    QNetworkReply *m_reply;

    QList<Song*> m_songs;

    SongList::Error m_error;
    QString m_errorString;

    Q_DECLARE_PUBLIC(SongList)
};

}

#endif // SONGLIST_P_H
