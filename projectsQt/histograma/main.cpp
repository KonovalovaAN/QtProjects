#include "widget.h"
#include<QWidget>
#include <QApplication>
#include<QLabel>
#include<QString>
#include<QLineEdit>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QRandomGenerator>
#include <QColor>
#include<QVBoxLayout>
#include <QVector>

int main(int argc, char *argv[])
{
   QApplication app(argc, argv);
    Widget window;
    window.setWindowTitle("Enter data: ");
    window.resize(300, 70);
    window.show();
    return app.exec();
}
