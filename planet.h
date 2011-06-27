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
    explicit Planet(qreal radius);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    qreal radius() { return _radius; }
    void increaseRadius();

    bool active() {return _active; }
    void setActive(bool active) {_active = active;}
protected:
    void advance(int phase);

signals:

public slots:

private:
    bool _active;
    qreal _radius;

};

#endif // PLANET_H
