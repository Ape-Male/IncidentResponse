#include "databreacheditor.h"
#include "ui_databreacheditor.h"
#include <QDir>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include <QRandomGenerator>
#include "mainmenu.h"

databreacheditor::databreacheditor(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::databreacheditor)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    setFixedSize(1280, 1080);
    setWindowTitle("Incident Response Tool");
    setStyleSheet("background-color: #2d42a8;");
    connect(ui->breachsaveButton, &QPushButton::clicked, this, &databreacheditor::saveIncident3);

}

databreacheditor::~databreacheditor()
{
    delete ui;
}

void databreacheditor::loadIncidentDetails3(int incidentID) {

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
    query.prepare("SELECT * FROM DataBreach WHERE IncidentID = :incidentID");
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

        QString breachTypeStore  = query.value("breachType").toString();
        QString breachDateTimeStore  = query.value("breachDateTime").toString();
        QString breachMethodStore  = query.value("breachMethod").toString();
        QString dataAffectedStore  = query.value("dataAffected").toString();
        QString exfilMethodStore  = query.value("exfilMethod").toString();
        QString exfilInfoStore  = query.value("exfilInfo").toString();
        QString externalNotifyStore  = query.value("externalNotify").toString();
        QString gdprStore = query.value("gdpr").toString();
        QString incidentAnalysis = query.value("IncidentAnalysis").toString();
        QString severity = query.value("severity").toString();
        QString ticketStatus = query.value("ticketStatus").toString();
        ui->breachType->setText(breachTypeStore);
        ui->breachDateTime->setDateTime(QDateTime::fromString(breachDateTimeStore, "yyyy-MM-dd hh:mm:ss"));
        ui->breachMethod->setText(breachMethodStore);
        ui->dataAffected->setText(dataAffectedStore);
        ui->exfilMethod->setText(exfilMethodStore);
        ui->exfilInfo->setText(exfilInfoStore);
        ui->externalNotify->setText(externalNotifyStore);
        ui->gdpr->setText(gdprStore);
        ui->incidentAnalysis->setPlainText(incidentAnalysis);
        ui->severity->setCurrentText(severity);
        ui->ticketStatus->setCurrentText(ticketStatus);


    } else {
        qDebug() << "No incident found with ID:" << incidentID;
    }
}





void databreacheditor::saveIncident3(int incidentID)
{
    qDebug() << "Initial value of incidentID Number 2:" << incidentIDStore;


    QString breachTypeStore = ui->breachType->text();
    QString breachDateTimeStore = ui->breachDateTime->text();
    QString breachMethodStore = ui->breachMethod->text();
    QString dataAffectedStore = ui->dataAffected->text();
    QString exfilMethodStore = ui->exfilMethod->text();
    QString exfilInfoStore = ui->exfilInfo->text();
    QString externalNotifyStore = ui->externalNotify->text();
    QString gdprStore = ui->gdpr->text();
    QString IncidentAnalysisStore = ui->incidentAnalysis->toPlainText();
    QString severityStore = ui->severity->currentText();
    QString statusStore = ui->ticketStatus->currentText();

    QString dbFilePath = QDir(QCoreApplication::applicationDirPath()).filePath("../../../SQL TEST/SQL/IncidentsDatabase.db");

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "IncidentsConnection");
    db.setDatabaseName(dbFilePath);
    if (!db.open()) {
        QMessageBox::critical(this, "Error", "Failed to open database: " + db.lastError().text());
        return;
    }


    QSqlQuery query(db);
    query.prepare("UPDATE DataBreach SET IncidentID = :incidentID,"
                  "breachType = :breachType, "
                  "breachDateTime = :breachDateTime, "
                  "breachMethod = :breachMethod, "
                  "dataAffected = :dataAffected, "
                  "exfilMethod = :exfilMethod, "
                  "exfilInfo = :exfilInfo, "
                  "externalNotify = :externalNotify, "
                  "gdpr = :gdpr, "
                  "incidentAnalysis = :incidentAnalysis, "
                  "severity = :severity, "
                  "ticketStatus = :ticketStatus "
                  "WHERE IncidentID = :incidentID");

    query.bindValue(":incidentID", incidentIDStore);
    query.bindValue(":breachType", breachTypeStore);
    query.bindValue(":breachDateTime", breachDateTimeStore);
    query.bindValue(":breachMethod", breachMethodStore);
    query.bindValue(":dataAffected", dataAffectedStore);
    query.bindValue(":exfilMethod", exfilMethodStore);
    query.bindValue(":exfilInfo", exfilInfoStore);
    query.bindValue(":externalNotify", externalNotifyStore);
    query.bindValue(":incidentAnalysis", IncidentAnalysisStore);
    query.bindValue(":severity", severityStore);
    query.bindValue(":ticketStatus", statusStore);


    qDebug() << "Values bound to the update query:";
    qDebug() << "IncidentID:" << incidentIDStore;
    qDebug() << "breachType:" << breachTypeStore;
    qDebug() << "breachDateTime:" << breachDateTimeStore;
    qDebug() << "breachMethod:" << breachMethodStore;
    qDebug() << "dataAffected:" << dataAffectedStore;
    qDebug() << "exfilMethod:" << exfilMethodStore;
    qDebug() << "exfilInfo:" << exfilInfoStore;
    qDebug() << "externalNotify:" << externalNotifyStore;
    qDebug() << "incidentAnalysis:" << IncidentAnalysisStore;
    qDebug() << "severity:" << severityStore;
    qDebug() << "ticketStatus:" << statusStore;


    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return;
    }
    if (query.numRowsAffected() == 1) {
        qDebug() << "Breach incident information updated successfully!";
    } else {
        qDebug() << "Failed to update Breach incident information!";
    }
}

void databreacheditor::on_pushButton_clicked()
{
    this->hide();
    mainMenu menu;
    menu.setModal(true);
    menu.exec();

}

