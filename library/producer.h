#ifndef PRODUCER_H
#define PRODUCER_H

#include <QObject>
#include <QSqlDatabase>
#include <QMutex>

class Producer : public QObject {
    Q_OBJECT

public:
    explicit Producer(QSqlDatabase db, QMutex *mutex, QObject *parent = nullptr);

public slots:
    void produceData();

signals:
    void dataProduced(const QString &data);  // Signal to emit produced data

private:
    QSqlDatabase db;
    QMutex *dbMutex;

    double generateRandomTemperature();
    double generateRandomVoltage();
};

#endif // PRODUCER_H
