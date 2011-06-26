#include "gamescene.h"

#include <QDebug>
#include <QtDeclarative/QDeclarativeEngine>
#include <QtDeclarative/QDeclarativeComponent>
#ifdef Q_WS_MAEMO_5
#include <QtDBus/QtDBus>
#endif

GameScene::GameScene(QObject *parent) :
    QGraphicsScene(parent), currentParticleNumber(0), _dt(0), firstStep(true    )
{
    currentParticleNumber = 0;
    startLevel(1);
    time.start();
    connect(&advanceTimer, SIGNAL(timeout()), SLOT(advance()));
    advanceTimer.start(1);
}

void GameScene::advance() {
    currentTime = time.elapsed();
    if(firstStep) {
        _dt = 0;
        firstStep = false;
    } else {
        _dt = (currentTime - lastFrameTime) / 1000.0;
    }
    lastFrameTime = currentTime;

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
        Particle* particle = new Particle(i);
        particle->setX((qreal)rand()/(qreal)RAND_MAX * 25);
        particle->setY(50 + (qreal)rand()/(qreal)RAND_MAX * 25);
        particles.append(particle);
        addItem(particle);
    }
    Planet* planet = new Planet(20, 300,50);
    _planets.append(planet);
    addItem(planet);

    currentParticleNumber = 0;
}

void GameScene::resized() {
    qDebug() << "Resized!";
}
