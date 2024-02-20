#ifndef RANSOMWAREINCIDENT_H
#define RANSOMWAREINCIDENT_H

#include <QDialog>

namespace Ui {
class ransomwareIncident;
}

class ransomwareIncident : public QDialog
{
    Q_OBJECT

public:
    explicit ransomwareIncident(QWidget *parent = nullptr);
    ~ransomwareIncident();

private slots:
    void on_ransomsaveButton_clicked();
    QString GenerateRandomID() const;

private:
    Ui::ransomwareIncident *ui;
};

#endif // RANSOMWAREINCIDENT_H
