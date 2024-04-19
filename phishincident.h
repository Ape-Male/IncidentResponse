#ifndef PHISHINCIDENT_H
#define PHISHINCIDENT_H

#include <QDialog>

namespace Ui {
class PhishIncident;
}

class PhishIncident : public QDialog
{
    Q_OBJECT

public:
    explicit PhishIncident(QWidget *parent = nullptr);
    ~PhishIncident();
    QString generateRandomID() const;
    void saveIncident();


private slots:



    void on_pushButton_clicked();

private:
    Ui::PhishIncident *ui;
};

#endif // PHISHINCIDENT_H
