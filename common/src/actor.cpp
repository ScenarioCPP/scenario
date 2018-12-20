#include "global_defines.h"
#include "actor.h"
#include<QDebug>

/*!
 * \brief Actor::Actor
 * \param parent
 *
 * Base constructor
 */
Actor::Actor(QObject *parent) : QObject(parent)
{
  m_jump_height = JUMP_INC;
  m_v_inc = V_INC;
  m_x = m_x_old = 0;
  m_y = m_y_old = 0;
  m_velocity_x = 0;
  m_velocity_y = 0;
  m_direction_x = -1;
  m_jumping    = true;
}

/*!
 * \brief Actor::Actor
 * \param sprite
 *
 */
Actor::Actor(SpritePtr sprite,QObject *parent) : Actor(parent)
{
    assert(sprite != nullptr);
    m_sprite = sprite;
    m_x = 0;
    m_y = 0;
    m_sprite->animator(new Animator());
    m_height = static_cast<int>(m_sprite->boundingRect().height());
    m_width = static_cast<int>(m_sprite->boundingRect().width());
    m_animate = false;
    m_sprite->connect_sprite_moved(this);
}


/*!
 * \brief Actor::Actor
 * \param width
 * \param height
 * \param assets
 * \param tile_set
 */
Actor::Actor(int width, int height,
             AssetsManagerPtr assets,
             TileSetPtr tile_set,QObject *parent) : Actor(parent)
{
    m_assets = assets;
    m_sprite = new Sprite(width,height,m_assets,tile_set);
    assert(m_sprite != nullptr);
    m_sprite->animator(new Animator());
    m_width = width;
    m_height = height;
}

/*!
 * \brief Actor::sprite
 * \return
 */
SpritePtr Actor::sprite() const
{
  assert(m_sprite != nullptr);
  return m_sprite;
}

/*!
 * \brief Actor::movable
 * \param m
 * \return Actor* self
 */
Actor *Actor::movable(bool m)
{
    sprite()->setFlag(QGraphicsItem::ItemIsMovable,m);
    return this;
}


/*!
 * \brief Actor::movable
 * \return
 */
bool Actor::movable() const
{
    assert(m_sprite != nullptr);
    return (m_sprite->flags() & QGraphicsItem::ItemIsMovable);
}

/*!
 * \brief Actor::selectable
 * \param s
 */
Actor* Actor::selectable(bool s)
{
    assert(m_sprite != nullptr);
    m_sprite->setFlag(QGraphicsItem::ItemIsSelectable,s);
    return this;
}

/*!
 * \brief Actor::selectable
 * \return
 */
bool Actor::selectable() const
{
  assert(m_sprite != nullptr);
  return (m_sprite->flags() & QGraphicsItem::ItemIsSelectable);
}

/*!
 * \brief Actor::hitshape
 * \return
 */
bool Actor::hitshape() const
{
  assert(m_sprite != nullptr);
  return m_sprite->hitshape();
}

/*!
 * \brief Actor::hitshape
 * \param hs
 * \return
 */
Actor *Actor::hitshape(bool hs)
{
    assert(m_sprite != nullptr);
    m_sprite->hitshape(hs);
    return this;
}

/*!
 * \brief Actor::rect
 * \return
 */
QRectF Actor::rect() const
{
    assert(m_sprite != nullptr);
    return m_sprite->rect();
}

/*!
 * \brief Actor::current_frame_rect
 * \return
 */
QRectF Actor::current_frame_rect() const
{
    return sprite()->current_frame_rect();
}

/*!
 * \brief Actor::tilemap
 * \return
 *
 * accessor returns the sprite's tilemap for animation and rendering
 */
PixmapPtr Actor::tilemap() const
{
    return sprite()->tilemap();
}

/*!
 * \brief Actor::signal_on_rendor
 * \param obj
 *
 * call the slot when a render signal is given, the slot is usually the sprite's render method
 */
