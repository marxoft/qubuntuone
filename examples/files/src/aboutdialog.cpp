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

    QLabel *label = new QLabel("<b>QUbuntuOne Files Example</b><br><br>Part of QUbuntuOne.<br><br>&copy; Stuart Howarth 2014", this);
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
