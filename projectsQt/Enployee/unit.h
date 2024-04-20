#ifndef UNIT_H
#define UNIT_H

#include <QString>
#include <QDate>

class Unit {
public:
    Unit(const QString& fio_, const QString& project_, const QString& task_, const QDate& deadline_, const QDate& startDate_, const QDate& endDate_);

    QString getFio() const;
    void setFio(const QString& fio_);

    QString getProject() const;
    void setProject(const QString& project_);

    QString getTask() const;
    void setTask(const QString& task_);

    QDate getDeadline() const;
    void setDeadline(const QDate& deadline_);

    QDate getStartDate() const;
    void setStartDate(const QDate& startDate_);

    QDate getEndDate() const;
    void setEndDate(const QDate& endDate_);

private:
    QString fio;
    QString project;
    QString task;
    QDate deadline;
    QDate startDate;
    QDate endDate;
};

#endif // UNIT_H
