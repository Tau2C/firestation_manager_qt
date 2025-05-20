#ifndef MEDICALEXAMINATIONSDIALOG_H
#define MEDICALEXAMINATIONSDIALOG_H

#include <optional>
#include <vector>

#include <QCalendarWidget>
#include <QComboBox>
#include <QDialog>
#include <QLineEdit>

#include <db_manager.hpp>
#include <firefighter_repository.hpp>

#include "medical_examination.hpp"

class MedicalExaminationsDialog : public QDialog
{
    Q_OBJECT
  public:
    MedicalExaminationsDialog(std::vector<Firefighter> firefighters, QWidget* parent = nullptr);

    void setData(DBManager& db, MedicalExamination ms);

    // MedicalExamination getMedicalExamination() const;
    MedicalExamination getMedicalExamination();

  private:
    QComboBox*       typeEdit;
    QComboBox*       idEdit;
    QCalendarWidget* dateCalendar;
    QCalendarWidget* expirationCalendar;
};

#endif
