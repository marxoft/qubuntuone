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

#include "mainwindow.h"
#include "files.h"
#include "authentication.h"
#include "aboutdialog.h"
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QRegExpValidator>
#include <QPushButton>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QComboBox>
#ifndef Q_WS_MAEMO_5
#include <QMenuBar>
#include <QMenu>
#include <QCoreApplication>
#endif

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_consumerKeyEdit(new QLineEdit(this)),
    m_consumerSecretEdit(new QLineEdit(this)),
    m_tokenKeyEdit(new QLineEdit(this)),
    m_tokenSecretEdit(new QLineEdit(this)),
    m_methodSelector(new QComboBox(this)),
    m_paramsEdit(new QLineEdit(this)),
    m_actionButton(new QPushButton(tr("Get result"), this)),
    m_cancelButton(new QPushButton(tr("Cancel"), this)),
    m_resultEdit(new QTextEdit(this))
{
    this->setMinimumSize(400, 400);
    this->setWindowTitle(tr("QUbuntuOne Files Example"));
    this->setCentralWidget(new QWidget(this));
#ifdef Q_WS_MAEMO_5
    this->menuBar()->addAction(tr("About"), this, SLOT(showAboutDialog()));
#else
    QMenu *fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(tr("Quit"), QCoreApplication::instance(), SLOT(quit()), Qt::CTRL + Qt::Key_Q);

    QMenu *helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(tr("About"), this, SLOT(showAboutDialog()));

    this->menuBar()->addMenu(fileMenu);
    this->menuBar()->addMenu(helpMenu);
#endif
    QRegExpValidator *validator = new QRegExpValidator(QRegExp("[\\S]+"), this);
    m_consumerKeyEdit->setValidator(validator);
    m_consumerSecretEdit->setValidator(validator);
    m_tokenKeyEdit->setValidator(validator);
    m_tokenSecretEdit->setValidator(validator);
    m_paramsEdit->setPlaceholderText(tr("Comma separated parameters"));
    m_resultEdit->setReadOnly(true);
    m_actionButton->setEnabled(false);
    m_cancelButton->setEnabled(false);

    m_methodSelector->addItems(QStringList()
                               << "getUser"
                               << "getVolumes"
                               << "getVolume"
                               << "createVolume"
                               << "deleteVolume"
                               << "makeDirectory"
                               << "listDirectory"
                               << "getNode"
                               << "moveNode"
                               << "deleteNode"
                               << "getPublicFiles"
                               << "setFilePublic"
                               << "uploadFile"
                               << "downloadFile");

    QWidget *formWidget = new QWidget(this);
    QFormLayout *formLayout = new QFormLayout(formWidget);
    formLayout->setContentsMargins(0, 0, 0, 0);
    formLayout->addRow(tr("&Consumer key:"), m_consumerKeyEdit);
    formLayout->addRow(tr("&Consumer secret:"), m_consumerSecretEdit);
    formLayout->addRow(tr("&Token key:"), m_tokenKeyEdit);
    formLayout->addRow(tr("&Token secret:"), m_tokenSecretEdit);
    formLayout->addRow(tr("&Method:"), m_methodSelector);
    formLayout->addRow(tr("&Params:"), m_paramsEdit);

    QVBoxLayout *vbox = new QVBoxLayout(this->centralWidget());
    vbox->addWidget(formWidget);
    vbox->addWidget(m_actionButton, 0, Qt::AlignRight);
    vbox->addWidget(m_cancelButton, 0, Qt::AlignRight);
    vbox->addWidget(new QLabel(tr("Result:"), this));
    vbox->addWidget(m_resultEdit);

    this->connect(m_consumerKeyEdit, SIGNAL(textEdited(QString)), this, SLOT(onCredentialsChanged()));
    this->connect(m_consumerSecretEdit, SIGNAL(textEdited(QString)), this, SLOT(onCredentialsChanged()));
    this->connect(m_tokenKeyEdit, SIGNAL(textEdited(QString)), this, SLOT(onCredentialsChanged()));
    this->connect(m_tokenSecretEdit, SIGNAL(textEdited(QString)), this, SLOT(onCredentialsChanged()));
    this->connect(m_actionButton, SIGNAL(clicked()), this, SLOT(getResult()));
}

