#include "phishincident.h"
#include "ui_phishincident.h"
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

PhishIncident::PhishIncident(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PhishIncident)
{
    ui->setupUi(this);
    //ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    setFixedSize(1280, 1080);
    setWindowTitle("Incident Response Tool");
    setStyleSheet("background-color: #2d42a8;");
    connect(ui->saveButton, &QPushButton::clicked, this, &PhishIncident::saveIncident);



}

PhishIncident::~PhishIncident()
{
    delete ui;
}
QString PhishIncident::generateRandomID() const
{
    QString randomID;
    for (int i = 0; i < 9; ++i) {
        randomID.append(QString::number(QRandomGenerator::global()->bounded(10)));
    }
    return randomID;
}

void PhishIncident::saveIncident(){
    QString malSenderStore = ui->malSender->text();
    QString emailSubjectStore = ui->emailSubject->text();
    QString emailAttachStore = ui->emailAttach->text();
    QString emailSHAStore = ui->emailSHA->text();
    QString maliciousIPStore = ui->maliciousIP->text();
    QString emailDateTimeStore = ui->emailDateTime->text();
    QString emailRecipientStore = ui->emailRecipient->text();
    QString incidentAnalysisStore = ui->incidentAnalysis->toPlainText();
    QString severityStore = ui->severity->currentText();
    QString statusStore = ui->ticketStatus->currentText();

    QString dbFilePath = QDir(QCoreApplication::applicationDirPath()).filePath("../../../SQL TEST/SQL/IncidentsDatabase.db");

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "IncidentsConnectionPhish");
    db.setDatabaseName(dbFilePath);
    if (!db.open()) {
        QMessageBox::critical(this, "Error", "Failed to open database: " + db.lastError().text());
        return;
    }

    QSqlQuery query(db);
    query.prepare("INSERT INTO Phish (IncidentID, MalSender, EmailSubject, EmailAttach, EmailSHA, MaliciousIP, EmailDateTime, EmailRecipient, IncidentAnalysis, severity, ticketStatus) "
                  "VALUES (:IncidentID, :MalSender, :EmailSubject, :EmailAttach, :EmailSHA, :MaliciousIP, :EmailDateTime, :EmailRecipient, :IncidentAnalysis, :severity, :ticketStatus)");

    QString incidentID = generateRandomID();
    query.bindValue(":IncidentID", incidentID);
    query.bindValue(":MalSender", malSenderStore);
    query.bindValue(":EmailSubject", emailSubjectStore);
    query.bindValue(":EmailAttach", emailAttachStore);
    query.bindValue(":EmailSHA", emailSHAStore);
    query.bindValue(":MaliciousIP", maliciousIPStore);
    query.bindValue(":EmailDateTime", emailDateTimeStore);
    query.bindValue(":EmailRecipient", emailRecipientStore);
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










void PhishIncident::on_pushButton_clicked()
{
    this->hide();
    mainMenu menu;
    menu.setModal(true);
    menu.exec();

}

