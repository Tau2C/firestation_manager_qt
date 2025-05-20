#ifndef BANKDIALOG_H
#define BANKDIALOG_H

#include <optional>

#include <QDialog>
#include <QLineEdit>

#include "bank.hpp"

class BankDialog : public QDialog
{
    Q_OBJECT
  public:
    BankDialog(QWidget* parent = nullptr);

    void setData(Bank b);

    Bank getBank() const;

  private:
    QLineEdit* idEdit;
    QLineEdit* nameEdit;
};

#endif
