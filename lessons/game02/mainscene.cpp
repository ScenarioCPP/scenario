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

    //loop_start(false);  // this will cause the act function to not be called on startup, it can be started later
    cpVect gravity = cpv(0, -100);

      // Create an empty space.
      m_space = cpSpaceNew();
      cpSpaceSetGravity(m_space, gravity);

      // Add a static line segment shape for the ground.
      // We'll make it slightly tilted so the ball will roll off.
      // We attach it to a static body to tell Chipmunk it shouldn't be movable.
      cpShape *ground = cpSegmentShapeNew(cpSpaceGetStaticBody(m_space), cpv(-20, 5), cpv(20, -5), 0);
      cpShapeSetFriction(ground, 1);
      cpSpaceAddShape(m_space, ground);

      // Now let's make a ball that falls onto the line and rolls off.
      // First we need to make a cpBody to hold the physical properties of the object.
      // These include the mass, position, velocity, angle, etc. of the object.
      // Then we attach collision shapes to the cpBody to give it a size and shape.

      cpFloat radius = 5;
      cpFloat mass = 1;

      // The moment of inertia is like mass for rotation
      // Use the cpMomentFor*() functions to help you approximate it.
      cpFloat moment = cpMomentForCircle(mass, 0, radius, cpvzero);

      // The cpSpaceAdd*() functions return the thing that you are adding.
      // It's convenient to create and add an object in one line.
      m_ballBody = cpSpaceAddBody(m_space, cpBodyNew(mass, moment));
      cpBodySetPosition(m_ballBody, cpv(0, 15));

      // Now we create the collision shape for the ball.
      // You can create multiple collision shapes that point to the same body.
      // They will all be attached to the body and move around to follow it.
      cpShape *ballShape = cpSpaceAddShape(m_space, cpCircleShapeNew(m_ballBody, radius, cpvzero));
      cpShapeSetFriction(ballShape, 0.7);

      // Now that it's all set up, we simulate all the objects in the space by
      // stepping forward through time in small increments called steps.
      // It is *highly* recommended to use a fixed size time step.
      m_timeStep = 1.0/60.0;
      m_time = 0.0;

//      // Clean up our objects and exit!
//      cpShapeFree(ballShape);
//      cpBodyFree(ballBody);
//      cpShapeFree(ground);
//      cpSpaceFree(space);
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

        cpVect pos = cpBodyGetPosition(m_ballBody);
        cpVect vel = cpBodyGetVelocity(m_ballBody);
        QString s = QString("Time is %1. ballBody is at (%2, %3). It's velocity is (%4, %5)").arg(m_time).arg(pos.x).arg(pos.y).arg(vel.x).arg(vel.y);
        qDebug() << s;

        cpSpaceStep(m_space, m_timeStep);
        m_time += m_timeStep;

}
