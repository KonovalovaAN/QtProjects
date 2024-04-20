#include "widget.h"
#include<QWidget>
#include <QApplication>
#include<QLabel>
#include<QPushButton>
#include<QVBoxLayout>
#include<QLineEdit>
#include<QDebug>
#include<QStringList>
#include <QtCharts/QtCharts>
#include <QRegExpValidator>
#include <QRegExp>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QRegExp regex("[0-9 ]+");
    QRegExpValidator *validator = new QRegExpValidator(regex);
    vbox = new QVBoxLayout();
    input = new QLineEdit;
    input->setValidator(validator);
    btnQuit = new QPushButton("&Create gistogramma");
    poloci  = new QBarSeries();
    chart  = new QChart();
    chartView  = new QChartView(chart);
    axisY = new QValueAxis();
    vbox -> addWidget(input);
    vbox -> addWidget(btnQuit);
    vbox -> addWidget(chartView);
    setLayout(vbox);
   connect(btnQuit, SIGNAL(clicked()), this, SLOT(on_btnQuit_clicked()));
}

void Widget::on_btnQuit_clicked()
{
    QVector<int> data;
    QString text = input -> text();
    QStringList list = text.split(' ');
    bool ok;
    for (QString valueStr : list) {
         int value = valueStr.toInt(&ok);
          data.push_back(value);
     }
    for(int i=0; i < data.size(); i++){
    recti = new QBarSet("");
    recti->append(data[i]);
    poloci->append(recti);
    }
    chart->addSeries(poloci);
    chart->setTitle("Numbers");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    QList<QBarSet *> sets = poloci->barSets();
    for(int i = 0; i < sets.size(); ++i)
    {
     QColor col = QColor(QRandomGenerator::global()->bounded(256),
                         QRandomGenerator::global()->bounded(256),
                          QRandomGenerator::global()->bounded(256));
      sets[i]->setColor(col);
    }
    axisY->setRange(0,20);
    chart->addAxis(axisY, Qt::AlignLeft);
    poloci->attachAxis(axisY);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);
    chartView->setRenderHint(QPainter::Antialiasing);
    resize(900, 700);
}


Widget::~Widget()
{
}

