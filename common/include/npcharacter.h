#ifndef NPCHARACTER_H
#define NPCHARACTER_H
#include "actor.h"
#include "animator.h"
#include "collider.h"
#include<QJsonObject>

class NPCharacter : public Actor
{

  ColliderPtr m_collider;
  QJsonObject m_conf;

public:
  NPCharacter(SpritePtr sprite,QObject *parent=nullptr);
  virtual void render(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget)=0;
  virtual void act(qint64 t) = 0;
};

#endif // NPCHARACTER_H
