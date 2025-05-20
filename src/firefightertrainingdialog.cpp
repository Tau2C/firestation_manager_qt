#include "firefightertrainingdialog.h"

#include <QDialogButtonBox>
#include <QFormLayout>
#include <QString>

#include <firefighter_repository.hpp>
#include <training_repository.hpp>
#include <utils.hpp>

FirefighterTrainingDialog::FirefighterTrainingDialog(const std::vector<Firefighter>& firefighters,
                                                     const std::vector<Training>&    trainings,
                                                     QWidget*                        parent)
    : QDialog(parent)
{
    setWindowTitle("Add Firefighter Training");

    auto* layout = new QFormLayout(this);

    firefighterEdit = new QComboBox;
    for (const auto& f : firefighters)
    {
        QString label = QString::fromStdString(f.surname + " " + f.name);
        firefighterEdit->addItem(label, QVariant(f.firefighter_id));
    }

    trainingEdit = new QComboBox;
    for (const auto& t : trainings)
    {
        trainingEdit->addItem(QString::fromStdString(t.id), QVariant(QString::fromStdString(t.id)));
    }

    dateCalendar       = new QCalendarWidget;
    expirationCalendar = new QCalendarWidget;

    statusCombo = new QComboBox;
    statusCombo->addItem("VALID");
    statusCombo->addItem("INVALID");

    layout->addRow("Firefighter:", firefighterEdit);
    layout->addRow("Training:", trainingEdit);
    layout->addRow("Date:", dateCalendar);
    layout->addRow("Expiration:", expirationCalendar);
    layout->addRow("Status:", statusCombo);

    auto* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout->addWidget(buttons);

    connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

FirefighterTraining FirefighterTrainingDialog::getFirefighterTraining()
{
    FirefighterTraining result;
    result.firefighter_id = firefighterEdit->currentData().toInt();
    result.training_id    = trainingEdit->currentData().toString().toStdString();
    result.status =
        statusCombo->currentText() == "VALID" ? TrainingStatus::Valid : TrainingStatus::Invalid;

    result.date = from_pg_date(dateCalendar->selectedDate().toString("yyyy-MM-dd").toStdString());
    result.expiration =
        from_pg_date(expirationCalendar->selectedDate().toString("yyyy-MM-dd").toStdString());

    return result;
}

void FirefighterTrainingDialog::setData(DBManager& db, const FirefighterTraining& ft)
{
    // Set firefighter combo
    FirefighterRepository frepo(db);
    if (auto opt = frepo.get_by_id(ft.firefighter_id))
    {
        const auto& f     = *opt;
        QString     label = QString::fromStdString(f.surname + " " + f.name);
        firefighterEdit->setCurrentText(label);
    }

    // Set training combo
    TrainingRepository trepo(db);
    if (auto opt = trepo.get_by_id(ft.training_id))
    {
        trainingEdit->setCurrentText(QString::fromStdString(opt->id));
    }

    // Dates
    QDate date = QDate::fromString(QString::fromStdString(to_pg_date(ft.date)), "yyyy-MM-dd");
    dateCalendar->setSelectedDate(date);

    if (ft.expiration)
    {
        QDate exp =
            QDate::fromString(QString::fromStdString(to_pg_date(*ft.expiration)), "yyyy-MM-dd");
        expirationCalendar->setSelectedDate(exp);
    }

    // Status
    statusCombo->setCurrentText(ft.status == TrainingStatus::Valid ? "VALID" : "INVALID");
}
