#include<iostream>
#include "mainscene.h"

/*!
 * \brief MainScenario::setup
 *
 *
 * So, what do we do here?
 *
 * The create function is where the worlds and the objects that interact with the World are created.
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
    install(new GameWorld); //  install the root World
}

/*!
 * \brief scene::Main::configure
 *
 * configure is where  the Actors in the newly created world as created and added.  This is also
 * used to configure the Scenario and the World it contains
 */
void scene::Main::configure()
{

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


}
