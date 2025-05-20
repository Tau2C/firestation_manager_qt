#ifndef FIREFIGHTERTRAININGDIALOG_H
#define FIREFIGHTERTRAININGDIALOG_H

#include <QCalendarWidget>
#include <QComboBox>
#include <QDialog>

#include <db_manager.hpp>
#include <firefighter.hpp>
#include <firefighter_training.hpp>
#include <training.hpp>

class FirefighterTrainingDialog : public QDialog
{
    Q_OBJECT
  public:
    FirefighterTrainingDialog(const std::vector<Firefighter>& firefighters,
                              const std::vector<Training>& trainings, QWidget* parent = nullptr);

    FirefighterTraining getFirefighterTraining();
    void                setData(DBManager& db, const FirefighterTraining& ft);

  private:
    QComboBox*       firefighterEdit;
    QComboBox*       trainingEdit;
    QCalendarWidget* dateCalendar;
    QCalendarWidget* expirationCalendar;
    QComboBox*       statusCombo;
};

#endif // FIREFIGHTERTRAININGDIALOG_H
