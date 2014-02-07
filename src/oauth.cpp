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

#include "oauth.h"
#include <QDateTime>
#include <QCryptographicHash>

namespace QtOAuth {

QString OAuth::getTimeStamp() {
    return QString::number(QDateTime::currentMSecsSinceEpoch() / 1000);
}

QString OAuth::getNonce() {
    qsrand(QDateTime::currentMSecsSinceEpoch());

    return QString::number(qrand());
}

QByteArray OAuth::createSignature(QByteArray key, QByteArray baseString) {
    int blockSize = 64; // HMAC-SHA-1 block size, defined in SHA-1 standard
    if (key.length() > blockSize) { // if key is longer than block size (64), reduce key length with SHA-1 compression
        key = QCryptographicHash::hash(key, QCryptographicHash::Sha1);
    }

    QByteArray innerPadding(blockSize, char(0x36)); // initialize inner padding with char "6"
    QByteArray outerPadding(blockSize, char(0x5c)); // initialize outer padding with char "\"
    // ascii characters 0x36 ("6") and 0x5c ("\") are selected because they have large
    // Hamming distance (http://en.wikipedia.org/wiki/Hamming_distance)

    for (int i = 0; i < key.length(); i++) {
        innerPadding[i] = innerPadding[i] ^ key.at(i); // XOR operation between every byte in key and innerpadding, of key length
        outerPadding[i] = outerPadding[i] ^ key.at(i); // XOR operation between every byte in key and outerpadding, of key length
    }

    // result = hash ( outerPadding CONCAT hash ( innerPadding CONCAT baseString ) ).toBase64
    QByteArray total = outerPadding;
    QByteArray part = innerPadding;
    part.append(baseString);
    total.append(QCryptographicHash::hash(part, QCryptographicHash::Sha1));
    QByteArray hashed = QCryptographicHash::hash(total, QCryptographicHash::Sha1);

    return hashed.toBase64();
}

QByteArray OAuth::createOAuthHeader(const QString &method, const QString &url, QMap<QString, QString> params) {
    QString baseString;
    baseString.append(method.toUpper() + "&" + url.toUtf8().toPercentEncoding() + "&");

    QString nonce(OAuth::getNonce());
    QString timeStamp(OAuth::getTimeStamp());

    params.insert("oauth_nonce", nonce);
    params.insert("oauth_timestamp", timeStamp);
    params.insert("oauth_signature_method", "HMAC-SHA1");
    params.insert("oauth_version", "1.0");

    QMapIterator<QString, QString> iterator(params);
    iterator.next();
    baseString.append(QString(iterator.key() + "=" + iterator.value().toUtf8().toPercentEncoding()).toUtf8().toPercentEncoding());

    while (iterator.hasNext()) {
        iterator.next();
        QString key(iterator.key());

        if ((key != "oauth_consumer_secret") && (key != "oauth_token_secret")) {
            if (iterator.hasPrevious()) {
                baseString.append(QString("&" + key + "=" + iterator.value()).toUtf8().toPercentEncoding());
            }
            else {
                baseString.append(QString(key + "=" + iterator.value()).toUtf8().toPercentEncoding());
            }
        }
    }

    QByteArray key(params.value("oauth_consumer_secret").toUtf8().toPercentEncoding() + "&" + params.value("oauth_token_secret").toUtf8().toPercentEncoding());
    QByteArray signature(OAuth::createSignature(key, baseString.toUtf8()));
    QByteArray header("OAuth ");

    params.insert("oauth_signature", QString(signature));
    params.remove("oauth_consumer_secret");
    params.remove("oauth_token_secret");

    foreach (QString key, params.keys()) {
        if (!key.startsWith("oauth_")) {
            params.remove(key);
        }
    }

    QMapIterator<QString, QString> headerIterator(params);
    headerIterator.toFront();

    while (headerIterator.hasNext()) {
        headerIterator.next();

        if (headerIterator.hasNext()) {
            header.append(headerIterator.key().toUtf8() + "=\"" + headerIterator.value().toUtf8().toPercentEncoding() + "\", ");
        }
        else {
            header.append(headerIterator.key().toUtf8() + "=\"" + headerIterator.value().toUtf8().toPercentEncoding() + "\"");
        }
    }

    return header;
}

}
