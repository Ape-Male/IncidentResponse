#ifndef DATABREACHEDITOR_H
#define DATABREACHEDITOR_H

#include <QDialog>

namespace Ui {
class databreacheditor;
}

class databreacheditor : public QDialog
{
    Q_OBJECT

public:
    explicit databreacheditor(QWidget *parent = nullptr);
    ~databreacheditor();
    void loadIncidentDetails3(int incidentID);
    void saveIncident3(int incidentID);

private slots:
    void on_pushButton_clicked();

private:
    Ui::databreacheditor *ui;
    int incidentIDStore;
};

#endif // DATABREACHEDITOR_H
