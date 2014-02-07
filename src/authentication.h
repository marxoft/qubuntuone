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
 * \file authentication.h
 */

#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include "qubuntuone_global.h"
#include <QObject>
#include <QMap>

namespace QtUbuntuOne {

class Token;

/**
 * \class Authentication
 * \brief Handles Ubuntu One authentication.
 *
 * Authentication handles all Ubuntu One authentication operations and OAuth signing.
 */
class QUBUNTUONESHARED_EXPORT Authentication : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString consumerKey
               READ consumerKey
               WRITE setConsumerKey)
    Q_PROPERTY(QString consumerSecret
               READ consumerSecret
               WRITE setConsumerSecret)
    Q_PROPERTY(QString tokenKey
               READ tokenKey
               WRITE setTokenKey)
    Q_PROPERTY(QString tokenSecret
               READ tokenSecret
               WRITE setTokenSecret)

public:
    Authentication(QObject *parent = 0);
    ~Authentication();

    /**
     * Returns the OAuth consumer key used for signing requests to the Ubuntu One API.
     *
     * \return QString The consumer key.
     */
    static QString consumerKey();

    /**
     * Sets the OAuth consumer key used for signing requests to the Ubuntu One API.
     *
     * \param key The consumer key.
     */
    static void setConsumerKey(const QString &key);

    /**
     * Returns the OAuth consumer secret used for signing requests to the Ubuntu One API.
     *
     * \return QString The consumer secret.
     */
    static QString consumerSecret();

    /**
     * Sets the OAuth consumer secret used for signing requests to the Ubuntu One API.
     *
     * \param secret The consumer secret.
     */
    static void setConsumerSecret(const QString &secret);

    /**
     * Returns the OAuth token key used for signing requests to the Ubuntu One API.
     *
     * \return QString The token key.
     */
    static QString tokenKey();

    /**
     * Sets the OAuth token key used for signing requests to the Ubuntu One API.
     *
     * \param key The token key.
     */
    static void setTokenKey(const QString &key);

    /**
     * Returns the OAuth token secret used for signing requests to the Ubuntu One API.
     *
     * \return QString The token secret.
     */
    static QString tokenSecret();

    /**
     * Sets the OAuth token secret used for signing requests to the Ubuntu One API.
     *
     * \param secret The token secret.
     */
    static void setTokenSecret(const QString &secret);

    /**
     * A convenience method that sets the OAuth credentials used for signing requests to the Ubuntu One API.
     *
     * \param consumerKey The consumer key.
     * \param consumerSecret The consumer secret.
     * \param tokenKey The token key.
     * \param tokenSecret The token secret.
     */
    Q_INVOKABLE static void setCredentials(const QString &consumerKey,
                                    const QString &consumerSecret,
                                    const QString &tokenKey,
                                    const QString &tokenSecret);

    /**
     * A convenience method that sets each of the OAuth credentials to an empty string.
     */
    Q_INVOKABLE static void clearCredentials();

    /**
     * Performs an authentication request using the supplied credentials, and returns a Token.
     *
     * \param email The email address of the user.
     * \param password The password of the user.
     * \param applicationName The name of the application requesting authorisation.
     *
     * \return Token* A reply containing the result of the authentication request.
     */
    Q_INVOKABLE static Token* authenticate(const QString &email, const QString &password, const QString &applicationName);

    /**
     * Overloaded method. Performs an authentication request using the supplied credentials, and returns a Token.
     * Only use this method if the user supplies a one-time password.
     *
     * \param email The email address of the user.
     * \param password The password of the user.
     * \param oneTimePassword The one-time password of the user.
     * \param applicationName The name of the application requesting authorisation.
     *
     * \return Token* A reply containing the result of the authentication request.
     */
    Q_INVOKABLE static Token* authenticate(const QString &email, const QString &password, const QString &oneTimePassword, const QString &applicationName);

    /**
     * Returns an OAuth Authorization header that can be used to when making requests to the Ubuntu One API.
     *
     * \param method The HTTP method to be used for the request.
     * \param url The URL to be used for the request.
     * \param params A map of the paramaters to be used for the request.
     *
     * \return QByteArray The OAuth Authorization header.
     */
    Q_INVOKABLE static QByteArray getOAuthHeader(const QString &method, const QString &url, QMap<QString, QString> params);
};

}

#endif // AUTHENTICATION_H
