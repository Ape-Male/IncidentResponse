#ifndef PHISHINCIDENTEDITOR_H
#define PHISHINCIDENTEDITOR_H

#include <QDialog>

namespace Ui {
class phishincidenteditor;
}

class phishincidenteditor : public QDialog
{
    Q_OBJECT

public:
    explicit phishincidenteditor(QWidget *parent = nullptr);
    ~phishincidenteditor();
    void loadIncidentDetails2(int incidentID);
    void saveIncident2(int incidentID);
private slots:
    void on_pushButton_clicked();

private:
    Ui::phishincidenteditor *ui;
    int incidentIDStore;
};

#endif // PHISHINCIDENTEDITOR_H
