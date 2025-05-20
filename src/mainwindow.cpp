#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>

#include "bankdialog.h"
#include "firefighterdialog.h"
#include "firefightertrainingdialog.h"
#include "medicalexaminationsdialog.h"
#include "trainingdialog.h"

#include "bank_repository.hpp"
#include "firefighter_repository.hpp"
#include "firefighter_training_repository.hpp"
#include "medical_examination_repository.hpp"
#include "training_repository.hpp"
#include "utils.hpp"

#include "emptylasttablewidgetitem.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    std::string conn =
        std::string() + "host=localhost dbname=postgres user=postgres password=postgres port=5432";

    db = std::make_unique<DBManager>(conn);

    ui->setupUi(this);

    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::onTabChanged);

    initFirefighters();
    initFirefighterTrainings();
    initTrainings();
    initMedicalExaminations();
    initBanks();

    onTabChanged(ui->tabWidget->currentIndex());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initFirefighters()
{
    connect(ui->firefightersTableWidget, &QTableWidget::itemSelectionChanged, this,
            [this]()
            {
                bool hasSelection = !ui->firefightersTableWidget->selectedItems().isEmpty();
                ui->firefightersEditButton->setEnabled(hasSelection);
                ui->firefightersRemoveButton->setEnabled(hasSelection);
            });
    ui->firefightersEditButton->setEnabled(false);
    ui->firefightersRemoveButton->setEnabled(false);

    connect(ui->firefightersAddButton, &QPushButton::clicked, this,
            [this]()
            {
                FirefighterDialog dialog(this);
                if (dialog.exec() == QDialog::Accepted)
                {
                    FirefighterRepository repo(*db);
                    Firefighter           f = dialog.getFirefighter();
                    repo.insert(f);
                    loadFirefighters();
                }
            });

    connect(ui->firefightersEditButton, &QPushButton::clicked, this,
            [this]()
            {
                auto selectedItems = ui->firefightersTableWidget->selectedItems();
                if (selectedItems.isEmpty())
                {
                    QMessageBox::warning(this, "No selection",
                                         "Please select a firefighter to edit.");
                    return;
                }

                int row = ui->firefightersTableWidget->row(selectedItems.first());

                int id = ui->firefightersTableWidget->item(row, 0)->text().toInt();

                FirefighterRepository repo(*db);

                printf("%d", id);

                FirefighterDialog dialog(this);
                dialog.setData(repo.get_by_id(id).value());

                if (dialog.exec() == QDialog::Accepted)
                {
                    Firefighter updated = dialog.getFirefighter();

                    repo.update(id, updated);

                    loadFirefighters();
                }
            });

    connect(ui->firefightersRemoveButton, &QPushButton::clicked, this,
            [this]()
            {
                auto* table = ui->firefightersTableWidget;

                int row = table->currentRow();
                if (row < 0)
                {
                    QMessageBox::warning(this, "No selection",
                                         "Please select a firefighter to remove.");
                    return;
                }

                int id = table->item(row, 0)->text().toInt();

                auto reply = QMessageBox::question(
                    this, "Confirm deletion",
                    QString("Are you sure you want to remove firefighter with ID %1?").arg(id));

                if (reply == QMessageBox::Yes)
                {
                    try
                    {
                        FirefighterRepository repo(*db);
                        repo.remove(id);
                        loadFirefighters();
                    }
                    catch (const std::exception& e)
                    {
                        QMessageBox::critical(this, "Error", e.what());
                    }
                }
            });
}

