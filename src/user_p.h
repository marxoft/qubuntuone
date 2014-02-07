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

#ifndef USER_P_H
#define USER_P_H

#include "user.h"
#include <QStringList>

namespace QtUbuntuOne {

class UserPrivate
{

public:
    UserPrivate(QNetworkReply *reply, User *parent);
    virtual ~UserPrivate();

    void loadUser(const QVariantMap &user);

    QString id() const;

    QString name() const;

    QString resourcePath() const;

    QString rootNodePath() const;

    QStringList userNodePaths() const;

    qint64 maxBytes() const;

    qint64 usedBytes() const;

    User::Error error() const;
    QString errorString() const;

    void cancel();

private:
    void setId(const QString &path);

    void setName(const QString &name);

    void setResourcePath(const QString &path);

    void setRootNodePath(const QString &path);

    void setUserNodePaths(const QStringList &paths);

    void setMaxBytes(qint64 bytes);

    void setUsedBytes(qint64 bytes);

    void setError(User::Error error);
    void setErrorString(const QString &errorString);

    void _q_onReplyFinished();

    User *q_ptr;

    QNetworkReply *m_reply;

    QString m_id;

    QString m_name;

    QString m_resourcePath;

    QString m_rootNodePath;

    QStringList m_userNodePaths;

    qint64 m_maxBytes;

    qint64 m_usedBytes;

    User::Error m_error;
    QString m_errorString;

    Q_DECLARE_PUBLIC(User)
};

}


#endif // USER_P_H
