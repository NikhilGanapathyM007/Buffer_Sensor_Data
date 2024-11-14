#include "producer.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QRandomGenerator64>

Producer::Producer(QSqlDatabase db, QMutex *mutex, QObject *parent)
    : QObject(parent), db(db), dbMutex(mutex) {}

void Producer::produceData() {
    double temperature = generateRandomTemperature();
    double voltage = generateRandomVoltage();

    QMutexLocker locker(dbMutex);
    QSqlQuery query(db);
    query.prepare("INSERT INTO SensorData (Temperature, Voltage) VALUES (:temperature, :voltage)");
    query.bindValue(":temperature", temperature);
    query.bindValue(":voltage", voltage);

    if (!query.exec()) {
        qDebug() << "Error inserting data:" << query.lastError().text();
    } else {
        QString data = QString("Data written - Temperature: %1 Voltage: %2").arg(temperature).arg(voltage);
        qDebug() << data;
        emit dataProduced(data);  // Emit signal with data string
    }
}

double Producer::generateRandomTemperature() {
    return 20.0 + static_cast<double>(QRandomGenerator::global()->bounded(1500)) / 100.0;
}

double Producer::generateRandomVoltage() {
    return 3.0 + static_cast<double>(QRandomGenerator::global()->bounded(200)) / 100.0;
}
