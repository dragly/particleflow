#ifndef PARTICLE_H
#define PARTICLE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <QVector2D>

class GameScene;

class Particle : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit Particle(int number);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    bool active() {return _active; }
    void setActive(bool active) {_active = active;}
    GameScene *gameScene();

    QVector2D velocity() {return _velocity; }
    void setVelocity(QVector2D velocity) { _velocity = velocity; }
protected:
    void advance(int phase);

signals:

public slots:

private:
    bool _active;
    int _number;
    QVector2D _velocity;

};

#endif // PARTICLE_H
