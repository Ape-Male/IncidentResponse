#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include "mainmenu.h";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    setFixedSize(1280, 1080);
    setWindowTitle("Incident Response Tool");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonLogin_clicked()
{
    // dead call, code doesnt work if i remove it!

}

void MainWindow::on_loginButton_clicked()
{
    QString username = ui->userName->text();
    QString password = ui->passWordInfo->text();

    qDebug() << "Username: " << username;
    qDebug() << "Password: " << password;

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Login", "Please enter both username and password.");
        return;
    }

    QString dbFilePath = QDir(QCoreApplication::applicationDirPath()).filePath("D:/Dissertation/SQL TEST/SQL/logins.db");

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbFilePath);
    if (!db.open()) {
        QMessageBox::critical(this, "Error", "Failed to open database: " + db.lastError().text());
        return;
    }
    QSqlQuery query;
    QString queryString = "SELECT * FROM Logins WHERE Username = :username AND Password = :password";
    qDebug() << "SQL query: " << queryString;

    query.prepare(queryString);
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (query.exec()) {
        if (query.next()) {
            QMessageBox::information(this, "Login", "Login successful!");
            this->hide();
            mainMenu mainmenu;
            mainmenu.setModal(true);
            mainmenu.exec();
        } else {
            QMessageBox::warning(this, "Login", "Invalid username or password.");
        }
    } else {
        QMessageBox::critical(this, "Error", "Failed to execute query: " + query.lastError().text());
    }

    db.close();
}

