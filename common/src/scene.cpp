#include "scene.h"
#include<QGraphicsPixmapItem>
#include <QPainter>
#include <QGraphicsView>
#include<QDebug>


/*!
 * \brief Scene::Scene
 * \param parent
 * Note that QGraphicsScene has no visual appearance of its own;
 */
Scene::Scene(QObject *parent) : QGraphicsScene(parent)
{
}


Scene::Scene(const QString &world, AssetsManagerPtr assets, QObject *parent) :
    QGraphicsScene(assets->grid_rect(),parent),
    m_assets(assets),
    m_rows(assets->rows()),
    m_columns(assets->columns()),
    m_tile_size(assets->cell_size()),
    m_map(assets->graphical_map()),
    m_show_grid(false),
    m_bkg_brush(QBrush(QColor(0,0x80,0))),
    m_animating(false),
    m_world(world)
{
    create_bk_image(assets->zones()[0]);
    create_grid(assets->zones()[0]);
    setBackgroundBrush(m_bkg_brush);
}

/*!
 * \brief Scene::add_actor
 * \param a
 */
void Scene::add_actor(ActorPtr a)
{
    addItem(a->sprite());
    connect(a,SIGNAL(sprite_moved(const QPointF&)),this,SLOT(sprite_move(const QPointF&)));
    connect(a,SIGNAL(current_sprite(const Actor*)),this,SLOT(offer_sprite(const Actor*)));
}

void Scene::create_bk_image(const QString &zone)
{
    m_assets->load(zone);
    m_rows = m_assets->rows();
    m_columns = m_assets->columns();
    m_tile_size = m_assets->cell_size();
    QPixmap src = *(m_assets->tile_map_image());
    TileMapContainer map = m_assets->graphical_map();
    m_bkg_img = Image(QSize(m_columns*m_tile_size,m_rows*m_tile_size),Image::Format_RGB32);
    TileRectContainer destination_tiles;
    for(int row=0;row<m_rows;row++)
        for(int col=0;col<m_columns;col++)
        {
            QRectF t = QRectF(QPointF(col*m_tile_size,row*m_tile_size),QSize(m_tile_size,m_tile_size));
            destination_tiles.push_back(t);
        }
    TileRectContainer src_map;
    for(int row=0;row<src.height()/m_tile_size;row++)
        for(int col=0;col<src.width()/m_tile_size;col++)
            src_map.push_back(QRectF(QPointF(col*m_tile_size,row*m_tile_size),QSize(m_tile_size,m_tile_size)));
    QPainter p(&m_bkg_img);
    p.fillRect(sceneRect(),Qt::white);
    Q_ASSERT(src_map.size() != 0);
    for(int i=0;i<destination_tiles.size();i++)
    {
        p.drawPixmap(destination_tiles.at(i),src,src_map.at(map.at(i)));
    }
}

void Scene::create_grid(const QString &zone)
{
    Q_UNUSED(zone)

    QPainterPath path;
    m_grid_img = Image(QSize(m_columns*m_tile_size,m_rows*m_tile_size),Image::Format_RGB32);
    QPainter painter(&m_grid_img);
    painter.drawImage(QPointF(0,0),m_bkg_img,QRectF(m_grid_img.rect()));
    for(int column = 0 ; column <= m_columns; column++)
    {
        path.moveTo(QPointF(m_tile_size *column,0));
        path.lineTo(QPointF(m_tile_size * column,m_rows * m_tile_size));
    }
    for(int row = 0 ; row <= m_rows; row++)
    {
        path.moveTo(QPointF(0,row*m_tile_size));
        path.lineTo(QPointF(m_tile_size * m_columns,row * m_tile_size));
    }
    painter.setPen(QPen(Qt::black,0.5,Qt::SolidLine));
    painter.drawPath(path);
}
/*!
 * \brief Scene::set_background
 * \param filename
 */
void Scene::set_background(QString filename)
{
    auto e = addPixmap(QPixmap(filename));
    setSceneRect(-e->pixmap().width()/2,-e->pixmap().height()/2,e->pixmap().width(),e->pixmap().height());
    e->setPos(sceneRect().topLeft());
    e->setZValue(-999);
}



/*!
 * \brief Scene::set_background
 * \param color
 */
void Scene::set_background(QColor color)
{
    setBackgroundBrush(QBrush(color));
}

/*!
 * \brief Scene::map
 * \param m_map
 */
void Scene::set_tile_map(TileMapContainer map)
{
    m_map =  map;
}

/*!
 * \brief Scene::map
 * \return
 */
TileMapContainer Scene::get_tile_map() const
{
    return m_map;
}

/*!
 * \brief Scene::show_grid
 * \param toggle
 */
void Scene::show_grid(bool toggle)
{
    m_show_grid = toggle;
    update_background();
}

bool Scene::animating() const
{
   return m_animating;
}

void Scene::animating(bool a)
{
    m_animating = a;
}


void Scene::reposition_players(const QPointF &p)
{
  emit move_player(p);
}

/*!
 * \brief Scene::signal_moved
 * \param a
 *
 * wire the Actor to the move_player signal
 */
void Scene::connect_teleport(ActorPtr a)
{
    connect(this,SIGNAL(move_player(const QPointF&)),a,SLOT(set_pos(const QPointF&)));
}

/*!
 * \brief Scene::scene_change
 */
void Scene::scene_change(const QString &zone)
{
    create_bk_image(zone);
    create_grid(zone);
    emit scene_changed(zone);
    update_background();
}

/*!
 * \brief Scene::mouseMoveEvent
 * \param mouseEvent
 */
void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mouseMoveEvent(mouseEvent);
    emit mouse_pos(mouseEvent->scenePos());
}

/*!
 * \brief Scene::sprite_move
 * \param pos
 */
void Scene::sprite_move(const QPointF &pos)
{
    emit sprite_pos(pos);
}

/*!
 * \brief Scene::offer_sprite
 * \param a
 */
void Scene::offer_sprite(const Actor *a)
{
    emit current_sprite(a);
}

/*!
 * \brief Scene::update_background
 */
void Scene::update_background()
{
    int margin = static_cast<int>(sceneRect().width()*0.1);
    update(sceneRect()+QMargins(margin,margin,margin,margin));
}


/*!
 * \brief Scene::drawBackground
 * \param painter
 * \param rect
 *
 * Draws the scene background using the background image built on the last
 * resize
 */
void Scene::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->fillRect(rect,m_bkg_brush);
    if(!m_show_grid)
    {
       painter->drawImage(QPointF(0,0),m_bkg_img,sceneRect());
    }
    else
    {
        painter->drawImage(QPointF(0,0),m_grid_img,sceneRect());
#if 1
        painter->setPen(QPen(Qt::yellow));
        int count=0;
        QFont font =QFont("Arial",4);
        painter->setFont(font);
        for(int row = 0;row<m_rows;row++)
            for(int col=0;col<m_columns;col++)
            {
                painter->drawText(QPointF(col*m_tile_size+5,row*m_tile_size+5),QString("%1").arg(count));
                painter->drawText(QPointF(col*m_tile_size+5,row*m_tile_size+10),QString("%1").arg(m_map.at(count)));
                count +=1;
            }
#endif
        /*
        */

      }
}

void Scene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    QGraphicsScene::dragMoveEvent(event);
    qDebug() << "Scene::dragMoveEvent"  << event->pos();
}
