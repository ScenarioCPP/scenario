#ifndef COLLIDER_H
#define COLLIDER_H

#include<QObject>
#include<QPointer>

#include "actor.h"

class Collider : public QObject
{
    Q_OBJECT

public:

    Collider(QObject *parent=nullptr);
    void collide(int value, Actor *actor, int tile_x, int tile_y, int tile_size);
    bool collide_bottom(Actor *actor, int tile_bottom);
    bool collide_left(Actor *actor, int tile_left);
    bool collide_right(Actor *actor, int tile_right);
    bool collide_top(Actor *actor, int tile_top);

signals:

public slots:

};

typedef QPointer<Collider> ColliderPtr;

#endif // COLLIDER_H