void MainWindow::initFirefighterTrainings()
{
    connect(ui->firefighterTrainingTableWidget, &QTableWidget::itemSelectionChanged, this,
            [this]()
            {
                bool hasSelection = !ui->firefighterTrainingTableWidget->selectedItems().isEmpty();
                ui->firefighterTrainingEditButton->setEnabled(hasSelection);
                ui->firefighterTrainingRemoveButton->setEnabled(hasSelection);
            });
    ui->firefighterTrainingEditButton->setEnabled(false);
    ui->firefighterTrainingRemoveButton->setEnabled(false);

    connect(ui->firefighterTrainingAddButton, &QPushButton::clicked, this,
            [this]()
            {
                FirefighterTrainingDialog dialog(FirefighterRepository(*db).get_all(),
                                                 TrainingRepository(*db).get_all(), this);
                if (dialog.exec() == QDialog::Accepted)
                {
                    FirefighterTrainingRepository repo(*db);
                    FirefighterTraining           ft = dialog.getFirefighterTraining();
                    repo.insert(ft);
                    loadFirefighterTrainings();
                }
            });

    connect(ui->firefighterTrainingEditButton, &QPushButton::clicked, this,
            [this]()
            {
                auto selectedItems = ui->firefighterTrainingTableWidget->selectedItems();
                if (selectedItems.isEmpty())
                {
                    QMessageBox::warning(this, "No selection",
                                         "Please select a firefighter training to edit.");
                    return;
                }

                int row = ui->firefighterTrainingTableWidget->row(selectedItems.first());

                int id = ui->firefighterTrainingTableWidget->item(row, 0)->text().toInt();

                FirefighterTrainingRepository repo(*db);

                FirefighterTrainingDialog dialog(FirefighterRepository(*db).get_all(),
                                                 TrainingRepository(*db).get_all(), this);
                dialog.setData(*db, repo.get_by_id(id).value());

                if (dialog.exec() == QDialog::Accepted)
                {
                    FirefighterTraining updated = dialog.getFirefighterTraining();

                    repo.update(id, updated);

                    loadFirefighterTrainings();
                }
            });

    connect(ui->firefighterTrainingRemoveButton, &QPushButton::clicked, this,
            [this]()
            {
                auto* table = ui->firefighterTrainingTableWidget;

                int row = table->currentRow();
                if (row < 0)
                {
                    QMessageBox::warning(this, "No selection",
                                         "Please select a firefighter to remove.");
                    return;
                }

                int id = table->item(row, 0)->text().toInt();

                auto reply = QMessageBox::question(
                    this, "Confirm deletion",
                    QString("Are you sure you want to remove firefighter with ID %1?").arg(id));

                if (reply == QMessageBox::Yes)
                {
                    try
                    {
                        FirefighterRepository repo(*db);
                        repo.remove(id);
                        loadFirefighterTrainings();
                    }
                    catch (const std::exception& e)
                    {
                        QMessageBox::critical(this, "Error", e.what());
                    }
                }
            });
}

void MainWindow::initTrainings()
{
    connect(ui->trainingsTableWidget, &QTableWidget::itemSelectionChanged, this,
            [this]()
            {
                bool hasSelection = !ui->trainingsTableWidget->selectedItems().isEmpty();
                ui->trainingsEditButton->setEnabled(hasSelection);
                ui->trainingsRemoveButton->setEnabled(hasSelection);
            });
    ui->trainingsEditButton->setEnabled(false);
    ui->trainingsRemoveButton->setEnabled(false);

    connect(ui->trainingsAddButton, &QPushButton::clicked, this,
            [this]()
            {
                TrainingDialog dialog(this);
                if (dialog.exec() == QDialog::Accepted)
                {
                    TrainingRepository repo(*db);
                    Training           t = dialog.getTraining();
                    repo.insert(t);
                    loadTrainings();
                }
            });

    connect(ui->trainingsEditButton, &QPushButton::clicked, this,
            [this]()
            {
                auto selectedItems = ui->firefightersTableWidget->selectedItems();
                if (selectedItems.isEmpty())
                {
                    QMessageBox::warning(this, "No selection",
                                         "Please select a firefighter to edit.");
                    return;
                }

                int row = ui->firefightersTableWidget->row(selectedItems.first());

                int id = ui->firefightersTableWidget->item(row, 0)->text().toInt();

                FirefighterRepository repo(*db);

                printf("%d", id);

                FirefighterDialog dialog(this);
                dialog.setData(repo.get_by_id(id).value());

                if (dialog.exec() == QDialog::Accepted)
                {
                    Firefighter updated = dialog.getFirefighter();

                    repo.update(id, updated);

                    loadTrainings();
                }
            });

    connect(ui->trainingsRemoveButton, &QPushButton::clicked, this,
            [this]()
            {
                auto* table = ui->firefightersTableWidget;

                int row = table->currentRow();
                if (row < 0)
                {
                    QMessageBox::warning(this, "No selection",
                                         "Please select a firefighter to remove.");
                    return;
                }

                int id = table->item(row, 0)->text().toInt();

                auto reply = QMessageBox::question(
                    this, "Confirm deletion",
                    QString("Are you sure you want to remove firefighter with ID %1?").arg(id));

                if (reply == QMessageBox::Yes)
                {
                    try
                    {
                        FirefighterRepository repo(*db);
                        repo.remove(id);
                        loadTrainings();
                    }
                    catch (const std::exception& e)
                    {
                        QMessageBox::critical(this, "Error", e.what());
                    }
                }
            });
}

