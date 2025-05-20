#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "db_manager.hpp"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

  private:
    Ui::MainWindow*            ui;
    std::unique_ptr<DBManager> db;

    void onTabChanged(int index);

    void initFirefighters();
    void initFirefighterTrainings();
    void initTrainings();
    void initMedicalExaminations();
    void initBanks();

    void loadFirefighters();
    void loadTrainings();
    void loadMedicalExaminations();
    void loadFirefighterTrainings();
    void loadBanks();
};
#endif // MAINWINDOW_H