void Actor::signal_on_rendor(QObject *obj)
{
  connect(obj,SIGNAL(signal_render(QPainter*,const QStyleOptionGraphicsItem *, QWidget *)),
          this,SLOT(on_render(QPainter*,const QStyleOptionGraphicsItem *, QWidget *)));
}

void Actor::connect_on_collide(QObject *obj)
{
  connect(this,SIGNAL(signal_collision(Sprite *,QGraphicsItem *)),obj,SLOT(on_item_collision(Sprite*,QGraphicsItem*)));
}

/*!
 * \brief Actor::default_render
 * \param painter
 * \param option
 * \param widget
 * default render action if none is implemented
 */
void Actor::default_render(QPainter *painter,
                           const QStyleOptionGraphicsItem *option,
                           QWidget *widget)
{
    sprite()->default_render(painter,option,widget);
}


/*!
 * \brief Actor::sprite
 * \param sprite
 */
void Actor::sprite(SpritePtr sprite)
{
    m_sprite = sprite;
}

/*!
 * \brief Actor::color
 * \return
 */
QColor Actor::color() const
{
    return m_color;
}


/*!
 * \brief Actor::animator
 * \param m_animate
 */
void Actor::animator(AnimatorPtr animate)
{
    m_animator = animate;
}

/*!
 * \brief Actor::animator
 * \return
 */
AnimatorPtr Actor::animator() const
{
   return m_animator;
}

/*!
 * \brief Actor::add_animation
 * \param name
 * \param f
 */
void Actor::add_animation(const QString &name, FramesContainer f)
{
    m_sprite->add_animation(name,f);
}

/*!
 * \brief Actor::current_animation
 * \param anim
 */
void Actor::current_animation(const QString &anim)
{
    m_sprite->current_animation(anim);
}

/*!
 * \brief Actor::current_animation
 * \return
 */
QString Actor::current_animation() const
{
  return m_sprite->current_animation();
}

/*!
 * \brief Actor::accept_drops
 * \param v
 */
void Actor::accept_drops(bool v)
{
  m_sprite->setAcceptDrops(v);
}

/*!
 * \brief Actor::accept_drops
 * \return
 */
bool Actor::accept_drops() const
{
  return m_sprite->acceptDrops();
}

bool Actor::check_collisions()
{
    if(sprite()->isVisible() && sprite()->collidingItems().size() > 0)
    {
        m_colliding_sprites.clear();
        for(auto item : sprite()->collidingItems()) {
            m_colliding_sprites.push_back(static_cast<Sprite*>(item));
            //emit signal_collision(sprite(),item);
        }
        return true;
    }
    return false;

}

/*!
 * \brief Actor::assets
 * \return
 */
AssetsManagerPtr Actor::assets() const
{
    return sprite()->assets();
}



/*!
 * \brief Actor::color
 * \param c
 */
void Actor::color(QColor c)
{
   m_color = c;
}

/*!
 * \brief Actor::height
 * \return
 */
int Actor::height() const
{
   return m_height;
}

/*!
 * \brief Actor::width
 * \return
 */
int Actor::width() const
{
   return m_width;
}

/*!
 * \brief Actor::height
 * \param h
 */
void Actor::height(int h)
{
   m_height = h;
}

/*!
 * \brief Actor::width
 * \param w
 */
void Actor::width(int w)
{
    m_width = w;
}

/*!
 * \brief Actor::direction_x
 * \return
 */
int Actor::direction_x() const
{
   return m_direction_x;
}

/*!
 * \brief Actor::direction_x
 * \param x
 */
void Actor::direction_x(int x)
{
  m_direction_x = x;
}

/*!
 * \brief Actor::face_right
 */
void Actor::face_right()
{
  direction_x( DIRECTION_RIGHT );
}

/*!
 * \brief Actor::face_left
 */
void Actor::face_left()
{
    direction_x(DIRECTION_LEFT);
}


/*!
 * \brief Actor::animate
 * \param a
 */
void Actor::animate(bool a)
{
    m_animate = a;
}

