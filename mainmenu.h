#ifndef MAINMENU_H
#define MAINMENU_H

#include <QDialog>

namespace Ui {
class mainMenu;
}

class mainMenu : public QDialog
{
    Q_OBJECT

public:
    explicit mainMenu(QWidget *parent = nullptr);
    ~mainMenu();

private slots:
    void on_logIncidentButton_clicked();

    void on_searchIncidentButon_clicked();

    void on_viewIncidentsButton_clicked();

private:
    Ui::mainMenu *ui;
};

#endif // MAINMENU_H
