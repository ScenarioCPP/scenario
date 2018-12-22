#include <QGraphicsSvgItem>
#include <QSvgRenderer>
#include <QDir>
#include <QFile>
#include <QtMath>
#include <QMediaPlayer>
#include <QMediaPlaylist>

#include "world.h"
#include "playerfactory.h"
#include "npcfactory.h"
#include "svgengine.h"
#include "sequentialguid.h"

#include <QDebug>


/*!
  \class World
  \brief World is the world that Actors live in.

  The World class represents a two-dimensional(currently) grid
  of cells. All Actor objects are associated with a World and can get access to the
  world object. The size of cells can be specified at world creation time, and
  is constant after creation. Simple scenarios may use large cells that entirely
  contain the representations of objects in a single cell. More elaborate
  scenarios may use smaller cells (down to single pixel size) to achieve
  fine-grained placement and smoother animation.

  The world background can be decorated with drawings or images.

  inspiration taken from from https://www.greenfoot.org/files/javadoc/

 */


/*!
 * \brief World::World  Construct a new world.
 * \param world_width
 * \param world_height
 * \param cell_size
 * \param bounded
 * \param parent
 * Construct a new world.
 * The size of the world (in number of cells) and the
 * size of each cell (in pixels) must be specified.
 * This constructor allows the option of creating an unbounded world,
 * which actors can move outside the boundaries of.
 */
    //m_game_engine->connect_update(this);  // wire the update signal to this world's on_update slot

World::World(GameEnginePtr ge,AssetsManagerPtr assets,ViewWidgetPtr display,QObject* parent):
    QObject(parent),
    m_display(display),
    m_game_engine(ge),
    m_assets(assets)
{

    if(! m_assets.isNull())  // Make sure that we have a valid assets pointer
      init_world();
    m_collider = new Collider(); // Here's the new collider class.
    m_mediaplayer = QPointer<QMediaPlayer>(new QMediaPlayer);
}

/*!
 * \brief World::game_engine
 * \param ge
 */
void World::game_engine(GameEnginePtr ge)
{
  m_game_engine = ge;
}

/*!
 * \brief World::view_widget
 * \param vw
 */
void World::view_widget(ViewWidgetPtr vw)
{
    m_display = vw;
    m_scene = m_display->scene();
}

/*!
 * \brief World::assets
 * \param assets
 */
void World::assets(AssetsManagerPtr assets)
{
    m_assets = assets;
    init_world();
}

void World::init_world()
{
    m_name = m_assets->world();
    m_width = m_assets->world_width();
    m_height = m_assets->world_height();
    m_rows = m_assets->rows();
    m_columns = m_assets->columns();
    m_cell_size = m_assets->cell_size();
    m_friction = m_assets->friction();
    m_gravity = m_assets->gravity();
    m_bounded = true;

}

/*!
 * \brief World::broadcast_score
 * \param name
 *
 * Specific application to games for Worlds
 */
void World::broadcast_score(const QString &name, int score)
{
  emit signal_score(name,score);
}

/*!
 * \brief World::zone
 * \return
 *
 * Current zone in the world
 */
QString World::zone() const
{
  return m_zone;
}

/*!
 * \brief World::music_play_list
 */
void World::music_play_list(Strings list)
{
    auto playlist = QPointer<QMediaPlaylist>(new QMediaPlaylist());
    for( auto s : list)
        playlist->addMedia(assets()->background_sound(s));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    m_mediaplayer->setPlaylist(playlist);
    m_mediaplayer->setVolume(40);
}





/*!
 * \brief World::load_scene
 * \param scene
 */
void World::load_scene(const QString &zone)
{
    //m_assets->load(p.destination_zone());
    //m_collision_map = m_assets->collision_map();
    //m_settings.insert("scene-title",m_assets->scene_title());
    //m_display->title(m_settings["scene-title"]);
    //add_portals(m_assets->portals());
    m_assets->load(zone);
    m_collision_map = m_assets->collision_map();
    m_zone = zone;
    m_scene->scene_change(zone);
    clear_portals();
    add_portals(m_assets->portals());
    // Setup the animation sets for player
    m_settings.insert("scene-title",m_assets->scene_title());
    m_display->title(m_settings["scene-title"]);
    m_display->update();
}

/*!
 * \brief World::on_update
 * \param timestamp
 */
void World::on_update(qint64 timestamp)
{
    portal_collision_check(timestamp);
    act(timestamp);  // call the subclassed act function
}

/*!
 * \brief World::portal_collision_check
 * \param timestamp
 */
void World::portal_collision_check(qint64 timestamp)
{
    Q_UNUSED(timestamp)

    for(auto player : m_players)
    {
        for(auto p : m_portals)
        {
            if(p->collide_object(player))
            {
                // this is where we go through the portal
                on_portal_entry(*p);
                player->set_pos(QPointF(p->destination_x(),p->destination_y()));
                break;
            }
        }
    }

}