/*!
 * \brief Actor::velocity_x
 * \return
 */
double Actor::velocity_x()
{
    return m_velocity_x;
}

/*!
 * \brief Actor::velocity_y
 * \return
 */
double Actor::velocity_y()
{
    return m_velocity_y;
}

double Actor::velocity_max() const
{
   return m_velocity_max;
}

/*!
 * \brief Actor::velocity_x
 * \param x
 */
void Actor::velocity_x(double x)
{
    m_velocity_x = x;
}

/*!
 * \brief Actor::velocity_y
 * \param y
 */
void Actor::velocity_y(double y)
{
    m_velocity_y = y;
}

/*!
 * \brief Actor::velocity_max
 * \param max
 */
void Actor::velocity_max(double max)
{
   m_velocity_max = max;
}

/*!
 * \brief Actor::inc_velocity_x
 * \param x
 */
void Actor::inc_velocity_x(double x)
{
    m_velocity_x += x;
}

/*!
 * \brief Actor::inc_velocity_y
 * \param y
 */
void Actor::inc_velocity_y(double delta)
{
    m_velocity_y += delta;
}

/*!
 * \brief Actor::mul_velocity_x
 * \param x
 */
void Actor::mul_velocity_x(double x)
{
   m_velocity_x *= x;
}

/*!
 * \brief Actor::mul_velocity_y
 * \param y
 */
void Actor::mul_velocity_y(double y)
{
   m_velocity_y *= y;
}

/*!
 * \brief Actor::jumping
 * \return
 */
bool Actor::jumping()
{
    return m_jumping;
}

/*!
 * \brief Actor::jumping
 * \param j
 */
void Actor::jumping(bool j)
{
    m_jumping = j;
}

/*!
 * \brief Actor::set_jump_height
 */
void Actor::jump_height(double h)
{
  m_jump_height = h;
}

/*!
 * \brief Actor::gravity
 * \param g
 */
void Actor::gravity(double g)
{
  m_gravity = g;
}

/*!
 * \brief Actor::gravity
 * \return
 */
double Actor::gravity() const
{
  return m_gravity;
}

/*!
 * \brief Actor::friction
 * \param f
 */
void Actor::friction(double f)
{
  m_friction = f;
}

/*!
 * \brief Actor::friction
 * \return
 */
double Actor::friction() const
{
    return m_friction;
}

/*!
 * \brief Actor::velocity_inc
 * \param inc
 */
void Actor::velocity_inc(double inc)
{
   m_v_inc = inc;
}

/*!
 * \brief Actor::x
 * \return
 */
double Actor::x() const
{
    return m_x;
}

/*!
 * \brief Actor::set_x
 * \param x
 */
void Actor::x(double x)
{
    m_x = x;
}

/*!
 * \brief Actor::y
 * \return
 */
double Actor::y() const
{
    return m_y;
}

/*!
 * \brief Actor::set_y
 * \param y
 */
void Actor::y(double y)
{
  m_y = y;
}

/*!
 * \brief Actor::name
 * \return
 */
QString Actor::name() const
{
  return m_name;
}

/*!
 * \brief Actor::name
 * \param name
 */
void Actor::name(const QString name)
{
  m_name = name;
}

/*!
 * \brief Actor::set_pos
 * \param pos
 */
void Actor::set_pos(const QPointF &pos)
{
  m_x = pos.x();
  m_y = pos.y();
  update();
}

/*!
 * \brief Actor::set_pos
 * \param x
 * \param y
 */
void Actor::set_pos(double x, double y)
{
    set_pos(QPointF(x,y));
}

/*!
 * \brief Actor::on_update
 * \param t
 *
 * signal handler for updates from gameengine or World
 */
void Actor::on_update(qint64 t)
{
  act(t);
}

void Actor::on_sprite_moved(const QPointF &p)
{
    //qDebug() << "Actor::on_sprite_moved" << p;
    set_pos(p);
    base_x(p.x());
    base_y(p.y());
}

