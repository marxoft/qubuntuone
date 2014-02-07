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
 * \file authentication.cpp
 */

#include "authentication.h"
#include "authentication_p.h"
#include "token.h"
#include "urls.h"
#include "oauth.h"
#include "networkaccessmanager.h"

namespace QtUbuntuOne {

Authentication::Authentication(QObject *parent) :
    QObject(parent)
{
}

Authentication::~Authentication() {}

/**
 * consumerKey
 */
QString Authentication::consumerKey() {
    return AuthenticationPrivate::consumerKey();
}

/**
 * setConsumerKey
 */
void Authentication::setConsumerKey(const QString &key) {
    AuthenticationPrivate::setConsumerKey(key);
}

/**
 * consumerSecret
 */
QString Authentication::consumerSecret() {
    return AuthenticationPrivate::consumerSecret();
}

/**
 * setConsumerSecret
 */
void Authentication::setConsumerSecret(const QString &secret) {
    AuthenticationPrivate::setConsumerSecret(secret);
}

/**
 * tokenKey
 */
QString Authentication::tokenKey() {
    return AuthenticationPrivate::tokenKey();
}

/**
 * setTokenKey
 */
void Authentication::setTokenKey(const QString &key) {
    AuthenticationPrivate::setTokenKey(key);
}

/**
 * tokenSecret
 */
QString Authentication::tokenSecret() {
    return AuthenticationPrivate::tokenSecret();
}

/**
 * setTokenSecret
 */
void Authentication::setTokenSecret(const QString &secret) {
    AuthenticationPrivate::setTokenSecret(secret);
}

/**
 * setCredentials
 */
void Authentication::setCredentials(const QString &consumerKey,
                                    const QString &consumerSecret,
                                    const QString &tokenKey,
                                    const QString &tokenSecret) {

    Authentication::setConsumerKey(consumerKey);
    Authentication::setConsumerSecret(consumerSecret);
    Authentication::setTokenKey(tokenKey);
    Authentication::setTokenSecret(tokenSecret);
}

/**
 * setCredentials
 */
void Authentication::clearCredentials() {
    Authentication::setConsumerKey(QString());
    Authentication::setConsumerSecret(QString());
    Authentication::setTokenKey(QString());
    Authentication::setTokenSecret(QString());
}

/**
 * getOAuthHeader
 */
QByteArray Authentication::getOAuthHeader(const QString &method, const QString &url, QMap<QString, QString> params) {
    params.insert("oauth_consumer_key", Authentication::consumerKey());
    params.insert("oauth_consumer_secret", Authentication::consumerSecret());
    params.insert("oauth_token", Authentication::tokenKey());
    params.insert("oauth_token_secret", Authentication::tokenSecret());

    return QtOAuth::OAuth::createOAuthHeader(method, url, params);
}

/**
 * authenticate
 */
Token* Authentication::authenticate(const QString &email, const QString &password, const QString &applicationName) {
    QString json = QString("{ \"email\": \"%1\", \"password\": \"%2\", \"token_name\": \"Ubuntu One @ localhost [%3]\" }").arg(email).arg(password).arg(applicationName);
    QUrl url(AUTH_URL);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Accept", "application/json");
    request.setRawHeader("User-Agent", "QUbuntuOne (Qt)");

    return new Token(NetworkAccessManager::instance()->post(request, json.toUtf8()));
}

/**
 * authenticate
 */
Token* Authentication::authenticate(const QString &email, const QString &password, const QString &oneTimePassword, const QString &applicationName) {
    if (oneTimePassword.isEmpty()) {
        return Authentication::authenticate(email, password, applicationName);
    }

    QString json = QString("{ \"email\": \"%1\", \"password\": \"%2\", \"otp\": \"%3\", \"token_name\": \"Ubuntu One @ localhost [%4]\" }").arg(email).arg(password).arg(oneTimePassword).arg(applicationName);
    QUrl url(AUTH_URL);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Accept", "application/json");
    request.setRawHeader("User-Agent", "QUbuntuOne (Qt)");

    return new Token(NetworkAccessManager::instance()->post(request, json.toUtf8()));
}

}
