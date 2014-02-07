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
 * \file files.cpp
 */

#include "files.h"
#include "nodelist.h"
#include "reply.h"
#include "filetransfer.h"
#include "user.h"
#include "authentication.h"
#include "urls.h"
#include "networkaccessmanager.h"

namespace QtUbuntuOne {

Files::Files(QObject *parent) :
    QObject(parent)
{
}

Files::~Files() {}

/**
 * getUser
 */
User* Files::getUser() {
    QUrl url(BASE_URL_FILES);
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", Authentication::getOAuthHeader("GET", url.toString(QUrl::RemoveQuery).toUtf8().toPercentEncoding(":/~_?="), QMap<QString, QString>()));
    request.setRawHeader("Accept", "application/json");
    request.setRawHeader("User-Agent", "QUbuntuOne (Qt)");

    return new User(NetworkAccessManager::instance()->get(request));
}

/**
 * getVolumes
 */
NodeList* Files::getVolumes() {
    QUrl url(BASE_URL_FILES + "/volumes");
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", Authentication::getOAuthHeader("GET", url.toString(QUrl::RemoveQuery).toUtf8().toPercentEncoding(":/~_?="), QMap<QString, QString>()));
    request.setRawHeader("Accept", "application/json");
    request.setRawHeader("User-Agent", "QUbuntuOne (Qt)");

    return new NodeList(NetworkAccessManager::instance()->get(request));
}

/**
 * getVolume
 */
Node* Files::getVolume(const QString &resourcePath) {
    QUrl url(BASE_URL_FILES + resourcePath);
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", Authentication::getOAuthHeader("GET", url.toString(QUrl::RemoveQuery).toUtf8().toPercentEncoding(":/~_?="), QMap<QString, QString>()));
    request.setRawHeader("Accept", "application/json");
    request.setRawHeader("User-Agent", "QUbuntuOne (Qt)");

    return new Node(NetworkAccessManager::instance()->get(request));
}

/**
 * createVolume
 */
Node* Files::createVolume(const QString &name) {
    QUrl url(BASE_URL_FILES + "/volumes/~/" + name);
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", Authentication::getOAuthHeader("PUT", url.toString(QUrl::RemoveQuery).toUtf8().toPercentEncoding(":/~_?="), QMap<QString, QString>()));
    request.setRawHeader("Accept", "application/json");
    request.setRawHeader("User-Agent", "QUbuntuOne (Qt)");

    return new Node(NetworkAccessManager::instance()->put(request, QByteArray()));
}

/**
 * deleteVolume
 */
Reply* Files::deleteVolume(const QString &resourcePath) {
    QUrl url(BASE_URL_FILES + resourcePath);
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", Authentication::getOAuthHeader("DELETE", url.toString(QUrl::RemoveQuery).toUtf8().toPercentEncoding(":/~_?="), QMap<QString, QString>()));
    request.setRawHeader("Accept", "application/json");
    request.setRawHeader("User-Agent", "QUbuntuOne (Qt)");

    return new Reply(NetworkAccessManager::instance()->deleteResource(request));
}

/**
 * makeDirectory
 */
Node* Files::makeDirectory(const QString &resourcePath) {
    QUrl url(BASE_URL_FILES + resourcePath);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", Authentication::getOAuthHeader("PUT", url.toString(QUrl::RemoveQuery).toUtf8().toPercentEncoding(":/~_?="), QMap<QString, QString>()));
    request.setRawHeader("Accept", "application/json");
    request.setRawHeader("User-Agent", "QUbuntuOne (Qt)");

    return new Node(NetworkAccessManager::instance()->put(request, "{ \"kind\": \"directory\" }"));
}

/**
 * listDirectory
 */
NodeList* Files::listDirectory(const QString &resourcePath) {
    QUrl url(BASE_URL_FILES + resourcePath);
#if QT_VERSION >= 0x050000
    QUrlQuery query(url);
    query.addQueryItem("include_children", "true");
    url.setQuery(query);
#else
    url.addQueryItem("include_children", "true");
#endif
    QMap<QString, QString> params;
    params["include_children"] = "true";
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", Authentication::getOAuthHeader("GET", url.toString(QUrl::RemoveQuery).toUtf8().toPercentEncoding(":/~_?="), params));
    request.setRawHeader("Accept", "application/json");
    request.setRawHeader("User-Agent", "QUbuntuOne (Qt)");

    return new NodeList(NetworkAccessManager::instance()->get(request));
}

/**
 * getNode
 */
Node* Files::getNode(const QString &resourcePath) {
    QUrl url(BASE_URL_FILES + resourcePath);
#if QT_VERSION >= 0x050000
    QUrlQuery query(url);
    query.addQueryItem("include_children", "false");
    url.setQuery(query);
#else
    url.addQueryItem("include_children", "false");
#endif
    QMap<QString, QString> params;
    params["include_children"] = "false";
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", Authentication::getOAuthHeader("GET", url.toString(QUrl::RemoveQuery).toUtf8().toPercentEncoding(":/~_?="), params));
    request.setRawHeader("Accept", "application/json");
    request.setRawHeader("User-Agent", "QUbuntuOne (Qt)");

    return new Node(NetworkAccessManager::instance()->get(request));
}

/**
 * moveNode
 */
Node* Files::moveNode(const QString &resourcePath, const QString &newPath) {
    QUrl url(BASE_URL_FILES + resourcePath);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", Authentication::getOAuthHeader("PUT", url.toString(QUrl::RemoveQuery).toUtf8().toPercentEncoding(":/~_?="), QMap<QString, QString>()));
    request.setRawHeader("Accept", "application/json");
    request.setRawHeader("User-Agent", "QUbuntuOne (Qt)");

    return new Node(NetworkAccessManager::instance()->put(request, "{ \"path\": \"" + newPath.toUtf8() + "\" }"));
}

/**
 * deleteNode
 */
Reply* Files::deleteNode(const QString &resourcePath) {
    QUrl url(BASE_URL_FILES + resourcePath);
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", Authentication::getOAuthHeader("DELETE", url.toString(QUrl::RemoveQuery).toUtf8().toPercentEncoding(":/~_?="), QMap<QString, QString>()));
    request.setRawHeader("Accept", "application/json");
    request.setRawHeader("User-Agent", "QUbuntuOne (Qt)");

    return new Reply(NetworkAccessManager::instance()->deleteResource(request));
}

/**
 * getPublicFiles
 */
NodeList* Files::getPublicFiles() {
    QUrl url(BASE_URL_FILES + "/public_files");
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", Authentication::getOAuthHeader("GET", url.toString(QUrl::RemoveQuery).toUtf8().toPercentEncoding(":/~_?="), QMap<QString, QString>()));
    request.setRawHeader("Accept", "application/json");
    request.setRawHeader("User-Agent", "QUbuntuOne (Qt)");

    return new NodeList(NetworkAccessManager::instance()->get(request));
}

/**
 * setFilePublic
 */
Node* Files::setFilePublic(const QString &resourcePath, bool isPublic) {
    QUrl url(BASE_URL_FILES + resourcePath);
    QString json = QString("{ \"is_public\": %1 }").arg(isPublic ? "true" : "false");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", Authentication::getOAuthHeader("PUT", url.toString(QUrl::RemoveQuery).toUtf8().toPercentEncoding(":/~_?="), QMap<QString, QString>()));
    request.setRawHeader("Accept", "application/json");
    request.setRawHeader("User-Agent", "QUbuntuOne (Qt)");

    return new Node(NetworkAccessManager::instance()->put(request, json.toUtf8()));
}

/**
 * uploadFile
 */
FileTransfer* Files::uploadFile(const QString &filePath, const QString &contentType, const QString &contentPath, bool isPublic) {
    FileTransfer *transfer = new FileTransfer;
    transfer->setTransferType(FileTransfer::Upload);
    transfer->setFilePath(filePath);
    transfer->setContentType(contentType.isEmpty() ? "application/octet-stream" : contentType);
    transfer->setContentPath(contentPath);
    transfer->setPublic(isPublic);
    transfer->start();

    return transfer;
}

/**
 * downloadFile
 */
FileTransfer* Files::downloadFile(const QString &contentPath, const QString &localPath, bool overwriteExistingFile) {
    FileTransfer *transfer = new FileTransfer;
    transfer->setTransferType(FileTransfer::Download);
    transfer->setContentPath(contentPath);
    transfer->setFilePath(localPath);
    transfer->setOverwriteExistingFile(overwriteExistingFile);
    transfer->start();

    return transfer;
}

}
