#ifndef PARTICLE_H
#define PARTICLE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <QVector2D>

#include "gameobject.h"

class Particle : public GameObject
{
    Q_OBJECT
public:
    explicit Particle(int number);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    bool active() {return _active; }

    void setActive(bool active) {_active = active;}

protected:
    void advance(int phase);

signals:

public slots:

private:
    bool _active;
    int _number;

};

#endif // PARTICLE_H
