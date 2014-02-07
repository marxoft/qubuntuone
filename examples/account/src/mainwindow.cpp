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
#include "account.h"
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
    m_actionButton(new QPushButton(tr("Get result"), this)),
    m_cancelButton(new QPushButton(tr("Cancel"), this)),
    m_resultEdit(new QTextEdit(this))
{
    this->setMinimumSize(400, 400);
    this->setWindowTitle(tr("QUbuntuOne Account Example"));
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
    m_resultEdit->setReadOnly(true);
    m_actionButton->setEnabled(false);
    m_cancelButton->setEnabled(false);

    m_methodSelector->addItems(QStringList()
                               << "getAccount"
                               << "getStorageQuota");

    QWidget *formWidget = new QWidget(this);
    QFormLayout *formLayout = new QFormLayout(formWidget);
    formLayout->setContentsMargins(0, 0, 0, 0);
    formLayout->addRow(tr("&Consumer key:"), m_consumerKeyEdit);
    formLayout->addRow(tr("&Consumer secret:"), m_consumerSecretEdit);
    formLayout->addRow(tr("&Token key:"), m_tokenKeyEdit);
    formLayout->addRow(tr("&Token secret:"), m_tokenSecretEdit);
    formLayout->addRow(tr("&Method:"), m_methodSelector);

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

void MainWindow::getAccount() {
    UserAccount *account = Account::getAccount();
    this->connect(m_cancelButton, SIGNAL(clicked()), account, SLOT(cancel()));
    this->connect(account, SIGNAL(ready(UserAccount*)), this, SLOT(onAccountReady(UserAccount*)));
    this->connect(account, SIGNAL(cancelled(UserAccount*)), this, SLOT(onAccountCancelled(UserAccount*)));
}

void MainWindow::getStorageQuota() {
    StorageQuota *quota = Account::getStorageQuota();
    this->connect(m_cancelButton, SIGNAL(clicked()), quota, SLOT(cancel()));
    this->connect(quota, SIGNAL(ready(StorageQuota*)), this, SLOT(onStorageQuotaReady(StorageQuota*)));
    this->connect(quota, SIGNAL(cancelled(StorageQuota*)), this, SLOT(onStorageQuotaCancelled(StorageQuota*)));
}

void MainWindow::onAccountReady(UserAccount *account) {
    m_actionButton->setEnabled(true);
    m_cancelButton->setEnabled(false);
    m_resultEdit->clear();

    switch (account->error()) {
    case UserAccount::NoError:
        m_resultEdit->append(tr("Id: %1").arg(account->id()));
        m_resultEdit->append(tr("Username: %1").arg(account->username()));
        m_resultEdit->append(tr("Nickname: %1").arg(account->nickname()));
        m_resultEdit->append(tr("First name: %1").arg(account->firstName()));
        m_resultEdit->append(tr("Last name: %1").arg(account->lastName()));
        m_resultEdit->append(tr("Email: %1").arg(account->email()));
        m_resultEdit->append(tr("Open ID: %1").arg(account->openId()));
        m_resultEdit->append(tr("Total storage: %1").arg(account->totalStorage()));
        m_resultEdit->append(tr("Current plan: %1").arg(account->currentPlan()));
        m_resultEdit->append(tr("Features: %1").arg(account->features().join(", ")));
        break;
    default:
        m_resultEdit->append(tr("Error: %1").arg(account->errorString()));
        break;
    }

    account->deleteLater();
}

void MainWindow::onAccountCancelled(UserAccount *account) {
    m_actionButton->setEnabled(true);
    m_cancelButton->setEnabled(false);
    m_resultEdit->append(tr("Operation cancelled."));
    account->deleteLater();
}

void MainWindow::onStorageQuotaReady(StorageQuota *quota) {
    m_actionButton->setEnabled(true);
    m_cancelButton->setEnabled(false);
    m_resultEdit->clear();

    switch (quota->error()) {
    case StorageQuota::NoError:
        m_resultEdit->append(tr("Total storage: %1").arg(quota->totalStorage()));
        m_resultEdit->append(tr("Used storage: %1").arg(quota->usedStorage()));
        break;
    default:
        m_resultEdit->append(tr("Error: %1").arg(quota->errorString()));
        break;
    }

    quota->deleteLater();
}

void MainWindow::onStorageQuotaCancelled(StorageQuota *quota) {
    m_actionButton->setEnabled(true);
    m_cancelButton->setEnabled(false);
    m_resultEdit->append(tr("Operation cancelled."));
    quota->deleteLater();
}

void MainWindow::showAboutDialog() {
    AboutDialog *dialog = new AboutDialog(this);
    dialog->open();
}
