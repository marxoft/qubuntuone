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

#ifndef NODE_P_H
#define NODE_P_H

#include "node.h"

namespace QtUbuntuOne {

class NodePrivate
{

public:
    NodePrivate(Node *parent);
    NodePrivate(Node *otherNode, Node *parent);
    NodePrivate(QNetworkReply *reply, Node *parent);
    virtual ~NodePrivate();

    void loadNode(Node *otherNode);
    void loadNode(const QVariantMap &node);

    Node::NodeType nodeType() const;

    QString path() const;

    QString resourcePath() const;

    QString contentPath() const;

    QString parentPath() const;

    QString volumePath() const;

    QString nodePath() const;

    QString name() const;

    QString suffix() const;

    QString key() const;

    QDateTime whenCreated() const;

    QDateTime lastModified() const;

    int generation() const;

    int generationCreated() const;

    QByteArray hash() const;

    qint64 size() const;

    bool isPublic() const;

    QUrl publicUrl() const;

    bool hasChildren() const;

    bool isRoot() const;

    Node::Error error() const;
    QString errorString() const;

    int index();

    Node* parentNode() const;

    QList<Node*> childNodes() const;

    int childNodeCount() const;

    Node* childNode(int i) const;

    void addChildNode(Node *node);
    void insertChildNode(int i, Node *node);

    Node* removeChildNode(Node *node);
    Node* removeChildNode(int i);

    void cancel();

private:
    void setNodeType(Node::NodeType type);

    void setPath(const QString &path);

    void setResourcePath(const QString &path);

    void setContentPath(const QString &path);

    void setParentPath(const QString &path);

    void setVolumePath(const QString &path);

    void setNodePath(const QString &path);

    void setName(const QString &name);

    void setSuffix(const QString &suffix);

    void setKey(const QString &key);

    void setWhenCreated(const QDateTime &created);

    void setLastModified(const QDateTime &modified);

    void setGeneration(int generation);

    void setGenerationCreated(int created);

    void setHash(const QByteArray &hash);

    void setSize(qint64 size);

    void setPublic(bool isPublic);

    void setPublicUrl(const QUrl &url);

    void setHasChildren(bool hasChildren);

    void setIsRoot(bool isRoot);

    void setError(Node::Error error);
    void setErrorString(const QString &errorString);

    void setParentNode(Node *node);

    void setChildNodes(const QList<Node*> &nodes);

    void _q_onReplyFinished();

    Node *q_ptr;

    QNetworkReply *m_reply;

    Node::NodeType m_nodeType;

    QString m_path;

    QString m_resourcePath;

    QString m_contentPath;

    QString m_parentPath;

    QString m_volumePath;

    QString m_nodePath;

    QString m_name;

    QString m_suffix;

    QString m_key;

    QDateTime m_created;

    QDateTime m_modified;

    int m_generation;

    int m_generationCreated;

    QByteArray m_hash;

    qint64 m_size;

    bool m_isPublic;

    QUrl m_publicUrl;

    bool m_hasChildren;

    bool m_isRoot;

    Node::Error m_error;
    QString m_errorString;

    Node *m_parentNode;

    QList<Node*> m_childNodes;

    Q_DECLARE_PUBLIC(Node)
};

}

#endif // NODE_P_H
