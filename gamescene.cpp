#include "gamescene.h"

#include <QDebug>
#include <QtDeclarative/QDeclarativeEngine>
#include <QtDeclarative/QDeclarativeComponent>
#ifdef Q_WS_MAEMO_5
#include <QtDBus/QtDBus>
#endif

GameScene::GameScene(QObject *parent) :
    QGraphicsScene(parent), currentParticleNumber(0)
{
    setSceneRect(-500, -500, 1000, 1000);

    startLevel(1);

    connect(&advanceTimer, SIGNAL(timeout()), SLOT(advance()));
    advanceTimer.start(1);
}

void GameScene::advance() {

    // Activate the next not yet active particle
    if(currentParticleNumber < particles.length()) {
        Particle* activateParticle = particles.at(currentParticleNumber);
        activateParticle->setActive(true);
        currentParticleNumber++;
    }
    QGraphicsScene::advance();
}

void GameScene::startLevel(int level) {
    // Generate particles
    particles.clear(); // should we delete all first? Or is this sufficient?
    for(int i = 0; i<level*1000; i++) {
        Particle* particle = new Particle();
        particles.append(particle);
        addItem(particle);
    }
    currentParticleNumber = 0;
}
