#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QList>
#include "atm.h"

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

private slots:
    void startTransactions();

private:
    Ui::MainWindow *ui;
    QList<QLineEdit*> lineEdits;
    ATM *atm1;
    ATM *atm2;
    ATM *atm3;
    QThread *thread1;
    QThread *thread2;
    QThread *thread3;
};
#endif // MAINWINDOW_H
