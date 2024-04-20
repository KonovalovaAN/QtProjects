#include "widget.h"
#include"unit.h"
#include<dialog.h>
#include<QDebug>
#include <QTextCodec>
#include <QRegExpValidator>
#include <QRegExp>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QRegExp regex("[а-яА-ЯёЁ]+");

    fioEdit = new QLineEdit(this);
    QRegExpValidator *validator = new QRegExpValidator(regex);
    fioEdit->setValidator(validator);
    projectEdit = new QLineEdit(this);
    taskEdit = new QTextEdit(this);
    calendarWidget = new QCalendarWidget(this);
    startDateEdit = new QDateEdit(this);
    endDateEdit = new QDateEdit(this);
    addButton = new QPushButton("Добавить", this);
    deleteButton = new QPushButton("Удалить", this);
    sortButton = new QPushButton("Сортировка", this);
    todayTasksButton = new QPushButton("Задания на сегодня", this);
    employeeReportButton = new QPushButton("Отчёт по сотрудникам", this);
    openFileButton = new QPushButton("Открыть файл", this);
    saveFileButton = new QPushButton("Сохранить файл", this);
    deleteAllButton = new QPushButton("Очистить таблицу",this);
    unitTable = new QTableWidget(this);
    unitTable->setColumnCount(6);
    unitTable->setHorizontalHeaderLabels(QStringList() << "ФИО исполнителя" << "Название проекта" << "Задание в рамках проекта" << "Дата выполнения задания" << "Дата начала работы" << "Дата окончания работы");

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(new QLabel("ФИО исполнителя"), 0, 0);
    layout->addWidget(fioEdit, 0, 1);
    layout->addWidget(new QLabel("Название проекта"), 1, 0);
    layout->addWidget(projectEdit, 1, 1);
    layout->addWidget(new QLabel("Задание в рамках проекта"), 2, 0);
    layout->addWidget(taskEdit, 2, 1);
    layout->addWidget(new QLabel("Дата выполнения задания"), 3, 0);
    layout->addWidget(calendarWidget, 3, 1);
    layout->addWidget(new QLabel("Дата начала работы"), 4, 0);
    layout->addWidget(startDateEdit, 4, 1);
    layout->addWidget(new QLabel("Дата окончания работы"), 5, 0);
    layout->addWidget(endDateEdit, 5, 1);
    layout->addWidget(addButton, 6, 0);
    layout->addWidget(deleteButton, 6, 1);
    layout->addWidget(sortButton, 7, 0);
    layout->addWidget(todayTasksButton, 7, 1);
    layout->addWidget(employeeReportButton, 8, 0);
    layout->addWidget(openFileButton, 9, 0);
    layout->addWidget(saveFileButton, 9, 1);
    layout->addWidget(deleteAllButton,8, 1);
    int windowHeight = this->height();
    unitTable->setFixedHeight(windowHeight);
    unitTable->setFixedWidth(600);
    layout->addWidget(unitTable, 0, 3, 5, 1);
    connect(addButton, &QPushButton::clicked, this, &Widget::addButtonClicked);
    connect(deleteButton, &QPushButton::clicked, this, &Widget::deleteButtonClicked);
    connect(openFileButton, &QPushButton::clicked, this, &Widget::openFileButtonClicked);
    connect(saveFileButton, &QPushButton::clicked, this, &Widget::saveFileButtonClicked);
    connect(deleteAllButton, &QPushButton::clicked, this, &Widget::clearUnitTable);
    connect(sortButton, &QPushButton::clicked, this, &Widget::sortButtonClicked);
    connect(employeeReportButton, &QPushButton::clicked, this, &Widget::employeeReportButtonClicked);
    connect(todayTasksButton, &QPushButton::clicked, this, &Widget::todayTasksButtonClicked);
}

Widget::~Widget()
{
    qDeleteAll(unitList);
}

