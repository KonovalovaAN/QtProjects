#include "unit.h"

Unit::Unit(const QString& fio_, const QString& project_, const QString& task_, const QDate& deadline_, const QDate& startDate_, const QDate& endDate_)
    : fio(fio_), project(project_), task(task_), deadline(deadline_), startDate(startDate_), endDate(endDate_)
{}

QString Unit::getFio() const {
    return fio;
}

void Unit::setFio(const QString& fio_) {
    fio = fio_;
}

QString Unit::getProject() const {
    return project;
}

void Unit::setProject(const QString& project_) {
    project = project_;
}

QString Unit::getTask() const {
    return task;
}

void Unit::setTask(const QString& task_) {
    task = task_;
}

QDate Unit::getDeadline() const {
    return deadline;
}

void Unit::setDeadline(const QDate& deadline_) {
    deadline = deadline_;
}

QDate Unit::getStartDate() const {
    return startDate;
}

void Unit::setStartDate(const QDate& startDate_) {
    startDate = startDate_;
}

QDate Unit::getEndDate() const {
    return endDate;
}

void Unit::setEndDate(const QDate& endDate_) {
    endDate = endDate_;
}
