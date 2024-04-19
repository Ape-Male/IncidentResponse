#ifndef RANSOMWAREEDITOR_H
#define RANSOMWAREEDITOR_H

#include <QDialog>

namespace Ui {
class ransomwareeditor;
}

class ransomwareeditor : public QDialog
{
    Q_OBJECT

public:
    explicit ransomwareeditor(QWidget *parent = nullptr);
    ~ransomwareeditor();
    void loadIncidentDetails4(int incidentID);
    void saveIncident4(int incidentID);
private slots:
    void on_pushButton_clicked();

private:
    Ui::ransomwareeditor *ui;
    int incidentIDStore;
};

#endif // RANSOMWAREEDITOR_H
