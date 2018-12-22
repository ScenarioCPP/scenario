#include "scenario.h"
#include "scene.h"
#include "assetsmanager.h"
#include "viewwidget.h"
#include "view.h"


/*!
 * \brief Scenario::Scenario
 * \param parent
 *
 * Scenario's manage worlds and the object interaction in the world
 *
 *
 */
Scenario::Scenario(QObject *parent) : QObject(parent),m_auto_start(true) {  }

/*!
 * \brief Scenario::name
 * \param name
 */
void Scenario::scenario_name(const QString &name)
{
  m_name = name;
}

/*!
 * \brief Scenario::name
 * \return
 */
QString Scenario::scenario_name() const
{
    return m_name;
}

/*!
 * \brief Scenario::auto_start
 * \param as
 */
void Scenario::loop_start(bool as)
{
  m_auto_start = as;
}

/*!
 * \brief Scenario::auto_start
 * \return
 */
bool Scenario::loop_start() const
{
    return m_auto_start;
}

/*!
 * \brief Scenario::add_world
 * \param name
 * \param world
 *
 * adds a world to the Scenario's world map
 */
void Scenario::add_world(const QString &name, WorldPtr world)
{
  m_worlds.insert(name,world);
}

/*!
 * \brief Scenario::world
 * \param name
 * \return
 *
 * Get the main world
 */
WorldPtr Scenario::world(const QString &name ) const
{
  return m_worlds[name];
}

/*!
 * \brief Scenario::default_world
 * \param name
 */
void Scenario::main_world(const QString &name)
{
  m_default_world = name;
}

/*!
 * \brief Scenario::remove_from_world
 */
void Scenario::remove(SpritePtr s)
{
  this->world(m_default_world)->remove(s);
}

/*!
 * \brief Scenario::add_actor
 * \param a
 * \param t
 * \param world_name
 */
void Scenario::add_actor(const QString &world_name,ActorPtr a, Scenario::ActorType type)
{
    if(type == PLAYER)
   {
        this->world(world_name)->add_player(a,a->x(),a->y());
        a->connect_on_collide(view(world_name));

   }
  else
  {
        this->world(world_name)->add_actor(a,a->x(),a->y());
  }
}

/*!
 * \brief create_world
 * \param name
 * \param world
 *
 * adds this world to the given scenario
 */
void Scenario::install(WorldPtr world)
{
  add_world(world);
  main_world(scenario_name());
}

/*!
 * \brief Scenario::default_world
 * \return
 */
QString Scenario::main_world() const
{
  return m_default_world;
}

/*!
 * \brief Scenario::world_zone
 * \param world_name
 * \return
 */
QString Scenario::world_zone(const QString &world_name) const
{
    return world(world_name)->zone();
}

/*!
 * \brief Scenario::last_time
 * \return
 */
qint64 Scenario::last_time() const
{
  return m_lasttimestamp;
}

qint64 Scenario::frame_rate() const
{
  return m_currenttimestamp - m_lasttimestamp;
}

/*!
 * \brief Scenario::connect_key_down_up
 * \param a
 */
void Scenario::connect_key_down_up(const QString &world_name,ActorPtr a)
{
    world(world_name)->signal_key_down_up(a);
}

/*!
 * \brief Scenario::assets
 * \return
 */
AssetsManagerPtr Scenario::assets(const QString &world_name) const
{
  return world(world_name)->assets();
}


/*!
 * \brief Scenario::music_play_list
 * \param world_name
 * \param list
 */
void Scenario::music_play_list(const QString &world_name, QVector<QString> list)
{
    world(world_name)->music_play_list(list);
}


/*!
 * \brief Scenario::play_pickup_sound
 * \param sound
 */
void Scenario::play_pickup_sound(const QString &sound)
{
    play_sound(QUrl(assets(m_name)->pickup_sound(sound)));
}

/*!
 * \brief Scenario::asset_root
 * \return
 */
QString Scenario::asset_root() const
{
  return m_asset_root;
}

/*!
 * \brief Scenario::asset_root
 * \param asset
 */
void Scenario::asset_root(const QString &asset)
{
  m_asset_root = asset;
}

QGraphicsItem *Scenario::add_graphics_item(QGraphicsItem *item)
{
   world(m_name)->get_scene()->addItem(item);
   return item;
}

/*!
 * \brief Scenario::play_sound
 * \param url
 */
void Scenario::play_sound(const QUrl &url)
{
    auto player = MediaPlayerPtr(new QMediaPlayer);
    player->setMedia(url);
    player->setVolume(100);
    player->play();

}


/*!
 * \brief Scenario::add_view
 * \param name
 * \param view
 */
void Scenario::add_view(const QString &name, ViewWidgetPtr view)
{
    m_views.insert(name,view);
}

/*!
 * \brief Scenario::views
 * \return
 */
ViewContainer Scenario::views() const
{
  return m_views;
}

ViewWidgetPtr Scenario::create_view(AssetsManagerPtr assets,const QString &name)
{

    auto gscene = new Scene(name,assets);
    gscene->setSceneRect(assets->grid_rect()); // why doesn't it set at construction? It's supposed to!
    return new ViewWidget(new View(gscene),assets);
}


/*!
 * \brief Scenario::view
 * \param name
 * \return
 */
ViewWidgetPtr Scenario::view(const QString &name) const
{
  return m_views[name];
}

/*!
 * \brief Scenario::add_world
 * \param world
 *
 * Convenience overloaded add_world mututator that uses the Scenario's name
 */
void Scenario::add_world(WorldPtr world)
{
    add_world(scenario_name(),world);
}

/*!
 * \brief Scenario::slot_update
 * \param timestamp
 *
 * timer tick update
 */
void Scenario::on_update(qint64 timestamp)
{
    m_currenttimestamp = timestamp;
    act(timestamp);
    m_lasttimestamp = timestamp;
}

