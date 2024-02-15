#include "phishincidentcreation.h"
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include "ui_phishincidentcreation.h"

phishincidentcreation::PhishIncidentCreation(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PhishIncidentCreation)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    setFixedSize(1280, 1080);
    setWindowTitle("Incident Response Tool");
    setStyleSheet("background-color: #2d42a8;");
}

PhishIncidentCreation::~PhishIncidentCreation()
{
    delete ui;
}

void PhishIncidentCreation::on_saveButton_clicked()
{
    // Retrieve incident information from UI
    QString malSenderStore = ui->malSender->text();
    QString emailSubjectStore = ui->emailSubject->text();
    QString emailAttachStore = ui->emailAttach->text();
    QString emailSHAStore = ui->emailSHA->text();
    QString maliciousIPStore = ui->maliciousIP->text();
    QString emailDateTimeStore = ui->emailDateTime->text();
    QString emailRecipientStore = ui->emailRecipient->text();
    QString incidentAnalysisStore = ui->incidentAnalysis->toPlainText();

    // Open the database connection
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "IncidentsConnection");
    db.setDatabaseName("INSERTYOURPATHHERE/IncidentsDatabase.db"); // Update path
    if (!db.open()) {
        QMessageBox::critical(this, "Error", "Failed to open database: " + db.lastError().text());
        return;
    }

    // Prepare the SQL query to insert the incident information into the database
    QSqlQuery query(db);
    query.prepare("INSERT INTO Phish (IncidentID, MalSender, EmailSubject, EmailAttach, EmailSHA, "
                  "MaliciousIP, EmailDateTime, EmailRecipient, IncidentAnalysis) "
                  "VALUES (:IncidentID, :MalSender, :EmailSubject, :EmailAttach, :EmailSHA, "
                  ":MaliciousIP, :EmailDateTime, :EmailRecipient, :IncidentAnalysis)");

    // Generate incident ID
    QString incidentID = generateRandomID();
    query.bindValue(":IncidentID", incidentID);

    // Bind values to the query parameters
    query.bindValue(":MalSender", malSenderStore);
    query.bindValue(":EmailSubject", emailSubjectStore);
    query.bindValue(":EmailAttach", emailAttachStore);
    query.bindValue(":EmailSHA", emailSHAStore);
    query.bindValue(":MaliciousIP", maliciousIPStore);
    query.bindValue(":EmailDateTime", emailDateTimeStore);
    query.bindValue(":EmailRecipient", emailRecipientStore);
    query.bindValue(":IncidentAnalysis", incidentAnalysisStore);

    // Execute the SQL query to insert the data into the database
    if (!query.exec()) {
        QMessageBox::critical(this,
                              "Error",
                              "Failed to insert incident information into database: "
                                  + query.lastError().text());
    } else {
        QMessageBox::information(this, "Success", "Incident information saved successfully!");
    }

    // Close the database connection
    db.close();
}

QString PhishIncidentCreation::generateRandomID() const
{
    // Generate a random 9-digit ID
    QString randomID;
    for (int i = 0; i < 9; ++i) {
        randomID.append(QString::number(QRandomGenerator::global()->bounded(10)));
    }
    return randomID;
}
