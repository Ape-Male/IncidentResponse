#include "dashboard.h"
#include "ui_dashboard.h"
#include <QtSql>

dashboard::dashboard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dashboard)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    setFixedSize(1280, 1080);
    setWindowTitle("Incident Response Tool");
    setStyleSheet("background-color: #2d42a8;");

    loadIncidentToList();
}

dashboard::~dashboard()
{
    delete ui;
}

void dashboard::loadIncidentToList()
{
    ui->ticketStatusDash->clear();
    loadIncidentCounts(ui->ticketStatusDash);
    ui->severityDash->clear();
    loadSeverityCounts(ui->severityDash);
    ui->affectedUserDash->clear();
    loadAffectedUsersCounts(ui->affectedUserDash);
    ui->MaliciousIPDash->clear();
    loadMaliciousIPs(ui->MaliciousIPDash);
}

void dashboard::loadIncidentCounts(QListWidget *listWidget)
{
    QString dbFilePath = QDir(QCoreApplication::applicationDirPath()).filePath("../../../SQL TEST/SQL/IncidentsDatabase.db");
    qDebug() << "Database file path for incident counts:" << dbFilePath;

    QSqlDatabase db2 = QSqlDatabase::addDatabase("QSQLITE", "IncidentsConnectionMalIP");
    db2.setDatabaseName(dbFilePath);
    if (!db2.open()) {
        QMessageBox::critical(this, "Error", "Failed to open database: " + db2.lastError().text());
        return;
    }

    QStringList tableNames = {"Phish", "DataBreach", "Malware", "Ransomware"};

    QMap<QString, QMap<QString, int>> counts;

    for (const QString &tableName : tableNames) {
        QSqlQuery query(db2);
        query.prepare("SELECT COUNT(*) FROM " + tableName + " WHERE ticketStatus = :ticketStatus");

        QStringList ticketStatusLevels = {"Open", "In Progress", "Closed"};
        for (const QString &ticketStatus : ticketStatusLevels) {
            query.bindValue(":ticketStatus", ticketStatus);
            if (query.exec() && query.next()) {
                int count = query.value(0).toInt();
                counts[tableName][ticketStatus] = count;
            } else {
                qDebug() << "Error executing query for table:" << tableName << "and ticketStatus:" << ticketStatus;
            }
            query.finish();
        }
    }

    for (const QString &tableName : counts.keys()) {
        for (const QString &ticketStatus : counts.value(tableName).keys()) {
            QString itemText = QString("%1 - %2 - %3").arg(tableName).arg(ticketStatus).arg(counts[tableName][ticketStatus]);
            listWidget->addItem(itemText);
        }
    }
}

//expected outputs are db location, potential fail, error loop. 3(+) total
void dashboard::loadSeverityCounts(QListWidget *listWidget)
{
    qDebug() << "Loading severity counts...";

    QString dbFilePath = QDir(QCoreApplication::applicationDirPath()).filePath("../../../SQL TEST/SQL/IncidentsDatabase.db");
    qDebug() << "Database file path for severity counts:" << dbFilePath;

    QSqlDatabase db2 = QSqlDatabase::addDatabase("QSQLITE", "IncidentsConnectionMalIP");
    db2.setDatabaseName(dbFilePath);
    if (!db2.open()) {
        QMessageBox::critical(this, "Error", "Failed to open database: " + db2.lastError().text());
        return;
    }

    qDebug() << "Database connection established.";

    QStringList tableNames = {"Phish", "DataBreach", "Malware", "Ransomware"};
    QStringList severityLevels = {"None", "Low", "Medium", "High"};
    qDebug() << "Severity levels:" << severityLevels;
    QMap<QString, int> counts;
    for (const QString &severity : severityLevels) {
        for (const QString &tableName : tableNames) {
            QSqlQuery query(db2);
            query.prepare("SELECT COUNT(*) FROM " + tableName + " WHERE severity = :severity");
            query.bindValue(":severity", severity);

            qDebug() << "Prepared SQL query:" << query.lastQuery();

            if (query.exec()) {
                if (query.next()) {
                    int count = query.value(0).toInt();
                    counts[severity] += count;
                } else {
                    qDebug() << "No incidents found for severity:" << severity;
                }
            } else {
                qDebug() << "Error executing query for severity:" << severity;
                qDebug() << "Error:" << query.lastError().text();
            }
            query.finish();
        }
    }
    qDebug() << "Severity counts:" << counts;
    for (const QString &severity : counts.keys()) {
        QString itemText = QString("%1 = %2 Incidents").arg(severity).arg(counts[severity]);
        listWidget->addItem(itemText);
    }

    qDebug() << "Severity counts loaded.";
}

void dashboard::loadMaliciousIPs(QListWidget *listWidget)
{
    QString dbFilePath = QDir(QCoreApplication::applicationDirPath()).filePath("../../../SQL TEST/SQL/IncidentsDatabase.db");
    qDebug() << "Database file path for malicious IPs:" << dbFilePath;

    QSqlDatabase db2 = QSqlDatabase::addDatabase("QSQLITE", "IncidentsConnectionMalIP");
    db2.setDatabaseName(dbFilePath);
    if (!db2.open()) {
        QMessageBox::critical(this, "Error", "Failed to open database: " + db2.lastError().text());
        return;
    }

    QSqlQuery query(db2);
    query.prepare("SELECT MaliciousIP FROM Phish");
    if (query.exec()) {
        listWidget->clear();
        while (query.next()) {
            QString maliciousIP = query.value(0).toString();
            listWidget->addItem(maliciousIP);
        }
    } else {
        qDebug() << "Error executing query to fetch MaliciousIPs from Phish table:";
        qDebug() << "Error:" << query.lastError().text();
    }
    query.finish();
}

void dashboard::loadAffectedUsersCounts(QListWidget *listWidget)
{
    // QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    // db.setDatabaseName("D:/Dissertation/SQL TEST/SQL/IncidentsDatabase.db");
    //if (!db.open()) {
    //     QMessageBox::critical(this, "Error", "Failed to open database: " + db.lastError().text());
    //     return;
    // }

    QString dbFilePath = QDir(QCoreApplication::applicationDirPath()).filePath("../../../SQL TEST/SQL/IncidentsDatabase.db");
    qDebug() << "Database file path for affected users counts:" << dbFilePath;

    QSqlDatabase db2 = QSqlDatabase::addDatabase("QSQLITE", "IncidentsConnectionMalIP");
    db2.setDatabaseName(dbFilePath);
    if (!db2.open()) {
        QMessageBox::critical(this, "Error", "Failed to open database: " + db2.lastError().text());
        return;
    }

    QMap<QString, QString> tableColumnMap = {
        {"Phish", "EmailRecipient"},
        {"DataBreach", "breachEmail"}
    };

    for (const QString &tableName : tableColumnMap.keys()) {
        QString column = tableColumnMap.value(tableName);

        QSqlQuery query(db2);
        query.prepare("SELECT " + column + ", COUNT(*) FROM " + tableName + " GROUP BY " + column);

        if (query.exec()) {
            while (query.next()) {
                QString affectedUser = query.value(0).toString();
                int count = query.value(1).toInt();
                QString itemText = QString("%1 = %2 Incidents").arg(affectedUser).arg(count);
                listWidget->addItem(itemText);
            }
        } else {
            qDebug() << "Error executing query for table:" << tableName << "and column:" << column;
            qDebug() << "Error:" << query.lastError().text();
        }
        query.finish();
    }
}
