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

#include "node_p.h"
#include "json.h"

namespace QtUbuntuOne {

NodePrivate::NodePrivate(Node *parent) :
    q_ptr(parent),
    m_reply(0),
    m_nodeType(Node::Volume),
    m_generation(0),
    m_generationCreated(0),
    m_size(0),
    m_isPublic(false),
    m_hasChildren(false),
    m_isRoot(true),
    m_error(Node::NoError),
    m_parentNode(0)
{
}

NodePrivate::NodePrivate(Node *otherNode, Node *parent) :
    q_ptr(parent),
    m_reply(0),
    m_nodeType(otherNode->nodeType()),
    m_path(otherNode->path()),
    m_resourcePath(otherNode->resourcePath()),
    m_contentPath(otherNode->contentPath()),
    m_parentPath(otherNode->parentPath()),
    m_volumePath(otherNode->volumePath()),
    m_nodePath(otherNode->nodePath()),
    m_name(otherNode->name()),
    m_suffix(otherNode->suffix()),
    m_key(otherNode->key()),
    m_created(otherNode->whenCreated()),
    m_modified(otherNode->lastModified()),
    m_generation(otherNode->generation()),
    m_generationCreated(otherNode->generationCreated()),
    m_hash(otherNode->hash()),
    m_size(otherNode->size()),
    m_isPublic(otherNode->isPublic()),
    m_publicUrl(otherNode->publicUrl()),
    m_hasChildren(otherNode->hasChildren()),
    m_isRoot(otherNode->isRoot()),
    m_error(otherNode->error()),
    m_errorString(otherNode->errorString()),
    m_parentNode(otherNode->parentNode()),
    m_childNodes(otherNode->childNodes())
{
    Q_Q(Node);

    emit q->ready(q);
}

NodePrivate::NodePrivate(QNetworkReply *reply, Node *parent) :
    q_ptr(parent),
    m_reply(reply),
    m_nodeType(Node::Volume),
    m_generation(0),
    m_generationCreated(0),
    m_size(0),
    m_isPublic(false),
    m_hasChildren(false),
    m_isRoot(true),
    m_error(Node::NoError),
    m_parentNode(0)
{
    Q_Q(Node);

    if (m_reply) {
        q->connect(m_reply, SIGNAL(finished()), q, SLOT(_q_onReplyFinished()));
    }
}

NodePrivate::~NodePrivate() {
    if (m_reply) {
        delete m_reply;
        m_reply = 0;
    }
}

void NodePrivate::loadNode(Node *otherNode) {
    Q_Q(Node);

    this->setNodeType(otherNode->nodeType());
    this->setPath(otherNode->path());
    this->setResourcePath(otherNode->resourcePath());
    this->setContentPath(otherNode->contentPath());
    this->setParentPath(otherNode->parentPath());
    this->setVolumePath(otherNode->volumePath());
    this->setNodePath(otherNode->nodePath());
    this->setName(otherNode->name());
    this->setSuffix(otherNode->suffix());
    this->setKey(otherNode->key());
    this->setWhenCreated(otherNode->whenCreated());
    this->setLastModified(otherNode->lastModified());
    this->setGeneration(otherNode->generation());
    this->setGenerationCreated(otherNode->generationCreated());
    this->setHash(otherNode->hash());
    this->setSize(otherNode->size());
    this->setPublic(otherNode->isPublic());
    this->setPublicUrl(otherNode->publicUrl());
    this->setHasChildren(otherNode->hasChildren());
    this->setIsRoot(otherNode->isRoot());
    this->setError(otherNode->error());
    this->setErrorString(otherNode->errorString());
    this->setParentNode(otherNode->parentNode());
    this->setChildNodes(otherNode->childNodes());

    emit q->ready(q);
}

void NodePrivate::loadNode(const QVariantMap &node) {
    Q_Q(Node);

    QString kind = node.value("kind").toString();

    if (kind == "file") {
        this->setNodeType(Node::File);
    }
    else if (kind == "directory") {
        this->setNodeType(Node::Directory);
    }

    this->setPath(node.value("path").toString());
    this->setResourcePath(node.value("resource_path").toString());
    this->setContentPath(node.value("content_path").toString());
    this->setParentPath(node.value("parent_path").toString());
    this->setVolumePath(node.value("volume_path").toString());
    this->setNodePath(node.value("node_path").toString());
    this->setName(this->path().mid(this->path().lastIndexOf('/') + 1));
    this->setSuffix(this->name().contains('.') ? this->name().mid(this->name().lastIndexOf('.') + 1) : QString());
    this->setKey(node.value("key").toString());
    this->setWhenCreated(QDateTime::fromString(node.value("when_created").toString(), Qt::ISODate));
    this->setLastModified(QDateTime::fromString(node.value("when_changed").toString(), Qt::ISODate));
    this->setGeneration(node.value("generation").toInt());
    this->setGenerationCreated(node.value("generation_created").toInt());
    this->setHash(node.value("hash").toByteArray());
    this->setSize(node.value("size").toLongLong());
    this->setPublic(node.value("is_public").toBool());
    this->setPublicUrl(node.value("public_url").toUrl());
    this->setHasChildren(node.value("has_children").toBool());
    this->setIsRoot(node.value("is_root").toBool());
    this->setError(Node::NoError);
    this->setErrorString(QString());

    emit q->ready(q);
}

Node::NodeType NodePrivate::nodeType() const {
    return m_nodeType;
}

void NodePrivate::setNodeType(Node::NodeType type) {
    m_nodeType = type;
}

QString NodePrivate::path() const {
    return m_path;
}

void NodePrivate::setPath(const QString &path) {
    m_path = path;
}

QString NodePrivate::resourcePath() const {
    return m_resourcePath;
}

void NodePrivate::setResourcePath(const QString &path) {
    m_resourcePath = path;
}

QString NodePrivate::contentPath() const {
    return m_contentPath;
}

void NodePrivate::setContentPath(const QString &path) {
    m_contentPath = path;
}

QString NodePrivate::parentPath() const {
    return m_parentPath;
}

void NodePrivate::setParentPath(const QString &path) {
    m_parentPath = path;
}

QString NodePrivate::volumePath() const {
    return m_volumePath;
}

void NodePrivate::setVolumePath(const QString &path) {
    m_volumePath = path;
}

QString NodePrivate::nodePath() const {
    return m_nodePath;
}

void NodePrivate::setNodePath(const QString &path) {
    m_nodePath = path;
}

QString NodePrivate::name() const {
    return m_name;
}

void NodePrivate::setName(const QString &name) {
    m_name = name;
}

QString NodePrivate::suffix() const {
    return m_suffix;
}

void NodePrivate::setSuffix(const QString &suffix) {
    m_suffix = suffix;
}

QString NodePrivate::key() const {
    return m_key;
}

void NodePrivate::setKey(const QString &key) {
    m_key = key;
}

QDateTime NodePrivate::whenCreated() const {
    return m_created;
}

void NodePrivate::setWhenCreated(const QDateTime &created) {
    m_created = created;
}

QDateTime NodePrivate::lastModified() const {
    return m_modified;
}

void NodePrivate::setLastModified(const QDateTime &modified) {
    m_modified = modified;
}

int NodePrivate::generation() const {
    return m_generation;
}

void NodePrivate::setGeneration(int generation) {
    m_generation = generation;
}

int NodePrivate::generationCreated() const {
    return m_generationCreated;
}

void NodePrivate::setGenerationCreated(int created) {
    m_generationCreated = created;
}

QByteArray NodePrivate::hash() const {
    return m_hash;
}

void NodePrivate::setHash(const QByteArray &hash) {
    m_hash = hash;
}

qint64 NodePrivate::size() const {
    return m_size;
}

void NodePrivate::setSize(qint64 size) {
    m_size = size;
}

bool NodePrivate::isPublic() const {
    return m_isPublic;
}

void NodePrivate::setPublic(bool isPublic) {
    m_isPublic = isPublic;
}

QUrl NodePrivate::publicUrl() const {
    return m_publicUrl;
}

void NodePrivate::setPublicUrl(const QUrl &url) {
    m_publicUrl = url;
}

bool NodePrivate::hasChildren() const {
    return m_hasChildren;
}

void NodePrivate::setHasChildren(bool hasChildren) {
    m_hasChildren = hasChildren;
}

bool NodePrivate::isRoot() const {
    return m_isRoot;
}

void NodePrivate::setIsRoot(bool isRoot) {
    m_isRoot = isRoot;
}

Node::Error NodePrivate::error() const {
    return m_error;
}

void NodePrivate::setError(Node::Error error) {
    m_error = error;
}

QString NodePrivate::errorString() const {
    return m_errorString;
}

void NodePrivate::setErrorString(const QString &errorString) {
    m_errorString = errorString;
}

int NodePrivate::index() {
    Q_Q(Node);

    if (Node *node = this->parentNode()) {
        return node->childNodes().indexOf(q);
    }

    return -1;
}

Node* NodePrivate::parentNode() const {
    return m_parentNode;
}

void NodePrivate::setParentNode(Node *node) {
    Q_Q(Node);

    if (node != this->parentNode()) {
        m_parentNode = node;
        emit q->parentNodeChanged();
    }
}

QList<Node*> NodePrivate::childNodes() const {
    return m_childNodes;
}

void NodePrivate::setChildNodes(const QList<Node *> &nodes) {
    Q_Q(Node);

    m_childNodes = nodes;
    emit q->childNodesChanged();
}

int NodePrivate::childNodeCount() const {
    return m_childNodes.size();
}

Node* NodePrivate::childNode(int i) const {
    if ((i >= 0) && (i < m_childNodes.size())) {
        return m_childNodes.at(i);
    }

    return 0;
}

void NodePrivate::addChildNode(Node *node) {
    Q_Q(Node);

    m_childNodes.append(node);
    node->d_func()->setParentNode(q);
    emit q->childNodesChanged();
}

void NodePrivate::insertChildNode(int i, Node *node) {
    Q_Q(Node);

    if ((i >= 0) && (i < m_childNodes.size())) {
        m_childNodes.insert(i, node);
        node->d_func()->setParentNode(q);

        emit q->childNodesChanged();
    }
    else {
        this->addChildNode(node);
    }
}

Node* NodePrivate::removeChildNode(Node *node) {
    return this->removeChildNode(m_childNodes.indexOf(node));
}

Node* NodePrivate::removeChildNode(int i) {
    Q_Q(Node);

    if ((i >= 0) && (i < m_childNodes.size())) {
        Node* node = m_childNodes.takeAt(i);
        node->d_func()->setParentNode(0);
        emit q->childNodesChanged();
        return node;
    }

    return 0;
}

void NodePrivate::cancel() {
    if (m_reply) {
        m_reply->abort();
    }
}

void NodePrivate::_q_onReplyFinished() {
    Q_Q(Node);

    if (m_reply) {
        switch (m_reply->error()) {
        case QNetworkReply::NoError:
            break;
        case QNetworkReply::OperationCanceledError:
            emit q->cancelled(q);
            return;
        default:
            this->setError(Node::Error(m_reply->error()));
            this->setErrorString(m_reply->errorString());
            emit q->ready(q);
            return;
        }

        QString response(m_reply->readAll());
        QVariantMap result = QtJson::Json::parse(response).toMap();

        if (!result.isEmpty()) {
            this->loadNode(result);
        }
        else {
            this->setError(Node::ParserError);
            this->setErrorString(QObject::tr("Cannot parse server response"));
            emit q->ready(q);
        }

        m_reply->deleteLater();
        m_reply = 0;
    }
}

}
