#ifndef PARTICLE_H
#define PARTICLE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>

class Particle : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit Particle();

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

};

#endif // PARTICLE_H
