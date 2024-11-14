#ifndef CONSUMER_H
#define CONSUMER_H

#include <QObject>
#include <QSqlDatabase>
#include <QMutex>

class Consumer : public QObject {
    Q_OBJECT

public:
    explicit Consumer(QSqlDatabase db, QMutex *mutex, QObject *parent = nullptr);

public slots:
    void consumeData();

signals:
    void dataConsumed(const QString &data);  // Signal to emit consumed data

private:
    QSqlDatabase db;
    QMutex *dbMutex;
};

#endif // CONSUMER_H
