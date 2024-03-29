#ifndef LOGINCIDENT_H
#define LOGINCIDENT_H

#include <QDialog>

namespace Ui {
class LogIncident;
}

class LogIncident : public QDialog
{
    Q_OBJECT

public:
    explicit LogIncident(QWidget *parent = nullptr);
    ~LogIncident();

private slots:
    void on_phishIncident_clicked();

    void on_backButton_clicked();

    void on_dataBreachIncident_clicked();

    void on_malwareAttack_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::LogIncident *ui;
};

#endif // LOGINCIDENT_H
