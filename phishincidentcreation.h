#ifndef PHISHINCIDENTCREATION_H
#define PHISHINCIDENTCREATION_H

#include <QDialog>

namespace Ui {
class phishincidentcreation;
}

class phishincidentcreation : public QDialog
{
    Q_OBJECT

public:
    explicit phishincidentcreation(QWidget *parent = nullptr);
    ~phishincidentcreation();

private:
    Ui::phishincidentcreation *ui;
};

#endif // PHISHINCIDENTCREATION_H
