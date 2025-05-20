#include "firefighterdialog.h"

#include <QDialogButtonBox>
#include <QFormLayout>

FirefighterDialog::FirefighterDialog(QWidget* parent) : QDialog(parent)
{
    setWindowTitle("Add Firefighter");

    auto* layout = new QFormLayout(this);
    nameEdit     = new QLineEdit;
    surnameEdit  = new QLineEdit;
    addressEdit  = new QLineEdit;
    peselEdit    = new QLineEdit;
    phoneEdit    = new QLineEdit;
    accountEdit  = new QLineEdit;

    layout->addRow("Name:", nameEdit);
    layout->addRow("Surname:", surnameEdit);
    layout->addRow("Address:", addressEdit);
    layout->addRow("PESEL:", peselEdit);
    layout->addRow("Phone:", phoneEdit);
    layout->addRow("Account #:", accountEdit);

    auto* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout->addWidget(buttons);
    connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

Firefighter FirefighterDialog::getFirefighter() const
{
    if (this->id.has_value())
        return Firefighter{.firefighter_id = *(this->id),
                           .name           = nameEdit->text().toStdString(),
                           .surname        = surnameEdit->text().toStdString(),
                           .address        = addressEdit->text().toStdString(),
                           .pesel          = peselEdit->text().toStdString(),
                           .phone          = phoneEdit->text().toStdString(),
                           .account_number = accountEdit->text().toStdString()};
    else
        return Firefighter{.name           = nameEdit->text().toStdString(),
                           .surname        = surnameEdit->text().toStdString(),
                           .address        = addressEdit->text().toStdString(),
                           .pesel          = peselEdit->text().toStdString(),
                           .phone          = phoneEdit->text().toStdString(),
                           .account_number = accountEdit->text().toStdString()};
}

void FirefighterDialog::setData(int id, const QString& name, const QString& surname,
                                const QString& address, const QString& pesel, const QString& phone,
                                const QString& account)
{
    this->id = std::optional<int>{id}; // store ID internally
    nameEdit->setText(name);
    surnameEdit->setText(surname);
    addressEdit->setText(address);
    peselEdit->setText(pesel);
    phoneEdit->setText(phone);
    accountEdit->setText(account);
}

void FirefighterDialog::setData(Firefighter f)
{
    this->id = std::optional<int>{f.firefighter_id};
    nameEdit->setText(QString::fromStdString(f.name));
    surnameEdit->setText(QString::fromStdString(f.surname));
    addressEdit->setText(QString::fromStdString(f.address.value_or("")));
    peselEdit->setText(QString::fromStdString(f.pesel.value_or("")));
    phoneEdit->setText(QString::fromStdString(f.phone.value_or("")));
    accountEdit->setText(QString::fromStdString(f.account_number.value_or("")));
}
