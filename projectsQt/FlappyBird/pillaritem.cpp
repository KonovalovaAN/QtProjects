#include "PillarItem.h"
#include<QRandomGenerator>
#include <QDebug>
#include <QGraphicsScene>
#include "BirdItem.h"
#include "Scene.h"

PillarItem::PillarItem():
    topPillar(new QGraphicsPixmapItem(QPixmap("C:\\Users\\PC\\Desktop\\images\\pipe.jpg"))),
    bottomPillar(new QGraphicsPixmapItem(QPixmap("C:\\Users\\PC\\Desktop\\images\\pipe.jpg"))),
    pastBird(false){
    topPillar->setPos(QPointF(0,0)-QPointF(topPillar->boundingRect().width()/2,
                      topPillar->boundingRect().height()+80));
    bottomPillar->setPos(QPointF(0,0) + QPointF(-bottomPillar->boundingRect().width()/2,
                                                60));


    addToGroup(topPillar);
    addToGroup(bottomPillar);

    yPos = QRandomGenerator::global()->bounded(150);
    int xRandomizer = QRandomGenerator::global()->bounded(200);

    setPos(QPointF(0,0) + QPoint(500 + xRandomizer,yPos));

    xAnimation = new QPropertyAnimation(this, "x",this);
    xAnimation->setStartValue(500 + xRandomizer);
    xAnimation->setEndValue(-500);
    xAnimation->setEasingCurve(QEasingCurve::Linear);
    xAnimation->setDuration(3000);

    connect(xAnimation,&QPropertyAnimation::finished,[=](){
        qDebug() << "Animation finished";
        scene()->removeItem(this);
        delete this;
    });

    xAnimation->start();
}

PillarItem::~PillarItem(){
    qDebug() << "Deleting Pillar";
    delete topPillar;
    delete bottomPillar;
}

qreal PillarItem::x() const{
    return m_x;
}

void PillarItem::freezeInPlace(){
    xAnimation->stop();
}

void PillarItem::setX(qreal x){
    m_x = x;

    if(x < 0 && !pastBird){
        pastBird = true;
        QGraphicsScene * mScene = scene();
        Scene * myScene = dynamic_cast<Scene * >(mScene);
        if(myScene){
            myScene->incrementScore();
        }
    }

    if(collidesWithBird()){
        emit collideFail();
    }
    setPos(QPointF(0,0) + QPointF(x,yPos));
}

bool PillarItem::collidesWithBird(){
    QList<QGraphicsItem*> collidingItems = topPillar->collidingItems();
    collidingItems.append(bottomPillar->collidingItems());
    foreach(QGraphicsItem * item, collidingItems){
        BirdItem *birdItem = dynamic_cast<BirdItem*>(item);
        if(birdItem){
            return true;
        }
    }
    return false;
}

