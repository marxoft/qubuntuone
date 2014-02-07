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

#ifndef STORAGEQUOTA_P_H
#define STORAGEQUOTA_P_H

#include "storagequota.h"
#include "json.h"

namespace QtUbuntuOne {

class StorageQuotaPrivate
{

public:
    StorageQuotaPrivate(QNetworkReply *reply, StorageQuota *parent) :
        q_ptr(parent),
        m_reply(reply),
        m_error(StorageQuota::NoError)
    {
        Q_Q(StorageQuota);

        if (m_reply) {
            q->connect(m_reply, SIGNAL(finished()), q, SLOT(_q_onReplyFinished()));
        }
    }

    virtual ~StorageQuotaPrivate() {
        if (m_reply) {
            delete m_reply;
            m_reply = 0;
        }
    }

    inline qint64 totalStorage() const { return m_totalStorage; }

    inline qint64 usedStorage() const { return m_usedStorage; }

    inline StorageQuota::Error error() const { return m_error; }
    inline QString errorString() const { return m_errorString; }

    inline void cancel() {
        if (m_reply) {
            m_reply->abort();
        }
    }

private:
    inline void setTotalStorage(qint64 total) { m_totalStorage = total; }

    inline void setUsedStorage(qint64 used) { m_usedStorage = used; }

    inline void setError(StorageQuota::Error error) { m_error = error; }
    inline void setErrorString(const QString &errorString) { m_errorString = errorString; }

    inline void _q_onReplyFinished() {
        Q_Q(StorageQuota);

        if (m_reply) {
            switch (m_reply->error()) {
            case QNetworkReply::NoError:
                break;
            case QNetworkReply::OperationCanceledError:
                emit q->cancelled(q);
                return;
            default:
                this->setError(StorageQuota::Error(m_reply->error()));
                this->setErrorString(m_reply->errorString());
                emit q->ready(q);
                return;
            }

            bool ok;
            QString response(m_reply->readAll());
            QVariantMap result = QtJson::Json::parse(response, ok).toMap();

            if (ok) {
                this->setTotalStorage(result.value("total").toLongLong());
                this->setUsedStorage(result.value("used").toLongLong());
            }
            else {
                this->setError(StorageQuota::ParserError);
                this->setErrorString(QObject::tr("Cannot parse server response"));
            }
        }

        emit q->ready(q);
    }

    StorageQuota *q_ptr;

    QNetworkReply *m_reply;

    qint64 m_totalStorage;
    qint64 m_usedStorage;

    StorageQuota::Error m_error;
    QString m_errorString;

    Q_DECLARE_PUBLIC(StorageQuota)
};

}

#endif // STORAGEQUOTA_P_H
