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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "reply.h"
#include "filetransfer.h"
#include "nodelist.h"
#include "user.h"
#include <QMainWindow>

class QPushButton;
class QLineEdit;
class QTextEdit;
class QComboBox;

using namespace QtUbuntuOne;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onCredentialsChanged();
    void getResult();
    void getUser();
    void getVolumes();
    void getVolume();
    void createVolume();
    void deleteVolume();
    void makeDirectory();
    void listDirectory();
    void getNode();
    void moveNode();
    void deleteNode();
    void getPublicFiles();
    void setFilePublic();
    void uploadFile();
    void downloadFile();
    void onUserReady(User *user);
    void onUserCancelled(User *user);
    void onNodeReady(Node *node);
    void onNodeCancelled(Node *node);
    void onNodeListReady(NodeList *nodes);
    void onNodeListCancelled(NodeList *nodes);
    void onReplyFinished(Reply *reply);
    void onReplyCancelled(Reply *reply);
    void onTransferProgressChanged(int progress);
    void onTransferStatusChanged(FileTransfer::Status status);
    void showAboutDialog();

private:
    QLineEdit *m_consumerKeyEdit;
    QLineEdit *m_consumerSecretEdit;
    QLineEdit *m_tokenKeyEdit;
    QLineEdit *m_tokenSecretEdit;
    QComboBox *m_methodSelector;
    QLineEdit *m_paramsEdit;
    QPushButton *m_actionButton;
    QPushButton *m_cancelButton;
    QTextEdit *m_resultEdit;
};

#endif // MAINWINDOW_H
