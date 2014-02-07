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

#ifndef TOKEN_P_H
#define TOKEN_P_H

#include "token.h"
#include "json.h"

namespace QtUbuntuOne {

class TokenPrivate
{

public:
    TokenPrivate(QNetworkReply *reply, Token *parent) :
        q_ptr(parent),
        m_reply(reply),
        m_error(Token::NoError)
    {
        Q_Q(Token);

        if (m_reply) {
            q->connect(m_reply, SIGNAL(finished()), q, SLOT(_q_onReplyFinished()));
        }
    }

    virtual ~TokenPrivate() {
        if (m_reply) {
            delete m_reply;
            m_reply = 0;
        }
    }

    inline QString tokenName() const { return m_tokenName; }

    inline QString consumerKey() const { return m_consumerKey; }

    inline QString consumerSecret() const { return m_consumerSecret; }

    inline QString tokenKey() const { return m_tokenKey; }

    inline QString tokenSecret() const { return m_tokenSecret; }

    inline Token::Error error() const { return m_error; }
    inline QString errorString() const { return m_errorString; }

    inline void cancel() {
        if (m_reply) {
            m_reply->abort();
        }
    }

private:
    inline void setTokenName(const QString &name) { m_tokenName = name; }

    inline void setConsumerKey(const QString &key) { m_consumerKey = key; }

    inline void setConsumerSecret(const QString &secret) { m_consumerSecret = secret; }

    inline void setTokenKey(const QString &key) { m_tokenKey = key; }

    inline void setTokenSecret(const QString &secret) { m_tokenSecret = secret; }

    inline void setError(Token::Error error) { m_error = error; }
    inline void setErrorString(const QString &errorString) { m_errorString = errorString; }

    inline void _q_onReplyFinished() {
        Q_Q(Token);

        if (m_reply) {
            switch (m_reply->error()) {
            case QNetworkReply::NoError:
                break;
            case QNetworkReply::OperationCanceledError:
                emit q->cancelled(q);
                return;
            default:
                this->setError(Token::Error(m_reply->error()));
                this->setErrorString(m_reply->errorString());
                emit q->ready(q);
                return;
            }

            bool ok;
            QString response(m_reply->readAll());
            QVariantMap result = QtJson::Json::parse(response, ok).toMap();

            if (ok) {
                this->setTokenName(result.value("token_name").toString());
                this->setConsumerKey(result.value("consumer_key").toString());
                this->setConsumerSecret(result.value("consumer_secret").toString());
                this->setTokenKey(result.value("token_key").toString());
                this->setTokenSecret(result.value("token_secret").toString());
            }
            else {
                this->setError(Token::ParserError);
                this->setErrorString(QObject::tr("Cannot parse server response"));
            }
        }

        emit q->ready(q);
    }

    Token *q_ptr;

    QNetworkReply *m_reply;

    QString m_tokenName;
    QString m_consumerKey;
    QString m_consumerSecret;
    QString m_tokenKey;
    QString m_tokenSecret;

    Token::Error m_error;
    QString m_errorString;

    Q_DECLARE_PUBLIC(Token)
};

}

#endif // TOKEN_P_H
