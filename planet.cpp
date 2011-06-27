#include "planet.h"

#include "gamescene.h"
#include "math.h"

Planet::Planet(qreal radius) : GameObject()
{
    _radius = radius;
    setActive(true);
}

void Planet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if(active()) {
        painter->setBrush(QBrush(QColor(200,20,20,100)));
        painter->setPen(QPen(Qt::blue));
        qreal pixelRadius = gameScene()->fromRel(radius());
        painter->drawEllipse(-pixelRadius, -pixelRadius,pixelRadius*2,pixelRadius*2);
    }
}

QRectF Planet::boundingRect() const {
    return QRectF(0,0,5,5);
}

void Planet::advance(int phase){
}

void Planet::increaseRadius() {
    //_radius+=0.001;
    //alt:
   _radius = sqrt(_radius*_radius +0.00001);
}
