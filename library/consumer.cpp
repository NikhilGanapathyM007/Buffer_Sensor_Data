#include "consumer.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMutexLocker>

Consumer::Consumer(QSqlDatabase db, QMutex *mutex, QObject *parent)
    : QObject(parent), db(db), dbMutex(mutex) {}

void Consumer::consumeData() {
    QMutexLocker locker(dbMutex);

    QSqlQuery readQuery(db);
    if (readQuery.exec("SELECT ID, Temperature, Voltage, Timestamp FROM SensorData ORDER BY ID LIMIT 1")) {
        if (readQuery.next()) {
            int id = readQuery.value("ID").toInt();
            double temperature = readQuery.value("Temperature").toDouble();
            double voltage = readQuery.value("Voltage").toDouble();
            QString timestamp = readQuery.value("Timestamp").toString();

            QString data = QString("ID: %1, Temperature: %2, Voltage: %3, Timestamp: %4")
                               .arg(id).arg(temperature).arg(voltage).arg(timestamp);
            qDebug() << "Processing - " << data;

            QSqlQuery deleteQuery(db);
            deleteQuery.prepare("DELETE FROM SensorData WHERE ID = :id");
            deleteQuery.bindValue(":id", id);

            if (deleteQuery.exec()) {
                emit dataConsumed(data);  // Emit signal with data string
            } else {
                qDebug() << "Error deleting data:" << deleteQuery.lastError().text();
            }
        } else {
            qDebug() << "No data to consume; the database is empty.";
        }
    } else {
        qDebug() << "Error reading data:" << readQuery.lastError().text();
    }
}
