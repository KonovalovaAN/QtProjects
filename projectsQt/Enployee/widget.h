#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QCalendarWidget>
#include <QDateEdit>
#include <QTextEdit>
#include <QPushButton>
#include<QGridLayout>
#include<QLabel>
#include<QMessageBox>
#include<QDate>
#include<QListWidgetItem>
#include<QList>
#include<QTableWidget>
#include<QFileDialog>
#include<QInputDialog>
#include"unit.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QLineEdit *fioEdit;
    QLineEdit *projectEdit;
    QTextEdit *taskEdit;
    QCalendarWidget *calendarWidget;
    QDateEdit *startDateEdit;
    QDateEdit *endDateEdit;
    QPushButton *addButton;
    QPushButton *deleteButton;
    QPushButton *sortButton;
    QPushButton *todayTasksButton;
    QPushButton *employeeReportButton;
    QPushButton *openFileButton;
    QPushButton *deleteAllButton;
    QPushButton *saveFileButton;
    QList<Unit*> unitList;
    QTableWidget *unitTable;

private slots:
    void clearUnitTable();
    void addButtonClicked();
    void deleteButtonClicked();
    void updateUnitTable();
    void sortButtonClicked();
    void todayTasksButtonClicked();
    void employeeReportButtonClicked();
    void openFileButtonClicked();
    void saveFileButtonClicked();
};

#endif // WIDGET_H
