#include "dialog.h"

Dialog::Dialog(QDialog *parent)
    : QDialog(parent)
{
    choice = new QComboBox(this);
    showOneEmplTasks = new QPushButton(this);
    closeDialog = new QPushButton(this);
    closeDialog->setText("Закрыть окно");
    showOneEmplTasks->setText("Выдать список");
    QGridLayout *dial = new QGridLayout(this);
    dial->addWidget(choice, 0, 0);
    dial->addWidget(showOneEmplTasks, 0, 2);
    dial->addWidget(closeDialog, 1, 2);
}

Dialog::~Dialog()
{
}
