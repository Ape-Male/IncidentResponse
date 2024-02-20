#include "ransomwareincident.h"
#include "ui_ransomwareincident.h"
#include <QDir>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include <QRandomGenerator>

ransomwareIncident::ransomwareIncident(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ransomwareIncident)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    setFixedSize(1280, 1080);
    setWindowTitle("Incident Response Tool");
    setStyleSheet("background-color: #2d42a8;");
}

ransomwareIncident::~ransomwareIncident()
{
    delete ui;
}

QString ransomwareIncident::GenerateRandomID() const
{
    QString randomID;
    for (int i = 0; i < 9; ++i) {
        randomID.append(QString::number(QRandomGenerator::global()->bounded(10)));
    }
    return randomID;
}

void ransomwareIncident::on_ransomsaveButton_clicked()
{
    QString ransomTypeStore = ui->ransomType->text();
    QString DateTimeStore = ui->breachDateTime->text();
    QString attackVectorStore = ui->attackVector->text();
    QString dataAffectedStore = ui->dataAffected->text();
    QString ransomCommsStore = ui->ransomComms->text();
    QString affectedSystemsStore = ui->affectedSystems->text();
    QString externalNotifyStore = ui->externalNotify->text();
    QString gdprStore = ui->gdpr->text();
    QString ransomSHAStore = ui->ransomSHA->text();
    QString incidentAnalysisStore = ui->incidentAnalysis->toPlainText();


    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "IncidentsConnectionRansom");
    db.setDatabaseName("D:/Dissertation/SQL TEST/SQL/IncidentsDatabase.db");
    if (!db.open()) {
        QMessageBox::critical(this, "Error", "Failed to open database: " + db.lastError().text());
        return;
    }
    QSqlQuery query(db);
    query.prepare("INSERT INTO Ransomware (IncidentID, ransomType, breachDateTime, attackVector, dataAffected, ransomComms, affectedSystems, externalNotify, gdpr, ransomSHA, IncidentAnalysis) "
                  "VALUES (:IncidentID, :ransomType, :breachDateTime, :attackVector, :dataAffected, :ransomComms, :affectedSystems, :externalNotify, :gdpr, :ransomSHA, :IncidentAnalysis)");

    QString incidentID = GenerateRandomID();
    query.bindValue(":IncidentID", incidentID);
    query.bindValue(":ransomType", ransomTypeStore);
    query.bindValue(":breachDateTime", DateTimeStore);
    query.bindValue(":attackVector", attackVectorStore);
    query.bindValue(":dataAffected", dataAffectedStore);
    query.bindValue(":ransomComms", ransomCommsStore);
    query.bindValue(":affectedSystems", affectedSystemsStore);
    query.bindValue(":externalNotify", externalNotifyStore);
    query.bindValue(":gdpr", gdprStore);
    query.bindValue(":ransomSHA", ransomSHAStore);
    query.bindValue(":IncidentAnalysis", incidentAnalysisStore);

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to insert incident information into database: " + query.lastError().text());
    } else {
        QMessageBox::information(this, "Success", "Incident information saved successfully!");
    }

    db.close();

}

