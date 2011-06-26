#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QTimer>
#include <QTime>

#include "particle.h"
#include "planet.h"

class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameScene(QObject *parent = 0);

    int level() {return _level; }
    void startLevel(int level);

    void resized();

    QList<Planet*> planets() {return _planets; }

    qreal dt() {return _dt; }

signals:

public slots:
    void advance();

private:
    QTimer advanceTimer;
    QList<Particle*> particles;
    QList<Planet*> _planets;
    int _level;
    int currentParticleNumber;
    qreal _dt;
    bool firstStep;
    int currentTime;
    int lastFrameTime;
    QTime time;
};

#endif // GAMESCENE_H
