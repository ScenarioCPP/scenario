#ifndef CARROT_H
#define CARROT_H
#include "npcharacter.h"
#include "animator.h"
#include "collider.h"
#include<QJsonObject>

class Carrot : public NPCharacter
{

  ColliderPtr m_collider;
  qint64  m_current_tick;
  int     m_count;
  int     m_delay;
  int     m_toggle;
  double  m_position_x;
  double  m_position_y;
  QJsonObject m_conf;

public:
  Carrot(SpritePtr sprite,QObject *parent=nullptr);
  virtual void render(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget);
  virtual void act(qint64 t);
};

#endif // CARROT_H
