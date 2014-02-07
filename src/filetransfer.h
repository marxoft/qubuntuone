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
 * \file filetransfer.h
 */

#ifndef FILETRANSFER_H
#define FILETRANSFER_H

#include "qubuntuone_global.h"
#include <QObject>
#include <QNetworkReply>

namespace QtUbuntuOne {

class Node;
class FileTransferPrivate;

/**
 * \class FileTransfer
 * \brief Performs file transfers.
 *
 * FileTransfer performs file transfers and provides notifications
 * of progress and status changes.
 */
class QUBUNTUONESHARED_EXPORT FileTransfer : public QObject
{
    Q_OBJECT

    Q_PROPERTY(TransferType transferType
               READ transferType
               WRITE setTransferType)
    Q_PROPERTY(QString id
               READ id)
    Q_PROPERTY(QUrl url
               READ url)
    Q_PROPERTY(QString contentPath
               READ contentPath
               WRITE setContentPath)
    Q_PROPERTY(QString filePath
               READ filePath
               WRITE setFilePath)
    Q_PROPERTY(QString contentType
               READ contentType
               WRITE setContentType)
    Q_PROPERTY(qint64 size
               READ size
               NOTIFY sizeChanged)
    Q_PROPERTY(qint64 position
               READ position
               NOTIFY progressChanged)
    Q_PROPERTY(int progress
               READ progress
               NOTIFY progressChanged)
    Q_PROPERTY(bool overwriteExistingFile
               READ overwriteExistingFile
               WRITE setOverwriteExistingFile)
    Q_PROPERTY(bool isPublic
               READ isPublic
               WRITE setPublic)
    Q_PROPERTY(Status status
               READ status
               NOTIFY statusChanged)
    Q_PROPERTY(QString statusString
               READ statusString
               NOTIFY statusChanged)
    Q_PROPERTY(Error error
               READ error
               NOTIFY statusChanged)
    Q_PROPERTY(QString errorString
               READ errorString
               NOTIFY statusChanged)

    Q_ENUMS(TransferType Status Error)

public:
    /**
     * \enum TransferType
     */
    enum TransferType {
        Download = 0,
        Upload
    };

    /**
     * \enum Status
     */
    enum Status {
        Paused = 0,
        Cancelled,
        Failed,
        Completed,
        Queued,
        Connecting,
        Downloading,
        Uploading,
        Unknown
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
        ResourceError = 1001,
        FileError = 1002,
        ParserError = 1003
    };

    explicit FileTransfer(QObject *parent = 0);
    explicit FileTransfer(TransferType transferType, const QString &contentPath, const QString &filePath, QObject *parent = 0);
    ~FileTransfer();

    /**
     * Returns the transfer type (upload or download).
     * The default is TransferType::Download.
     *
     * \return TransferType
     */
    TransferType transferType() const;

    /**
     * Sets the transfer type (upload or download).
     *
     * \param TransferType::Type
     */
    void setTransferType(TransferType type);

    /**
     * Returns the transfer id.
     *
     * \return QString
     */
    QString id() const;

    /**
     * Returns the transfer URL.
     *
     * \return QUrl
     */
    QUrl url() const;

    /**
     * Returns the transfer content path.
     *
     * \return QString
     */
    QString contentPath() const;

    /**
     * Sets the transfer content path.
     *
     * \param QString
     */
    void setContentPath(const QString &path);

    /**
     * Returns the transfer file path. This is the local path
     * to which the file will be downloaded, or the path of
     * the file to be uploaded.
     *
     * \return QString
     */
    QString filePath() const;

    /**
     * Sets the transfer file path.
     *
     * \param QString
     */
    void setFilePath(const QString &path);

    /**
     * Returns the transfer content type, which will be
     * passed to the Ubuntu One server in the Content-Type header.
     * The default is 'application/octet-stream'.
     *
     * \return QString
     */
    QString contentType() const;

    /**
     * Sets the transfer content type, which will be
     * passed to the Ubuntu One server in the Content-Type header.
     *
     * \param QString
     */
    void setContentType(const QString &type);

    /**
     * Returns the transfer file size.
     *
     * \return qint64
     */
    qint64 size() const;

    /**
     * Returns the transfer position (number of bytes transferred).
     *
     * \return qint64
     */
    qint64 position() const;

    /**
     * Returns the transfer progress (maximum is 100).
     *
     * \return int
     */
    int progress() const;

    /**
     * Returns whether an existing file should be overwritten.
     * Only relevant for downloads. The default is false.
     *
     * \return bool
     */
    bool overwriteExistingFile() const;

    /**
     * Sets whether an existing file should be overwritten.
     * Only relevant for downloads.
     *
     * \param bool
     */
    void setOverwriteExistingFile(bool overwrite);

    /**
     * Returns whether the uploaded file should be published.
     * Only relevant for uploads. The default is false.
     *
     * \return bool
     */
    bool isPublic() const;

    /**
     * Sets whether the uploaded file should be published.
     * Only relevant for uploads.
     *
     * \param bool
     */
    void setPublic(bool isPublic);

    /**
     * Returns the current status of the transfer.
     *
     * \return Status
     */
    Status status() const;

    /**
     * Returns the status string of the transfer.
     *
     * \return QString
     */
    QString statusString() const;

    /**
     * Returns the error resulting from the transfer (or NoError).
     *
     * \return Error
     */
    Error error() const;

    /**
     * Returns the error string resulting from the transfer.
     *
     * \return QString
     */
    QString errorString() const;

public slots:
    /**
     * Starts the transfer. Partially completed downloads
     * will be resumed.
     */
    void start();

    /**
     * Queues the transfer.
     */
    void queue();

    /**
     * Pauses the transfer. Uploads cannot be paused.
     */
    void pause();

    /**
     * Cancels the transfer. For downloads, the partially
     * downloaded file will be deleted.
     */
    void cancel();

signals:
    void sizeChanged(qint64 size);
    void progressChanged(int progress);
    void statusChanged(FileTransfer::Status status);

private:
    explicit FileTransfer(FileTransferPrivate &d, QObject *parent = 0);

    QScopedPointer<FileTransferPrivate> d_ptr;

    Q_DECLARE_PRIVATE(FileTransfer)

    Q_PRIVATE_SLOT(d_func(), void _q_setMetaData(Node* node))
    Q_PRIVATE_SLOT(d_func(), void _q_onMetaDataChanged())
    Q_PRIVATE_SLOT(d_func(), void _q_onProgressChanged(qint64 transferred, qint64 total))
    Q_PRIVATE_SLOT(d_func(), void _q_onReadyRead())
    Q_PRIVATE_SLOT(d_func(), void _q_onUploadFinished())
    Q_PRIVATE_SLOT(d_func(), void _q_onDownloadFinished())
    Q_PRIVATE_SLOT(d_func(), void _q_onFilePublished(Node* node))
};

}

Q_DECLARE_METATYPE(QtUbuntuOne::FileTransfer::TransferType)
Q_DECLARE_METATYPE(QtUbuntuOne::FileTransfer::Status)
Q_DECLARE_METATYPE(QtUbuntuOne::FileTransfer::Error)

#endif // FILETRANSFER_H
