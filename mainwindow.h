#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QSqlDatabase setupDatabase();

public slots:
    void displayProducedData(const QString &data);  // Slot to display produced data
    void displayConsumedData(const QString &data);  // Slot to display consumed data

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H