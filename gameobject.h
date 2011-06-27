#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QGraphicsItem>
#include <QVector2D>

class GameScene;

class GameObject : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit GameObject();

    QVector2D velocity() {return _velocity; }
    void setVelocity(qreal x, qreal y) { setVelocity(QVector2D(x,y)); }
    void setVelocity(QVector2D velocity) { _velocity = velocity; }

    QVector2D position() {return _position; }
    void setPosition(qreal x, qreal y) { setPosition(QVector2D(x,y)); }
    void setPosition(QVector2D position);
    GameScene *gameScene();

signals:

public slots:
    void resized();

protected:
    QVector2D _velocity;
    QVector2D _position;

private:

};

#endif // GAMEOBJECT_H
