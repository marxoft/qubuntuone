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
#include "authentication.h"
#include "aboutdialog.h"
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QRegExpValidator>
#include <QPushButton>
#include <QFormLayout>
#include <QVBoxLayout>
#ifndef Q_WS_MAEMO_5
#include <QMenuBar>
#include <QMenu>
#include <QCoreApplication>
#endif

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_applicationEdit(new QLineEdit("QUbuntuOne", this)),
    m_emailEdit(new QLineEdit(this)),
    m_passwordEdit(new QLineEdit(this)),
    m_otpEdit(new QLineEdit(this)),
    m_authenticateButton(new QPushButton(tr("Authenticate"), this)),
    m_resultEdit(new QTextEdit(this))
{
    this->setMinimumSize(400, 400);
    this->setWindowTitle(tr("QUbuntuOne Authentication Example"));
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
    m_applicationEdit->setValidator(new QRegExpValidator(QRegExp(".+"), m_applicationEdit));
    m_emailEdit->setValidator(new QRegExpValidator(QRegExp("[\\S]+@[\\S]+"), m_emailEdit));
    m_passwordEdit->setValidator(new QRegExpValidator(QRegExp("[\\S]+"), m_passwordEdit));
    m_passwordEdit->setEchoMode(QLineEdit::Password);
    m_otpEdit->setValidator(new QRegExpValidator(QRegExp("([\\S]+|)"), m_passwordEdit));
    m_otpEdit->setEchoMode(QLineEdit::Password);
    m_resultEdit->setReadOnly(true);
    m_authenticateButton->setEnabled(false);

    QWidget *formWidget = new QWidget(this);
    QFormLayout *formLayout = new QFormLayout(formWidget);
    formLayout->setContentsMargins(0, 0, 0, 0);
    formLayout->addRow(tr("&Application name:"), m_applicationEdit);
    formLayout->addRow(tr("&Email:"), m_emailEdit);
    formLayout->addRow(tr("&Password:"), m_passwordEdit);
    formLayout->addRow(tr("&One time password (optional)"), m_otpEdit);

    QVBoxLayout *vbox = new QVBoxLayout(this->centralWidget());
    vbox->addWidget(formWidget);
    vbox->addWidget(m_authenticateButton, 0, Qt::AlignRight);
    vbox->addWidget(new QLabel(tr("Result:"), this));
    vbox->addWidget(m_resultEdit);

    this->connect(m_applicationEdit, SIGNAL(textEdited(QString)), this, SLOT(onCredentialsChanged()));
    this->connect(m_emailEdit, SIGNAL(textEdited(QString)), this, SLOT(onCredentialsChanged()));
    this->connect(m_passwordEdit, SIGNAL(textEdited(QString)), this, SLOT(onCredentialsChanged()));
    this->connect(m_otpEdit, SIGNAL(textEdited(QString)), this, SLOT(onCredentialsChanged()));
    this->connect(m_authenticateButton, SIGNAL(clicked()), this, SLOT(authenticate()));
}

MainWindow::~MainWindow() {}

void MainWindow::onCredentialsChanged() {
    m_authenticateButton->setEnabled((m_applicationEdit->hasAcceptableInput())
                                     && (m_emailEdit->hasAcceptableInput())
                                     && (m_passwordEdit->hasAcceptableInput())
                                     && (m_otpEdit->hasAcceptableInput()));
}

void MainWindow::authenticate() {
    m_resultEdit->setText(tr("Authenticating..."));

    Token *token = m_otpEdit->text().isEmpty() ? Authentication::authenticate(m_emailEdit->text(),
                                                              m_passwordEdit->text(),
                                                              m_applicationEdit->text())
                                                             : Authentication::authenticate(m_emailEdit->text(),
                                                                                            m_passwordEdit->text(),
                                                                                            m_otpEdit->text(),
                                                                                            m_applicationEdit->text());

    this->connect(token, SIGNAL(ready(Token*)), this, SLOT(onTokenReady(Token*)));
}

void MainWindow::onTokenReady(Token *token) {
    m_resultEdit->clear();

    switch (token->error()) {
    case Token::NoError:
        m_resultEdit->append(tr("Token name: %1").arg(token->tokenName()));
        m_resultEdit->append(tr("Consumer key: %1").arg(token->consumerKey()));
        m_resultEdit->append(tr("Consumer secret: %1").arg(token->consumerSecret()));
        m_resultEdit->append(tr("Token key: %1").arg(token->tokenKey()));
        m_resultEdit->append(tr("Token secret: %1").arg(token->tokenSecret()));
        break;
    default:
        m_resultEdit->append(tr("Error: %1").arg(token->errorString()));
        break;
    }

    token->deleteLater();
}

void MainWindow::showAboutDialog() {
    AboutDialog *dialog = new AboutDialog(this);
    dialog->open();
}