void Widget::addButtonClicked()
{
    {
        QString fio = fioEdit->text();
        QString project = projectEdit->text();
        QString task = taskEdit->toPlainText();
        QDate deadline = calendarWidget->selectedDate();
        QDate startDate = startDateEdit->date();
        QDate endDate = endDateEdit->date();

        Unit* newUnit = new Unit(fio, project, task, deadline, startDate, endDate);

        unitList.append(newUnit);

        fioEdit->clear();
        projectEdit->clear();
        taskEdit->clear();
        calendarWidget->setSelectedDate(QDate::currentDate());
        startDateEdit->setDate(QDate::currentDate());
        endDateEdit->setDate(QDate::currentDate());

        int row = unitTable->rowCount();
        unitTable->insertRow(row);

        QTableWidgetItem* fioItem = new QTableWidgetItem(fio);
        QTableWidgetItem* projectItem = new QTableWidgetItem(project);
        QTableWidgetItem* taskItem = new QTableWidgetItem(task);
        QTableWidgetItem* deadlineItem = new QTableWidgetItem(deadline.toString("dd.MM.yyyy"));
        QTableWidgetItem* startDateItem = new QTableWidgetItem(startDate.toString("dd.MM.yyyy"));
        QTableWidgetItem* endDateItem = new QTableWidgetItem(endDate.toString("dd.MM.yyyy"));

        unitTable->setItem(row, 0, fioItem);
        unitTable->setItem(row, 1, projectItem);
        unitTable->setItem(row, 2, taskItem);
        unitTable->setItem(row, 3, deadlineItem);
        unitTable->setItem(row, 4, startDateItem);
        unitTable->setItem(row, 5, endDateItem);
   // updateUnitTable();
    }}

void Widget::deleteButtonClicked(){
    int row = unitTable->currentRow();
    if (row != -1){
        unitTable->removeRow(row);
    }
}

void Widget::clearUnitTable(){
    unitTable->clearContents();
    unitTable->setRowCount(0);
}

void Widget::updateUnitTable(){
//    unitTable->clearContents();

    for (int i = 0; i < unitList.size(); ++i) {
        Unit unit = *unitList.at(i);
        QTableWidgetItem *fioItem = new QTableWidgetItem(unit.getFio());
        QTableWidgetItem *projectItem = new QTableWidgetItem(unit.getProject());
        QTableWidgetItem *taskItem = new QTableWidgetItem(unit.getTask());
        QTableWidgetItem *deadlineItem = new QTableWidgetItem(unit.getDeadline().toString("dd.MM.yyyy"));
        QTableWidgetItem *startDateItem = new QTableWidgetItem(unit.getStartDate().toString("dd.MM.yyyy"));
        QTableWidgetItem *endDateItem = new QTableWidgetItem(unit.getEndDate().toString("dd.MM.yyyy"));

        unitTable->setItem(i, 0, fioItem);
        unitTable->setItem(i, 1, projectItem);
        unitTable->setItem(i, 2, taskItem);
        unitTable->setItem(i, 3, deadlineItem);
        unitTable->setItem(i, 4, startDateItem);
        unitTable->setItem(i, 5, endDateItem);
    }
}

void Widget::openFileButtonClicked(){
    QString filePath = QFileDialog::getOpenFileName(this, "Открыть файл", "", "Текстовые файлы (*.txt)");
    if (filePath.isEmpty()) {
        return;
    }
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Не удалось открыть файл" << filePath;
        return;
    }
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');
        if (fields.size() == 6) {
            Unit unit(fields.at(0), fields.at(1), fields.at(2), QDate::fromString(fields.at(3), "dd.MM.yyyy"),
                      QDate::fromString(fields.at(4), "dd.MM.yyyy"), QDate::fromString(fields.at(5), "dd.MM.yyyy"));
            int row = unitTable->rowCount();
            unitTable->setRowCount(row + 1);
            unitTable->setItem(row, 0, new QTableWidgetItem(unit.getFio()));
            unitTable->setItem(row, 1, new QTableWidgetItem(unit.getProject()));
            unitTable->setItem(row, 2, new QTableWidgetItem(unit.getTask()));
            unitTable->setItem(row, 3, new QTableWidgetItem(unit.getDeadline().toString("dd.MM.yyyy")));
            unitTable->setItem(row, 4, new QTableWidgetItem(unit.getStartDate().toString("dd.MM.yyyy")));
            unitTable->setItem(row, 5, new QTableWidgetItem(unit.getEndDate().toString("dd.MM.yyyy")));
        } else {
            qDebug() << "Неправильный формат строки:" << line;
        }
    }
    file.close();
}

void Widget::saveFileButtonClicked(){
    QString filePath = QFileDialog::getSaveFileName(this, "Сохранить файл", "", "Текстовые файлы (*.txt)");
    if (filePath.isEmpty()) {
        return;
    }
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Не удалось открыть файл" << filePath;
        return;
    }

    QTextStream out(&file);
    for (int i = 0; i < unitTable->rowCount(); ++i) {
    QString fio = unitTable->item(i, 0)->text();
    QString project = unitTable->item(i, 1)->text();
    QString task = unitTable->item(i, 2)->text();
    QString deadline = unitTable->item(i, 3)->text();
    QString startDate = unitTable->item(i, 4)->text();
    QString endDate = unitTable->item(i, 5)->text();
    out << fio << "," << project << "," << task << "," << deadline << "," << startDate << "," << endDate << "\n";
}

    file.close();
}