void MainWindow::initMedicalExaminations()
{
    connect(ui->medicalExaminationsTableWidget, &QTableWidget::itemSelectionChanged, this,
            [this]()
            {
                bool hasSelection = !ui->medicalExaminationsTableWidget->selectedItems().isEmpty();
                ui->medicalExaminationsEditButton->setEnabled(hasSelection);
                ui->medicalExaminationsRemoveButton->setEnabled(hasSelection);
            });
    ui->medicalExaminationsEditButton->setEnabled(false);
    ui->medicalExaminationsRemoveButton->setEnabled(false);

    connect(ui->medicalExaminationsAddButton, &QPushButton::clicked, this,
            [this]()
            {
                MedicalExaminationsDialog dialog(FirefighterRepository(*db).get_all(), this);
                if (dialog.exec() == QDialog::Accepted)
                {
                    MedicalExaminationRepository repo(*db);
                    MedicalExamination           me = dialog.getMedicalExamination();
                    repo.insert(me);
                    loadMedicalExaminations();
                }
            });

    connect(ui->medicalExaminationsEditButton, &QPushButton::clicked, this,
            [this]()
            {
                auto selectedItems = ui->medicalExaminationsTableWidget->selectedItems();
                if (selectedItems.isEmpty())
                {
                    QMessageBox::warning(this, "No selection", "Please select a bank to edit.");
                    return;
                }

                int row = ui->medicalExaminationsTableWidget->row(selectedItems.first());

                int id = ui->medicalExaminationsTableWidget->item(row, 0)->text().toInt();

                MedicalExaminationRepository repo(*db);

                // Show dialog for editing (you can reuse the add form, just initialize with values)
                ;
                MedicalExaminationsDialog dialog(FirefighterRepository(*db).get_all(), this);
                dialog.setData(*db, repo.get_by_id(id).value());

                if (dialog.exec() == QDialog::Accepted)
                {
                    MedicalExamination updated = dialog.getMedicalExamination();

                    // Update in DB
                    repo.update(id, updated);

                    // Reload table
                    loadMedicalExaminations();
                }
            });

    connect(ui->medicalExaminationsRemoveButton, &QPushButton::clicked, this,
            [this]()
            {
                auto* table = ui->medicalExaminationsTableWidget;

                int row = table->currentRow();
                if (row < 0)
                {
                    QMessageBox::warning(this, "No selection",
                                         "Please select an examination to remove.");
                    return;
                }

                int id = table->item(row, 0)->text().toInt();

                auto reply = QMessageBox::question(
                    this, "Confirm deletion",
                    QString("Are you sure you want to remove examination with ID %1?").arg(id));

                if (reply == QMessageBox::Yes)
                {
                    try
                    {
                        MedicalExaminationRepository repo(*db);
                        repo.remove(id);
                        loadMedicalExaminations();
                    }
                    catch (const std::exception& e)
                    {
                        QMessageBox::critical(this, "Error", e.what());
                    }
                }
            });
}