/*!
 * \brief Actor::on_render
 * \param painter
 * \param option
 * \param widget
 *
 * signal handler for render signals
 */
void Actor::on_render(QPainter *painter,
                      const QStyleOptionGraphicsItem *option,
                      QWidget *widget)
{
    // calls the implemented render function of the subclass
    // remember, this is an abstract class
  render(painter,option,widget);
}

/*!
 * \brief Actor::on_gravity
 * \param g
 *
 * change character's gravity
 */
void Actor::on_gravity(double g)
{
    m_gravity = g;
}

/*!
 * \brief Actor::jump
 */
void Actor::jump()
{
    if (!m_jumping)
    {
      play_jump_sound();
      m_jumping     = true;
      m_velocity_y -= m_jump_height;
    }
}

/*!
 * \brief Actor::move_left
 */
void Actor::move_left()
{
  m_direction_x = -1;
  m_velocity_x -= m_v_inc;

}

/*!
 * \brief Actor::move_right
 */
void Actor::move_right()
{
  m_direction_x = 1;
  m_velocity_x += m_v_inc;
}

/*!
 * \brief Actor::update
 */
void Actor::update()
{
    m_sprite->setPos(QPointF(m_x,m_y));
    m_x_old = m_x;
    m_y_old = m_y;
    m_x += m_velocity_x;
    m_y += m_velocity_y;
}

/*!
 * \brief Actor::update_position
 * \param gravity
 * \param friction
 */
void Actor::update_position(double gravity, double friction)
{
    /* This used to be the update function, but now it's a little bit better. It takes
      gravity and friction as parameters so the player class can decide what to do with
      them. */
        if(static_cast<int>(m_x) != static_cast<int>(m_x_old) || static_cast<int>(m_y) != static_cast<int>(m_y_old))
            emit current_sprite(this);
        m_sprite->setPos(QPointF(m_x,m_y));
        m_x_old = m_x;
        m_y_old = m_y;
        m_velocity_y += gravity;
        m_x += m_velocity_x;
        m_y += m_velocity_y;

        m_velocity_x *= friction;
        m_velocity_y *= friction;
}

/*!
 * \brief Actor::update_animation
 */
void Actor::update_animation()
{

      m_sprite->update_animation();
}

/*!
 * \brief Actor::getBottom
 * \return
 */
double Actor::get_bottom()
{
    return m_y + m_height;
}

/*!
 * \brief Actor::get_left
 * \return
 */
double Actor::get_left()
{
    return m_x;
}

/*!
 * \brief Actor::get_right
 * \return
 */
double Actor::get_right()
{
    return m_x + m_width;
}

/*!
 * \brief Actor::get_top
 * \return
 */
double Actor::get_top()
{
    return m_y;
}

/*!
 * \brief Actor::get_center_x
 * \return
 */
double Actor::get_center_x() const
{
    return m_x + m_width * 0.5;
}

/*!
 * \brief Actor::get_center_y
 * \return
 */
double Actor::get_center_y() const
{
    return m_y + m_height * 0.5;
}

/*!
 * \brief Actor::get_old_center_x
 * \return
 */
double Actor::get_old_center_x()
{
    return m_x_old + m_width  * 0.5;
}

/*!
 * \brief Actor::get_old_center_y
 * \return
 */
double Actor::get_old_center_y()
{
    return m_y_old + m_height  * 0.5;
}

/*!
 * \brief Actor::get_old_bottom
 * \return
 */
double Actor::get_old_bottom()
{
    return m_y_old + m_height;
}

/*!
 * \brief Actor::get_old_left
 * \return
 */
double Actor::get_old_left()
{
    return m_x_old;
}

/*!
 * \brief Actor::get_old_right
 * \return
 */
double Actor::get_old_right()
{
    return m_x_old + m_width;
}

/*!
 * \brief Actor::get_old_top
 * \return
 */
double Actor::get_old_top()
{
    return m_y_old;
}

/*!
 * \brief Actor::set_bottom
 * \param y
 */