void Widget::sortButtonClicked() {

    QList<QPair<QString, QDate>> projects;

    for (int i = 0; i < unitTable->rowCount(); i++) {
        QString projectName = unitTable->item(i, 1)->text();
        QDate projectEndDate = QDate::fromString(unitTable->item(i, 5)->text(), "dd.MM.yyyy");

        projects.append(qMakePair(projectName, projectEndDate));
    }

    std::sort(projects.begin(), projects.end(), [](const QPair<QString, QDate>& p1, const QPair<QString, QDate>& p2) {
        return p1.second < p2.second;
    });

    QString report = "Список всех проектов фирмы, отсортированных по дате завершения работы:\n\n";
    for (auto project : projects) {
        report += project.first + ", завершение работы: " + project.second.toString("dd.MM.yyyy") + "\n";
    }

    QMessageBox::information(this, "Отчет", report);
}

void Widget::todayTasksButtonClicked(){

    QStringList employeeNames;
    for (int i = 0; i < unitTable->rowCount(); i++) {
        QString employeeName = unitTable->item(i, 0)->text();
        if (!employeeNames.contains(employeeName)) {
            employeeNames.append(employeeName);
        }
    }

    QString selectedEmployee = QInputDialog::getItem(this, tr("Отчет по сотруднику"), tr("Выберите сотрудника:"), employeeNames);

    QDate currentDate = QDate::currentDate();

    QStringList tasksList;
    for (int i = 0; i < unitTable->rowCount(); i++) {

        QString taskEmployeeName = unitTable->item(i, 0)->text();
        QString taskStartDateString = unitTable->item(i, 4)->text();
        QString taskEndDateString = unitTable->item(i, 5)->text();

        QDateTime taskStartDate = QDateTime::fromString(taskStartDateString, "dd.MM.yyyy");
        QDateTime taskEndDate = QDateTime::fromString(taskEndDateString, "dd.MM.yyyy");

        if (taskStartDate.date() <= currentDate && taskEndDate.date() >= currentDate && taskEmployeeName == selectedEmployee) {
            QString taskName = unitTable->item(i, 2)->text();
            tasksList.append(taskName);
        }
    }

    if (tasksList.isEmpty()) {
        QMessageBox::information(this, tr("Список задач"), tr("Нет задач для выбранного сотрудника за текущие сутки."));
    } else {
        QMessageBox::information(this, tr("Список задач"), tasksList.join("\n"));
    }
}

void Widget::employeeReportButtonClicked(){

    QDateTime currentTime = QDateTime::currentDateTime();
    QDate currentDate = currentTime.date();
    QDate startDate = currentDate.addMonths(-1).addDays(1 - currentDate.day());
    QDate endDate = currentDate.addDays(-currentDate.day());

    QMap<QString, int> employeeTimeMap;

    for (int i = 0; i < unitTable->rowCount(); i++) {

        QString employeeName = unitTable->item(i, 0)->text();
        QString taskStartDateString = unitTable->item(i, 4)->text();
        QString taskEndDateString = unitTable->item(i, 5)->text();

        QDateTime taskStartDate = QDateTime::fromString(taskStartDateString, "dd.MM.yyyy");
        QDateTime taskEndDate = QDateTime::fromString(taskEndDateString, "dd.MM.yyyy");

        if (taskStartDate.date() >= startDate && taskEndDate.date() <= endDate) {
            int taskDuration = taskStartDate.secsTo(taskEndDate) / 3600;

            if (employeeTimeMap.contains(employeeName)) {
                employeeTimeMap[employeeName] += taskDuration;
            } else {
                employeeTimeMap.insert(employeeName, taskDuration);
            }
        }
    }

    QStringList employeeTimeList;
    for (const QString& employeeName : employeeTimeMap.keys()) {
        int employeeTime = employeeTimeMap.value(employeeName);
        employeeTimeList.append(QString("%1: %2 ч.").arg(employeeName).arg(employeeTime/2));
    }

    if (employeeTimeList.isEmpty()) {
        QMessageBox::information(this, tr("Список сотрудников"), tr("Нет данных о работе сотрудников за прошедший месяц."));
    } else {
        QMessageBox::information(this, tr("Список сотрудников"), employeeTimeList.join("\n"));
    }
}
