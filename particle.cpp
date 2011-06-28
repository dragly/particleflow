#include "particle.h"
#include "gamescene.h"

#include <QStaticText>

static qreal GravityConstant = 0.001;

Particle::Particle() :
    GameObject(), _active(false)
{
}

void Particle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if(active()) {
       // painter->setPen(QPen(Qt::blue));
         painter->setBrush(QBrush(Qt::blue));
        painter->drawRect(-2.5,-2.5,5,5);
//                painter->drawPoint(0,0);
    }
}

QRectF Particle::boundingRect() const {
    return QRectF(0,0,5,5);
}

void Particle::advance(int phase){

    if(active()) {
        QVector2D force;
        foreach(Planet* planet, gameScene()->planets()) {
            QVector2D r = QVector2D(this->position() - planet->position());
            // save the length and lengthSquared to memory to avoid recalculations (with square roots!)
    //        double distance = r.length();
            double distanceSquared = r.lengthSquared() - planet->radius()*planet->radius();
            QVector2D rn = r.normalized();
            if(distanceSquared != 0) {
                QVector2D gravity = - rn * GravityConstant * planet->mass() / distanceSquared;
                force += gravity;

                if (r.lengthSquared() < planet->radius()*planet->radius()) { //Vj: Temporary fix while testing :O)
                    planet->collideWithParticle();
                    gameScene()->removeParticle(this);
                    return;
                }
            }
        }
        QVector2D acceleration = force / 1.0;
        _velocity += acceleration * gameScene()->dt();
        _position += _velocity * gameScene()->dt();
        resized();
    }
    if(position().lengthSquared() > 5.0) { // if we are too far away to be useful, just delete this particle
        gameScene()->removeParticle(this);
    }
}
