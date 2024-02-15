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

PhishIncident::PhishIncident(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PhishIncident)
{
    ui->setupUi(this);
    ui->setupUi(this);
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
    QMessageBox::critical(this,"DUDE!","IT WORKS");
    QString malSenderStore = ui->malSender->text();
    QString emailSubjectStore = ui->emailSubject->text();
    QString emailAttachStore = ui->emailAttach->text();
    QString emailSHAStore = ui->emailSHA->text();
    QString maliciousIPStore = ui->maliciousIP->text();
    QString emailDateTimeStore = ui->emailDateTime->text();
    QString emailRecipientStore = ui->emailRecipient->text();
    QString incidentAnalysisStore = ui->incidentAnalysis->toPlainText();

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "IncidentsConnection");
    db.setDatabaseName("D:/Dissertation/SQL TEST/SQL/IncidentsDatabase.db"); // Update path
    if (!db.open()) {
        QMessageBox::critical(this, "Error", "Failed to open database: " + db.lastError().text());
        return;
    }

    QSqlQuery query(db);
    query.prepare("INSERT INTO Phish (IncidentID, MalSender, EmailSubject, EmailAttach, EmailSHA, MaliciousIP, EmailDateTime, EmailRecipient, IncidentAnalysis) "
                  "VALUES (:IncidentID, :MalSender, :EmailSubject, :EmailAttach, :EmailSHA, :MaliciousIP, :EmailDateTime, :EmailRecipient, :IncidentAnalysis)");

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

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to insert incident information into database: " + query.lastError().text());
    } else {
        QMessageBox::information(this, "Success", "Incident information saved successfully!");
    }

    db.close();

}









