#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QGridLayout>
#include<QPushButton>
#include<QVBoxLayout>
#include<QPaintEvent>
#include<QPainter>
#include<QPixmap>
#include<QVector>
#include<QMessageBox>
#include<QComboBox>
#include<QLabel>
#include <QTimer>
#include<QPropertyAnimation>

class Widget : public QWidget
{
    Q_OBJECT
    QGridLayout *field;
    QPushButton *button;
    QPushButton *buttons[3][3];
    QVBoxLayout *vbox;
    QComboBox *modeSwitch;
    QLabel *label;
    QLabel *turn;

private:
bool playerTurn;
void Field();
bool checkRow();
bool checkCol();
bool checkDiag();
QVector<QVector<int>> values;
bool checkWin();
int counter;
//void resetGame();
void computerTurn();
QPoint getBestMove();
int minimax(int, bool);

private slots:
void clickButton();
void resetGame();
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
};
#endif // WIDGET_H
