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

#ifndef MUSICSTREAM_P_H
#define MUSICSTREAM_P_H

#include "musicstream.h"
#include <QFile>
#include <QMutex>

namespace QtUbuntuOne {

class MusicStreamPrivate
{

public:
    MusicStreamPrivate(MusicStream *parent);
    MusicStreamPrivate(const QUrl &url, const QString &filePath, MusicStream *parent);
    virtual ~MusicStreamPrivate();

    QUrl url() const;

    QString filePath() const;

    qint64 streamSize() const;

    qint64 streamPosition() const;

    MusicStream::Status status() const;

    MusicStream::Error error() const;

    bool open(QIODevice::OpenMode mode);

    void close();

    bool seek(qint64 pos);

    bool reset();

    qint64 pos() const;

    qint64 size() const;

    void start();
    void stop();

private:
    void setUrl(const QUrl &url);

    void setFilePath(const QString &path);

    void setStreamSize(qint64 size);

    qint64 resumePosition() const;

    void setResumePosition(qint64 position);

    void setStatus(MusicStream::Status status);

    void setError(MusicStream::Error error);

    void performDownload(const QUrl &url);

    qint64 readData(char *data, qint64 maxlen);
    qint64 writeData(const char *data, qint64 len);

    void _q_onMetaDataChanged();
    void _q_onProgressChanged(qint64 transferred, qint64 total);
    void _q_onReadyRead();
    void _q_onDownloadFinished();


    MusicStream *q_ptr;

    QNetworkReply *m_reply;

    QFile m_file;

    QUrl m_url;

    QString m_filePath;

    qint64 m_size;

    qint64 m_resumePosition;

    qint64 m_transferredBytes;

    MusicStream::Status m_status;

    MusicStream::Error m_error;

    qint64 m_readPos;
    qint64 m_writePos;

    QByteArray m_buffer;

    mutable QMutex m_mutex;

    Q_DECLARE_PUBLIC(MusicStream)
};

}

#endif // MUSICSTREAM_P_H
