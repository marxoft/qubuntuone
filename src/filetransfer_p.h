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

#ifndef FILETRANSFER_P_H
#define FILETRANSFER_P_H

#include "filetransfer.h"
#include <QFile>
#include <qplatformdefs.h>
#ifdef MEEGO_EDITION_HARMATTAN
#include <TransferUI/Client>
#include <TransferUI/Transfer>
#endif

namespace QtUbuntuOne {

class FileTransferPrivate
{

public:
    FileTransferPrivate(FileTransfer *parent);
    FileTransferPrivate(FileTransfer::TransferType transferType, const QString &contentPath, const QString &filePath, FileTransfer *parent);
    virtual ~FileTransferPrivate();

    FileTransfer::TransferType transferType() const;
    void setTransferType(FileTransfer::TransferType type);

    QString id() const;

    QUrl url() const;

    QString contentPath() const;
    void setContentPath(const QString &path);

    QString filePath() const;
    void setFilePath(const QString &path);

    QString contentType() const;
    void setContentType(const QString &type);

    qint64 size() const;

    qint64 position() const;

    qint64 resumePosition() const;

    int progress() const;

    bool overwriteExistingFile() const;
    void setOverwriteExistingFile(bool overwrite);

    bool isPublic() const;
    void setPublic(bool isPublic);

    FileTransfer::Status status() const;
    QString statusString() const;

    FileTransfer::Error error() const;
    QString errorString() const;

    void start();
    void queue();
    void pause();
    void cancel();

private:
    void setId(const QString &id);

    void setUrl(const QUrl &url);

    void setSize(qint64 size);

    void setResumePosition(qint64 position);

    void setProgress(int progress);

    void setStatus(FileTransfer::Status status);

    void setError(FileTransfer::Error error);
    void setErrorString(const QString &errorString);

    void renameDownloadedFile();

    void publishFile(const QString &resourcePath);

    void performUpload();
    void performDownload();

    void getMetaData();

    void _q_setMetaData(Node *node);
    void _q_onMetaDataChanged();

    void _q_onProgressChanged(qint64 transferred, qint64 total);

    void _q_onReadyRead();

    void _q_onUploadFinished();
    void _q_onDownloadFinished();

    void _q_onFilePublished(Node *node);

    FileTransfer *q_ptr;

    QNetworkReply *m_reply;

    QFile m_file;

    FileTransfer::TransferType m_transferType;

    QString m_id;

    QUrl m_url;

    QString m_contentPath;

    QString m_filePath;

    QString m_contentType;

    qint64 m_size;

    qint64 m_resumePosition;

    qint64 m_transferredBytes;

    int m_progress;

    bool m_overwrite;

    bool m_public;

    FileTransfer::Status m_status;

    FileTransfer::Error m_error;
    QString m_errorString;

#ifdef MEEGO_EDITION_HARMATTAN
    TransferUI::Transfer *m_tuiTransfer;

    static TransferUI::Client *m_tuiClient;
    static int m_tuiCount;
#endif

    Q_DECLARE_PUBLIC(FileTransfer)
};

}

#endif // FILETRANSFER_P_H
