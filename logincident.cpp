#include "logincident.h"
#include "ui_logincident.h"
#include "phishincident.h"
#include "mainmenu.h"

LogIncident::LogIncident(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LogIncident)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    setFixedSize(1280, 1080);
    setWindowTitle("Incident Response Tool");
    setStyleSheet("background-color: #2d42a8;");

}

LogIncident::~LogIncident()
{
    delete ui;
}

void LogIncident::on_phishIncident_clicked()
{
    this->hide();
    PhishIncident phishingIncident;
    phishingIncident.setModal(true);
    phishingIncident.exec();
}


void LogIncident::on_backButton_clicked()
{
    this->hide();
    mainMenu menu;
    menu.setModal(true);
    menu.exec();

}

