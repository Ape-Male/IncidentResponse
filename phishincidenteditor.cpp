#include "phishincidenteditor.h"
#include "ui_phishincidenteditor.h"
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

phishincidenteditor::phishincidenteditor(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::phishincidenteditor)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    setFixedSize(1280, 1080);
    setWindowTitle("Incident Response Tool");
    setStyleSheet("background-color: #2d42a8;");
    connect(ui->saveButton, &QPushButton::clicked, this, &phishincidenteditor::saveIncident2);

}

phishincidenteditor::~phishincidenteditor()
{
    delete ui;
}

void phishincidenteditor::loadIncidentDetails2(int incidentID) {

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
    query.prepare("SELECT * FROM Phish WHERE IncidentID = :incidentID");
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

        QString MalSender = query.value("MalSender").toString();
        QString EmailSubject = query.value("EmailSubject").toString();
        QString EmailAttach = query.value("EmailAttach").toString();
        QString EmailSHA = query.value("EmailSHA").toString();
        QString MaliciousIP = query.value("MaliciousIP").toString();
        QString EmailDateTime = query.value("EmailDateTime").toString();
        QString EmailRecipient = query.value("EmailRecipient").toString();
        QString IncidentAnalysis = query.value("IncidentAnalysis").toString();
        QString severity = query.value("severity").toString();
        QString ticketStatus = query.value("ticketStatus").toString();

        qDebug() << "MalSender:" << MalSender;
        qDebug() << "EmailSubject:" << EmailSubject;
        qDebug() << "EmailAttach:" << EmailAttach;
        qDebug() << "EmailSHA:" << EmailSHA;
        qDebug() << "MaliciousIP:" << MaliciousIP;
        qDebug() << "EmailDateTime:" << EmailDateTime;
        qDebug() << "EmailRecipient:" << EmailRecipient;
        qDebug() << "IncidentAnalysis:" << IncidentAnalysis;
        qDebug() << "severity:" << severity;
        qDebug() << "ticketStatus:" << ticketStatus;

        ui->malSender->setText(MalSender);
        ui->emailSubject->setText(EmailSubject);
        ui->emailAttach->setText(EmailAttach);
        ui->emailSHA->setText(EmailSHA);
        ui->maliciousIP->setText(MaliciousIP);
        ui->emailDateTime->setDateTime(QDateTime::fromString(EmailDateTime, "yyyy-MM-dd hh:mm:ss"));
        ui->emailRecipient->setText(EmailRecipient);
        ui->incidentAnalysis->setPlainText(IncidentAnalysis); //potentialerror here
        ui->severity->setCurrentText(severity);
        ui->ticketStatus->setCurrentText(ticketStatus);


    } else {
        qDebug() << "No incident found with ID:" << incidentID;
    }
}

    void phishincidenteditor::saveIncident2(int incidentID)
    {
        qDebug() << "Initial value of incidentID Number 2:" << incidentIDStore;

        QString MalSenderStore = ui->malSender->text();
        QString EmailSubjectStore = ui->emailSubject->text();
        QString EmailAttachStore = ui->emailAttach->text();
        QString EmailSHAStore = ui->emailSHA->text();
        QString MaliciousIPStore = ui->maliciousIP->text();
        QString EmailDateTimeStore = ui->emailDateTime->text();
        QString EmailRecipientStore = ui->emailRecipient->text();
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
        query.prepare("UPDATE Phish SET IncidentID = :incidentID,"
              "MalSender = :MalSender, "
              "EmailSubject = :EmailSubject, "
              "EmailAttach = :EmailAttach, "
              "EmailSHA = :EmailSHA, "
              "MaliciousIP = :MaliciousIP, "
              "EmailDateTime = :EmailDateTime, "
              "EmailRecipient = :EmailRecipient, "
              "IncidentAnalysis = :IncidentAnalysis, " //could cause issue
              "severity = :severity, "
              "ticketStatus = :ticketStatus "
              "WHERE IncidentID = :incidentID"); //

        query.bindValue(":incidentID", incidentIDStore);
        query.bindValue(":MalSender", MalSenderStore);
        query.bindValue(":MalSender", MalSenderStore);
        query.bindValue(":EmailSubject", EmailSubjectStore);
        query.bindValue(":EmailAttach", EmailAttachStore);
        query.bindValue(":EmailSHA", EmailSHAStore);
        query.bindValue(":MaliciousIP", MaliciousIPStore);
        query.bindValue(":EmailDateTime", EmailDateTimeStore);
        query.bindValue(":EmailRecipient", EmailRecipientStore);
        query.bindValue(":IncidentAnalysis", IncidentAnalysisStore);
        query.bindValue(":severity", severityStore);
        query.bindValue(":ticketStatus", statusStore);


        qDebug() << "Values bound to the update query:";
        qDebug() << "IncidentID:" << incidentIDStore;
        qDebug() << "MalSender:" << MalSenderStore;
        qDebug() << "EmailSubject:" << EmailSubjectStore;
        qDebug() << "EmailAttach:" << EmailAttachStore;
        qDebug() << "EmailSHA:" << EmailSHAStore;
        qDebug() << "MaliciousIP:" << MaliciousIPStore;
        qDebug() << "EmailDateTime:" << EmailDateTimeStore;
        qDebug() << "EmailRecipient:" << EmailRecipientStore;
        qDebug() << "IncidentAnalysis:" << IncidentAnalysisStore;
        qDebug() << "severity:" << severityStore;
        qDebug() << "ticketStatus:" << statusStore;
        if (!query.exec()) {
            qDebug() << "Error executing query:" << query.lastError().text();
            return;
        }
        if (query.numRowsAffected() == 1) {
            qDebug() << "Phish incident information updated successfully!";
        } else {
            qDebug() << "Failed to update malware incident information!";
        }
    }




void phishincidenteditor::on_pushButton_clicked()
{
    this->hide();
    mainMenu menu;
    menu.setModal(true);
    menu.exec();

}

