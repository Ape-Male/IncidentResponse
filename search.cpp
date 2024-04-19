#include "search.h"
#include "ui_search.h"
#include <QDir>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include <QRandomGenerator>
#include <QSqlRecord>
#include "malwareincidenteditor.h"
#include "phishincidenteditor.h"
#include "databreacheditor.h"
#include "ransomwareeditor.h"
#include "mainmenu.h"

Search::Search(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Search)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    setFixedSize(1280, 1080);
    setWindowTitle("Incident Response Tool");
    setStyleSheet("background-color: #2d42a8;");
}

Search::~Search()
{
    delete ui;
}

void Search::displayQueryResults(QSqlQuery& query, const QString& incidentType) {
    int rowCount = 0;
    while (query.next()) {
        rowCount++;
        QString resultString = "[" + incidentType + "] ";
        for (int i = 0; i < query.record().count(); ++i) {
            resultString += query.value(i).toString() + " ";
        }


        ui->listWidget->addItem(resultString.trimmed());

        qDebug() << "Query result: " << resultString;
    }
    qDebug() << "Number of " << incidentType << " rows returned: " << rowCount;
}



void Search::on_searchButton_clicked()
{
    QString generalSearchStore = ui->generalSearch->toPlainText();
    //QString incidentTypeStore = ui->IncidentType->currentText();


    QString dbFilePath = QDir(QCoreApplication::applicationDirPath()).filePath("../../../SQL TEST/SQL/IncidentsDatabase.db");

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "IncidentsConnection");
    db.setDatabaseName(dbFilePath);
    if (!db.open()) {
        QMessageBox::critical(this, "Error", "Failed to open database: " + db.lastError().text());
        return;
    }

    qDebug() << "Database file path for severity counts:" << dbFilePath;


    QSqlQuery breachQuery(db);
    QSqlQuery malwareQuery(db);
    QSqlQuery phishQuery(db);
    QSqlQuery ransomwareQuery(db);

    QString breachQueryString = "SELECT * FROM DataBreach WHERE IncidentID LIKE '%" + generalSearchStore + "%'OR breachType LIKE '%" + generalSearchStore + "%' OR breachEmail LIKE '%" + generalSearchStore + "%' OR exfilMethod LIKE '%" + generalSearchStore + "%'";
    QString malwareQueryString = "SELECT * FROM Malware WHERE IncidentID LIKE '%" + generalSearchStore + "%' OR malwareSource LIKE '%" + generalSearchStore + "%' OR systemsAffected LIKE '%" + generalSearchStore + "%'";
    QString phishQueryString = "SELECT * FROM Phish WHERE IncidentID LIKE '%" + generalSearchStore + "%' OR malSender LIKE '%" + generalSearchStore + "%' OR EmailSubject LIKE '%" + generalSearchStore + "%' OR EmailRecipient LIKE '%" + generalSearchStore + "%' OR MaliciousIP LIKE '%" + generalSearchStore + "%'";
    QString ransomwareQueryString = "SELECT * FROM Ransomware WHERE IncidentID LIKE '%" + generalSearchStore + "%' OR ransomType LIKE '%" + generalSearchStore + "%' OR attackVector LIKE '%" + generalSearchStore + "%' OR affectedSystems LIKE '%" + generalSearchStore + "%' OR ransomSHA LIKE '%" + generalSearchStore + "%'";

    qDebug() << "Executing breach query: " << breachQueryString;
    if (!breachQuery.exec(breachQueryString)) {
        QMessageBox::critical(this, "Error", "Failed to execute breach query: " + breachQuery.lastError().text());
        return;
    }

    qDebug() << "Executing malware query: " << malwareQueryString;
    if (!malwareQuery.exec(malwareQueryString)) {
        QMessageBox::critical(this, "Error", "Failed to execute malware query: " + malwareQuery.lastError().text());
        return;
    }

    qDebug() << "Executing phish query: " << phishQueryString;
    if (!phishQuery.exec(phishQueryString)) {
        QMessageBox::critical(this, "Error", "Failed to execute phish query: " + phishQuery.lastError().text());
        return;
    }

    qDebug() << "Executing ransomware query: " << ransomwareQueryString;
    if (!ransomwareQuery.exec(ransomwareQueryString)) {
        QMessageBox::critical(this, "Error", "Failed to execute ransomware query: " + ransomwareQuery.lastError().text());
        return;
    }

    ui->listWidget->clear();
    displayQueryResults(breachQuery, "Breach");
    displayQueryResults(malwareQuery, "Malware");
    displayQueryResults(phishQuery, "Phish");
    displayQueryResults(ransomwareQuery, "Ransomware");

}


QString Search::extractIncidentID(const QString &itemText) {
    QStringList parts = itemText.split(' ');
    if (parts.size() >= 2) {
        QString incidentID = parts[1];
        qDebug() << "Extracted IncidentID:" << incidentID;
        return incidentID;
    } else {
        qDebug() << "Failed to extract IncidentID from item text: " << itemText;
        return QString();
    }
}


void Search::on_listWidget_itemClicked(QListWidgetItem *item)
{
    QString selectedItemText = item->text();

    QString incidentType;
    if (selectedItemText.contains("Breach")) {
        incidentType = "Breach";
    } else if (selectedItemText.contains("Malware")) {
        incidentType = "Malware";
    } else if (selectedItemText.contains("Phish")) {
        incidentType = "Phish";
    } else if (selectedItemText.contains("Ransomware")) {
        incidentType = "Ransomware";
    } else {
        qDebug() << "Unknown incident type for item: " << selectedItemText;
        return;
    }

    if (incidentType == "Malware") {
        int incidentID = extractIncidentID(selectedItemText).toInt();

        MalwareIncidentEditor *malwareEditor = new MalwareIncidentEditor(this);
        malwareEditor->setAttribute(Qt::WA_DeleteOnClose);
        malwareEditor->loadIncidentDetails(incidentID);
        malwareEditor->saveIncident(incidentID);
        malwareEditor->show();
    }
    else if(incidentType == "Phish"){
        int incidentID = extractIncidentID(selectedItemText).toInt();
        phishincidenteditor *phisheditor = new phishincidenteditor(this);
        phisheditor->setAttribute(Qt::WA_DeleteOnClose);
        phisheditor->loadIncidentDetails2(incidentID);
        phisheditor->saveIncident2(incidentID);
        phisheditor->show();
        }
    else if(incidentType == "Breach"){
        int incidentID = extractIncidentID(selectedItemText).toInt();
            databreacheditor *breacheditor = new databreacheditor(this);
            breacheditor->setAttribute(Qt::WA_DeleteOnClose);
            breacheditor->loadIncidentDetails3(incidentID);
            breacheditor->saveIncident3(incidentID);
            breacheditor->show();
    }
     else if(incidentType == "Ransomware"){
            int incidentID = extractIncidentID(selectedItemText).toInt();
            ransomwareeditor *ransomeditor = new ransomwareeditor(this);
            ransomeditor->setAttribute(Qt::WA_DeleteOnClose);
            ransomeditor->loadIncidentDetails4(incidentID);
            ransomeditor->saveIncident4(incidentID);
            ransomeditor->show();
        }
}





void Search::on_pushButton_clicked()
{
    this->hide();
    mainMenu menu;
    menu.setModal(true);
    menu.exec();

}

