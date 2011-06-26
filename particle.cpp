#include "particle.h"
#include "gamescene.h"

#include <QStaticText>

Particle::Particle(int number) :
    QGraphicsObject(), _active(false), _velocity(0,0)
{
    _number = number;
    _velocity.setY(number*0.01);
}

void Particle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if(active()) {
        painter->setPen(QPen(Qt::blue));
        painter->drawRect(-2.5,-2.5,5,5);
        //        painter->drawPoint(0,0);
        //        painter->drawStaticText(0,0,QStaticText(QString::number(_number)));
    }
}

QRectF Particle::boundingRect() const {
    return QRectF(0,0,5,5);
}

void Particle::advance(int phase){

    if(active()) {
        QVector2D force;
        foreach(Planet* planet, gameScene()->planets()) {
            QVector2D r = QVector2D(this->pos() - planet->pos());
            // save the length and lengthSquared to memory to avoid recalculations (with square roots!)
    //        double distance = r.length();
            double distanceSquared = r.lengthSquared();
            QVector2D rn = r.normalized();
            if(distanceSquared != 0) {
                QVector2D gravity = - rn * 10000.0 / distanceSquared;
                force += gravity;

                if (distanceSquared < planet->radius()*planet->radius()) { //Vj: Temporary fix while testing :O)
                    force=QVector2D(0,0);
                    _velocity = QVector2D(0,0);
                    break;
                }
            }
        }
        QVector2D acceleration = force / 1.0;
        _velocity += acceleration * gameScene()->dt();
        setX(x() + _velocity.x() * gameScene()->dt());
        setY(y() + _velocity.y() * gameScene()->dt());
    }
}

GameScene* Particle::gameScene() {
    if(scene()) {
        return (GameScene*)scene();
    } else {
        qDebug() << "GameObject::gameScene(): Cannot return gameScene without scene";
        return 0;
    }
}
