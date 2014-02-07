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

#ifndef REPLY_P_H
#define REPLY_P_H

#include "reply.h"
#include "json.h"

namespace QtUbuntuOne {

class ReplyPrivate
{

public:
    ReplyPrivate(QNetworkReply *reply, Reply *parent) :
        q_ptr(parent),
        m_reply(reply),
        m_error(Reply::NoError)
    {
        Q_Q(Reply);

        if (m_reply) {
            q->connect(m_reply, SIGNAL(finished()), q, SLOT(_q_onReplyFinished()));
        }
    }

    virtual ~ReplyPrivate() {
        if (m_reply) {
            delete m_reply;
            m_reply = 0;
        }
    }

    inline QVariant result() const { return m_result; }

    inline Reply::Error error() const { return m_error; }
    inline QString errorString() const { return m_errorString; }

    inline void cancel() {
        if (m_reply) {
            m_reply->abort();
        }
    }

private:
    inline void setResult(const QVariant &result) { m_result = result; }

    inline void setError(Reply::Error error) { m_error = error; }
    inline void setErrorString(const QString &errorString) { m_errorString = errorString; }

    inline virtual void _q_onReplyFinished() {
        Q_Q(Reply);

        if (m_reply) {
            switch (m_reply->error()) {
            case QNetworkReply::NoError:
                break;
            case QNetworkReply::OperationCanceledError:
                emit q->cancelled(q);
                return;
            default:
                this->setError(Reply::Error(m_reply->error()));
                this->setErrorString(m_reply->errorString());
                emit q->finished(q);
                return;
            }

            bool ok;
            QString response(m_reply->readAll());
            QVariant result = QtJson::Json::parse(response, ok);

            if (ok) {
                this->setResult(result);
            }
            else {
                this->setResult(response);
                this->setError(Reply::ParserError);
                this->setErrorString(QObject::tr("Cannot parse server response"));
            }
        }

        emit q->finished(q);
    }

    Reply *q_ptr;

    QNetworkReply *m_reply;

    QVariant m_result;

    Reply::Error m_error;
    QString m_errorString;

    Q_DECLARE_PUBLIC(Reply)
};

}

#endif // REPLY_P_H