MainWindow::~MainWindow() {}

void MainWindow::onCredentialsChanged() {
    m_actionButton->setEnabled((m_consumerKeyEdit->hasAcceptableInput())
                               && (m_consumerSecretEdit->hasAcceptableInput())
                               && (m_tokenKeyEdit->hasAcceptableInput())
                               && (m_tokenSecretEdit->hasAcceptableInput()));
}

void MainWindow::getResult() {
    Authentication::setCredentials(m_consumerKeyEdit->text(),
                                   m_consumerSecretEdit->text(),
                                   m_tokenKeyEdit->text(),
                                   m_tokenSecretEdit->text());

    m_resultEdit->setText(tr("Calling method %1...").arg(m_methodSelector->currentText()));
    m_actionButton->setEnabled(false);
    m_cancelButton->setEnabled(true);

    QMetaObject::invokeMethod(this, m_methodSelector->currentText().toUtf8());
}

void MainWindow::getUser() {
    User *user = Files::getUser();
    this->connect(m_cancelButton, SIGNAL(clicked()), user, SLOT(cancel()));
    this->connect(user, SIGNAL(ready(User*)), this, SLOT(onUserReady(User*)));
    this->connect(user, SIGNAL(cancelled(User*)), this, SLOT(onUserCancelled(User*)));
}

void MainWindow::getVolumes() {
    NodeList *nodes = Files::getVolumes();
    this->connect(m_cancelButton, SIGNAL(clicked()), nodes, SLOT(cancel()));
    this->connect(nodes, SIGNAL(ready(NodeList*)), this, SLOT(onNodeListReady(NodeList*)));
    this->connect(nodes, SIGNAL(cancelled(NodeList*)), this, SLOT(onNodeListCancelled(NodeList*)));
}

void MainWindow::getVolume() {
    Node *node = Files::getVolume(m_paramsEdit->text());
    this->connect(m_cancelButton, SIGNAL(clicked()), node, SLOT(cancel()));
    this->connect(node, SIGNAL(ready(Node*)), this, SLOT(onNodeReady(Node*)));
    this->connect(node, SIGNAL(cancelled(Node*)), this, SLOT(onNodeCancelled(Node*)));
}

void MainWindow::createVolume() {
    Node *node = Files::createVolume(m_paramsEdit->text());
    this->connect(m_cancelButton, SIGNAL(clicked()), node, SLOT(cancel()));
    this->connect(node, SIGNAL(ready(Node*)), this, SLOT(onNodeReady(Node*)));
    this->connect(node, SIGNAL(cancelled(Node*)), this, SLOT(onNodeCancelled(Node*)));
}

void MainWindow::deleteVolume() {
    Reply *reply = Files::deleteVolume(m_paramsEdit->text());
    this->connect(m_cancelButton, SIGNAL(clicked()), reply, SLOT(cancel()));
    this->connect(reply, SIGNAL(finished(Reply*)), this, SLOT(onReplyFinished(Reply*)));
    this->connect(reply, SIGNAL(cancelled(Reply*)), this, SLOT(onReplyCancelled(Reply*)));
}

void MainWindow::makeDirectory() {
    Node *node = Files::makeDirectory(m_paramsEdit->text());
    this->connect(m_cancelButton, SIGNAL(clicked()), node, SLOT(cancel()));
    this->connect(node, SIGNAL(ready(Node*)), this, SLOT(onNodeReady(Node*)));
    this->connect(node, SIGNAL(cancelled(Node*)), this, SLOT(onNodeCancelled(Node*)));
}

