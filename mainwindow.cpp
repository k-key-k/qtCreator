#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    //, ui(new Ui::MainWindow)
{
    // ui->setupUi(this);

    QVBoxLayout *layout = new QVBoxLayout();
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    for (int i = 0; i < 3; ++i) {
        QLineEdit *lineEdit = new QLineEdit();
        layout->addWidget(lineEdit);
        lineEdits.append(lineEdit);
    }

    QPushButton *startButton = new QPushButton("START", this);
    layout->addWidget(startButton);
    connect(startButton, &QPushButton::clicked, this, &MainWindow::startTransactions);

    atm1 = new ATM(1, 1000);
    atm2 = new ATM(2, 1500);
    atm3 = new ATM(3, 2000);

    thread1 = new QThread();
    thread2 = new QThread();
    thread3 = new QThread();

    atm1->moveToThread(thread1);
    atm2->moveToThread(thread2);
    atm3->moveToThread(thread3);

    connect(atm1, &ATM::finished, thread1, &QThread::quit);
    connect(thread1, &QThread::finished, thread1, &QThread::deleteLater);
    connect(atm2, &ATM::finished, thread2, &QThread::quit);
    connect(thread2, &QThread::finished, thread2, &QThread::deleteLater);
    connect(atm3, &ATM::finished, thread3, &QThread::quit);
    connect(thread3, &QThread::finished, thread3, &QThread::deleteLater);

    thread1->start();
    thread2->start();
    thread3->start();
}

MainWindow::~MainWindow()
{
    // delete ui;
    delete atm1;
    delete atm2;
    delete atm3;
    delete thread1;
    delete thread2;
    delete thread3;
}

void MainWindow::startTransactions() {
    for (int i = 0; i < 3; ++i) {
        int amount = lineEdits[i]->text().toInt();
        if (amount > 0) {
            if (i == 0)
                QMetaObject::invokeMethod(atm1, "withdrawCash", Qt::QueuedConnection, Q_ARG(int, amount));
            else if (i == 1)
                QMetaObject::invokeMethod(atm2, "withdrawCash", Qt::QueuedConnection, Q_ARG(int, amount));
            else if (i == 2)
                QMetaObject::invokeMethod(atm3, "withdrawCash", Qt::QueuedConnection, Q_ARG(int, amount));
        } else if (amount < 0) {
            amount = -amount;
            if (i == 0)
                QMetaObject::invokeMethod(atm1, "depositCash", Qt::QueuedConnection, Q_ARG(int, amount));
            else if (i == 1)
                QMetaObject::invokeMethod(atm2, "depositCash", Qt::QueuedConnection, Q_ARG(int, amount));
            else if (i == 2)
                QMetaObject::invokeMethod(atm3, "depositCash", Qt::QueuedConnection, Q_ARG(int, amount));
        }
    }
}
