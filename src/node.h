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
 * \file node.h
 */

#ifndef NODE_H
#define NODE_H

#include "qubuntuone_global.h"
#include <QObject>
#include <QDateTime>
#include <QUrl>
#include <QVariantMap>
#include <QNetworkReply>

namespace QtUbuntuOne {

class NodePrivate;

/**
 * \class Node
 * \brief Contains the metadata of an UbuntuOne node.
 *
 * Node contains the metadata of an UbuntuOne node.
 * The metadata is read-only.
 */
class QUBUNTUONESHARED_EXPORT Node : public QObject
{
    Q_OBJECT

    Q_PROPERTY(NodeType nodeType
               READ nodeType
               NOTIFY ready)
    Q_PROPERTY(QString path
               READ path
               NOTIFY ready)
    Q_PROPERTY(QString resourcePath
               READ resourcePath
               NOTIFY ready)
    Q_PROPERTY(QString contentPath
               READ contentPath
               NOTIFY ready)
    Q_PROPERTY(QString parentPath
               READ parentPath
               NOTIFY ready)
    Q_PROPERTY(QString volumePath
               READ volumePath
               NOTIFY ready)
    Q_PROPERTY(QString nodePath
               READ nodePath
               NOTIFY ready)
    Q_PROPERTY(QString name
               READ name
               NOTIFY ready)
    Q_PROPERTY(QString suffix
               READ suffix
               NOTIFY ready)
    Q_PROPERTY(QString key
               READ key
               NOTIFY ready)
    Q_PROPERTY(QDateTime whenCreated
               READ whenCreated
               NOTIFY ready)
    Q_PROPERTY(QDateTime lastModified
               READ lastModified
               NOTIFY ready)
    Q_PROPERTY(int generation
               READ generation
               NOTIFY ready)
    Q_PROPERTY(int generationCreated
               READ generationCreated
               NOTIFY ready)
    Q_PROPERTY(QByteArray hash
               READ hash
               NOTIFY ready)
    Q_PROPERTY(qint64 size
               READ size
               NOTIFY ready)
    Q_PROPERTY(bool isPublic
               READ isPublic
               NOTIFY ready)
    Q_PROPERTY(QUrl publicUrl
               READ publicUrl
               NOTIFY ready)
    Q_PROPERTY(bool hasChildren
               READ hasChildren
               NOTIFY ready)
    Q_PROPERTY(bool isRoot
               READ isRoot
               NOTIFY ready)
    Q_PROPERTY(Error error
               READ error
               NOTIFY ready)
    Q_PROPERTY(QString errorString
               READ errorString
               NOTIFY ready)
    Q_PROPERTY(int index
               READ index
               NOTIFY indexChanged)
    Q_PROPERTY(Node *parentNode
               READ parentNode
               NOTIFY parentNodeChanged)
    Q_PROPERTY(QList<Node*> childNodes
               READ childNodes
               NOTIFY childNodesChanged)
    Q_PROPERTY(int childNodeCount
               READ childNodeCount
               NOTIFY childNodesChanged)

    Q_ENUMS(NodeType Error)

    friend class Files;
    friend class NodeListPrivate;

public:
    /**
     * \enum NodeType
     */
    enum NodeType {
        File = 0,
        Directory,
        Volume
    };

    /**
     * \enum Error
     */
    enum Error {
        NoError = QNetworkReply::NoError,
        ConnectionRefusedError = QNetworkReply::ConnectionRefusedError,
        RemoteHostClosedError = QNetworkReply::RemoteHostClosedError,
        HostNotFoundError = QNetworkReply::HostNotFoundError,
        TimeoutError = QNetworkReply::TimeoutError,
        OperationCanceledError = QNetworkReply::OperationCanceledError,
        SslHandshakeFailedError = QNetworkReply::SslHandshakeFailedError,
        TemporaryNetworkFailureError = QNetworkReply::TemporaryNetworkFailureError,
        ProxyConnectionRefusedError = QNetworkReply::ProxyConnectionRefusedError,
        ProxyConnectionClosedError = QNetworkReply::ProxyConnectionClosedError,
        ProxyNotFoundError = QNetworkReply::ProxyNotFoundError,
        ProxyTimeoutError = QNetworkReply::ProxyTimeoutError,
        ProxyAuthenticationRequiredError = QNetworkReply::ProxyAuthenticationRequiredError,
        ContentAccessDenied = QNetworkReply::ContentAccessDenied,
        ContentOperationNotPermittedError = QNetworkReply::ContentOperationNotPermittedError,
        ContentNotFoundError = QNetworkReply::ContentNotFoundError,
        AuthenticationRequiredError = QNetworkReply::AuthenticationRequiredError,
        ContentReSendError = QNetworkReply::ContentReSendError,
        ProtocolUnknownError = QNetworkReply::ProtocolUnknownError,
        ProtocolInvalidOperationError = QNetworkReply::ProtocolInvalidOperationError,
        UnknownNetworkError = QNetworkReply::UnknownNetworkError,
        UnknownProxyError = QNetworkReply::UnknownProxyError,
        UnknownContentError = QNetworkReply::UnknownContentError,
        ProtocolFailure = QNetworkReply::ProtocolFailure,
        ParserError = 1001
    };

    explicit Node(QObject *parent = 0);
    explicit Node(Node *otherNode, QObject *parent = 0);
    ~Node();

