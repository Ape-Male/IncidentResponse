#include "ransomwareeditor.h"
#include "ui_ransomwareeditor.h"
#include <QDir>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include <QRandomGenerator>
#include <QSqlQuery>
#include <QSqlRecord>
#include "mainmenu.h"
ransomwareeditor::ransomwareeditor(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ransomwareeditor)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    setFixedSize(1280, 1080);
    setWindowTitle("Incident Response Tool");
    setStyleSheet("background-color: #2d42a8;");
    connect(ui->ransomsaveButton, &QPushButton::clicked, this, &ransomwareeditor::saveIncident4);

}

ransomwareeditor::~ransomwareeditor()
{
    delete ui;
}

void ransomwareeditor::loadIncidentDetails4(int incidentID) {

    qDebug() << "Loading incident details for IncidentID:" << incidentID;
    incidentIDStore = incidentID;

    QString dbFilePath = QDir(QCoreApplication::applicationDirPath()).filePath("../../../SQL TEST/SQL/IncidentsDatabase.db");

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "IncidentsConnection");
    db.setDatabaseName(dbFilePath);
    if (!db.open()) {
        QMessageBox::critical(this, "Error", "Failed to open database: " + db.lastError().text());
        return;
    }


    QSqlQuery query(db);
    query.prepare("SELECT * FROM Ransomware WHERE IncidentID = :incidentID");
    qDebug() << "Prepared query:" << query.lastQuery();
    query.bindValue(":incidentID", incidentID);

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return;
    }

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return;
    }

    if (query.next()) {
        qDebug() << "Incident found with ID:" << incidentID;

        QString ransomType = query.value("ransomType").toString();
        QString breachDateTime = query.value("breachDateTime").toString();
        QString attackVector = query.value("attackVector").toString();
        QString dataAffected = query.value("dataAffected").toString();
        QString ransomComms = query.value("ransomComms").toString();
        QString affectedSystems = query.value("affectedSystems").toString();
        QString externalNotify = query.value("externalNotify").toString();
        QString gdpr = query.value("gdpr").toString();
        QString ransomSHA = query.value("ransomSHA").toString();
        QString incidentAnalysis = query.value("IncidentAnalysis").toString();
        QString severity = query.value("severity").toString();
        QString ticketStatus = query.value("ticketStatus").toString();


       // qDebug() << "ransomType:" << ransomType;
        //qDebug() << "breachDateTime:" << breachDateTime;
       // qDebug() << "malwareSource:" << malwareSource;
        //qDebug() << "systemsAffected:" << systemsAffected;
       // qDebug() << "threatActions:" << threatActions;
       // qDebug() << "detectionMethod:" << detectionMethod;
       // qDebug() << "userIsolation:" << userIsolation;
       // qDebug() << "incidentAnalysis:" << incidentAnalysis;

        ui->ransomType ->setText(ransomType );
        ui->breachDateTime->setDateTime(QDateTime::fromString(breachDateTime, "yyyy-MM-dd hh:mm:ss"));
        ui->attackVector->setText(attackVector);
        ui->dataAffected->setText(dataAffected);
        ui->ransomComms->setText(ransomComms);
        ui->affectedSystems->setText(affectedSystems);
        ui->externalNotify->setText(externalNotify);
        ui->gdpr->setText(gdpr);
        ui->ransomSHA->setText(ransomSHA);
        ui->incidentAnalysis->setPlainText(incidentAnalysis);
        ui->severity->setCurrentText(severity);
        ui->ticketStatus->setCurrentText(ticketStatus);


    } else {
        qDebug() << "No incident found with ID:" << incidentID;
    }
}





void ransomwareeditor::saveIncident4(int incidentID)
{
    qDebug() << "Initial value of incidentID Number 2:" << incidentIDStore;


    QString ransomTypeStore = ui->ransomType->text();
    QString breachDateTimeStore = ui->breachDateTime->text();
    QString attackVectorStore = ui->attackVector->text();
    QString dataAffectedStore = ui->dataAffected->text();
    QString ransomCommsStore = ui->ransomComms->text();
    QString affectedSystemsStore = ui->affectedSystems->text();
    QString externalNotifyStore = ui->externalNotify->text();
    QString gdprStore = ui->gdpr->text();
    QString ransomSHAStore = ui->ransomSHA->text();
    QString IncidentAnalysisStore = ui->incidentAnalysis->toPlainText();
    QString severityStore = ui->severity->currentText();
    QString ticketStatusStore = ui->ticketStatus->currentText();

    QString dbFilePath = QDir(QCoreApplication::applicationDirPath()).filePath("../../../SQL TEST/SQL/IncidentsDatabase.db");

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "IncidentsConnection");
    db.setDatabaseName(dbFilePath);
    if (!db.open()) {
        QMessageBox::critical(this, "Error", "Failed to open database: " + db.lastError().text());
        return;
    }


    QSqlQuery query(db);
    query.prepare("UPDATE Ransomware SET IncidentID = :incidentID,"
                  "ransomType = :ransomType, "
                  "breachDateTime = :breachDateTime, "
                  "attackVector = :attackVector, "
                  "dataAffected = :dataAffected, "
                  "ransomComms = :ransomComms, "
                  "affectedSystems = :affectedSystems, "
                  "externalNotify = :externalNotify, "
                  "gdpr = :gdpr, "
                  "ransomSHA = :ransomSHA, "
                  "IncidentAnalysis = :IncidentAnalysis, "
                  "severity = :severity, "
                  "ticketStatus = :ticketStatus "
                  "WHERE IncidentID = :incidentID");


    query.bindValue(":incidentID", incidentIDStore);
    query.bindValue(":ransomType", ransomTypeStore);
    query.bindValue(":breachDateTime", breachDateTimeStore);
    query.bindValue(":attackVector", attackVectorStore);
    query.bindValue(":dataAffected", dataAffectedStore);
    query.bindValue(":ransomComms", ransomCommsStore);
    query.bindValue(":affectedSystems", affectedSystemsStore);
    query.bindValue(":externalNotify", externalNotifyStore);
    query.bindValue(":gdpr", gdprStore);
    query.bindValue(":ransomSHA", ransomSHAStore);
    query.bindValue(":IncidentAnalysis", IncidentAnalysisStore);
    query.bindValue(":severity", severityStore);
    query.bindValue(":ticketStatus", ticketStatusStore);

    qDebug() << "Values bound to the update query:";
    qDebug() << "IncidentID:" << incidentIDStore;
    qDebug() << "ransomType:" << ransomTypeStore;
    qDebug() << "breachDateTime:" << breachDateTimeStore;
    qDebug() << "attackVector:" << attackVectorStore;
    qDebug() << "dataAffected:" << dataAffectedStore;
    qDebug() << "ransomComms:" << ransomCommsStore;
    qDebug() << "affectedSystems:" << affectedSystemsStore;
    qDebug() << "externalNotify:" << externalNotifyStore;
    qDebug() << "gdpr:" << gdprStore;
    qDebug() << "ransomSHA:" << ransomSHAStore;
    qDebug() << "IncidentAnalysis:" << IncidentAnalysisStore;
    qDebug() << "severity:" << severityStore;
    qDebug() << "ticketStatus:" << ticketStatusStore;

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return;
    }
    if (query.numRowsAffected() == 1) {
        qDebug() << "Ransomware incident information updated successfully!";
    } else {
        qDebug() << "Failed to update malware incident information!";
    }
}

void ransomwareeditor::on_pushButton_clicked()
{
    this->hide();
    mainMenu menu;
    menu.setModal(true);
    menu.exec();

}

