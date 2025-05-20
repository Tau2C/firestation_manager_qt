#include "medicalexaminationsdialog.h"

#include <QDialogButtonBox>
#include <QFormLayout>
#include <QMessageBox>

#include <utils.hpp>

MedicalExaminationsDialog::MedicalExaminationsDialog(std::vector<Firefighter> firefighters,
                                                     QWidget*                 parent)
    : QDialog(parent)
{
    setWindowTitle("Add Medical Examination");

    auto* layout = new QFormLayout(this);
    typeEdit     = new QComboBox;
    typeEdit->addItem("FIREFIGHTER");
    typeEdit->addItem("DRIVER");

    idEdit = new QComboBox;

    for (auto f : firefighters)
    {
        idEdit->addItem(QString::fromStdString(std::string() + f.surname + " " + f.name),
                        QVariant(f.firefighter_id));
    }

    dateCalendar       = new QCalendarWidget;
    expirationCalendar = new QCalendarWidget;

    layout->addRow("Type:", typeEdit);
    layout->addRow("Firefighter:", idEdit);
    layout->addRow("Date:", dateCalendar);
    layout->addRow("Expiration:", expirationCalendar);

    auto* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout->addWidget(buttons);
    connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

void MedicalExaminationsDialog::setData(DBManager& db, MedicalExamination ms)
{
    typeEdit->setCurrentText(to_string(ms.type).c_str());

    FirefighterRepository repo(db);
    Firefighter           f = repo.get_by_id(ms.firefighter_id).value();
    idEdit->setCurrentText(QString::fromStdString(std::string() + f.surname + " " + f.name));

    QDate date = QDate::fromString(QString::fromStdString(to_pg_date(ms.date)), "yyyy-MM-dd");
    QDate expiration =
        QDate::fromString(QString::fromStdString(to_pg_date(ms.expiration)), "yyyy-MM-dd");

    dateCalendar->setSelectedDate(date);
    expirationCalendar->setSelectedDate(expiration);
}

// MedicalExamination MedicalExaminationsDialog::getMedicalExamination() const
MedicalExamination MedicalExaminationsDialog::getMedicalExamination()
{
    MedicalExamination result;

    result.type           = to_examination_type(typeEdit->currentText().toStdString());
    result.firefighter_id = idEdit->currentData().toInt();

    QDate qdate = dateCalendar->selectedDate();
    QDate qexp  = expirationCalendar->selectedDate();

    result.date = from_pg_date(qdate.toString("yyyy-MM-dd").toStdString());

    result.expiration = from_pg_date(qexp.toString("yyyy-MM-dd").toStdString());

    return result;
}