void MainWindow::initBanks()
{
    connect(ui->banksTableWidget, &QTableWidget::itemSelectionChanged, this,
            [this]()
            {
                bool hasSelection = !ui->banksTableWidget->selectedItems().isEmpty();
                ui->banksEditButton->setEnabled(hasSelection);
                ui->banksRemoveButton->setEnabled(hasSelection);
            });
    ui->banksEditButton->setEnabled(false);
    ui->banksRemoveButton->setEnabled(false);

    connect(ui->banksAddButton, &QPushButton::clicked, this,
            [this]()
            {
                BankDialog dialog(this);
                if (dialog.exec() == QDialog::Accepted)
                {
                    BankRepository repo(*db);
                    Bank           b = dialog.getBank();
                    repo.insert(b);
                    loadBanks();
                }
            });

    connect(ui->banksEditButton, &QPushButton::clicked, this,
            [this]()
            {
                auto selectedItems = ui->banksTableWidget->selectedItems();
                if (selectedItems.isEmpty())
                {
                    QMessageBox::warning(this, "No selection", "Please select a bank to edit.");
                    return;
                }

                int row = ui->banksTableWidget->row(selectedItems.first());

                std::string id = ui->banksTableWidget->item(row, 0)->text().toStdString();

                BankRepository repo(*db);

                // Show dialog for editing (you can reuse the add form, just initialize with values)
                BankDialog dialog(this);
                dialog.setData(repo.get_by_id(id).value());

                if (dialog.exec() == QDialog::Accepted)
                {
                    Bank updated = dialog.getBank();

                    // Update in DB
                    repo.update(id, updated);

                    // Reload table
                    loadBanks();
                }
            });

    connect(ui->banksRemoveButton, &QPushButton::clicked, this,
            [this]()
            {
                auto* table = ui->banksTableWidget;

                int row = table->currentRow();
                if (row < 0)
                {
                    QMessageBox::warning(this, "No selection", "Please select a bank to remove.");
                    return;
                }

                std::string id = table->item(row, 0)->text().toStdString();

                auto reply = QMessageBox::question(
                    this, "Confirm deletion",
                    QString("Are you sure you want to remove bank with ID %1?")
                        .arg(QString::fromStdString(id)));

                if (reply == QMessageBox::Yes)
                {
                    try
                    {
                        BankRepository repo(*db);
                        repo.remove(id);
                        loadBanks();
                    }
                    catch (const std::exception& e)
                    {
                        QMessageBox::critical(this, "Error", e.what());
                    }
                }
            });
}

void MainWindow::onTabChanged(int index)
{
    QWidget* tab = ui->tabWidget->widget(index);
    if (tab == ui->firefightersTab)
    {
        loadFirefighters();
    }
    else if (tab == ui->trainingsTab)
    {
        loadTrainings();
    }
    else if (tab == ui->banksTab)
    {
        loadBanks();
    }
    else if (tab == ui->firefighterTrainingTab)
    {
        loadFirefighterTrainings();
    }
    else if (tab == ui->medicalExaminationsTab)
    {
        loadMedicalExaminations();
    }
}

