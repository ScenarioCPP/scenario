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
    m_player = create_player("Bunny",32,96,true);  //  Create the Bunny at position 32,96 and make it movable
    m_player->name("Snow Flake");  // Set the player's name
    create_npc("Carrot",112,32,true); // Create the carrot at position 112,32 and make it movable
    create_npc("Carrot",112,64,true);
    create_npc("Carrot",64,64,true);

    // How about some game music?
    music_play_list(scenario_name(),{"o_fortuna","mars"});
    loop_start(false);  // this will cause the act function to not be called on startup, it can be started later
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

  static int playerscore=0; // we want the score to be here each time we enter, so make it static

  if(m_player->check_collisions()) {
      for(auto sprite : m_player->colliding_sprites())
      {
        if(sprite->get_type() == CARROT || sprite->get_type() == 2)
        {
            playerscore++;
            remove(sprite);
            play_pickup_sound("pickup02");
            score(m_player->name(),playerscore);
        }
      }
  }

}
