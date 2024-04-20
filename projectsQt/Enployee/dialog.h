#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include<QComboBox>
#include<QGridLayout>
#include<QPushButton>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QDialog *parent = nullptr);
    ~Dialog();

private:
    QComboBox *choice;
    QPushButton *showOneEmplTasks;
    QPushButton *closeDialog;

private slots:

};

#endif // WIDGET_H
