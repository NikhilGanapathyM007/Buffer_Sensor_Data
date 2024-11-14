#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "producer.h"
#include "consumer.h"
#include <QThread>
#include <QMutex>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set up database
    QSqlDatabase db = setupDatabase();
    QMutex *dbMutex = new QMutex();

    // Create producer and consumer objects
    Producer *producer = new Producer(db, dbMutex, this);
    Consumer *consumer = new Consumer(db, dbMutex, this);

    // Create threads
    QThread *producerThread = new QThread(this);
    QThread *consumerThread = new QThread(this);

    // Move producer and consumer to their respective threads
    producer->moveToThread(producerThread);
    consumer->moveToThread(consumerThread);

    // Connect signals to display produced and consumed data
    connect(producer, &Producer::dataProduced, this, &MainWindow::displayProducedData);
    connect(consumer, &Consumer::dataConsumed, this, &MainWindow::displayConsumedData);

    // Start threads
    producerThread->start();
    consumerThread->start();

    // Set up timers to call produceData and consumeData periodically
    QTimer *producerTimer = new QTimer(this);
    connect(producerTimer, &QTimer::timeout, producer, &Producer::produceData);
    producerTimer->start(500);  // Produces data every 500 ms

    QTimer *consumerTimer = new QTimer(this);
    connect(consumerTimer, &QTimer::timeout, consumer, &Consumer::consumeData);
    consumerTimer->start(1000);  // Consumes data every 1000 ms
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Database setup function
QSqlDatabase MainWindow::setupDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("sensor_data.db");

    if (!db.open()) {
        qDebug() << "Error: Unable to open the database:" << db.lastError().text();
    } else {
        QSqlQuery query(db);
        query.exec("CREATE TABLE IF NOT EXISTS SensorData ("
                   "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "Temperature REAL, "
                   "Voltage REAL, "
                   "Timestamp DATETIME DEFAULT CURRENT_TIMESTAMP)");
        if (query.lastError().isValid()) {
            qDebug() << "Error creating table:" << query.lastError().text();
        }
    }
    return db;
}

// Slot to display produced data in txtBrowserProducer
void MainWindow::displayProducedData(const QString &data) {
    ui->txtBrowserProducer->append(data);
}

// Slot to display consumed data in txtBrowserConsumer
void MainWindow::displayConsumedData(const QString &data) {
    ui->txtBrowserConsumer->append(data);
}