void MainWindow::listDirectory() {
    NodeList *nodes = Files::listDirectory(m_paramsEdit->text());
    this->connect(m_cancelButton, SIGNAL(clicked()), nodes, SLOT(cancel()));
    this->connect(nodes, SIGNAL(ready(NodeList*)), this, SLOT(onNodeListReady(NodeList*)));
    this->connect(nodes, SIGNAL(cancelled(NodeList*)), this, SLOT(onNodeListCancelled(NodeList*)));
}

void MainWindow::getNode() {
    Node *node = Files::getNode(m_paramsEdit->text().section(',', 0, 0).trimmed());
    this->connect(m_cancelButton, SIGNAL(clicked()), node, SLOT(cancel()));
    this->connect(node, SIGNAL(ready(Node*)), this, SLOT(onNodeReady(Node*)));
    this->connect(node, SIGNAL(cancelled(Node*)), this, SLOT(onNodeCancelled(Node*)));
}

void MainWindow::moveNode() {
    Node *node = Files::moveNode(m_paramsEdit->text().section(',', 0, 0).trimmed(),
                                 m_paramsEdit->text().section(',', -1).trimmed());

    this->connect(m_cancelButton, SIGNAL(clicked()), node, SLOT(cancel()));
    this->connect(node, SIGNAL(ready(Node*)), this, SLOT(onNodeReady(Node*)));
    this->connect(node, SIGNAL(cancelled(Node*)), this, SLOT(onNodeCancelled(Node*)));
}

void MainWindow::deleteNode() {
    Reply *reply = Files::deleteNode(m_paramsEdit->text());
    this->connect(m_cancelButton, SIGNAL(clicked()), reply, SLOT(cancel()));
    this->connect(reply, SIGNAL(finished(Reply*)), this, SLOT(onReplyFinished(Reply*)));
    this->connect(reply, SIGNAL(cancelled(Reply*)), this, SLOT(onReplyCancelled(Reply*)));
}

void MainWindow::getPublicFiles() {
    NodeList *nodes = Files::getPublicFiles();
    this->connect(m_cancelButton, SIGNAL(clicked()), nodes, SLOT(cancel()));
    this->connect(nodes, SIGNAL(ready(NodeList*)), this, SLOT(onNodeListReady(NodeList*)));
    this->connect(nodes, SIGNAL(cancelled(NodeList*)), this, SLOT(onNodeListCancelled(NodeList*)));
}

void MainWindow::setFilePublic() {
    Node *node = Files::setFilePublic(m_paramsEdit->text().section(',', 0, 0).trimmed(),
                                      m_paramsEdit->text().section(',', -1).trimmed() == "true");

    this->connect(m_cancelButton, SIGNAL(clicked()), node, SLOT(cancel()));
    this->connect(node, SIGNAL(ready(Node*)), this, SLOT(onNodeReady(Node*)));
    this->connect(node, SIGNAL(cancelled(Node*)), this, SLOT(onNodeCancelled(Node*)));
}

void MainWindow::uploadFile() {
    FileTransfer *transfer = Files::uploadFile(m_paramsEdit->text().section(',', 0, 0).trimmed(),
                                               m_paramsEdit->text().section(',', 1, 1).trimmed(),
                                               m_paramsEdit->text().section(',', 2, 2).trimmed(),
                                               m_paramsEdit->text().section(',', -1).trimmed() == "true");

    this->connect(m_cancelButton, SIGNAL(clicked()), transfer, SLOT(cancel()));
    this->connect(transfer, SIGNAL(progressChanged(int)), this, SLOT(onTransferProgressChanged(int)));
    this->connect(transfer, SIGNAL(statusChanged(FileTransfer::Status)), this, SLOT(onTransferStatusChanged(FileTransfer::Status)));
}

void MainWindow::downloadFile() {
    FileTransfer *transfer = Files::downloadFile(m_paramsEdit->text().section(',', 0, 0).trimmed(),
                                                 m_paramsEdit->text().section(',', 1, 1).trimmed(),
                                                 m_paramsEdit->text().section(',', -1).trimmed() == "true");

    this->connect(m_cancelButton, SIGNAL(clicked()), transfer, SLOT(cancel()));
    this->connect(transfer, SIGNAL(progressChanged(int)), this, SLOT(onTransferProgressChanged(int)));
    this->connect(transfer, SIGNAL(statusChanged(FileTransfer::Status)), this, SLOT(onTransferStatusChanged(FileTransfer::Status)));
}

