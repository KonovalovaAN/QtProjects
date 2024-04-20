#include "widget.h"
#include"dialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
  //  Dialog z;
  //  z.show();
    w.show();
    return a.exec();
}
