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
 * \file musicstream.h
 */

#ifndef MUSICSTREAM_H
#define MUSICSTREAM_H

#include "qubuntuone_global.h"
#include <QIODevice>
#include <QUrl>
#include <QNetworkReply>

namespace QtUbuntuOne {

class MusicStreamPrivate;

/**
 * \class MusicStream
 * \brief Handles streaming of songs using the Ubuntu One music streaming API.
 *
 * MusicStream Handles streaming of songs using the Ubuntu One music streaming API by
 * downloading the stream and caching it to a local file. The local file is deleted when
 * the MusicStream instanced is destroyed. As MusicStream inherits QIODevice,
 * the stream can be accessed using the QIODevice API, and can be used
 * with QtMultimediaKit and Phonon for playback.
 */
class QUBUNTUONESHARED_EXPORT MusicStream : public QIODevice
{
    Q_OBJECT

    Q_PROPERTY(QUrl url
               READ url
               WRITE setUrl)
    Q_PROPERTY(QString filePath
               READ filePath
               WRITE setFilePath)
    Q_PROPERTY(qint64 streamSize
               READ streamSize
               NOTIFY streamSizeChanged)
    Q_PROPERTY(qint64 streamPosition
               READ streamPosition
               NOTIFY streamPositionChanged)
    Q_PROPERTY(Status status
               READ status
               NOTIFY statusChanged)
    Q_PROPERTY(Error error
               READ error
               NOTIFY statusChanged)
    Q_PROPERTY(QString errorString
               READ errorString
               NOTIFY statusChanged)

    Q_ENUMS(Status Error)

public:
    /**
     * \enum Status
     */
    enum Status {
        Stopped = 0,
        Buffering,
        Ready,
        Finished,
        Failed
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
        FileError = 1001
    };

    explicit MusicStream(QObject *parent = 0);
    explicit MusicStream(const QUrl &url, const QString &filePath, QObject *parent = 0);
    ~MusicStream();

    /**
     * Returns the stream URL.
     *
     * \return QUrl
     */
    QUrl url() const;

    /**
     * Sets the stream URL.
     *
     * \param url
     */
    void setUrl(const QUrl &url);

    /**
     * Returns the local file path to which the stream is cached.
     *
     * \return QString
     */
    QString filePath() const;

    /**
     * Sets the local file path to which the stream is cached.
     *
     * \param path
     */
    void setFilePath(const QString &path);

    /**
     * Returns the size of the stream.
     *
     * \return qint64
     */
    qint64 streamSize() const;

    /**
     * Returns the number of bytes downloaded.
     *
     * \return qint64
     */
    qint64 streamPosition() const;

    /**
     * Returns the status of the stream download.
     *
     * \return Status
     */
    Status status() const;

    /**
     * Returns the error resulting from the stream download (or NoError).
     *
     * \return Error
     */
    Error error() const;

    bool open(OpenMode mode);

    void close();

    bool seek(qint64 pos);

    bool reset();

    qint64 pos() const;

    qint64 size() const;

public slots:
    /**
     * Starts the stream download. Partially completed downloads
     * will be resumed.
     */
    void start();

    /**
     * Stops the stream download. The local file is not deleted.
     */
    void stop();

protected:
    qint64 readData(char *data, qint64 maxlen);
    qint64 writeData(const char *data, qint64 len);

signals:
    /**
     * Emitted when the size of the stream changes.
     *
     * \param size
     */
    void streamSizeChanged(qint64 size);

    /**
     * Emitted when the position of the stream changes.
     *
     * \param position
     */
    void streamPositionChanged(qint64 position);

    /**
     * Emitted when the status of the stream changes.
     *
     * \param status
     */
    void statusChanged(MusicStream::Status status);

private:
    explicit MusicStream(MusicStreamPrivate &d, QObject *parent = 0);

    QScopedPointer<MusicStreamPrivate> d_ptr;

    Q_DECLARE_PRIVATE(MusicStream)

    Q_PRIVATE_SLOT(d_func(), void _q_onMetaDataChanged())
    Q_PRIVATE_SLOT(d_func(), void _q_onProgressChanged(qint64 transferred, qint64 total))
    Q_PRIVATE_SLOT(d_func(), void _q_onReadyRead())
    Q_PRIVATE_SLOT(d_func(), void _q_onDownloadFinished())
};

}

Q_DECLARE_METATYPE(QtUbuntuOne::MusicStream::Status)
Q_DECLARE_METATYPE(QtUbuntuOne::MusicStream::Error)

#endif // MUSICSTREAM_H
