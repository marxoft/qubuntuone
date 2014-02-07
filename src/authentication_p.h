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

#ifndef AUTHENTICATION_P_H
#define AUTHENTICATION_P_H

#include <QString>

namespace QtUbuntuOne {

static QString m_consumerKey;
static QString m_consumerSecret;
static QString m_tokenKey;
static QString m_tokenSecret;

class AuthenticationPrivate
{

public:
    inline static QString consumerKey() { return m_consumerKey; }
    inline static void setConsumerKey(const QString &key) { m_consumerKey = key; }

    inline static QString consumerSecret() { return m_consumerSecret; }
    inline static void setConsumerSecret(const QString &secret) { m_consumerSecret = secret; }

    inline static QString tokenKey() { return m_tokenKey; }
    inline static void setTokenKey(const QString &key) { m_tokenKey = key; }

    inline static QString tokenSecret() { return m_tokenSecret; }
    inline static void setTokenSecret(const QString &secret) { m_tokenSecret = secret; }
};

}

#endif // AUTHENTICATION_P_H
