#include "sprite.h"
#include <QPainter>
#include<QDebug>
#include <QWidget>
/*!
 * data mapping data(key) and setData(key,value) is as follows:
 * 0 - type (PLAYER | NPC)
 * 1 - name
 * 2 - hit test (boolean) whether there is a collision or not
 * 3 - collidable (boolean) whether it is collidable or not
*/
const int CHARACTER_TYPE = 0;
const int CHARACTER_NAME = 1;
const int CHARACTER_HIT = 2;
const int CHARACTER_COLLIDABLE = 3;
/*!
 * \brief Sprite::Sprite
 * \param r
 * \param parent
 *
 * constructor for the sprite using the given rectangle
 */
Sprite::Sprite(const QRectF &r,QGraphicsItem *parent) :
    QObject(dynamic_cast<QObject*>(parent)), QGraphicsItem (parent),m_rect(r) { }

/*!
 * \brief Sprite::Sprite
 * \param width
 * \param height
 * \param parent
 *
 * constructor for a sprite with a defined height and width.
 */
Sprite::Sprite(int width, int height, AssetsManagerPtr assets, TileSetPtr tile_set, QGraphicsItem *parent) :
    Sprite::Sprite(QRectF(QPointF(0,0),QSize(width,height)),parent)
{
    m_assets = assets;
    m_tilemap = m_assets->tile_map_image();
    m_tile_set = tile_set;
    m_animating = true;
    m_hitshape = false;
    setObjectName("Sprite");
}

/*!
 * \brief Sprite::~Sprite
 */
Sprite::~Sprite()
{
}

/*!
 * \brief Sprite::boundingRect
 * \return
 */
QRectF Sprite::boundingRect() const
{
    return m_rect;
}

/*!
 * \brief Sprite::animator
 * \return
 */
AnimatorPtr Sprite::animator() const
{
    return m_animator;
}

/*!
 * \brief Sprite::animator
 * \param a
 */
void Sprite::animator(AnimatorPtr a)
{
    m_animator = a;
}

void Sprite::update_animation()
{
    m_animator->animate();
}

void Sprite::add_animation(const QString &name, const FramesContainer &f)
{
    m_anim_map.insert(name,f);

}

void Sprite::changeFrameSet(const QString &frame_set, const QString &mode, int delay, int frame_index)
{

    if(frame_index < m_anim_map.size())
        m_animator->changeFrameSet(m_anim_map[frame_set], mode,delay,frame_index);
    m_current_animation = frame_set;
}

/*!
 * \brief Sprite::animating
 * \return
 */
bool Sprite::animating() const
{
   return m_animating;
}

/*!
 * \brief Sprite::animating
 * \param a
 */
void Sprite::animating(bool a)
{
  m_animating = a;
}

QRectF Sprite::rect() const
{
    return m_rect;
}

/*!
 * \brief Sprite::character_type
 * \param t
 */
void Sprite::character_type(int t)
{
   m_type = t;
}

/*!
 * \brief Sprite::character_type
 * \return
 */
int Sprite::character_type() const
{
    return m_type;
}

/*!
 * \brief Sprite::current_animation
 * \return
 */
QString Sprite::current_animation() const
{
  return m_current_animation;
}

/*!
 * \brief Sprite::hitshape
 * \return
 */
bool Sprite::hitshape() const
{
  return m_hitshape;
}

/*!
 * \brief Sprite::hitshape
 * \param hs
 */
void Sprite::hitshape(bool hs)
{
  m_hitshape = hs;
}

/*!
 * \brief Sprite::assets
 * \return
 */
AssetsManagerPtr Sprite::assets() const
{
  return m_assets;
}

/*!
 * \brief Sprite::tilemap
 * \return
 */
PixmapPtr Sprite::tilemap() const
{
  return m_tilemap;
}

/*!
 * \brief Sprite::current_frame_rect
 * \return
 */
QRectF Sprite::current_frame_rect() const
{
  return m_animator->current_frame_rect(m_tile_set);
}

