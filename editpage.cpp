#include "editpage.h"
#include "ui_editpage.h"

EditPage::EditPage(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::EditPage)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    setFixedSize(800, 800);
    setWindowTitle("Edit Page");
    setStyleSheet("background-color: #2d42a8;");
}

EditPage::~EditPage()
{
    delete ui;
}
