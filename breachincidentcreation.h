#ifndef BREACHINCIDENTCREATION_H
#define BREACHINCIDENTCREATION_H

#include <QDialog>

namespace Ui {
class BreachIncidentCreation;
}

class BreachIncidentCreation : public QDialog
{
    Q_OBJECT

public:
    explicit BreachIncidentCreation(QWidget *parent = nullptr);
    ~BreachIncidentCreation();
    void saveIncident();
    QString GenerateRandomID() const;

private slots:
    void on_pushButton_clicked();

private:
    Ui::BreachIncidentCreation *ui;
};

#endif // BREACHINCIDENTCREATION_H
