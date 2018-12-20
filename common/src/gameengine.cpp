#include "global_defines.h"
#include "gameengine.h"
#include <QTime>
#include <QDebug>




GameEngine::GameEngine(int time_step, QObject *parent) :
    QObject(parent),
    m_time_step(time_step),
    m_accumulated_time(0)
{
}

/*!
 * \brief GameEngine::signal_update
 *
 * Wire the update signal to the on_update slot of the receiving object
 */
GameEngine *GameEngine::connect_update(QObject *obj)
{
    connect(this,SIGNAL(update(qint64)),obj,SLOT(on_update(qint64)),Qt::UniqueConnection);
    return this;
}

void GameEngine::time_step(int step)
{
    stop();
    m_time_step = MS_DEFAULT/step;
    start();
}

int GameEngine::time_step() const
{
  return m_time_step;
}

/*!
 * \brief GameEngine::run
 * \param time_stamp
 * This is one cycle of the game loop
 */
void GameEngine::run(qint64 time_stamp)
{
    m_accumulated_time += time_stamp - m_time;
    m_time = time_stamp;
    /* If the device is too slow, updates may take longer than our time step. If
    this is the case, it could freeze the game and overload the cpu. To prevent this,
    we catch a memory spiral early and never allow FRAME_LIMIT full frames to pass without
    an update. This is not ideal, but at least the user won't crash their cpu. */
    if (m_accumulated_time >= m_time_step * FRAME_LIMIT) {
       m_accumulated_time = m_time_step;
    }
    /* Since we can only update when the screen is ready to draw and timer
    calls the run function, we need to keep track of how much time has passed. We
    store that accumulated time and test to see if enough has passed to justify
    an update. Remember, we want to update every time we have accumulated one time step's
    worth of time, and if multiple time steps have accumulated, we must update one
    time for each of them to stay up to speed. */
    while(m_accumulated_time > m_time_step)
    {
        m_accumulated_time -= m_time_step;
        m_updated = true;
    }

    /* This allows us to only draw when the game has updated. */
    if (m_updated) {

      emit update(time_stamp);
      emit render(time_stamp);
      m_updated = false;
    }


}

/*!
 * \brief GameEngine::timerEvent
 * \param event
 */
void GameEngine::timerEvent(QTimerEvent *event)
{
    handle_run(event);
}

/*!
 * \brief GameEngine::handle_run
 */
void GameEngine::handle_run(QTimerEvent *event)
{
    Q_UNUSED(event)

    run( QDateTime::currentMSecsSinceEpoch());
}

/*!
 * \brief GameEngine::start
 * Start the game engine
 */
void GameEngine::start()
{
    m_accumulated_time = m_time_step;
    m_time = QDateTime::currentMSecsSinceEpoch();
    m_timer_id = startTimer(m_time_step);
}

/*!
 * \brief GameEngine::stop
 * Stop the game engine timer
 */
void GameEngine::stop()
{
    if(m_timer_id != -1)
    {
        killTimer(m_timer_id);
        m_timer_id = -1;
    }
    else {
        qDebug() << "Can't kill timer " << m_timer_id;
    }
}
