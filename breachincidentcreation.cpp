#include "breachincidentcreation.h"
#include "ui_breachincidentcreation.h"
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

BreachIncidentCreation::BreachIncidentCreation(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::BreachIncidentCreation)
{
    ui->setupUi(this);
    //ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    setFixedSize(1280, 1080);
    setWindowTitle("Incident Response Tool");
    setStyleSheet("background-color: #2d42a8;");
    connect(ui->breachsaveButton, &QPushButton::clicked, this, &BreachIncidentCreation::saveIncident);

}

BreachIncidentCreation::~BreachIncidentCreation()
{
    delete ui;
}
QString BreachIncidentCreation::GenerateRandomID() const
{
    QString randomID;
    for (int i = 0; i < 9; ++i) {
        randomID.append(QString::number(QRandomGenerator::global()->bounded(10)));
    }
    return randomID;
}

void BreachIncidentCreation::saveIncident(){
    QString breachTypeStore = ui->breachType->text();
    QString breachDateTimeStore = ui->breachDateTime->text();
    QString breachMethodStore = ui->breachMethod->text();
    QString dataAffectedStore = ui->dataAffected->text();
    QString exfilMethodStore = ui->exfilMethod->text();
    QString exfilInfoStore = ui->exfilInfo->text();
    QString externalNotifyStore = ui->externalNotify->text();
    QString gdprStore = ui->gdpr->text();
    QString breachEmailStore = ui->breachEmail->text();
    QString incidentAnalysisStore = ui->incidentAnalysis->toPlainText();
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
    query.prepare("INSERT INTO DataBreach (IncidentID, breachType, breachDateTime, breachMethod, dataAffected, exfilMethod, exfilInfo, externalNotify, gdpr, breachEmail, IncidentAnalysis, severity, ticketStatus) "
                  "VALUES (:IncidentID, :breachType, :breachDateTime, :breachMethod, :dataAffected, :exfilMethod, :exfilInfo, :externalNotify, :gdpr, :breachEmail, :IncidentAnalysis, :severity, :ticketStatus)");

    QString incidentID = GenerateRandomID();
    query.bindValue(":IncidentID", incidentID);
    query.bindValue(":breachType", breachTypeStore);
    query.bindValue(":breachDateTime", breachDateTimeStore);
    query.bindValue(":breachMethod", breachMethodStore);
    query.bindValue(":dataAffected", dataAffectedStore);
    query.bindValue(":exfilMethod", exfilMethodStore);
    query.bindValue(":exfilInfo", exfilInfoStore);
    query.bindValue(":externalNotify", externalNotifyStore);
    query.bindValue(":gdpr", gdprStore);
    query.bindValue(":breachEmail", breachEmailStore);
    query.bindValue(":IncidentAnalysis", incidentAnalysisStore);
    query.bindValue(":severity", severityStore);
    query.bindValue(":ticketStatus", statusStore);


    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to insert incident information into database: " + query.lastError().text());
    } else {
        QMessageBox::information(this, "Success", "Incident information saved successfully!");
    }

    db.close();

}

void BreachIncidentCreation::on_pushButton_clicked()
{
    this->hide();
    mainMenu menu;
    menu.setModal(true);
    menu.exec();

}