void MainWindow::onUserReady(User *user) {
    m_actionButton->setEnabled(true);
    m_cancelButton->setEnabled(false);
    m_resultEdit->clear();

    switch (user->error()) {
    case User::NoError:
        m_resultEdit->append(tr("Id: %1").arg(user->id()));
        m_resultEdit->append(tr("Name: %1").arg(user->name()));
        m_resultEdit->append(tr("Resource path: %1").arg(user->resourcePath()));
        m_resultEdit->append(tr("Root node path: %1").arg(user->rootNodePath()));
        m_resultEdit->append(tr("User node paths: %1").arg(user->userNodePaths().join(", ")));
        m_resultEdit->append(tr("Max bytes: %1").arg(user->maxBytes()));
        m_resultEdit->append(tr("Used bytes: %1").arg(user->usedBytes()));
        break;
    default:
        m_resultEdit->append(tr("Error: %1").arg(user->errorString()));
        break;
    }

    user->deleteLater();
}

void MainWindow::onUserCancelled(User *user) {
    m_actionButton->setEnabled(true);
    m_cancelButton->setEnabled(false);
    m_resultEdit->append(tr("Operation cancelled."));
    user->deleteLater();
}

void MainWindow::onNodeReady(Node *node) {
    m_actionButton->setEnabled(true);
    m_cancelButton->setEnabled(false);
    m_resultEdit->clear();

    switch (node->error()) {
    case Node::NoError:
        m_resultEdit->append(tr("Path: %1").arg(node->path()));
        m_resultEdit->append(tr("Resource path: %1").arg(node->resourcePath()));
        m_resultEdit->append(tr("Content path: %1").arg(node->contentPath()));
        m_resultEdit->append(tr("Parent path: %1").arg(node->parentPath()));
        m_resultEdit->append(tr("Volume path: %1").arg(node->volumePath()));
        m_resultEdit->append(tr("Name: %1").arg(node->name()));
        m_resultEdit->append(tr("Suffix: %1").arg(node->suffix()));
        m_resultEdit->append(tr("Key: %1").arg(node->key()));
        m_resultEdit->append(tr("Created: %1").arg(node->whenCreated().toString()));
        m_resultEdit->append(tr("Last modified: %1").arg(node->lastModified().toString()));
        m_resultEdit->append(tr("Generation: %1").arg(node->generation()));
        m_resultEdit->append(tr("Generation created: %1").arg(node->generationCreated()));
        m_resultEdit->append(tr("Hash: %1").arg(QString(node->hash())));
        m_resultEdit->append(tr("size: %1").arg(node->size()));
        m_resultEdit->append(tr("Is public: %1").arg(node->isPublic() ? "true" : "false"));
        m_resultEdit->append(tr("Public url: %1").arg(node->publicUrl().toString()));
        m_resultEdit->append(tr("Has children: %1").arg(node->hasChildren() ? "true" : "false"));
        m_resultEdit->append(tr("Is root: %1").arg(node->isRoot() ? "true" : "false"));
        break;
    default:
        m_resultEdit->append(tr("Error: %1").arg(node->errorString()));
        break;
    }

    node->deleteLater();
}

void MainWindow::onNodeCancelled(Node *node) {
    m_actionButton->setEnabled(true);
    m_cancelButton->setEnabled(false);
    m_resultEdit->append(tr("Operation cancelled."));
    node->deleteLater();
}