void Sprite::default_render(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->drawPixmap(rect(),*(tilemap()),current_frame_rect());
}

/*!
 * \brief Sprite::current_animation
 * \param ca
 */
void Sprite::current_animation(const QString &ca)
{
    changeFrameSet(ca,"pause");
}

/*!
 * \brief Sprite::paint
 * \param painter
 * \param option
 * \param widget
 */
void Sprite::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
      if(m_hitshape)
      {
              painter->setBrush(QBrush(Qt::transparent));
              painter->setPen(QPen(Qt::black,0.5));
              painter->drawRect(m_rect);
      }
      emit signal_render(painter,option,widget);
      if(!m_animating)
      {
          painter->setBrush(QBrush(Qt::blue));
          painter->setPen(Qt::transparent);
          painter->drawRect(m_rect);
          painter->setPen(Qt::yellow);
          painter->setFont(QFont ("Helvetica [Cronyx]", 4));
          painter->drawText(QPointF(6,0),QString("(%1,%2)").arg(x(),0,'f',0).arg(y(),0,'f',0));
        }
}

/*!
 * \brief Sprite::mousePressEvent
 * \param evt
 */
void Sprite::mousePressEvent(QGraphicsSceneMouseEvent *evt)
{
  QGraphicsItem::mousePressEvent(evt);
  setCursor(Qt::ClosedHandCursor);
}

/*!
 * \brief Sprite::mouseMoveEvent
 * \param evt
 */
void Sprite::mouseMoveEvent(QGraphicsSceneMouseEvent *evt)
{
   QGraphicsItem::mouseMoveEvent(evt);
   emit signal_moving(this->scenePos());
}

/*!
 * \brief Sprite::mouseReleaseEvent
 * \param evt
 */
void Sprite::mouseReleaseEvent(QGraphicsSceneMouseEvent *evt)
{
  QGraphicsItem::mouseReleaseEvent(evt);
  setCursor(Qt::OpenHandCursor);
  emit signal_moved(this->scenePos());
}

void Sprite::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    QGraphicsItem::dragMoveEvent(event);
    qDebug() << "Sprite::dragMoveEvent" << event->pos();
}

/*!
 * \brief Sprite::set_type
 * \param type
 * set the datamap with the sprite type currently it is PLAYER=1 and NPC = 2
 */
void Sprite::set_type(int type)
{
  setData(CHARACTER_TYPE,type);
}

/*!
 * \brief Sprite::get_type
 */
int Sprite::get_type() const
{
    return data(CHARACTER_TYPE).toInt();
}

/*!
 * \brief Sprite::set_hit
 * \param hit
 *
 * set the data map with whether the sprite has collided with another object
 */
void Sprite::set_hit(bool hit)
{
  setData(CHARACTER_HIT,hit);
}

/*!
 * \brief Sprite::collidable
 * \param c
 */
void Sprite::collidable(bool c)
{
  setData(CHARACTER_COLLIDABLE,c);
}

bool Sprite::collidable() const
{
  return data(CHARACTER_COLLIDABLE).toBool();
}

/*!
 * \brief Sprite::name
 * \return
 *
 * set the data map with the name of the sprite
 */
QString Sprite::name() const
{
  return data(CHARACTER_NAME).toString();
}

/*!
 * \brief Sprite::connect_sprite_moving
 * \param obj
 */
void Sprite::connect_sprite_moving(QObject *obj)
{
    connect(this,SIGNAL(signal_moving(const QPointF &)),obj,SLOT(on_sprite_moving(const QPointF &)));
}

/*!
 * \brief Sprite::connect_sprite_moved
 * \param obj
 */
void Sprite::connect_sprite_moved(QObject *obj)
{
  connect(this,SIGNAL(signal_moved(const QPointF &)),obj,SLOT(on_sprite_moved(const QPointF &)));
}

bool Sprite::is_a(int t) const
{
    return get_type() == t;
}
