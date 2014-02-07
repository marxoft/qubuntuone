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
 * node.cpp
 */

#include "node.h"
#include "node_p.h"

namespace QtUbuntuOne {

Node::Node(QObject *parent) :
    QObject(parent),
    d_ptr(new NodePrivate(this))
{
}

Node::Node(Node *otherNode, QObject *parent) :
    QObject(parent),
    d_ptr(new NodePrivate(otherNode, this))
{
}

Node::Node(QNetworkReply *reply, QObject *parent) :
    QObject(parent),
    d_ptr(new NodePrivate(reply, this))
{
}

Node::Node(NodePrivate &d, QObject *parent) :
    QObject(parent),
    d_ptr(&d)
{
}

Node::~Node() {}

/**
 * loadNode
 */
void Node::loadNode(Node *otherNode) {
    Q_D(Node);

    d->loadNode(otherNode);
}

/**
 * nodeType
 */
Node::NodeType Node::nodeType() const {
    Q_D(const Node);

    return d->nodeType();
}

/**
 * path
 */
QString Node::path() const {
    Q_D(const Node);

    return d->path();
}

/**
 * resourcePath
 */
QString Node::resourcePath() const {
    Q_D(const Node);

    return d->resourcePath();
}

/**
 * contentPath
 */
QString Node::contentPath() const {
    Q_D(const Node);

    return d->contentPath();
}

/**
 * parentPath
 */
QString Node::parentPath() const {
    Q_D(const Node);

    return d->parentPath();
}

/**
 * volumePath
 */
QString Node::volumePath() const {
    Q_D(const Node);

    return d->volumePath();
}

/**
 * nodePath
 */
QString Node::nodePath() const {
    Q_D(const Node);

    return d->nodePath();
}

/**
 * name
 */
QString Node::name() const {
    Q_D(const Node);

    return d->name();
}

/**
 * suffix
 */
QString Node::suffix() const {
    Q_D(const Node);

    return d->suffix();
}

/**
 * key
 */
QString Node::key() const {
    Q_D(const Node);

    return d->key();
}

/**
 * whenCreated
 */
QDateTime Node::whenCreated() const {
    Q_D(const Node);

    return d->whenCreated();
}

/**
 * lastModified
 */
QDateTime Node::lastModified() const {
    Q_D(const Node);

    return d->lastModified();
}

/**
 * generation
 */
int Node::generation() const {
    Q_D(const Node);

    return d->generation();
}

/**
 * generationCreated
 */
int Node::generationCreated() const {
    Q_D(const Node);

    return d->generationCreated();
}

/**
 * hash
 */
QByteArray Node::hash() const {
    Q_D(const Node);

    return d->hash();
}

/**
 * size
 */
qint64 Node::size() const {
    Q_D(const Node);

    return d->size();
}

/**
 * isPublic
 */
bool Node::isPublic() const {
    Q_D(const Node);

    return d->isPublic();
}

/**
 * publicUrl
 */
QUrl Node::publicUrl() const {
    Q_D(const Node);

    return d->publicUrl();
}

/**
 * hasChildren
 */
bool Node::hasChildren() const {
    Q_D(const Node);

    return d->hasChildren();
}

/**
 * isRoot
 */
bool Node::isRoot() const {
    Q_D(const Node);

    return d->isRoot();
}

/**
 * error
 */
Node::Error Node::error() const {
    Q_D(const Node);

    return d->error();
}

/**
 * errorString
 */
QString Node::errorString() const {
    Q_D(const Node);

    return d->errorString();
}

/**
 * index
 */
int Node::index() {
    Q_D(Node);

    return d->index();
}

/**
 * parentNode
 */
Node* Node::parentNode() const {
    Q_D(const Node);

    return d->parentNode();
}

/**
 * childNodes
 */
QList<Node*> Node::childNodes() const {
    Q_D(const Node);

    return d->childNodes();
}

/**
 * childNodeCount
 */
int Node::childNodeCount() const {
    Q_D(const Node);

    return d->childNodeCount();
}

/**
 * childNode
 */
Node* Node::childNode(int i) const {
    Q_D(const Node);

    return d->childNode(i);
}

/**
 * addChildNode
 */
void Node::addChildNode(Node *node) {
    Q_D(Node);

    d->addChildNode(node);
}

/**
 * insertChildNode
 */
void Node::insertChildNode(int i, Node *node) {
    Q_D(Node);

    d->insertChildNode(i, node);
}

/**
 * removeChildNode
 */
Node* Node::removeChildNode(Node *node) {
    Q_D(Node);

    return d->removeChildNode(node);
}

/**
 * removeChildNode
 */
Node* Node::removeChildNode(int i) {
    Q_D(Node);

    return d->removeChildNode(i);
}

/**
 * cancel
 */
void Node::cancel() {
    Q_D(Node);

    d->cancel();
}

#include "moc_node.cpp"

}
