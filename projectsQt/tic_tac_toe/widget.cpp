#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    vbox = new QVBoxLayout;
    turn = new QLabel;
    counter = 0;
    Field();
}

void Widget::Field(){
    field = new QGridLayout;
    button = new QPushButton;
    modeSwitch = new QComboBox(this);
    label = new QLabel;
    label->setText("Выберите режим игры: ");
    modeSwitch->addItem("Игрок против компьютера");
    modeSwitch->addItem("Игрок против игрока");
    connect(modeSwitch, SIGNAL(currentIndexChanged(int)), this, SLOT(resetGame()));
    for (int row = 0 ; row < 3; row++ ){
        QVector<int> rows;
        for (int col = 0; col < 3; col++){
            rows.push_back(0);
            button = new QPushButton;
            button->setFixedSize(100,100);
            connect(button, SIGNAL(clicked()), this, SLOT(clickButton()));
            field->addWidget(button, row, col);
            buttons[row][col] = button;
        }
        values.push_back(rows);
    }
    modeSwitch->setFixedSize(200,30);
    field->setAlignment(Qt::AlignCenter);
    vbox->addLayout(field);
    vbox->addWidget(label);
    vbox->addWidget(modeSwitch);
    setLayout(vbox);
    vbox->setAlignment(Qt::AlignCenter);

}

void Widget::clickButton(){
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    int row = -1;
    int col = -1;
    if (button){
        for(int i = 0; i < 3; i++){
            for(int j = 0; j<3; j++){
                if (buttons[i][j]==button){
                    row = i;
                    col = j;
                    break;
                }
            }
            if (row != -1){
                break;
            }
        }
    }
    if(!buttons[row][col]->isEnabled()){
        return;
    }

if(playerTurn){
    turn->setText("Ход нолика");
    vbox->addWidget(turn);
    setLayout(vbox);
    vbox->setAlignment(Qt::AlignCenter);

    counter++;
    QPixmap pixmap(100,100);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::red, 5));
    int x1 = 10; int y1 = 10;
    int x2 = button ->width() - 10; int y2 = button ->height() - 10;
    int x3 = button ->width() - 10; int y3 = 10;
    int x4 = 10; int y4 = button ->height() - 10;
    painter.drawLine(x1, y1, x2, y2);
    painter.drawLine(x3, y3, x4, y4);
    painter.end();
    button->setIcon(QIcon(pixmap));
    button->setIconSize(QSize(90,90));
    button->setStyleSheet("background-color: red;");
    button->setEnabled(false);

    playerTurn = false;
    values[row][col] = 1;
    if (checkWin()){
        QMessageBox information;
        information.setText("Крестики победили");
        information.exec();
        resetGame();
        return;
    }
    if(counter == 9)
    {
        QMessageBox information;
        information.setText("Ничья");
        information.exec();
        resetGame();
        return;
    }

    if(modeSwitch->currentIndex() == 0)
    {
         QTimer::singleShot(400, this, &Widget::computerTurn);
    }

}

    else {
        turn->setText("Ход крестика");
        counter++;
        QPixmap pixmap(100,100);
        pixmap.fill(Qt::transparent);
        QPainter painter(&pixmap);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(QPen(Qt::blue, 5));
        painter.drawEllipse(5,5,90,90);
        painter.end();
        button->setIcon(QIcon(pixmap));
        button->setIconSize(QSize(90,90));
        button->setStyleSheet("background-color: blue;");
        button->setEnabled(false);

        values[row][col] = 2;
        if (checkWin()){
            QMessageBox information;
            information.setText("Нолики победили");
            information.exec();
            resetGame();
            return;
        }
        if(counter == 9)
        {
            QMessageBox information;
            information.setText("Ничья");
            information.exec();
            resetGame();
            return;
        }
        playerTurn = true;
    }
}

bool Widget::checkRow(){
    for (int i = 0; i < 3; i++){
        if(values[i][0] != 0 && values[i][0] == values[i][1] && values[i][1] == values[i][2]){
            return true;
        }
    }
    return false;
}

bool Widget::checkCol(){
    for (int i = 0; i < 3; i++){
        if(values[0][i] != 0 && values[0][i] == values[1][i] && values[1][i] == values[2][i]){
            return true;
        }
    }
    return false;
}

bool Widget::checkDiag(){
    if((values[0][0] != 0 && values[0][0] == values[1][1] && values[1][1] == values[2][2] ) ||
            (values[0][2] != 0 && values[0][2] == values[1][1] && values[1][1] == values[2][0])) {
        return true;
    }
    return false;
}

bool Widget::checkWin(){
    return checkRow() || checkCol() || checkDiag();
}

Widget::~Widget()
{
}

void Widget::resetGame()
{
    for (int row = 0 ; row < 3; row++ ){
        for (int col = 0; col < 3; col++){
            QPixmap pixmap;
            buttons[row][col]->setIcon(pixmap);
            buttons[row][col]->setStyleSheet("");
            buttons[row][col]->setEnabled(true);
        }
    }

    values.clear();
    QVector<int> row(3, 0);
    for (int i = 0; i < 3; i++){
        values.push_back(row);
    }

    counter = 0;
    turn->setText("");
    playerTurn = true;
}

int Widget::minimax(int depth, bool isMaximizingPlayer)
{
    int score;
    int bestScore;

    if (checkWin()) {
        if (isMaximizingPlayer) {
            return -10;
        } else {
            return 10;
        }
    } else if (counter == 9) {
        return 0;
    }

    if (isMaximizingPlayer) {
        bestScore = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (values[i][j] == 0) {
                    values[i][j] = 2;
                    counter++;
                    score = minimax(depth + 1, false);
                    values[i][j] = 0;
                    counter--;
                    bestScore = std::max(score, bestScore);
                }
            }
        }
        return bestScore;
    } else {
        bestScore = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (values[i][j] == 0) {
                    values[i][j] = 1;
                    counter++;
                    score = minimax(depth + 1, true);
                    values[i][j] = 0;
                    counter--;
                    bestScore = std::min(score, bestScore);
                }
            }
        }
        return bestScore;
    }
}

void Widget::computerTurn()
{
    int bestScore = -1000;
    int score;
    int bestRow = -1;
    int bestCol = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (values[i][j] == 0) {
                values[i][j] = 2;
                counter++;
                score = minimax(0, false);
                values[i][j] = 0;
                counter--;
                if (score > bestScore) {
                    bestScore = score;
                    bestRow = i;
                    bestCol = j;
                }
            }
        }
    }

    buttons[bestRow][bestCol]->click();
}
