#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QDialog>
#include <QtWidgets>

namespace Ui {
class dashboard;
}

class dashboard : public QDialog
{
    Q_OBJECT

public:
    explicit dashboard(QWidget *parent = nullptr);
    ~dashboard();

private slots:
    void loadIncidentToList();

private:
    Ui::dashboard *ui;
    QListWidget *severityDash;

    void loadIncidentCounts(QListWidget *listWidget);
    void loadSeverityCounts(QListWidget *listWidget);
    void loadAffectedUsersCounts (QListWidget *listWidget);
    void loadMaliciousIPs (QListWidget *listWidget);



};

#endif // DASHBOARD_H
