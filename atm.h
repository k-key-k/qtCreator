#ifndef ATM_H
#define ATM_H

#include <QObject>
#include <QThread>

class ATM : public QObject {
    Q_OBJECT
public:
    ATM(int id, int startCash);

    int getCash() const;

public slots:
    void withdrawCash(int amount);
    void depositCash(int amoun);

signals:
    void finished();
    void cashChanged(int newCash);

private:
    int id;
    int cash;
};

#endif // ATM_H
