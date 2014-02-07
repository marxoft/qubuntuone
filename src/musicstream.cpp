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
 * \file musicstream.cpp
 */

#include "musicstream.h"
#include "musicstream_p.h"

namespace QtUbuntuOne {

MusicStream::MusicStream(QObject *parent) :
    QIODevice(parent),
    d_ptr(new MusicStreamPrivate(this))
{
}

MusicStream::MusicStream(const QUrl &url, const QString &filePath, QObject *parent) :
    QIODevice(parent),
    d_ptr(new MusicStreamPrivate(url, filePath, this))
{
}

MusicStream::MusicStream(MusicStreamPrivate &d, QObject *parent) :
    QIODevice(parent),
    d_ptr(&d)
{
}

MusicStream::~MusicStream() {}

/**
 * url
 */
QUrl MusicStream::url() const {
    Q_D(const MusicStream);

    return d->url();
}

/**
 * setUrl
 */
void MusicStream::setUrl(const QUrl &url) {
    Q_D(MusicStream);

    d->setUrl(url);
}

/**
 * filePath
 */
QString MusicStream::filePath() const {
    Q_D(const MusicStream);

    return d->filePath();
}

/**
 * setFilePath
 */
void MusicStream::setFilePath(const QString &path) {
    Q_D(MusicStream);

    d->setFilePath(path);
}

/**
 * streamSize
 */
qint64 MusicStream::streamSize() const {
    Q_D(const MusicStream);

    return d->streamSize();
}

/**
 * streamPosition
 */
qint64 MusicStream::streamPosition() const {
    Q_D(const MusicStream);

    return d->streamPosition();
}

/**
 * status
 */
MusicStream::Status MusicStream::status() const {
    Q_D(const MusicStream);

    return d->status();
}

/**
 * error
 */
MusicStream::Error MusicStream::error() const {
    Q_D(const MusicStream);

    return d->error();
}

bool MusicStream::open(OpenMode mode) {
    Q_D(MusicStream);

    return (d->open(QIODevice::ReadWrite)) && (QIODevice::open(mode));
}

void MusicStream::close() {
    Q_D(MusicStream);

    d->close();
}

bool MusicStream::seek(qint64 pos) {
    Q_D(MusicStream);

    return (d->seek(pos)) && (QIODevice::seek(pos));
}

bool MusicStream::reset() {
    Q_D(MusicStream);

    return (d->reset()) && (QIODevice::reset());
}

qint64 MusicStream::pos() const {
    Q_D(const MusicStream);

    return d->pos();
}

qint64 MusicStream::size() const {
    Q_D(const MusicStream);

    return d->size();
}

qint64 MusicStream::readData(char *data, qint64 maxlen) {
    Q_D(MusicStream);

    return d->readData(data, maxlen);
}

qint64 MusicStream::writeData(const char *data, qint64 len) {
    Q_D(MusicStream);

    return d->writeData(data, len);
}

/**
 * start
 */
void MusicStream::start() {
    Q_D(MusicStream);

    d->start();
}

/**
 * stop
 */
void MusicStream::stop() {
    Q_D(MusicStream);

    d->stop();
}

#include "moc_musicstream.cpp"

}
