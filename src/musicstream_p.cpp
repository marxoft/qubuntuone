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

#include "musicstream_p.h"
#include "authentication.h"
#include "networkaccessmanager.h"
#include <QDir>
#include <QDebug>

namespace QtUbuntuOne {

static const int BUFFER_SIZE = 1024 * 100;

MusicStreamPrivate::MusicStreamPrivate(MusicStream *parent) :
    q_ptr(parent),
    m_reply(0),
    m_size(0),
    m_resumePosition(0),
    m_transferredBytes(0),
    m_status(MusicStream::Stopped),
    m_error(MusicStream::NoError),
    m_readPos(0),
    m_writePos(0)
{
}

MusicStreamPrivate::MusicStreamPrivate(const QUrl &url, const QString &filePath, MusicStream *parent) :
    q_ptr(parent),
    m_reply(0),
    m_file(filePath),
    m_url(url),
    m_size(0),
    m_resumePosition(0),
    m_transferredBytes(0),
    m_status(MusicStream::Stopped),
    m_error(MusicStream::NoError),
    m_readPos(0),
    m_writePos(0)
{
}

MusicStreamPrivate::~MusicStreamPrivate() {
    QMutexLocker locker(&m_mutex);

    m_file.close();

    if (m_file.exists()) {
        m_file.remove();
    }

    if (m_reply) {
        delete m_reply;
        m_reply = 0;
    }
}

QUrl MusicStreamPrivate::url() const {
    return m_url;
}

void MusicStreamPrivate::setUrl(const QUrl &url) {
    m_url = url;
}

QString MusicStreamPrivate::filePath() const {
    return m_file.fileName();
}

void MusicStreamPrivate::setFilePath(const QString &path) {
    m_file.setFileName(path);
}

qint64 MusicStreamPrivate::streamSize() const {
    return m_size;
}

void MusicStreamPrivate::setStreamSize(qint64 size) {
    m_size = size;
}

qint64 MusicStreamPrivate::streamPosition() const {
    return m_resumePosition + m_transferredBytes;
}

qint64 MusicStreamPrivate::resumePosition() const {
    return m_resumePosition;
}

void MusicStreamPrivate::setResumePosition(qint64 position) {
    m_resumePosition = position;
}

MusicStream::Status MusicStreamPrivate::status() const {
    return m_status;
}

void MusicStreamPrivate::setStatus(MusicStream::Status status) {
    Q_Q(MusicStream);

    if (status != this->status()) {
        m_status = status;
        emit q->statusChanged(status);
    }
}

MusicStream::Error MusicStreamPrivate::error() const {
    return m_error;
}

void MusicStreamPrivate::setError(MusicStream::Error error) {
    m_error = error;
}

bool MusicStreamPrivate::open(QIODevice::OpenMode mode) {
    QMutexLocker locker(&m_mutex);

    return (m_file.isOpen()) || (m_file.open(mode | QIODevice::Unbuffered));
}

void MusicStreamPrivate::close() {
    QMutexLocker locker(&m_mutex);

    m_file.close();
}

bool MusicStreamPrivate::seek(qint64 pos) {
    QMutexLocker locker(&m_mutex);

    qDebug() << "MusicStreamPrivate::seek";

    if (m_file.seek(pos)) {
        m_readPos = pos;
        return true;
    }

    qDebug() << "MusicStreamPrivate::seek failed";

    return false;
}

bool MusicStreamPrivate::reset() {
    return this->seek(0);
}

qint64 MusicStreamPrivate::pos() const {
    return m_readPos;
}

qint64 MusicStreamPrivate::size() const {
    qDebug() << "MusicStreamPrivate::size";

    return this->streamPosition();
}

qint64 MusicStreamPrivate::readData(char *data, qint64 maxlen) {
    QMutexLocker locker(&m_mutex);

    qDebug() << "MusicStreamPrivate::readData";

    if (!m_file.seek(m_readPos)) {
        return -1;
    }

    qint64 bytes = m_file.read(data, maxlen);

    if (bytes > 0) {
        m_readPos += bytes;
    }

    qDebug() << "MusicStreamPrivate::readData " << bytes;

    return bytes;
}

qint64 MusicStreamPrivate::writeData(const char *data, qint64 len) {
    Q_Q(MusicStream);

    QMutexLocker locker(&m_mutex);

    if (!m_file.seek(m_writePos)) {
        return -1;
    }

    qint64 bytes = m_file.write(data, len);

    if (bytes > 0) {
        m_writePos += bytes;
        emit q->bytesWritten(bytes);
    }

    qDebug() << "MusicStreamPrivate::writeData " << bytes;

    return bytes;
}

void MusicStreamPrivate::start() {
    Q_Q(MusicStream);

    if (!QDir().mkpath(this->filePath().left(this->filePath().lastIndexOf('/')))) {
        q->setErrorString(QObject::tr("Cannot create directory %1").arg(this->filePath().left(this->filePath().lastIndexOf('/'))));
        this->setError(MusicStream::FileError);
        this->setStatus(MusicStream::Failed);
        return;
    }

    if (!this->open(QIODevice::ReadWrite)) {
        q->setErrorString(QObject::tr("Cannot open file %1: %2").arg(this->filePath()).arg(m_file.errorString()));
        this->setError(MusicStream::FileError);
        this->setStatus(MusicStream::Failed);
        return;
    }

    this->setResumePosition(m_file.size());
    this->performDownload(this->url());

    if (this->streamPosition() > BUFFER_SIZE) {
        this->setStatus(MusicStream::Ready);
    }
    else {
        this->setStatus(MusicStream::Buffering);
    }
}

void MusicStreamPrivate::stop() {
    if (m_reply) {
        m_reply->abort();
    }
}

void MusicStreamPrivate::performDownload(const QUrl &url) {
    Q_Q(MusicStream);

    QNetworkRequest request(url);

    if (this->resumePosition() > 0) {
        request.setRawHeader("Range", QByteArray::number(this->resumePosition()) + "-");
    }

    request.setRawHeader("Authorization", Authentication::getOAuthHeader("GET", url.toString(QUrl::RemoveQuery), QMap<QString, QString>()));
    request.setRawHeader("User-Agent", "QUbuntuOne (Qt)");
    m_reply = NetworkAccessManager::instance()->get(request);
    q->connect(m_reply, SIGNAL(downloadProgress(qint64,qint64)), q, SLOT(_q_onProgressChanged(qint64,qint64)));
    q->connect(m_reply, SIGNAL(readyRead()), q, SLOT(_q_onReadyRead()));
    q->connect(m_reply, SIGNAL(finished()), q, SLOT(_q_onDownloadFinished()));

    if (this->size() <= 0) {
        q->connect(m_reply, SIGNAL(metaDataChanged()), q, SLOT(_q_onMetaDataChanged()));
    }
}

void MusicStreamPrivate::_q_onMetaDataChanged() {
    if (m_reply) {
        qint64 size = m_reply->header(QNetworkRequest::ContentLengthHeader).toLongLong();

        if (size <= 0) {
            size = m_reply->rawHeader("Content-Length").toLongLong();
        }

        if (size > 0) {
            this->setStreamSize(size);
        }
    }
}

void MusicStreamPrivate::_q_onProgressChanged(qint64 transferred, qint64 total) {
    Q_UNUSED(total)

    Q_Q(MusicStream);

    m_transferredBytes = transferred;
    emit q->streamPositionChanged(this->streamPosition());
}

void MusicStreamPrivate::_q_onReadyRead() {
    Q_Q(MusicStream);

    if (m_reply) {
        m_buffer += m_reply->readAll();

        if (m_buffer.size() > BUFFER_SIZE) {
            this->writeData(m_buffer.data(), qint64(m_buffer.size()));
            m_buffer.clear();
            emit q->readyRead();

            switch (this->status()) {
            case MusicStream::Buffering:
                this->setStatus(MusicStream::Ready);
                return;
            default:
                return;
            }
        }
    }
}

void MusicStreamPrivate::_q_onDownloadFinished() {
    Q_Q(MusicStream);

    if (m_reply) {
        QUrl redirect = m_reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();

        if (!redirect.isEmpty()) {
            m_reply->deleteLater();
            m_reply = 0;
            this->performDownload(redirect);
            return;
        }

        switch (m_reply->error()) {
        case QNetworkReply::NoError:
            break;
        case QNetworkReply::OperationCanceledError:
            m_reply->deleteLater();
            m_reply = 0;
            this->setStatus(MusicStream::Stopped);
            return;
        default:
            this->close();
            q->setErrorString(m_reply->errorString());
            this->setError(MusicStream::Error(m_reply->error()));
            this->setStatus(MusicStream::Failed);
            m_reply->deleteLater();
            m_reply = 0;
            return;
        }
    }

    m_reply->deleteLater();
    m_reply = 0;

    this->setStatus(MusicStream::Finished);
}

}