    /**
     * Loads metadata from another instance of Node.
     *
     * \param Node*
     */
    Q_INVOKABLE void loadNode(Node *otherNode);

    /**
     * Returns the node type of the Node.
     *
     * \return Node::NodeType
     */
    NodeType nodeType() const;

    /**
     * Returns the path of the Node.
     *
     * \return QString
     */
    QString path() const;

    /**
     * Returns the resource path of the Node.
     *
     * \return QString
     */
    QString resourcePath() const;

    /**
     * Returns the content path of the Node.
     *
     * \return QString
     */
    QString contentPath() const;

    /**
     * Returns the parent path of the Node.
     *
     * \return QString
     */
    QString parentPath() const;

    /**
     * Returns the volume path of the Node.
     *
     * \return QString
     */
    QString volumePath() const;

    /**
     * Returns the node path of the Node (volumes only).
     *
     * \return QString
     */
    QString nodePath() const;

    /**
     * Returns the name of the Node.
     *
     * \return QString
     */
    QString name() const;

    /**
     * Returns the suffix of the Node (files only).
     *
     * \return QString
     */
    QString suffix() const;

    /**
     * Returns the unique key of the Node.
     *
     * \return QString
     */
    QString key() const;

    /**
     * Returns the creation date of the Node.
     *
     * \return QDateTime
     */
    QDateTime whenCreated() const;

    /**
     * Returns the last modified date of the Node.
     *
     * \return QDateTime
     */
    QDateTime lastModified() const;

    /**
     * Returns the generation of the Node.
     *
     * \return int
     */
    int generation() const;

    /**
     * Returns the created generation of the Node.
     *
     * \return int
     */
    int generationCreated() const;

    /**
     * Returns the sha1 hash of the Node.
     *
     * \return QByteArray
     */
    QByteArray hash() const;

    /**
     * Returns the size of the Node.
     *
     * \return qint64
     */
    qint64 size() const;

    /**
     * Returns whether the Node is public (files only).
     *
     * \return bool
     */
    bool isPublic() const;

    /**
     * Returns the public URL of the Node (files only).
     *
     * \return QUrl
     */
    QUrl publicUrl() const;

    /**
     * Returns whether the Node has children (directories only).
     *
     * \return bool
     */
    bool hasChildren() const;

    /**
     * Returns whether the Node is root.
     *
     * \return QString
     */
    bool isRoot() const;

    /**
     * Returns the error resulting from the request, or NoError if no error was reported.
     *
     * \return Error The request error.
     */
    Error error() const;

    /**
     * Returns a human-readable string detailing the error resulting from the request, or an empty string if no error was reported.
     *
     * \return QString The request error string.
     */
    QString errorString() const;

    /**
     * Returns the index of the Node in the child nodes of its parent node.
     *
     * \return int
     */
    int index();

    /**
     * Returns the parent node of the Node.
     *
     * \return Node*
     */
    Node* parentNode() const;

    /**
     * Returns the child nodes of the Node.
     *
     * \return QList<Node*>
     */
    QList<Node*> childNodes() const;

    /**
     * Returns the number of child nodes of the Node.
     *
     * \return int
     */
    int childNodeCount() const;

    /**
     * Returns the child node of the Node at the specified index.
     *
     * \param int
     *
     * \return Node*
     */
    Q_INVOKABLE Node* childNode(int i) const;

    /**
     * Appends a child node. The Node does not take ownership of
     * the child node.
     *
     * \param Node*
     */
    Q_INVOKABLE void addChildNode(Node *node);

    /**
     * Inserts a child node at the specified index.
     * The Node does not take ownership of the child node.
     *
     * \param int
     * \param Node*
     */
    Q_INVOKABLE void insertChildNode(int i, Node *node);

    /**
     * Removes and returns the specified child node.
     *
     * \param Node*
     *
     * \return Node*
     */
    Q_INVOKABLE Node* removeChildNode(Node *node);

    /**
     * Removes and returns the child node at the specified index.
     *
     * \param int
     *
     * \return Node*
     */
    Q_INVOKABLE Node* removeChildNode(int i);

public slots:
    /**
     * Cancels the request.
     */
    void cancel();

signals:
    /**
     * Emitted when the request is completed.
     *
     * \param node The Node object.
     */
    void ready(Node *node);

    /**
     * Emitted when the request is cancelled.
     *
     * \param node The Node object.
     */
    void cancelled(Node *node);

    /**
     * Emitted when the node index changes.
     */
    void indexChanged();

    /**
     * Emitted when the parent node changes.
     */
    void parentNodeChanged();

    /**
     * Emitted when the child nodes change.
     */
    void childNodesChanged();
    
private:
    explicit Node(QNetworkReply *reply, QObject *parent = 0);
    explicit Node(NodePrivate &d, QObject *parent = 0);

    QScopedPointer<NodePrivate> d_ptr;

    Q_DECLARE_PRIVATE(Node)

    Q_PRIVATE_SLOT(d_func(), void _q_onReplyFinished())
};

}

Q_DECLARE_METATYPE(QtUbuntuOne::Node*)
Q_DECLARE_METATYPE(QtUbuntuOne::Node::NodeType)
Q_DECLARE_METATYPE(QtUbuntuOne::Node::Error)

#endif // NODE_H
