#ifndef MAINSCENE_H
#define MAINSCENE_H
#include "scenario.h"
#include "world.h"
#include "playerfactory.h"
#include "npcfactory.h"
#include <QDebug>


class MainWorld : public World
{
    Q_OBJECT
public:
    /*!
     * \brief MainWorld::MainWorld
     * \param ge
     * \param assets
     * \param display
     * \param parent
     * Construct a new world.
     * The size of the world (in number of cells) and the
     * size of each cell (in pixels) must be specified in the AssetManager.
     */
    MainWorld(GameEnginePtr ge=nullptr, AssetsManagerPtr assets=nullptr, ViewWidgetPtr display=nullptr, QObject *parent=nullptr) :
      World(ge,assets,display,parent)
    {
    }

    virtual ~MainWorld() {}

    /*!
     * \brief RabbitTrap::setup
     * \param world
     */
    void setup()
    {
        // Setup the Scene and the View
            load_scene(assets()->zone());
    }

    /*!
     * \brief setup_display
     *
     * this method is called after the view is initialized
     */
    void setup_display()
    {
          display()->connect_scene_changed(this)
                   ->connect_gravity_changed(this)
                   ->connect_friction_changed(this)
                   ->connect_spawn_npc(this)
                   ->connect_music(this)
                   ->connect_score(this,display())
                   ->connect_focus(display(),this)
                   ->connect_timer_change(display(),this)
                   ->connect_change_root(display(),this)
                   ->connect_start_stop(this)
                   ;
    }
    /*!
     * \brief MainWorld::loop
     * time loop method
     */
    void act(qint64 timestamp)
    {
        Q_UNUSED(timestamp);
    }

};

namespace scene
{

const int CARROT = 254;
class Main: public Scenario
{

    ActorPtr m_player;

public:
    void create() override;
    void configure() override;
    void act(qint64 time) override;

    /*!
     * \brief add_scenario
     * \param name
     * \param world
     *
     * adds this scenario with the given world
     */
    void add_scenario(const QString &name,WorldPtr world)
    {
      if(scenario_name() != name )
            scenario_name(name);  // we need to name the Main scenario, it's also the first world name
      add_world(world);
      start_world(scenario_name());
    }

    /*!
     * \brief create_player
     * \param character_name
     * \param x
     * \param y
     * \param movable
     * \return
     */
    ActorPtr create_player(const QString character_name,double x=0,double y=0,bool movable=true)
    {
      auto player = PlayerFactory(assets(scenario_name())).new_character(character_name);
      connect_key_down_up(scenario_name(),player);
      add_actor(scenario_name(),player,Scenario::PLAYER);
      player->has_sound(true);
      player->set_pos(x,y);
      player->movable(movable);
      player->face_right();
      return player;
    }

    /*!
     * \brief create_npc
     * \param character_name
     * \param x
     * \param y
     * \param movable
     * \return
     */
    ActorPtr create_npc(const QString &character_name,double x=0,double y=0,bool movable=true)
    {
      auto npc = NPCFactory(assets(scenario_name())).new_character(character_name);
      npc->movable(movable);
      npc->set_pos(x,y);
      add_actor(scenario_name(),npc,Scenario::NPC);
      if(character_name == "Carrot") npc->set_type(CARROT);
      return npc;
    }

    /*!
     * \brief MainScene::broadcast_score
     * \param actor_name
     * \param score
     */
    void score(const QString &actor_name, int score)
    {
      world(scenario_name())->broadcast_score(actor_name,score);
    }
};

}
#endif // MAINSCENE_H
