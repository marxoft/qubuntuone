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
 * \file reply.cpp
 */

#include "reply.h"
#include "reply_p.h"

namespace QtUbuntuOne {

Reply::Reply(QNetworkReply *reply, QObject *parent) :
    QObject(parent),
    d_ptr(new ReplyPrivate(reply, this))
{
}

Reply::Reply(ReplyPrivate &d, QObject *parent) :
    QObject(parent),
    d_ptr(&d)
{
}

Reply::~Reply() {}

/**
 * url
 */
QUrl Reply::url() const {
    Q_D(const Reply);

    return d->m_reply ? d->m_reply->request().url() : QUrl();
}

/**
 * status
 */
int Reply::status() const {
    Q_D(const Reply);

    return d->m_reply ? d->m_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() : 0;
}

/**
 * result
 */
QVariant Reply::result() const {
    Q_D(const Reply);

    return d->result();
}

/**
 * resultString
 */
QString Reply::resultString() const {
    return this->resultType() == QVariant::String ? this->result().toString()
                                                  : QtJson::Json::serialize(this->result());
}

/**
 * resultType
 */
QVariant::Type Reply::resultType() const {
    return this->result().type();
}

/**
 * resultTypeString
 */
QString Reply::resultTypeString() const {
    return QString(this->result().typeName());
}

/**
 * error
 */
Reply::Error Reply::error() const {
    Q_D(const Reply);

    return d->error();
}

/**
 * errorString
 */
QString Reply::errorString() const {
    Q_D(const Reply);

    return d->errorString();
}

/**
 * cancel
 */
void Reply::cancel() {
    Q_D(Reply);

    d->cancel();
}

#include "moc_reply.cpp"

}
