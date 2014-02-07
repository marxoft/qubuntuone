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

#include "filetransfer_p.h"
#include "authentication.h"
#include "files.h"
#include "node.h"
#include "networkaccessmanager.h"
#include "urls.h"
#include "json.h"
#include <QDir>
#include <QDateTime>

namespace QtUbuntuOne {

#ifdef MEEGO_EDITION_HARMATTAN
TransferUI::Client* FileTransferPrivate::m_tuiClient = 0;
int FileTransferPrivate::m_tuiCount = 0;
#endif

FileTransferPrivate::FileTransferPrivate(FileTransfer *parent) :
    q_ptr(parent),
    m_reply(0),
    m_transferType(FileTransfer::Download),
    m_id(QString::number(QDateTime::currentMSecsSinceEpoch())),
    m_contentType("application/octet-stream"),
    m_size(0),
    m_resumePosition(0),
    m_transferredBytes(0),
    m_progress(0),
    m_overwrite(false),
    m_public(false),
    m_status(FileTransfer::Queued),
    m_error(FileTransfer::NoError)
{
#ifdef MEEGO_EDITION_HARMATTAN
    Q_Q(FileTransfer);
    
    if (!m_tuiClient) {
        m_tuiClient = new TransferUI::Client;
        m_tuiClient->init();
    }

    m_tuiCount++;
    
    m_tuiTransfer = m_tuiClient->registerTransfer(QString(), TransferUI::Client::TRANSFER_TYPES_DOWNLOAD);
    m_tuiTransfer->waitForCommit();
    m_tuiTransfer->setTargetName("Ubuntu One");
    m_tuiTransfer->setIcon("icon-m-content-document");
    m_tuiTransfer->setCanPause(true);
    m_tuiTransfer->commit();
    
    q->connect(m_tuiTransfer, SIGNAL(start()), q, SLOT(queue()));
    q->connect(m_tuiTransfer, SIGNAL(pause()), q, SLOT(pause()));
    q->connect(m_tuiTransfer, SIGNAL(cancel()), q, SLOT(cancel()));
    q->connect(m_tuiTransfer, SIGNAL(repairError()), q, SLOT(queue()));
#endif
}

FileTransferPrivate::FileTransferPrivate(FileTransfer::TransferType transferType, const QString &contentPath, const QString &filePath, FileTransfer *parent) :
    q_ptr(parent),
    m_reply(0),
    m_transferType(transferType),
    m_id(QString::number(QDateTime::currentMSecsSinceEpoch())),
    m_contentPath(contentPath),
    m_filePath(filePath),
    m_contentType("application/octet-stream"),
    m_size(0),
    m_resumePosition(0),
    m_transferredBytes(0),
    m_progress(0),
    m_overwrite(false),
    m_public(false),
    m_status(FileTransfer::Queued),
    m_error(FileTransfer::NoError)
{
#ifdef MEEGO_EDITION_HARMATTAN
    Q_Q(FileTransfer);
    
    if (!m_tuiClient) {
        m_tuiClient = new TransferUI::Client;
        m_tuiClient->init();
    }

    m_tuiCount++;
    
    m_tuiTransfer = m_tuiClient->registerTransfer(filePath.mid(filePath.lastIndexOf('/') + 1),
                                                  transferType == FileTransfer::Upload ? TransferUI::Client::TRANSFER_TYPES_UPLOAD
                                                                                       : TransferUI::Client::TRANSFER_TYPES_DOWNLOAD);

    m_tuiTransfer->waitForCommit();
    m_tuiTransfer->setTargetName("Ubuntu One");
    m_tuiTransfer->setIcon("icon-m-content-document");
    m_tuiTransfer->setCanPause(transferType == FileTransfer::Download);
    m_tuiTransfer->commit();
    
    q->connect(m_tuiTransfer, SIGNAL(start()), q, SLOT(queue()));
    q->connect(m_tuiTransfer, SIGNAL(pause()), q, SLOT(pause()));
    q->connect(m_tuiTransfer, SIGNAL(cancel()), q, SLOT(cancel()));
    q->connect(m_tuiTransfer, SIGNAL(repairError()), q, SLOT(queue()));
#endif
}

FileTransferPrivate::~FileTransferPrivate() {
    if (m_reply) {
        delete m_reply;
        m_reply = 0;
    }
#ifdef MEEGO_EDITION_HARMATTAN
    if (m_tuiTransfer) {
        if (m_tuiClient) {
            m_tuiClient->removeTransfer(m_tuiTransfer->transferId());
        }

        delete m_tuiTransfer;
        m_tuiTransfer = 0;

        m_tuiCount--;

        if ((!m_tuiCount) && (m_tuiClient)) {
            delete m_tuiClient;
            m_tuiClient = 0;
        }
    }
#endif
}

FileTransfer::TransferType FileTransferPrivate::transferType() const {
    return m_transferType;
}

void FileTransferPrivate::setTransferType(FileTransfer::TransferType type) {
    m_transferType = type;
#ifdef MEEGO_EDITION_HARMATTAN
    if (m_tuiTransfer) {
        switch (type) {
        case FileTransfer::Upload:
            m_tuiTransfer->waitForCommit();
            m_tuiTransfer->setTransferType(TransferUI::Client::TRANSFER_TYPES_UPLOAD);
            m_tuiTransfer->setCanPause(false);
            m_tuiTransfer->commit();
            return;
        default:
            m_tuiTransfer->waitForCommit();
            m_tuiTransfer->setTransferType(TransferUI::Client::TRANSFER_TYPES_DOWNLOAD);
            m_tuiTransfer->setCanPause(true);
            m_tuiTransfer->commit();
            return;
        }
    }
#endif
}

QString FileTransferPrivate::id() const {
    return m_id;
}

void FileTransferPrivate::setId(const QString &id) {
    m_id = id;
}

QUrl FileTransferPrivate::url() const {
    return m_url;
}

void FileTransferPrivate::setUrl(const QUrl &url) {
    m_url = url;
}

QString FileTransferPrivate::contentPath() const {
    return m_contentPath;
}

void FileTransferPrivate::setContentPath(const QString &path) {
    m_contentPath = path;
}

QString FileTransferPrivate::filePath() const {
    return m_filePath;
}

void FileTransferPrivate::setFilePath(const QString &path) {
    m_filePath = path;
#ifdef MEEGO_EDITION_HARMATTAN
    if (m_tuiTransfer) {
        m_tuiTransfer->setName(path.mid(path.lastIndexOf('/') + 1));
    }
#endif
}

QString FileTransferPrivate::contentType() const {
    return m_contentType;
}

void FileTransferPrivate::setContentType(const QString &type) {
    m_contentType = type;
}

qint64 FileTransferPrivate::size() const {
    return m_size;
}

void FileTransferPrivate::setSize(qint64 size) {
    Q_Q(FileTransfer);
    
    if (size != this->size()) {
        m_size = size;
        emit q->sizeChanged(size);
#ifdef MEEGO_EDITION_HARMATTAN
        if (m_tuiTransfer) {
            m_tuiTransfer->setSize(size);
        }
#endif
    }
}

qint64 FileTransferPrivate::resumePosition() const {
    return m_resumePosition;
}

void FileTransferPrivate::setResumePosition(qint64 position) {
    m_resumePosition = position;
}

qint64 FileTransferPrivate::position() const {
    return m_resumePosition + m_transferredBytes;
}

int FileTransferPrivate::progress() const {
    return m_progress;
}

void FileTransferPrivate::setProgress(int progress) {
    Q_Q(FileTransfer);
    
    if (progress != this->progress()) {
        m_progress = progress;
        emit q->progressChanged(progress);
#ifdef MEEGO_EDITION_HARMATTAN
        if ((m_tuiClient) && (m_tuiClient->isTUIVisible())) {
            if (m_tuiTransfer) {
                m_tuiTransfer->setProgress(float(progress) / 100);
            }
        }
#endif
    }
}

bool FileTransferPrivate::overwriteExistingFile() const {
    return m_overwrite;
}

void FileTransferPrivate::setOverwriteExistingFile(bool overwrite) {
    m_overwrite = overwrite;
}

bool FileTransferPrivate::isPublic() const {
    return m_public;
}

void FileTransferPrivate::setPublic(bool isPublic) {
    m_public = isPublic;
}

FileTransfer::Status FileTransferPrivate::status() const {
    return m_status;
}

void FileTransferPrivate::setStatus(FileTransfer::Status status) {
    Q_Q(FileTransfer);
    
    if (status != this->status()) {
        m_status = status;
#ifdef MEEGO_EDITION_HARMATTAN
        switch (status) {
        case FileTransfer::Queued:
            if (m_tuiTransfer) m_tuiTransfer->setPending(this->statusString());
            break;
        case FileTransfer::Connecting:
        case FileTransfer::Downloading:
        case FileTransfer::Uploading:
            if (m_tuiTransfer) m_tuiTransfer->markResumed();
            break;
        case FileTransfer::Completed:
            if (m_tuiTransfer) m_tuiTransfer->markCompleted();
            break;
        case FileTransfer::Paused:
            if (m_tuiTransfer) m_tuiTransfer->markPaused();
            break;
        case FileTransfer::Cancelled:
            if (m_tuiTransfer) m_tuiTransfer->markCancelled();
            break;
        case FileTransfer::Failed:
            if (m_tuiTransfer) m_tuiTransfer->markRepairableFailure(this->statusString(), this->errorString(), QObject::tr("Retry"));
            break;
        default:
            break;
        }
#endif
        emit q->statusChanged(status);
    }
}

QString FileTransferPrivate::statusString() const {
    switch (this->status()) {
    case FileTransfer::Queued:
        return QObject::tr("Queued");
    case FileTransfer::Paused:
        return QObject::tr("Paused");
    case FileTransfer::Connecting:
        return QObject::tr("Connecting");
    case FileTransfer::Downloading:
        return QObject::tr("Downloading");
    case FileTransfer::Uploading:
        return QObject::tr("Uploading");
    case FileTransfer::Cancelled:
        return QObject::tr("Cancelled");
    case FileTransfer::Failed:
        return QObject::tr("Failed");
    case FileTransfer::Completed:
        return QObject::tr("Completed");
    default:
        return QObject::tr("Unknown");
    }
}

FileTransfer::Error FileTransferPrivate::error() const {
    return m_error;
}

void FileTransferPrivate::setError(FileTransfer::Error error) {
    m_error = error;
}

QString FileTransferPrivate::errorString() const {
    return m_errorString;
}

void FileTransferPrivate::setErrorString(const QString &errorString) {
    m_errorString = errorString;
}

void FileTransferPrivate::start() {
    if (this->contentPath().isEmpty()) {
        this->setError(FileTransfer::ResourceError);
        this->setErrorString(QObject::tr("No resource path specified"));
        this->setStatus(FileTransfer::Failed);
        return;
    }
    
    switch (this->transferType()) {
    case FileTransfer::Upload:
        m_file.setFileName(this->filePath());
        
        if (!m_file.open(QIODevice::ReadOnly)) {
            this->setError(FileTransfer::FileError);
            this->setErrorString(QObject::tr("Cannot open file %1: %2").arg(m_file.fileName()).arg(m_file.errorString()));
            this->setStatus(FileTransfer::Failed);
            return;
        }
        
        this->setUrl(QUrl(CONTENT_ROOT_FILES + this->contentPath()));
        this->setSize(m_file.size());
        this->performUpload();
        break;
    default:
        if (!QDir().mkpath(this->filePath().left(this->filePath().lastIndexOf('/')))) {
            this->setError(FileTransfer::FileError);
            this->setErrorString(QObject::tr("Cannot create directory %1").arg(this->filePath().left(this->filePath().lastIndexOf('/'))));
            this->setStatus(FileTransfer::Failed);
            return;
        }
        
        m_file.setFileName(this->filePath().endsWith(".qubuntuone") ? this->filePath() : this->filePath() + ".qubuntuone");
        
        if (!m_file.open(m_file.exists() ? QIODevice::Append : QIODevice::WriteOnly)) {
            this->setError(FileTransfer::FileError);
            this->setErrorString(QObject::tr("Cannot open file %1: %2").arg(m_file.fileName()).arg(m_file.errorString()));
            this->setStatus(FileTransfer::Failed);
            return;
        }
        
        this->setResumePosition(m_file.size());
        this->setUrl(QUrl(CONTENT_ROOT_FILES + this->contentPath()));
        //        this->performDownload();
        this->getMetaData(); // Temporary fix for incorrect Content-Length header
        break;
    }
}

void FileTransferPrivate::queue() {
    switch(this->status()) {
    case FileTransfer::Paused:
    case FileTransfer::Failed:
        this->setStatus(FileTransfer::Queued);
        return;
    default:
        return;
    }
}

void FileTransferPrivate::pause() {
    switch(this->transferType()) {
    case FileTransfer::Upload:
        return;
    default:
        break;
    }
    
    if (m_reply) {
        m_reply->abort();
    }
    
    this->setStatus(FileTransfer::Paused);
}

void FileTransferPrivate::cancel() {
    if (m_reply) {
        m_reply->abort();
    }
    
    switch (this->transferType()) {
    case FileTransfer::Download:
        if (QFile::exists(this->filePath() + ".qubuntuone")) {
            QFile::remove(this->filePath() + ".qubuntuone");
        }
        
        break;
    default:
        break;
    }
    
    this->setStatus(FileTransfer::Cancelled);
}

void FileTransferPrivate::performUpload() {
    Q_Q(FileTransfer);
    
    this->setStatus(FileTransfer::Uploading);
    
    QNetworkRequest request(this->url());
    request.setHeader(QNetworkRequest::ContentTypeHeader, this->contentType());
    request.setHeader(QNetworkRequest::ContentLengthHeader, this->size());
    request.setRawHeader("Authorization", Authentication::getOAuthHeader("PUT", this->url().toString(QUrl::RemoveQuery).toUtf8().toPercentEncoding(":/~_?="), QMap<QString, QString>()));
    request.setRawHeader("Accept", "application/json");
    request.setRawHeader("User-Agent", "QUbuntuOne (Qt)");
    m_reply = NetworkAccessManager::instance()->put(request, &m_file);
    q->connect(m_reply, SIGNAL(uploadProgress(qint64,qint64)), q, SLOT(_q_onProgressChanged(qint64,qint64)));
    q->connect(m_reply, SIGNAL(finished()), q, SLOT(_q_onUploadFinished()));
}

void FileTransferPrivate::performDownload() {
    Q_Q(FileTransfer);
    
    this->setStatus(FileTransfer::Downloading);
    
    QNetworkRequest request(this->url());
    
    if (this->resumePosition() > 0) {
        request.setRawHeader("Range", QByteArray::number(this->resumePosition()) + "-");
    }
    
    request.setRawHeader("Authorization", Authentication::getOAuthHeader("GET", this->url().toString(QUrl::RemoveQuery).toUtf8().toPercentEncoding(":/~_?="), QMap<QString, QString>()));
    request.setRawHeader("User-Agent", "QUbuntuOne (Qt)");
    m_reply = NetworkAccessManager::instance()->get(request);
    q->connect(m_reply, SIGNAL(downloadProgress(qint64,qint64)), q, SLOT(_q_onProgressChanged(qint64,qint64)));
    q->connect(m_reply, SIGNAL(readyRead()), q, SLOT(_q_onReadyRead()));
    q->connect(m_reply, SIGNAL(finished()), q, SLOT(_q_onDownloadFinished()));
    
    if (this->size() <= 0) {
        q->connect(m_reply, SIGNAL(metaDataChanged()), q, SLOT(_q_onMetaDataChanged()));
    }
}

void FileTransferPrivate::getMetaData() {
    /* Temporary fix. The Ubuntu One API does not return a Content-Length header when downloading,
       so get the metadata before downloading.
    */
    
    Q_Q(FileTransfer);
    
    this->setStatus(FileTransfer::Connecting);
    
    Node *node = Files::getNode(this->contentPath().remove(0, 8));
    q->connect(node, SIGNAL(ready(Node*)), q, SLOT(_q_setMetaData(Node*)));
}

void FileTransferPrivate::_q_setMetaData(Node *node) {
    switch (node->error()) {
    case Node::NoError:
        this->setSize(node->size());
        break;
    default:
        break;
    }
    
    this->performDownload();
    
    node->deleteLater();
}

void FileTransferPrivate::_q_onMetaDataChanged() {
    if (m_reply) {
        qint64 size = m_reply->header(QNetworkRequest::ContentLengthHeader).toLongLong();
        
        if (size <= 0) {
            size = m_reply->rawHeader("Content-Length").toLongLong();
        }
        
        if (size > 0) {
            this->setSize(size);
        }
    }
}

void FileTransferPrivate::_q_onProgressChanged(qint64 transferred, qint64 total) {
    Q_UNUSED(total)
    
    m_transferredBytes = transferred;
    
    if (this->size() > 0) {
        this->setProgress(this->position() * 100 / this->size());
    }
}

void FileTransferPrivate::_q_onReadyRead() {
    if (m_reply) {
        m_file.write(m_reply->readAll());
    }
}

void FileTransferPrivate::_q_onUploadFinished() {
    m_file.close();
    
    if (m_reply) {
        QUrl redirect = m_reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
        
        if (!redirect.isEmpty()) {
            m_reply->deleteLater();
            m_reply = 0;
            this->setUrl(redirect);
            this->performUpload();
            return;
        }
        
        switch (m_reply->error()) {
        case QNetworkReply::NoError:
            break;
        case QNetworkReply::OperationCanceledError:
            return;
        default:
            this->setError(FileTransfer::Error(m_reply->error()));
            this->setErrorString(m_reply->errorString());
            this->setStatus(FileTransfer::Failed);
            m_reply->deleteLater();
            m_reply = 0;
            return;
        }
        
        bool ok;
        QString response(m_reply->readAll());
        QVariant result = QtJson::Json::parse(response, ok);
        
        m_reply->deleteLater();
        m_reply = 0;
        
        if (ok) {
            if (this->isPublic()) {
                this->publishFile(result.toMap().value("resource_path").toString());
            }
            else {
                this->setStatus(FileTransfer::Completed);
            }
        }
        else {
            this->setError(FileTransfer::ParserError);
            this->setErrorString(QObject::tr("Cannot parse server response"));
            this->setStatus(FileTransfer::Failed);
        }
    }
}

void FileTransferPrivate::_q_onDownloadFinished() {
    if (m_reply) {
        QUrl redirect = m_reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
        
        if (!redirect.isEmpty()) {
            m_reply->deleteLater();
            m_reply = 0;
            this->setUrl(redirect);
            this->performDownload();
            return;
        }
        
        switch (m_reply->error()) {
        case QNetworkReply::NoError:
            switch (this->transferType()) {
            case FileTransfer::Download:
                this->renameDownloadedFile();
                break;
            default:
                this->setStatus(FileTransfer::Completed);
                break;
            }
            
            break;
        case QNetworkReply::OperationCanceledError:
            m_file.close();
            m_reply->deleteLater();
            m_reply = 0;
            return;
        default:
            this->setError(FileTransfer::Error(m_reply->error()));
            this->setErrorString(m_reply->errorString());
            this->setStatus(FileTransfer::Failed);
            break;
        }
        
        m_file.close();
        m_reply->deleteLater();
        m_reply = 0;
    }
}

void FileTransferPrivate::renameDownloadedFile() {
    QString fileName = this->filePath();
    
    if (this->overwriteExistingFile()) {
        if ((!QFile::exists(fileName)) || (QFile::remove(fileName))) {
            m_file.rename(fileName);
        }
    }
    else {
        int lastDot = fileName.lastIndexOf('.');
        int i = 1;
        
        while ((!m_file.rename(fileName)) && (i < 100)) {
            fileName = QString("%1(%2)%3").arg(this->filePath().left(lastDot)).arg(i).arg(this->filePath().mid(lastDot));
            i++;
        }
    }
    
    this->setStatus(FileTransfer::Completed);
}

void FileTransferPrivate::publishFile(const QString &resourcePath) {
    Q_Q(FileTransfer);
    
    Node *node = Files::setFilePublic(resourcePath, true);
    q->connect(node, SIGNAL(ready(Node*)), q, SLOT(_q_onFilePublished(Node*)));
}

void FileTransferPrivate::_q_onFilePublished(Node *node) {
    switch (node->error()) {
    case Node::NoError:
        this->setStatus(FileTransfer::Completed);
        break;
    default:
        this->setError(FileTransfer::ResourceError);
        this->setErrorString(node->errorString());
        this->setStatus(FileTransfer::Failed);
        break;
    }
    
    node->deleteLater();
}

}
