#include "trainingdialog.h"

#include <QDialogButtonBox>
#include <QFormLayout>

TrainingDialog::TrainingDialog(QWidget* parent) : QDialog(parent)
{
    setWindowTitle("Add Training");

    auto* layout = new QFormLayout(this);

    auto* buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout->addWidget(buttons);
    connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

Training TrainingDialog::getTraining() const
{
    return Training{};
}

void TrainingDialog::setData(Training ft)
{
}
