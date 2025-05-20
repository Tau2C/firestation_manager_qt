#include "bankdialog.h"

#include <QDialogButtonBox>
#include <QFormLayout>

BankDialog::BankDialog(QWidget* parent) : QDialog(parent)
{
    setWindowTitle("Add Bank");

    auto* layout = new QFormLayout(this);
    idEdit       = new QLineEdit;
    nameEdit     = new QLineEdit;

    layout->addRow("Id:", idEdit);
    layout->addRow("Name:", nameEdit);

    auto* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout->addWidget(buttons);
    connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

Bank BankDialog::getBank() const
{
    return Bank{.id = idEdit->text().toStdString(), .name = nameEdit->text().toStdString()};
}

void BankDialog::setData(Bank b)
{
    idEdit->setText(QString::fromStdString(b.id));
    nameEdit->setText(QString::fromStdString(b.name));
}
