#include "particle.h"

Particle::Particle() :
    QGraphicsObject()
{
}

void Particle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if(active()) {
        painter->setBrush(QBrush(Qt::red));
        painter->setPen(QPen(Qt::blue));
        painter->drawRect(0,0,5,5);
    }
}

QRectF Particle::boundingRect() const {
    return QRectF(0,0,5,5);
}

void Particle::advance(int phase){
    if(active()) {
        setX(x() + 0.8 * (qreal)rand() / (qreal)RAND_MAX);
        setY(y() + 0.7 * (qreal)rand() / (qreal)RAND_MAX);
    }
}