void MainWindow::loadFirefighters()
{
    FirefighterRepository repo(*db);
    auto                  list = repo.get_all();

    ui->firefightersTableWidget->setSortingEnabled(false);

    ui->firefightersTableWidget->setRowCount(static_cast<int>(list.size()));
    ui->firefightersTableWidget->setColumnCount(8);
    QStringList headers = {"ID",      "Name",    "Surname", "Phone",
                           "Account", "Address", "Email",   "PESEL"};
    ui->firefightersTableWidget->setHorizontalHeaderLabels(headers);
    ui->firefightersTableWidget->verticalHeader()->setVisible(false);

    for (int i = 0; i < static_cast<int>(list.size()); ++i)
    {
        const auto& f = list[i];
        ui->firefightersTableWidget->setItem(
            i, 0, new EmptyLastTableWidgetItem(QString::number(f.firefighter_id)));
        ui->firefightersTableWidget->setItem(
            i, 1, new EmptyLastTableWidgetItem(QString::fromStdString(f.name)));
        ui->firefightersTableWidget->setItem(
            i, 2, new EmptyLastTableWidgetItem(QString::fromStdString(f.surname)));
        ui->firefightersTableWidget->setItem(
            i, 3, new EmptyLastTableWidgetItem(QString::fromStdString(f.phone.value_or(""))));
        ui->firefightersTableWidget->setItem(
            i, 4,
            new EmptyLastTableWidgetItem(QString::fromStdString(f.account_number.value_or(""))));
        ui->firefightersTableWidget->setItem(
            i, 5, new EmptyLastTableWidgetItem(QString::fromStdString(f.address.value_or(""))));
        ui->firefightersTableWidget->setItem(
            i, 6, new EmptyLastTableWidgetItem(QString::fromStdString(f.email.value_or(""))));
        ui->firefightersTableWidget->setItem(
            i, 7, new EmptyLastTableWidgetItem(QString::fromStdString(f.pesel.value_or(""))));
    }

    ui->firefightersTableWidget->resizeColumnsToContents();
    ui->firefightersTableWidget->setSortingEnabled(true);
}

void MainWindow::loadTrainings()
{
    TrainingRepository repo(*db);
    auto               list = repo.get_all();

    ui->trainingsTableWidget->setSortingEnabled(false);

    ui->trainingsTableWidget->setRowCount(static_cast<int>(list.size()));
    ui->trainingsTableWidget->setColumnCount(2);
    QStringList headers = {"ID", "Name"};
    ui->trainingsTableWidget->setHorizontalHeaderLabels(headers);
    ui->trainingsTableWidget->verticalHeader()->setVisible(false);

    for (int i = 0; i < static_cast<int>(list.size()); ++i)
    {
        const auto& t = list[i];
        ui->trainingsTableWidget->setItem(
            i, 0, new EmptyLastTableWidgetItem(QString::fromStdString(t.id)));
        ui->trainingsTableWidget->setItem(
            i, 1, new EmptyLastTableWidgetItem(QString::fromStdString(t.name)));
    }

    ui->trainingsTableWidget->resizeColumnsToContents();

    ui->trainingsTableWidget->setSortingEnabled(true);
}

void MainWindow::loadMedicalExaminations()
{
    MedicalExaminationRepository repo(*db);
    auto                         list = repo.get_all();

    ui->medicalExaminationsTableWidget->setSortingEnabled(false);

    ui->medicalExaminationsTableWidget->setRowCount(static_cast<int>(list.size()));
    ui->medicalExaminationsTableWidget->setColumnCount(5);
    QStringList headers = {"ID", "Type", "Firefighter", "Date", "Expiration"};
    ui->medicalExaminationsTableWidget->setHorizontalHeaderLabels(headers);
    ui->medicalExaminationsTableWidget->verticalHeader()->setVisible(false);

    for (int i = 0; i < static_cast<int>(list.size()); ++i)
    {
        const MedicalExamination& me = list[i];
        ui->medicalExaminationsTableWidget->setItem(
            i, 0, new EmptyLastTableWidgetItem(QString::number(me.id)));
        ui->medicalExaminationsTableWidget->setItem(
            i, 1, new EmptyLastTableWidgetItem(QString::fromStdString(to_string(me.type))));
        Firefighter f = FirefighterRepository(*db).get_by_id(me.firefighter_id).value();
        ui->medicalExaminationsTableWidget->setItem(
            i, 2,
            new EmptyLastTableWidgetItem(
                QString::fromStdString(std::string() + f.surname + " " + f.name)));
        ui->medicalExaminationsTableWidget->setItem(
            i, 3, new EmptyLastTableWidgetItem(QString::fromStdString(to_pg_date(me.date))));
        ui->medicalExaminationsTableWidget->setItem(
            i, 4, new EmptyLastTableWidgetItem(QString::fromStdString(to_pg_date(me.expiration))));
    }

    ui->medicalExaminationsTableWidget->resizeColumnsToContents();

    ui->medicalExaminationsTableWidget->setSortingEnabled(false);
}

