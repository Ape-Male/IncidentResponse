#ifndef SEARCH_H
#define SEARCH_H
#include <QSqlQuery>
#include <QListWidgetItem>

#include <QDialog>

namespace Ui {
class Search;
}

class Search : public QDialog
{
    Q_OBJECT

public:
    explicit Search(QWidget *parent = nullptr);
    ~Search();
    void displayQueryResults(QSqlQuery& query, const QString& incidentType);
    QString extractIncidentID(const QString &itemText);

private slots:
    void on_searchButton_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_pushButton_clicked();

private:
    Ui::Search *ui;
};

#endif // SEARCH_H