/*!
 * \brief World::on_portal_entry
 * \param p
 */
void World::on_portal_entry(const Portal &p)
{
    stop_world();
    load_scene(p.destination_zone());
    start_world();
}

/*!
 * \brief World::add_object
 * \param object
 * \param x
 * \param y
 */
void World::add_player(ActorPtr actor, int x, int y)
{
    this->add_actor(actor,x,y);
    m_scene->connect_teleport(actor);  // wire the scene to alert actor to teleport
    m_display->connect_gravity_changed(actor);
    m_players.push_back(actor);
}


/*!
 * \brief World::add_actor
 * \param actor
 * \param x
 * \param y
 * \return
 */
World *World::add_actor(ActorPtr actor, int x, int y)
{
  m_scene->add_actor(actor);
  actor->set_pos(QPointF(x,y));
  actor->set_base(QPointF(x,y));
  actor->animate(true);
  actor->update();
  m_game_engine->connect_update(actor);
  return this;
}

/*!
 * \brief World::set_background
 * \param filename
 * Set a background image for the world from an image file.
 * Images of type 'jpeg', 'gif' and 'png' are supported.
 * If the image size is larger than the world in pixels, it is clipped.
 * A pattern showing the cells can easily be shown by setting a background
 * image with a size equal to the cell size.
 */
void World::set_background(CStr filename)
{
    m_scene->set_background(QString(filename));
}

/*!
 * \brief World::set_background
 * \param color
 */
void World::set_background(QColor color)
{
    m_scene->set_background(color);
}

/*!
 * \brief World::get_height
 * \return height
 *
 * Return the height of the world (in number of cells).
 */
int World::get_height() const
{
    return m_height;
}

/*!
 * \brief World::get_width
 * \return
 * Return the width of the world (in number of cells).
 */
int World::get_width() const
{
    return m_width;
}


/*!
 * \brief World::set_view
 * \param view
 */
void World::set_view(ViewPtr view)
{
    m_view = view;
}

/*!
 * \brief World::get_scene
 * \return
 */
ScenePtr World::get_scene()
{
    return m_scene;
}

/*!
 * \brief World::set_scene
 * \param scene
 */
void World::set_scene(ScenePtr scene)
{
    m_scene = scene;
}

/*!
 * \brief World::fill_scene
 * \param file
 */
void World::fill_scene(QString file)
{
    SvgEngine se(file);
    se.fill_scene(m_scene);
}

/*!
 * \brief World::start_game
 */
void World::start_game()
{
    m_game_engine->start();
}

/*!
 * \brief World::stop_game
 */
void World::stop_game()
{
  m_game_engine->stop();
}

/*!
 * \brief World::on_start_world
 */
void World::on_start_world()
{
   start_world();
}

/*!
 * \brief World::on_stop_world
 */
void World::on_stop_world()
{
  stop_world();
}

/*!
 * \brief World::on_start_stop
 */
void World::on_start_stop(bool value)
{
    if(value) start_world();
    else stop_world();
}

/*!
 * \brief World::start_world
 */
void World::start_world()
{
    start_game();
}

/*!
 * \brief World::stop_world
 */
void World::stop_world()
{
  stop_game();
}

/*!
 * \brief World::on_init
 *
 * Called first time world is initialized
 */
void World::on_init()
{
    setup();
}

/*!
 * \brief World::gravity
 * \param g
 */
void World::on_gravity(double g)
{
    m_gravity = g;
}

/*!
 * \brief World::friction
 * \param f
 */
void World::on_friction(double f)
{
   m_friction = f;
}

/*!
 * \brief World::x_increment
 * \param x
 */
void World::on_x_inc(double x)
{
   m_xinc = x;
}

/*!
 * \brief World::y_increment
 * \param y
 */
void World::on_y_inc(double y)
{
   m_yinc = y;
}



/*!
 * \brief World::show_grid
 * \param toggle
 */
void World::show_grid(bool toggle)
{
    m_scene->show_grid(toggle);
}

/*!
 * \brief World::settings_change
 * \param dm
 */
void World::settings_change(DataMap &dm)
{
    m_display->title(dm["scene-title"]);
    m_settings = dm;
}


/*!
 * \brief World::rows
 * \return
 */
int World::rows() const
{
    return m_rows;
}

/*!
 * \brief World::columns
 * \return
 */
int World::columns() const
{
    return m_columns;
}

/*!
 * \brief World::cell_size
 * \return
 */
int World::cell_size() const
{
    return m_cell_size;
}

/*!
 * \brief World::set_display
 * \param display
 */
void World::set_display(ViewWidgetPtr display)
{
    m_display = display;
}

/*!
 * \brief World::gravity
 * \return
 */
