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

#include "aboutdialog.h"
#include <QLabel>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QDesktopServices>
#include <QUrl>

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent)
{
    this->setWindowTitle(tr("About"));
    this->setAttribute(Qt::WA_DeleteOnClose, true);

    QLabel *label = new QLabel("<b>QUbuntuOne Music Example</b><br><br>Part of QUbuntuOne.<br><br>&copy; Stuart Howarth 2014", this);
    label->setWordWrap(true);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(this);
    buttonBox->addButton(tr("Visit website"), QDialogButtonBox::AcceptRole);

    QGridLayout *grid = new QGridLayout(this);

#ifdef Q_WS_MAEMO_5
    buttonBox->setOrientation(Qt::Vertical);
    grid->addWidget(label, 0, 0);
    grid->addWidget(buttonBox, 0, 1);
#else
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->addButton(QDialogButtonBox::Close);
    grid->addWidget(label, 0, 0);
    grid->addWidget(buttonBox, 1, 0);
#endif

    this->connect(buttonBox, SIGNAL(accepted()), this, SLOT(showWebsite()));
    this->connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

AboutDialog::~AboutDialog() {}

void AboutDialog::showWebsite() {
    QDesktopServices::openUrl(QUrl("http://marxoft.co.uk/qubuntuone"));
    this->accept();
}
