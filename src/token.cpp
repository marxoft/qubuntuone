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
 * \file token.cpp
 */

#include "token.h"
#include "token_p.h"

namespace QtUbuntuOne {

Token::Token(QNetworkReply *reply, QObject *parent) :
    QObject(parent),
    d_ptr(new TokenPrivate(reply, this))
{
}

Token::Token(TokenPrivate &d, QObject *parent) :
    QObject(parent),
    d_ptr(&d)
{
}

Token::~Token() {}

/**
 * tokenName
 */
QString Token::tokenName() const {
    Q_D(const Token);

    return d->tokenName();
}

/**
 * consumerKey
 */
QString Token::consumerKey() const {
    Q_D(const Token);

    return d->consumerKey();
}

/**
 * consumerSecret
 */
QString Token::consumerSecret() const {
    Q_D(const Token);

    return d->consumerSecret();
}

/**
 * tokenKey
 */
QString Token::tokenKey() const {
    Q_D(const Token);

    return d->tokenKey();
}

/**
 * tokenSecret
 */
QString Token::tokenSecret() const {
    Q_D(const Token);

    return d->tokenSecret();
}

/**
 * error
 */
Token::Error Token::error() const {
    Q_D(const Token);

    return d->error();
}

/**
 * errorString
 */
QString Token::errorString() const {
    Q_D(const Token);

    return d->errorString();
}

/**
 * cancel
 */
void Token::cancel() {
    Q_D(Token);

    d->cancel();
}

#include "moc_token.cpp"

}