void Actor::set_bottom(double y)
{
    m_y  = y - m_height;

}

/*!
 * \brief Actor::set_left
 * \param x
 */
void Actor::set_left(double x)
{
    m_x = x;
}

/*!
 * \brief Actor::set_right
 * \param x
 */
void Actor::set_right(double x)
{
    m_x = x - m_width;

}

/*!
 * \brief Actor::set_top
 * \param y
 */
void Actor::set_top(double y)
{
    m_y = y;
}

/*!
 * \brief Actor::set_center_x
 * \param x
 */
void Actor::set_center_x(double x)
{
    m_x = x - m_width  * 0.5;
}

/*!
 * \brief Actor::set_center_y
 * \param x
 */
void Actor::set_center_y(double y)
{
    m_y = y - m_height  * 0.5;
}

/*!
 * \brief Actor::set_old_center_x
 * \param x
 */
void Actor::set_old_center_x(double x)
{
    m_x_old = x - m_width  * 0.5;
}

/*!
 * \brief Actor::set_old_center_y
 * \param y
 */
void Actor::set_old_center_y(double y)
{
    m_y_old = y - m_height  * 0.5;
}

/*!
 * \brief Actor::set_old_bottom
 * \param y
 */
void Actor::set_old_bottom(double y)
{
    m_y_old = y - m_height;
}

/*!
 * \brief Actor::set_old_left
 * \param x
 */
void Actor::set_old_left(double x)
{
    m_x_old = x;
}

/*!
 * \brief Actor::set_old_right
 * \param x
 */
void Actor::set_old_right(double x)
{
    m_x_old = x = m_width;
}

/*!
 * \brief Actor::set_old_top
 * \param y
 */
void Actor::set_old_top(double y)
{
  m_y_old = y;
}

/*!
 * \brief Actor::set_base
 * \param p
 */
void Actor::set_base(const QPointF p)
{
    m_base_x = p.x();
    m_base_y = p.y();
}


/*!
 * \brief Actor::base_x
 * \param x
 */
void Actor::base_x(double x)
{
    m_base_x = x;
}

/*!
 * \brief Actor::base_y
 * \param y
 */
void Actor::base_y(double y)
{
    m_base_y = y;
}

/*!
 * \brief Actor::tooltip
 * \param tool_tip
 */
void Actor::tooltip(const QString &tool_tip)
{
   assert(sprite() != nullptr);
   sprite()->setToolTip(tool_tip);
}


/*!
 * \brief Actor::sprite
 * \param sprite
 */
QString Actor::getJump_sound() const
{
  return m_jump_sound;
}

/*!
 * \brief Actor::setJump_sound
 * \param jump_sound
 */
void Actor::setJump_sound(const QString &jump_sound)
{
  m_jump_sound = jump_sound;
}

/*!
 * \brief Actor::play_jump_sound
 */
void Actor::play_jump_sound()
{
      if(m_mplayer != nullptr)
      {
          m_mplayer->setMedia(QUrl((m_jump_sound.isEmpty()) ? assets()->jump_sound(DEFAULT_JUMP_SOUND) : assets()->jump_sound(m_jump_sound)));
          m_mplayer->setVolume(40);
          m_mplayer->play();
      }
      else {
          qWarning("actor.cpp Actor::play_jump_sound() media player is not initialized");
      }
}

/*!
 * \brief Actor::colliding_sprites
 * \return
 */
CollidingList Actor::colliding_sprites() const
{
  return m_colliding_sprites;
}

/*!
 * \brief Actor::set_type
 * \param t
 */
void Actor::set_type(int t)
{
  sprite()->set_type(t);  // sets the sprite type
}

/*!
 * \brief Actor::get_type
 * \param t
 * \return
 */
int Actor::get_type() const
{
  return sprite()->get_type();
}

void Actor::has_sound(bool mp)
{
  if(mp)
    m_mplayer = new QMediaPlayer(); // does everyone need their own voice?
}
