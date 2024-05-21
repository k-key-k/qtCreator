#include "atm.h"
#include <QDebug>
#include <QThread>

ATM::ATM(int id, int startCash) : id(id), cash(startCash) {}

int ATM::getCash() const {
    return cash;
}

void ATM::withdrawCash(int amount) {
    if (amount > cash) {
        qDebug() << "ATM" << id << ": Ошибка вывода средств!";
        return;
    }
    qDebug() << "ATM" << id << ": Вывод средств начат.";
    QThread::sleep(2);
    cash -= amount;
    qDebug() << "ATM" << id << ": Вывод средств завершен.";
    qDebug() << "ATM" << id << ": Текущие средства:" << cash;
    emit cashChanged(cash);

}

void ATM::depositCash(int amount) {

    qDebug() << "ATM" << id << ": Пополнение счёта начато.";
    QThread::sleep(1);
    cash += amount;
    qDebug() << "ATM" << id << ": Пополнение счёта завершено.";
    qDebug() << "ATM" << id << ": Текущие средства:" << cash;
    emit cashChanged(cash);
}