void MainWindow::loadFirefighterTrainings()
{
    FirefighterTrainingRepository repo(*db);
    auto                          list = repo.get_all();

    ui->firefighterTrainingTableWidget->setSortingEnabled(false);

    ui->firefighterTrainingTableWidget->setRowCount(static_cast<int>(list.size()));
    ui->firefighterTrainingTableWidget->setColumnCount(6);
    QStringList headers = {"ID", "Firefighter", "Training", "Date", "Expiration", "Status"};
    ui->firefighterTrainingTableWidget->setHorizontalHeaderLabels(headers);
    ui->firefighterTrainingTableWidget->verticalHeader()->setVisible(false);

    for (int i = 0; i < static_cast<int>(list.size()); ++i)
    {
        const auto& ft = list[i];
        ui->firefighterTrainingTableWidget->setItem(
            i, 0, new EmptyLastTableWidgetItem(QString::number(ft.id)));
        Firefighter f = FirefighterRepository(*db).get_by_id(ft.firefighter_id).value();
        ui->firefighterTrainingTableWidget->setItem(
            i, 1,
            new EmptyLastTableWidgetItem(
                QString::fromStdString(std::string() + f.surname + " " + f.name)));
        Training t = TrainingRepository(*db).get_by_id(ft.training_id).value();
        ui->firefighterTrainingTableWidget->setItem(
            i, 2, new EmptyLastTableWidgetItem(QString::fromStdString(std::string() + t.name)));
        ui->firefighterTrainingTableWidget->setItem(
            i, 3, new EmptyLastTableWidgetItem(QString::fromStdString(to_pg_date(ft.date))));
        ui->firefighterTrainingTableWidget->setItem(
            i, 4,
            new EmptyLastTableWidgetItem(QString::fromStdString(
                ft.expiration.has_value() ? to_pg_date(ft.expiration.value()) : "")));
        ui->firefighterTrainingTableWidget->setItem(
            i, 5,
            new EmptyLastTableWidgetItem(QString::fromStdString(repo.status_to_string(ft.status))));
    }

    ui->firefighterTrainingTableWidget->resizeColumnsToContents();

    ui->firefighterTrainingTableWidget->setSortingEnabled(false);
}

void MainWindow::loadBanks()
{
    BankRepository repo(*db);
    auto           list = repo.get_all();

    ui->banksTableWidget->setSortingEnabled(false);

    ui->banksTableWidget->setRowCount(static_cast<int>(list.size()));
    ui->banksTableWidget->setColumnCount(2);
    QStringList headers = {"ID", "Name"};
    ui->banksTableWidget->setHorizontalHeaderLabels(headers);
    ui->banksTableWidget->verticalHeader()->setVisible(false);

    for (int i = 0; i < static_cast<int>(list.size()); ++i)
    {
        const auto& b = list[i];
        ui->banksTableWidget->setItem(i, 0,
                                      new EmptyLastTableWidgetItem(QString::fromStdString(b.id)));
        ui->banksTableWidget->setItem(i, 1,
                                      new EmptyLastTableWidgetItem(QString::fromStdString(b.name)));
    }

    ui->banksTableWidget->resizeColumnsToContents();

    ui->banksTableWidget->setSortingEnabled(false);
}
