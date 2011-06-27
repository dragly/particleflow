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
    qreal random();

    void resized();

    QList<Planet*> planets() {return _planets; }

    qreal dt() {return _dt; }

    enum RelativeMode {
        RelativeToWidth,
        RelativeToHeight
    };
    Q_DECLARE_FLAGS(RelativeModes, RelativeMode)

    qreal toRel(qreal val, RelativeModes widthOrHeight);
    qreal toRel(qreal val) { return toRel(val,RelativeToWidth); }
    QVector2D toRel(QVector2D val, RelativeModes widthOrHeight);
    QVector2D toRel(QVector2D val) { return toRel(val,RelativeToWidth); }
    qreal fromRel(qreal val, RelativeModes widthOrHeight);
    qreal fromRel(qreal val) { return fromRel(val,RelativeToWidth); }
    QVector2D fromRel(QVector2D val, RelativeModes widthOrHeight);
    QVector2D fromRel(QVector2D val) { return fromRel(val,RelativeToWidth); }

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

Q_DECLARE_OPERATORS_FOR_FLAGS(GameScene::RelativeModes)

#endif // GAMESCENE_H
