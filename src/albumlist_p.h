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

#ifndef ALBUMLIST_P_H
#define ALBUMLIST_P_H

#include "albumlist.h"

namespace QtUbuntuOne {

class AlbumListPrivate
{

public:
    AlbumListPrivate(QNetworkReply *reply, AlbumList *parent);
    virtual ~AlbumListPrivate();

    int count() const;

    QList<Album*> albums() const;

    AlbumList::Error error() const;
    QString errorString() const;

    void cancel();

private:
    void setError(AlbumList::Error error);
    void setErrorString(const QString &errorstring);

    void loadAlbums(const QVariantList &albums);

    void _q_onReplyFinished();

    AlbumList *q_ptr;

    QNetworkReply *m_reply;

    QList<Album*> m_albums;

    AlbumList::Error m_error;
    QString m_errorString;

    Q_DECLARE_PUBLIC(AlbumList)
};

}

#endif // ALBUMLIST_P_H
