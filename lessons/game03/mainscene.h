#ifndef MAINSCENE_H
#define MAINSCENE_H
#include "scenario.h"
#include "world.h"
#include "playerfactory.h"
#include "Box2D.h"
#include "npcfactory.h"
#include <QDebug>

const int CARROT = 254;

class GameWorld : public World
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
    GameWorld(GameEnginePtr ge=nullptr, AssetsManagerPtr assets=nullptr, ViewWidgetPtr display=nullptr, QObject *parent=nullptr) :
      World(ge,assets,display,parent)
    {
    }

    virtual ~GameWorld() override {}

    /*!
     * \brief RabbitTrap::setup
     * \param world
     */
    void setup() override
    {
        // Setup the Scene and the View
            load_scene(assets()->zone());
    }

    /*!
     * \brief setup_display
     *
     * this method is called after the view is initialized
     */
    void setup_display() override
    {
          display()->connect_scene_changed(this)
                   ->connect_gravity_changed(this)
                   ->connect_friction_changed(this)
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
    void act(qint64 timestamp) override
    {
        Q_UNUSED(timestamp);
    }

};

namespace scene
{

class Main: public Scenario
{

    ActorPtr m_player;

public:
    void init() override {scenario_name("pool");}
    void create() override;
    void configure() override;
    void act(qint64 time) override;


};

}
#endif // MAINSCENE_H
