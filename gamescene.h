#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QTimer>

#include "particle.h"

class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit GameScene(QObject *parent = 0);

    int level() {return _level; }
    void startLevel(int level);

signals:

public slots:
    void advance();

private:
    QTimer advanceTimer;
    QList<Particle*> particles;
    int _level;
    int currentParticleNumber;
};

#endif // GAMESCENE_H
