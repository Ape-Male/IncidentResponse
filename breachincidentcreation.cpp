#include "breachincidentcreation.h"
#include "ui_breachincidentcreation.h"

BreachIncidentCreation::BreachIncidentCreation(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::BreachIncidentCreation)
{
    ui->setupUi(this);
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    setFixedSize(1280, 1080);
    setWindowTitle("Incident Response Tool");
    setStyleSheet("background-color: #2d42a8;");
}

BreachIncidentCreation::~BreachIncidentCreation()
{
    delete ui;
}
