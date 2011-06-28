#ifndef PLANET_H
#define PLANET_H

#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>

#include "gameobject.h"

class Planet : public GameObject
{
    Q_OBJECT
public:
    explicit Planet(qreal radius, qreal mass);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    qreal radius() { return _radius; }
    qreal mass() {return _mass; }
    void collideWithParticle();

    bool active() {return _active; }
    void setActive(bool active) {_active = active;}
protected:
    void advance(int phase);

signals:

public slots:

private:
    bool _active;
    qreal _radius;
    qreal _mass;

};

#endif // PLANET_H
