#include "mainmenu.h"
#include "search.h"
#include "ui_mainmenu.h"
#include "logincident.h"
#include "dashboard.h"

mainMenu::mainMenu(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::mainMenu)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    setFixedSize(1280, 1080);
    setWindowTitle("Incident Response Tool");
    setStyleSheet("background-color: #2d42a8;");
}


mainMenu::~mainMenu()
{
    delete ui;
}

void mainMenu::on_logIncidentButton_clicked()
{
    this->hide();
    LogIncident logincident;
    logincident.setModal(true);
    logincident.exec();
}





void mainMenu::on_searchIncidentButon_clicked()
{
    this->hide();
    Search searchincident;
    searchincident.setModal(true);
    searchincident.exec();
}


void mainMenu::on_viewIncidentsButton_clicked()
{
    this->hide();
    dashboard Dash;
    Dash.setModal(true);
    Dash.exec();

}

