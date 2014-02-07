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
 * \file files.h
 */

#ifndef FILES_H
#define FILES_H

#include "qubuntuone_global.h"
#include <QObject>
#include <QList>

namespace QtUbuntuOne {

class Node;
class NodeList;
class Reply;
class FileTransfer;
class User;

/**
 * \class Files
 * \brief Handles requests to the Ubuntu One file storage API.
 *
 * Files handles all requests to the Ubuntu One file storage API.
 */
class QUBUNTUONESHARED_EXPORT Files : public QObject
{
    Q_OBJECT

public:
    Files(QObject *parent = 0);
    ~Files();

    /**
     * Requests the root for the currently authenticated user,
     * and returns a User instance that handles the response.
     *
     * \return User* An instance of User that contains the response metadata.
     */
    Q_INVOKABLE static User* getUser();

    /**
     * Requests the list of volumes for the currently authenticated user,
     * and returns a NodeList instance that handles the response.
     *
     * \return NodeList* An instance of NodeList that contains the response metadata.
     */
    Q_INVOKABLE static NodeList* getVolumes();

    /**
     * Requests the specified volume for the currently authenticated user,
     * and returns a Node instance that handles the response.
     *
     * \param resourcePath
     *
     * \return Node* An instance of Node that contains the response metadata.
     */
    Q_INVOKABLE static Node* getVolume(const QString &resourcePath);

    /**
     * Creates a new volume for the currently authenticated user,
     * and returns a Node instance that handles the response.
     *
     * \param name
     *
     * \return Node* An instance of Node that contains the response metadata.
     */
    Q_INVOKABLE static Node* createVolume(const QString &name);

    /**
     * Deletes the specified volume for the currently authenticated user,
     * and returns a Reply instance that handles the response.
     *
     * \param resourcePath
     *
     * \return Reply* An instance of Reply that contains the response metadata.
     */
    Q_INVOKABLE static Reply* deleteVolume(const QString &resourcePath);

    /**
     * Creates a new directory for the currently authenticated user,
     * and returns a Node instance that handles the response.
     *
     * \param resourcePath
     *
     * \return Node* An instance of Node that contains the response metadata.
     */
    Q_INVOKABLE static Node* makeDirectory(const QString &resourcePath);

    /**
     * Requests the children of the specified directory for the currently authenticated user,
     * and returns a NodeList instance that handles the response.
     *
     * \param resourcePath
     *
     * \return NodeList* An instance of NodeList that contains the response metadata.
     */
    Q_INVOKABLE static NodeList* listDirectory(const QString &resourcePath);

    /**
     * Requests the specified node (file or directory) for the currently authenticated user,
     * and returns a Node instance that handles the response.
     *
     * \param resourcePath
     *
     * \return Node* An instance of Node that contains the response metadata.
     */
    Q_INVOKABLE static Node* getNode(const QString &resourcePath);

    /**
     * Moves the specified node (file or directory) for the currently authenticated user,
     * and returns a Node instance that handles the response.
     *
     * \param resourcePath
     * \param newPath
     *
     * \return Node* An instance of Node that contains the response metadata.
     */
    Q_INVOKABLE static Node* moveNode(const QString &resourcePath, const QString &newPath);

    /**
     * Deletes the specified node for the currently authenticated user,
     * and returns a Reply instance that handles the response.
     *
     * \param resourcePath
     *
     * \return Reply* An instance of Reply that contains the response metadata.
     */
    Q_INVOKABLE static Reply* deleteNode(const QString &resourcePath);

    /**
     * Requests the list of public files for the currently authenticated user,
     * and returns a NodeList instance that handles the response.
     *
     * \return NodeList* An instance of NodeList that contains the response metadata.
     */
    Q_INVOKABLE static NodeList* getPublicFiles();

    /**
     * Sets the public status of the specified file for the currently authenticated user,
     * and returns a Reply instance that handles the response.
     *
     * \param resourcePath
     * \param isPublic
     *
     * \return Node* An instance of Node that contains the response metadata.
     */
    Q_INVOKABLE static Node* setFilePublic(const QString &resourcePath, bool isPublic);

    /**
     * Starts a file upload for the currently authenticated user,
     * and returns a FileTransfer instance that performs the upload.
     *
     * \param filePath
     * \param contentType
     * \param contentPath
     * \param isPublic
     *
     * \return FileTransfer* An instance of Reply that performs the file upload.
     */
    Q_INVOKABLE static FileTransfer* uploadFile(const QString &filePath, const QString &contentType, const QString &contentPath, bool isPublic);

    /**
     * Starts a file download for the currently authenticated user,
     * and returns a FileTransfer instance that performs the upload.
     *
     * \param contentPath
     * \param localPath
     * \param overwriteExistingFile
     * \return FileTransfer* An instance of Reply that performs the file download.
     */
    Q_INVOKABLE static FileTransfer* downloadFile(const QString &contentPath, const QString &localPath, bool overwriteExistingFile);
};

}

#endif
