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

#include "useraccount_p.h"
#include "json.h"

namespace QtUbuntuOne {

UserAccountPrivate::UserAccountPrivate(QNetworkReply *reply, UserAccount *parent) :
    q_ptr(parent),
    m_reply(reply),
    m_totalStorage(0),
    m_error(UserAccount::NoError)
{
    Q_Q(UserAccount);

    if (m_reply) {
        q->connect(m_reply, SIGNAL(finished()), q, SLOT(_q_onReplyFinished()));
    }
}

UserAccountPrivate::~UserAccountPrivate() {
    if (m_reply) {
        delete m_reply;
        m_reply = 0;
    }
}

void UserAccountPrivate::loadAccount(const QVariantMap &account) {
    Q_Q(UserAccount);

    this->setId(account.value("id").toString());
    this->setUsername(account.value("username").toString());
    this->setNickname(account.value("nickname").toString());
    this->setFirstName(account.value("first_name").toString());
    this->setLastName(account.value("last_name").toString());
    this->setEmail(account.value("email").toString());
    this->setOpenId(account.value("openid").toString());
    this->setTotalStorage(account.value("total_storage").toLongLong());
    this->setCurrentPlan(account.value("current_plan").toString());
    this->setDetailedPlans(account.value("detailed_plans").toList());
    this->setFeatures(account.value("features").toStringList());
    this->setSubscription(account.value("subscription").toMap());

    emit q->ready(q);
}

QString UserAccountPrivate::id() const {
    return m_id;
}

void UserAccountPrivate::setId(const QString &id) {
    m_id = id;
}

QString UserAccountPrivate::username() const {
    return m_username;
}

void UserAccountPrivate::setUsername(const QString &name) {
    m_username = name;
}

QString UserAccountPrivate::nickname() const {
    return m_nickname;
}

void UserAccountPrivate::setNickname(const QString &name) {
    m_nickname = name;
}

QString UserAccountPrivate::firstName() const {
    return m_firstName;
}

void UserAccountPrivate::setFirstName(const QString &name) {
    m_firstName = name;
}

QString UserAccountPrivate::lastName() const {
    return m_lastName;
}

void UserAccountPrivate::setLastName(const QString &name) {
    m_lastName = name;
}

QString UserAccountPrivate::email() const {
    return m_email;
}

void UserAccountPrivate::setEmail(const QString &email) {
    m_email = email;
}

QString UserAccountPrivate::openId() const {
    return m_openId;
}

void UserAccountPrivate::setOpenId(const QString &id) {
    m_openId = id;
}

qint64 UserAccountPrivate::totalStorage() const {
    return m_totalStorage;
}

void UserAccountPrivate::setTotalStorage(qint64 bytes) {
    m_totalStorage = bytes;
}

QString UserAccountPrivate::currentPlan() const {
    return m_currentPlan;
}

void UserAccountPrivate::setCurrentPlan(const QString &plan) {
    m_currentPlan = plan;
}

QVariantList UserAccountPrivate::detailedPlans() const {
    return m_detailedPlans;
}

void UserAccountPrivate::setDetailedPlans(const QVariantList &plans) {
    m_detailedPlans = plans;
}

QStringList UserAccountPrivate::features() const {
    return m_features;
}

void UserAccountPrivate::setFeatures(const QStringList &features) {
    m_features = features;
}

QVariantMap UserAccountPrivate::subscription() const {
    return m_subscription;
}

void UserAccountPrivate::setSubscription(const QVariantMap &subscription) {
    m_subscription = subscription;
}

UserAccount::Error UserAccountPrivate::error() const {
    return m_error;
}

void UserAccountPrivate::setError(UserAccount::Error error) {
    m_error = error;
}

QString UserAccountPrivate::errorString() const {
    return m_errorString;
}

void UserAccountPrivate::setErrorString(const QString &errorString) {
    m_errorString = errorString;
}

void UserAccountPrivate::cancel() {
    if (m_reply) {
        m_reply->abort();
    }
}

void UserAccountPrivate::_q_onReplyFinished() {
    Q_Q(UserAccount);

    if (m_reply) {
        switch (m_reply->error()) {
        case QNetworkReply::NoError:
            break;
        case QNetworkReply::OperationCanceledError:
            emit q->cancelled(q);
            return;
        default:
            this->setError(UserAccount::Error(m_reply->error()));
            this->setErrorString(m_reply->errorString());
            emit q->ready(q);
            return;
        }

        QString response(m_reply->readAll());
        QVariantMap result = QtJson::Json::parse(response).toMap();

        if (!result.isEmpty()) {
            this->loadAccount(result);
        }
        else {
            this->setError(UserAccount::ParserError);
            this->setErrorString(QObject::tr("Cannot parse server response"));
            emit q->ready(q);
        }

        m_reply->deleteLater();
        m_reply = 0;
    }
}

}
