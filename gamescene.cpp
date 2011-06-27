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

    setSceneRect(0,0,800,480);
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
    // TODO: Delete before generate.
    // Generate particles
    particles.clear();
    for(int i = 0; i<level*1000; i++) {
        Particle* particle = new Particle(i);
        addItem(particle); // always add items before adjusting position (because they need a gameScene)
        particle->setPosition(0, 0.25 + random() * 0.01);
        particle->setVelocity(0.1 + random() * 0.02, 0.02 + random() * 0.02);
        particles.append(particle);
    }
    Planet* planet = new Planet(0.03);
    addItem(planet);
    _planets.append(planet);
    planet->setPosition(0.8,0.25);

    currentParticleNumber = 0;
}

void GameScene::resized() {
    qDebug() << "Resized!";

    foreach(Particle* particle, particles) {
        particle->resized();
    }
    foreach(Planet* planet, planets()) {
        planet->resized();
    }
}

/*!
 Random function. Returns a random number between 0 and 1. Not seeded.
*/
qreal GameScene::random()
{
    return (qreal)rand()/(qreal)RAND_MAX;
}

qreal GameScene::toRel(qreal val, RelativeModes widthOrHeight)
{
    if(widthOrHeight == RelativeToHeight) {
        return val / height();
    } else {
        return val / width();
    }
}

QVector2D GameScene::toRel(QVector2D val, RelativeModes widthOrHeight)
{
    if(widthOrHeight == RelativeToHeight) {
        return val / height();
    } else {
        return val / width();
    }
}

qreal GameScene::fromRel(qreal val, RelativeModes widthOrHeight)
{
    if(widthOrHeight == RelativeToHeight) {
        return val * height();
    } else {
        return val * width();
    }
}

QVector2D GameScene::fromRel(QVector2D val, RelativeModes widthOrHeight)
{
    if(widthOrHeight == RelativeToHeight) {
        return val * height();
    } else {
        return val * width();
    }
}
