#include <QtMath>
#include <QDebug>
#include "global_defines.h"
#include "pcharacter.h"


PCharacter::PCharacter(SpritePtr sprite, ColliderPtr collider, ControllerPtr controller, QObject *parent) :
  Actor(sprite,parent),m_collider(collider),m_controller(controller)
{
    signal_on_rendor(sprite);
    sprite->set_type(PLAYER);
}

void PCharacter::act(qint64 t)
{
    Q_UNUSED(t)

    /* Because animation is entirely dependent on the player's movement at this point,
      this is a separate just for the animation to be called after collision
      between the player and the world. This gives the most accurate animations for what
      the player is doing movement wise on the screen. */
      if (m_controller->btn_left()->active())  {
            move_left();
      }
      if (m_controller->btn_right()->active())  {
            move_right();
      }
      if (m_controller->btn_up()->active())  {
            jump();
            m_controller->btn_up()->active(false);
      }
      update_position(gravity(), friction());
      collide_objects();
      if (m_velocity_y < 0)
      {

          if (m_direction_x < 0) m_sprite->changeFrameSet("jump-left", "pause");
          else m_sprite->changeFrameSet("jump-right", "pause");

      }
      else if (m_direction_x < 0) {

          if (m_velocity_x < -0.1) m_sprite->changeFrameSet("move-left", "loop", 5);
          else m_sprite->changeFrameSet("idle-left", "pause");

      } else if (m_direction_x > 0) {

          if (m_velocity_x > 0.1) m_sprite->changeFrameSet("move-right", "loop", 5);
          else m_sprite->changeFrameSet("idle-right", "pause");

      }
      update_animation();

}

void PCharacter::render(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //painter->drawPixmap(rect(),*(tilemap()),current_frame_rect());
    default_render(painter,option,widget);
}

void PCharacter::collide_objects()
{
  /* Let's collide with some tiles!!! The side values refer to the tile grid
      row and column spaces that the object is occupying on each of its sides. For
      instance bottom refers to the row in the collision map that the bottom of the
      object occupies. Right refers to the column in the collision map occupied by
      the right side of the object. Value refers to the value of a collision tile in
      the map under the specified row and column occupied by the object. */
  double bottom, left, right, top, value;

  /* First we test the top left corner of the object. We get the row and column
      he occupies in the collision map, then we get the value from the collision map
      at that row and column. In this case the row is top and the column is left. Then
      we hand the information to the collider's collide function. */
  auto conf = assets();
  assert(conf != nullptr);
  auto collision_map = conf->collision_map();
  int cell_size = conf->cell_size();
  int columns = conf->columns();
  top    = floor(get_top() / cell_size);
  left   = floor(get_left()   / cell_size);
  if(top*columns+left>=0 && top*columns+left < collision_map.size())
  {
      value  = collision_map.at(static_cast<int>(top * columns + left));
      m_collider->collide(value, this, static_cast<int>(left * cell_size), static_cast<int>(top * cell_size), cell_size);
  }

  /* We must redefine top since the last collision check because the object may
      have moved since the last collision check. Also, the reason we check the top corners
      first is because if the object is moved down while checking the top, he will be
      moved back up when checking the bottom, and it is better to look like he is standing
      on the ground than being pushed down through the ground by the ceiling. */
  top    = floor(get_top() / cell_size);
  right   = floor(get_right()   / cell_size);
  if(top*columns+right >=0 && top*columns+right < collision_map.size())
  {
      value  = collision_map.at(static_cast<int>(top * columns + right));
      m_collider->collide(value, this, static_cast<int>(right * cell_size), static_cast<int>(top * cell_size), cell_size);
  }

  bottom    = floor(get_bottom() / cell_size);
  left   = floor(get_left()   / cell_size);
  if(bottom * columns+left >= 0 && bottom*columns+left < collision_map.size())
  {
      value  = collision_map.at(static_cast<int>(bottom * columns + left));
      m_collider->collide(value, this, static_cast<int>(left * cell_size), static_cast<int>(bottom * cell_size), cell_size);
  }

  bottom    = floor(get_bottom() / cell_size);
  right   = floor(get_right()   / cell_size);
  if(bottom*columns+right >=0 && bottom*columns+right < collision_map.size())
  {
      value  = collision_map.at(static_cast<int>(bottom * columns + right));
      m_collider->collide(value, this, static_cast<int>(right * cell_size), static_cast<int>(bottom * cell_size), cell_size);
  }

}

void PCharacter::on_key_down_up(QKeyEvent *e)
{
    m_controller->key_down_up(e);
}
