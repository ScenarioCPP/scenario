#ifndef PCHARACTER_H
#define PCHARACTER_H
#include "icharacter.h"
#include "actor.h"
#include "collider.h"
#include "controller.h"

class PCharacter : public Actor
{
  Q_OBJECT

  ColliderPtr m_collider;
  ControllerPtr m_controller;

public:
  PCharacter(SpritePtr sprite,ColliderPtr collider,ControllerPtr controller,QObject *parent=nullptr);
  virtual void act(qint64 t);
  virtual void render(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget);
  void collide_objects();
public slots:
  virtual void on_key_down_up(QKeyEvent *e);
};


#endif // PCHARACTER_H