double World::on_gravity() const
{
    return m_gravity;
}

/*!
 * \brief World::friction
 * \return
 */
double World::on_friction() const
{
  return m_friction;
}

/*!
 * \brief World::is_npc
 * \param item
 * \return
 * predicate determines if the item is a non player character, this requires using the
 * data mapper for the QGraphicsItem
 */
bool World::is_npc(const QGraphicsItem *item) const
{
  return item->data(0).toInt() == NPC;
}

/*!
 * \brief World::is_player
 * \param item
 * \return
 * predicate determines if the item is a player character, this requires using the
 * data mapper for the QGraphicsItem
 */
bool World::is_player(const QGraphicsItem *item) const
{
  return item->data(0).toInt() == PLAYER;
}

/*!
 * \brief World::is_hit
 * \param item
 * \return
 */
bool World::is_hit(const QGraphicsItem *item) const
{
    return item->data(2).toBool();
}

/*!
 * \brief World::get_display
 * \return
 */
ViewWidgetPtr World::view()
{
    return m_display;
}



/*!
 * \brief World::settings
 * \return
 */
DataMap World::settings()
{
    return m_settings;
}

/*!
 * \brief World::settings
 */
void World::settings(const DataMap &dm)
{
    m_settings = dm;
}

/*!
 * \brief World::name
 * \return
 */
QString World::name() const
{
    return m_name;
}

/*!
 * \brief World::add_portals
 * \param portals
 */
void World::add_portals(const PortalContainer &portals)
{
    clear_portals();
    for(auto p : portals)
        m_portals.push_back(new Portal(p));

}

/*!
 * \brief World::clear_portals
 */
void World::clear_portals()
{
   m_portals.clear();
}

/*!
 * \brief World::signal_portal_entry
 * \param obj
 * \return
 */
World *World::signal_portal_entry(QObject *obj)
{
    connect(this,SIGNAL(portal_entry(const Portal&)),obj,SLOT(on_portal_entry(const Portal &)));
    return this;
}

/*!
 * \brief World::signal_key_down_up
 * \param obj
 * \return
 */
World *World::signal_key_down_up(QObject *obj)
{
    connect(this,SIGNAL(key_down_up(QKeyEvent *)),obj,SLOT(on_key_down_up(QKeyEvent *)));
    return this;
}


/*!
 * \brief World::music
 * \param state
 * \return
 */
World *World::music(bool state)
{
    if(state)
      m_mediaplayer->play();
    else
      m_mediaplayer->pause();
    return this;
}

/*!
 * \brief World::display
 * \return
 */
ViewWidgetPtr World::display() const
{
    return m_display;
}

/*!
 * \brief World::assets
 * \return
 */
AssetsManagerPtr World::assets() const
{
  return m_assets;
}

/*!
 * \brief World::remove
 * \param s
 * remove the sprite from the world
 */
void World::remove(SpritePtr s)
{
    m_scene->removeItem(s);
}

/*!
 * \brief World::music
 * \return
 */
bool World::music() const
{
  return m_mediaplayer->state() == QMediaPlayer::PlayingState;
}



/*!
 * \brief World::handleKeyEvent
 * \param e
 */
void World::on_key_event(QKeyEvent *e)
{
    emit key_down_up(e);
}

/*!
 * \brief World::handleResizeEvent
 * \param e
 */
void World::on_resize_event(QResizeEvent *e)
{
    double width = e->size().width();
    double swidth = get_scene()->sceneRect().width();
    qreal scale = abs(width/swidth - .005 * swidth);
    QMatrix matrix;
    matrix.scale(scale, scale);
    view()->view()->setMatrix(matrix);
}

void World::on_spawn_npc(double x, double y, const QString &type)
{
    auto npc = NPCFactory(m_assets).new_character(type);
    if(npc != nullptr)
    {
        this->add_actor(npc,static_cast<int>(x),static_cast<int>(y));
        npc->movable(true);
        m_game_engine->connect_update(npc);
    }
    else {
        qDebug() << type << "NPC is not implemented";
    }
}


void World::on_music(bool checked)
{
    music(checked);
}




/*!
 * \brief World::on_timer_change
 * \param t
 */
void World::on_timer_change(int t)
{
    if(t > 0)
      m_game_engine->time_step(t);
}

/*!
 * \brief World::on_change_root
 * \param root
 */
void World::on_change_root(const QString &root)
{
    m_assets->change_root(root);
}

/*!
 * \brief World::on_focus
 */
void World::on_focus()
{
    m_scene->setFocus();
}

/*!
 * \brief World::reposition_player
 * \param p
 */
void World::reposition_player(const QPointF &p)
{
    for(auto player:m_players)
    {
        player->x(p.x());
        player->y(p.y());
        player->update_position(m_gravity,m_friction);
    }
}