void MainWindow::onNodeListReady(NodeList *nodes) {
    m_actionButton->setEnabled(true);
    m_cancelButton->setEnabled(false);
    m_resultEdit->clear();

    switch (nodes->error()) {
    case NodeList::NoError:
        foreach (Node *node, nodes->nodes()) {
            m_resultEdit->append(tr("Path: %1").arg(node->path()));
            m_resultEdit->append(tr("Resource path: %1").arg(node->resourcePath()));
            m_resultEdit->append(tr("Content path: %1").arg(node->contentPath()));
            m_resultEdit->append(tr("Parent path: %1").arg(node->parentPath()));
            m_resultEdit->append(tr("Volume path: %1").arg(node->volumePath()));
            m_resultEdit->append(tr("Name: %1").arg(node->name()));
            m_resultEdit->append(tr("Suffix: %1").arg(node->suffix()));
            m_resultEdit->append(tr("Key: %1").arg(node->key()));
            m_resultEdit->append(tr("Created: %1").arg(node->whenCreated().toString()));
            m_resultEdit->append(tr("Last modified: %1").arg(node->lastModified().toString()));
            m_resultEdit->append(tr("Generation: %1").arg(node->generation()));
            m_resultEdit->append(tr("Generation created: %1").arg(node->generationCreated()));
            m_resultEdit->append(tr("Hash: %1").arg(QString(node->hash())));
            m_resultEdit->append(tr("size: %1").arg(node->size()));
            m_resultEdit->append(tr("Is public: %1").arg(node->isPublic() ? "true" : "false"));
            m_resultEdit->append(tr("Public url: %1").arg(node->publicUrl().toString()));
            m_resultEdit->append(tr("Has children: %1").arg(node->hasChildren() ? "true" : "false"));
            m_resultEdit->append(tr("Is root: %1").arg(node->isRoot() ? "true" : "false"));
            m_resultEdit->append("\n");
        }

        break;
    default:
        m_resultEdit->append(tr("Error: %1").arg(nodes->errorString()));
        break;
    }

    qDeleteAll(nodes->nodes());
    nodes->deleteLater();
}

void MainWindow::onNodeListCancelled(NodeList *nodes) {
    m_actionButton->setEnabled(true);
    m_cancelButton->setEnabled(false);
    m_resultEdit->append(tr("Operation cancelled."));
    qDeleteAll(nodes->nodes());
    nodes->deleteLater();
}

void MainWindow::onReplyFinished(Reply *reply) {
    m_actionButton->setEnabled(true);
    m_cancelButton->setEnabled(false);
    m_resultEdit->clear();
    m_resultEdit->append(tr("Status: %1").arg(reply->status()));

    switch (reply->error()) {
    case Reply::NoError:
        m_resultEdit->append(reply->resultString());
        break;
    default:
        m_resultEdit->append(tr("Error: %1").arg(reply->errorString()));
        break;
    }

    reply->deleteLater();
}

void MainWindow::onReplyCancelled(Reply *reply) {
    m_actionButton->setEnabled(true);
    m_cancelButton->setEnabled(false);
    m_resultEdit->append(tr("Operation cancelled."));
    reply->deleteLater();
}

void MainWindow::onTransferProgressChanged(int progress) {
    m_resultEdit->append(tr("Progress: %1%").arg(progress));
}

void MainWindow::onTransferStatusChanged(FileTransfer::Status status) {
    if (FileTransfer *transfer = qobject_cast<FileTransfer*>(this->sender())) {
        switch (status) {
        case FileTransfer::Completed:
            m_actionButton->setEnabled(true);
            m_cancelButton->setEnabled(false);
            m_resultEdit->append(tr("Transfer completed successfully."));
            break;
        case FileTransfer::Cancelled:
            m_actionButton->setEnabled(true);
            m_cancelButton->setEnabled(false);
            m_resultEdit->append(tr("Transfer cancelled."));
            break;
        case FileTransfer::Failed:
            m_actionButton->setEnabled(true);
            m_cancelButton->setEnabled(false);
            m_resultEdit->append(tr("Error: %1").arg(transfer->errorString()));
            break;
        default:
            return;
        }

        transfer->deleteLater();
    }
}

void MainWindow::showAboutDialog() {
    AboutDialog *dialog = new AboutDialog(this);
    dialog->open();
}
