#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "logincident.h"

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




