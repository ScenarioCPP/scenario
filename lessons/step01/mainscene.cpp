#include "mainscene.h"
#include "playerfactory.h"
#include "npcfactory.h"
#include "circle.h"

/*!
 * \brief MainScenario::setup
 *
 *
 * So, what do we do here?
 *
 * The setup function is where the worlds and the objects that interact with the World are created.
 *
 * scene::Main is a subtype of the abstract Scenario, A Scenario ties together the following elements:
 *
 *  o World -> the world manages:
 *      o Actors (players and non players)
 *      o Gameengine  - right now is just a timer manager
 *      o Physics
 *      o Assets
 *  o View
 *  o GameController
 *
    //loop_start(false); // this will turn off the processing loop
 */
/*!
 * \brief scene::Main::create
 *
 * Create worlds in the main Scenario
 */
void scene::Main::create()
{
    name("main");  // we need to name the Main scenario, it's also the first world name
    add_world(name(),new MainWorld());
    start_world(name());

    loop_start(false);
}

Circle *circle;

void scene::Main::configure()
{

    circle = new Circle(10);
    add_graphics_item(circle);
}
/*!
 * \brief MainScenario::act
 * \param time
 *
 * This is the main game loop, it is called on every clock tick cycle
 * roughly 33/sec by default, this is for game logic
 * be careful with expensive operations in this function, it may slow the whole
 * Scenario
 */
void scene::Main::act(qint64 time)
{
    Q_UNUSED(time)   // this turns off the warning at compile time

    circle->setX(circle->x() + 1);
    circle->setY(circle->y() + 1);

}

