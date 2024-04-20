#include "widget.h"
#include "ui_widget.h"
#include <cstdlib>
#include <ctime>
#include<QMessageBox>
#include<QString>
#include<QComboBox>
#include<QDebug>
#include<QWidget>
#include<QGroupBox>
#include<QCheckBox>
#include<QButtonGroup>
#include<QRadioButton>
#include<QtAlgorithms>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    // Список возможных результатов теста
    QStringList results = {"Трушный студент", "студэнт", "щенок", "демократ"};
    srand(time(NULL));
    int index = rand() % results.size();
    // Отображение результата теста в отдельном окне
    QMessageBox::information(this, "Результат теста", results[index]);

    QStringList myStringList;

    // Получить содержимое QLineEdit
    QString myText = ui->lineEdit->text();
    // Добавить его в QStringList
    if (myText != ""){
    myStringList.append(myText);
    }
    ui->lineEdit->clear();

    myText = ui->lineEdit_2->text();
    if (myText != ""){
    myStringList.append(myText);
    }
    ui->lineEdit_2->clear();

    myText = ui->lineEdit_3->text();
    if (myText != ""){
    myStringList.append(myText);
    }
    ui->lineEdit_3->clear();

    myText = ui->lineEdit_4->text();
    if (myText != ""){
    myStringList.append(myText);
    }
    ui->lineEdit_4->clear();

    for (int i = 2; i <= 21; ++i) {
        QCheckBox* checkBox = this->findChild<QCheckBox*>("checkBox_" + QString::number(i));
        if (checkBox != nullptr) {
            if (checkBox->isChecked()) {
                myStringList.append(checkBox->text());
            }
            checkBox->setChecked(false);
        }
    }

    QCheckBox* checkBox = this->findChild<QCheckBox*>("checkBox");
    if (checkBox != nullptr) {
        if (checkBox->isChecked()) {
            myStringList.append(checkBox->text());
        }
        checkBox->setChecked(false);
    }

    // Группа #1 ..............................
    if(QRadioButton* checkedRadioButton = qobject_cast<QRadioButton*>(ui->buttonGroup->checkedButton())) {
        myStringList.append(checkedRadioButton->text());
    }

    if (QRadioButton *checkedButton = qobject_cast<QRadioButton *>(ui->buttonGroup->checkedButton())) {
            // Сбрасываем выбранную радиокнопку
            ui->buttonGroup->setExclusive(false); // Отключаем эксклюзивный выбор в группе
            checkedButton->setChecked(false); // Сбрасываем выбранную радиокнопку
            ui->buttonGroup->setExclusive(true); // Включаем эксклюзивный выбор в группе
    }

    // Группа #2
    if(QRadioButton* checkedRadioButton = qobject_cast<QRadioButton*>(ui->buttonGroup_2->checkedButton())) {
        myStringList.append(checkedRadioButton->text());
    }

    if (QRadioButton *checkedButton = qobject_cast<QRadioButton *>(ui->buttonGroup_2->checkedButton())) {
            // Сбрасываем выбранную радиокнопку
            ui->buttonGroup_2->setExclusive(false); // Отключаем эксклюзивный выбор в группе
            checkedButton->setChecked(false); // Сбрасываем выбранную радиокнопку
            ui->buttonGroup_2->setExclusive(true); // Включаем эксклюзивный выбор в группе
        }

    // Группа #3
    if(QRadioButton* checkedRadioButton = qobject_cast<QRadioButton*>(ui->buttonGroup_3->checkedButton())) {
        myStringList.append(checkedRadioButton->text());
    }
    if (QRadioButton *checkedButton = qobject_cast<QRadioButton *>(ui->buttonGroup_3->checkedButton())) {
            // Сбрасываем выбранную радиокнопку
            ui->buttonGroup_3->setExclusive(false); // Отключаем эксклюзивный выбор в группе
            checkedButton->setChecked(false); // Сбрасываем выбранную радиокнопку
            ui->buttonGroup_3->setExclusive(true); // Включаем эксклюзивный выбор в группе
        }

    // Группа #4
    if (QRadioButton *checkedButton = qobject_cast<QRadioButton *>(ui->buttonGroup_4->checkedButton())) {
        // Сбрасываем выбранную радиокнопку
        ui->buttonGroup_4->setExclusive(false); // Отключаем эксклюзивный выбор в группе
        checkedButton->setChecked(false); // Сбрасываем выбранную радиокнопку
        ui->buttonGroup_4->setExclusive(true); // Включаем эксклюзивный выбор в группе
    }

    QDate date = ui->dateEdit->date(); // Получение выбранной пользователем даты из QDateEdit
    QString dateString = date.toString("dd.MM.yyyy"); // Преобразование даты в строку в формате "dd.MM.yyyy"
    myStringList.append(dateString); // Добавление даты в QStringList
    ui->dateEdit->clear(); // Сбрасываем значение даты

    QString selectedText = ui->comboBox->currentText(); // Получение выбранного пользователем текста
    if (selectedText != ""){
    myStringList.append(selectedText); // Добавление выбранного текста в QStringList
    }
    selectedText = ui->comboBox_2->currentText();
    if (selectedText != ""){
    myStringList.append(selectedText);
    }
    selectedText = ui->comboBox_4->currentText();
    if (selectedText != ""){
    myStringList.append(selectedText);
    }
    selectedText = ui->comboBox_5->currentText();
    if (selectedText != ""){
    myStringList.append(selectedText);
    }
    selectedText = ui->comboBox_6->currentText();
    if (selectedText != ""){
    myStringList.append(selectedText);
    }
    selectedText = ui->comboBox_7->currentText();
    if (selectedText != ""){
    myStringList.append(selectedText);
    }

    ui->comboBox->setCurrentIndex(-1); // Сбрасываем выбранный элемент
    ui->comboBox_2->setCurrentIndex(-1);
    ui->comboBox_4->setCurrentIndex(-1);
    ui->comboBox_5->setCurrentIndex(-1);
    ui->comboBox_6->setCurrentIndex(-1);
    ui->comboBox_7->setCurrentIndex(-1);

    myStringList.QStringList::sort();

    QMessageBox msg;
    msg.setText("Sort QStringList");
    msg.setInformativeText(myStringList.join('\n'));
    msg.exec();

    qDebug() << myStringList;
}

