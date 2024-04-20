#ifndef WIDGET_H
#define WIDGET_H
#include<QWidget>
#include <QApplication>
#include<QLabel>
#include<QPushButton>
#include<QVBoxLayout>
#include<QLineEdit>
#include<cmath>
#include<QString>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QRandomGenerator>
#include <QColor>
#include <QVector>
#include <QtCharts/QtCharts>






class Widget : public QWidget
{
    Q_OBJECT
private:
    QLineEdit *input;
    QPushButton *btnQuit;
    QVBoxLayout *vbox;
    QBarSet *recti;
    QBarSeries *poloci;
    QChart *chart;
    QChartView *chartView;
    QValueAxis *axisY;
private slots:
    void on_btnQuit_clicked();
public:

    Widget(QWidget *parent = nullptr);
    ~Widget();
};
#endif // WIDGET_H
