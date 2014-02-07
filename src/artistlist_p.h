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

#ifndef ARTISTLIST_P_H
#define ARTISTLIST_P_H

#include "artistlist.h"

namespace QtUbuntuOne {

class ArtistListPrivate
{

public:
    ArtistListPrivate(QNetworkReply *reply, ArtistList *parent);
    virtual ~ArtistListPrivate();

    int count() const;

    QList<Artist*> artists() const;

    ArtistList::Error error() const;
    QString errorString() const;

    void cancel();

private:
    void setError(ArtistList::Error error);
    void setErrorString(const QString &errorstring);

    void loadArtists(const QVariantList &artists);

    void _q_onReplyFinished();

    ArtistList *q_ptr;

    QNetworkReply *m_reply;

    QList<Artist*> m_artists;

    ArtistList::Error m_error;
    QString m_errorString;

    Q_DECLARE_PUBLIC(ArtistList)
};

}

#endif // ARTISTLIST_P_H
