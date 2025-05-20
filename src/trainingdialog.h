#ifndef TRAININGDIALOG_H
#define TRAININGDIALOG_H

#include <optional>

#include <QDialog>
#include <QLineEdit>

#include "training.hpp"

class TrainingDialog : public QDialog
{
    Q_OBJECT
  public:
    TrainingDialog(QWidget* parent = nullptr);

    void setData(Training t);

    Training getTraining() const;

  private:
};

#endif
