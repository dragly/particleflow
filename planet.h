#ifndef PLANET_H
#define PLANET_H

#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>

class Planet : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit Planet(qreal radius, qreal x, qreal y);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    qreal radius() { return _radius; }

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
