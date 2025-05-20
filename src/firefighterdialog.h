#ifndef FIREFIGHTERDIALOG_H
#define FIREFIGHTERDIALOG_H

#include <optional>

#include <QDialog>
#include <QLineEdit>

#include "firefighter.hpp"

class FirefighterDialog : public QDialog
{
    Q_OBJECT
  public:
    FirefighterDialog(QWidget* parent = nullptr);

    void setData(Firefighter f);
    void setData(int id, const QString& name, const QString& surname, const QString& address,
                 const QString& pesel, const QString& phone, const QString& account);

    Firefighter getFirefighter() const;

  private:
    QLineEdit *nameEdit, *surnameEdit, *addressEdit, *peselEdit, *phoneEdit, *accountEdit;

    std::optional<int> id = std::nullopt;
};

#endif // FIREFIGHTERDIALOG_H
