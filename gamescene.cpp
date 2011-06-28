#include "gamescene.h"

#include <QDebug>
#include <QtDeclarative/QDeclarativeEngine>
#include <QtDeclarative/QDeclarativeComponent>
#ifdef Q_WS_MAEMO_5
#include <QtDBus/QtDBus>
#endif

static qreal particlesPerSecond = 100;

GameScene::GameScene(QObject *parent) :
    QGraphicsScene(parent),
    currentParticleNumber(0),
    _dt(0),
    firstStep(true),
    particlesToAdd(0)
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
    particlesToAdd += _dt * particlesPerSecond;

    // Activate the next not yet active particle
    if(currentParticleNumber < level()*100000 ) {
        int particlesToAddNow = (int)particlesToAdd; // how many particles (integer number) to add this frame
        for(int i = 0; i < particlesToAddNow; i++) {
            Particle* particle = new Particle();
            _particles.append(particle);
            addItem(particle); // always add items before adjusting position (because they need a gameScene)
            particle->setActive(true);
            QVector2D particlePosition = generatorPosition;
            particlePosition.setY(particlePosition.y() + random()*0.001);
            particle->setPosition(particlePosition);
            QVector2D particleVelocity = generatorVelocityDirection * generatorVelocityMagnitude;
            particleVelocity.setX(particleVelocity.x() + random()*0.001);
            particleVelocity.setY(particleVelocity.y() + random()*0.001);
            particle->setVelocity(particleVelocity);
            currentParticleNumber++; // Increase the global counter
            particlesToAdd--; // For each added particle, remove one from the queue
        }
    }
    QGraphicsScene::advance();
}

void GameScene::removeParticle(Particle *particle)
{
    _particles.removeAll(particle);
    removeItem(particle);
    delete particle;
}

void GameScene::startLevel(int level) {
    _level = level;
    // TODO: Delete before generate.
    // Clear all particles
    _particles.clear();
    // Particles are now generated in the advance function (and should be deleted when they are too far away)

    // Particle generator
    generatorPosition = QVector2D(0,0.25);
    generatorVelocityDirection = QVector2D(1.0,0.0).normalized();
    generatorVelocityMagnitude = 0.1;

    // Planets
    Planet* planet = new Planet(0.02, 0.8);
    addItem(planet);
    _planets.append(planet);
    planet->setPosition(0.8,0.25);
    Planet* planet2 = new Planet(0.015, 0.7);
    addItem(planet2);
    _planets.append(planet2);
    planet2->setPosition(0.4,0.1);
    Planet* planet3 = new Planet(0.015, 0.6);
    addItem(planet3);
    _planets.append(planet3);
    planet3->setPosition(0.2,0.5);
    Planet* planet4 = new Planet(0.015, 0.4);
    addItem(planet4);
    _planets.append(planet4);
    planet4->setPosition(0.4,0.3);

    currentParticleNumber = 0;
}

void GameScene::resized() {
    qDebug() << "Resized!";

    foreach(Particle* particle, _particles) {
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

void GameScene::aimGenerator(QPointF scenePosition)
{
    QVector2D mousePosition = QVector2D(toRel(scenePosition.x()), toRel(scenePosition.y()));
    generatorVelocityDirection = (mousePosition - generatorPosition).normalized();
}

void GameScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    aimGenerator(event->scenePos());
}

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    aimGenerator(event->scenePos());
}


