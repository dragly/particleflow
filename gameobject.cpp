#include "gameobject.h"
#include "gamescene.h"

GameObject::GameObject() :
    QGraphicsObject()
{
}


void GameObject::setPosition(QVector2D position) {
    _position = position;
    // set the position in pixel coordinates using the toRel function
    setPos(gameScene()->fromRel(_position).toPointF());
}

GameScene* GameObject::gameScene() {
    if(scene()) {
        return (GameScene*)scene();
    } else {
        qDebug() << "GameObject::gameScene(): Cannot return gameScene without scene. Have you used an object before adding it to the scene using addItem?";
        return 0;
    }
}

/*!
  This function is called whenever the scene is resized, so that the position is updated.
*/
void GameObject::resized()
{
    setPosition(position());
}
