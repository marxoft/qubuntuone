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
 * \file filetransfer.cpp
 */

#include "filetransfer.h"
#include "filetransfer_p.h"

namespace QtUbuntuOne {

FileTransfer::FileTransfer(QObject *parent) :
    QObject(parent),
    d_ptr(new FileTransferPrivate(this))
{
}

FileTransfer::FileTransfer(TransferType transferType, const QString &contentPath, const QString &filePath, QObject *parent) :
    QObject(parent),
    d_ptr(new FileTransferPrivate(transferType, contentPath, filePath, this))
{
}

FileTransfer::FileTransfer(FileTransferPrivate &d, QObject *parent) :
    QObject(parent),
    d_ptr(&d)
{
}

FileTransfer::~FileTransfer() {}

/**
 * transferType
 */
FileTransfer::TransferType FileTransfer::transferType() const {
    Q_D(const FileTransfer);

    return d->transferType();
}

/**
 * setTransferType
 */
void FileTransfer::setTransferType(TransferType type) {
    Q_D(FileTransfer);

    d->setTransferType(type);
}

/**
 * id
 */
QString FileTransfer::id() const {
    Q_D(const FileTransfer);

    return d->id();
}

/**
 * url
 */
QUrl FileTransfer::url() const {
    Q_D(const FileTransfer);

    return d->url();
}

/**
 * contentPath
 */
QString FileTransfer::contentPath() const {
    Q_D(const FileTransfer);

    return d->contentPath();
}

/**
 * setContentPath
 */
void FileTransfer::setContentPath(const QString &path) {
    Q_D(FileTransfer);

    d->setContentPath(path);
}

/**
 * filePath
 */
QString FileTransfer::filePath() const {
    Q_D(const FileTransfer);

    return d->filePath();
}

/**
 * setFilePath
 */
void FileTransfer::setFilePath(const QString &path) {
    Q_D(FileTransfer);

    d->setFilePath(path);
}

/**
 * contentType
 */
QString FileTransfer::contentType() const {
    Q_D(const FileTransfer);

    return d->contentType();
}

/**
 * setContentType
 */
void FileTransfer::setContentType(const QString &type) {
    Q_D(FileTransfer);

    d->setContentType(type);
}

/**
 * size
 */
qint64 FileTransfer::size() const {
    Q_D(const FileTransfer);

    return d->size();
}

/**
 * position
 */
qint64 FileTransfer::position() const {
    Q_D(const FileTransfer);

    return d->position();
}

/**
 * progress
 */
int FileTransfer::progress() const {
    Q_D(const FileTransfer);

    return d->progress();
}

/**
 * overwriteExistingFile
 */
bool FileTransfer::overwriteExistingFile() const {
    Q_D(const FileTransfer);

    return d->overwriteExistingFile();
}

/**
 * setOverwriteExistingFile
 */
void FileTransfer::setOverwriteExistingFile(bool overwrite) {
    Q_D(FileTransfer);

    d->setOverwriteExistingFile(overwrite);
}

/**
 * isPublic
 */
bool FileTransfer::isPublic() const {
    Q_D(const FileTransfer);

    return d->isPublic();
}

/**
 * setPublic
 */
void FileTransfer::setPublic(bool isPublic) {
    Q_D(FileTransfer);

    d->setPublic(isPublic);
}

/**
 * status
 */
FileTransfer::Status FileTransfer::status() const {
    Q_D(const FileTransfer);

    return d->status();
}

/**
 * statusString
 */
QString FileTransfer::statusString() const {
    Q_D(const FileTransfer);

    return d->statusString();
}

/**
 * error
 */
FileTransfer::Error FileTransfer::error() const {
    Q_D(const FileTransfer);

    return d->error();
}

/**
 * errorString
 */
QString FileTransfer::errorString() const {
    Q_D(const FileTransfer);

    return d->errorString();
}

/**
 * start
 */
void FileTransfer::start() {
    Q_D(FileTransfer);

    d->start();
}

/**
 * queue
 */
void FileTransfer::queue() {
    Q_D(FileTransfer);

    d->queue();
}

/**
 * pause
 */
void FileTransfer::pause() {
    Q_D(FileTransfer);

    d->pause();
}

/**
 * cancel
 */
void FileTransfer::cancel() {
    Q_D(FileTransfer);

    d->cancel();
}

#include "moc_filetransfer.cpp"

}
