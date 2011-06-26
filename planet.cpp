#include "planet.h"

Planet::Planet(qreal radius, qreal x, qreal y) : QGraphicsObject()
{
    _radius = radius;
    setActive(true);
    setX(x);
    setY(y);
}

void Planet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if(active()) {
        painter->setBrush(QBrush(Qt::red));
        painter->setPen(QPen(Qt::blue));
        painter->drawEllipse(-radius(), -radius(),radius()*2,radius()*2);
    }
}

QRectF Planet::boundingRect() const {
    return QRectF(0,0,5,5);
}

void Planet::advance(int phase){
}
