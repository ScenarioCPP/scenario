#include "controller.h"
#include<QDebug>

/*!
 * \brief Controller::Controller
 * \param parent
 */
Controller::Controller(const ButtonKeyMap &bk_map,QObject *parent) : QObject(parent)
{
    m_down = new ButtonInput();
    m_up = new ButtonInput();
    m_left = new ButtonInput();
    m_right = new ButtonInput();
    m_button_key_map = bk_map;

    // much better solution, putting it in a map,
    // now we have constant look up for the key_down_up event
    m_input_button_map.insert(m_button_key_map["Down"],m_down);
    m_input_button_map.insert(m_button_key_map["Up"],m_up);
    m_input_button_map.insert(m_button_key_map["Left"],m_left);
    m_input_button_map.insert(m_button_key_map["Right"],m_right);
}


/*!
 * \brief Controller::button_key_map
 * \return
 */
ButtonKeyMap Controller::button_key_map() const
{
  return m_button_key_map;
}

/*!
 * \brief Controller::button_map
 * \param map
 */
void Controller::button_map(const ButtonKeyMap &map)
{
    m_button_key_map = map;
}


/*!
 * \brief Controller::btn_down
 * \return
 */
ButtonInputPtr Controller::btn_down()
{
    return m_down;
}

/*!
 * \brief Controller::btn_left
 * \return
 */
ButtonInputPtr Controller::btn_left()
{
    return m_left;
}

/*!
 * \brief Controller::btn_right
 * \return
 */
ButtonInputPtr Controller::btn_right()
{
    return m_right;
}

/*!
 * \brief Controller::btn_up
 * \return
 */
ButtonInputPtr Controller::btn_up()
{
    return m_up;
}

/*!
 * \brief Controller::key_down_up
 * \param e
 *
 * Event handler for keys down or up
 */
void Controller::key_down_up(QKeyEvent *e)
{
    if(m_input_button_map.keys().contains(e->key()))
        m_input_button_map[e->key()]->getInput(e->type() == QEvent::KeyPress);
}
