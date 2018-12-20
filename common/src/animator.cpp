#include "animator.h"
#include<QDebug>


/*!
 * \brief Animator::Animator
 */
Animator::Animator(QObject* parent) : QObject(parent),m_count(0),m_frame_index(0),m_frame_value(0),m_mode("pause") { }


/*!
 * \brief animate
 */
void Animator::animate() {
  if(m_mode == "loop") loop();

}

/*!
 * \brief changeFrameSet
 * \param frame_set
 * \param mode
 * \param delay
 * \param frame_index
 */
void Animator::changeFrameSet(FramesContainer frame_set, QString mode, int delay, int frame_index)
{
    if (m_frame_set == frame_set) { return; }

    m_count       = 0;
    m_delay       = delay;
    m_frame_set   = frame_set;
    m_frame_index = frame_index;
    m_frame_value = frame_set[frame_index];
    m_mode        = mode;
}

/*!
 * \brief loop
 * catch up any missed cycles
 */
void Animator::loop()
{
    m_count ++;
    while(m_count > m_delay)
    {
          m_count -= m_delay;
          m_frame_index = (m_frame_index < m_frame_set.size()-1) ? m_frame_index + 1 : 0;
          m_frame_value = m_frame_set[m_frame_index];
    }
}


/*!
 * \brief mode
 * \return
 */
QString Animator::mode() const
{
  return  m_mode;
}


/*!
 * \brief count
 * \return
 */
int Animator::count() const { return m_count; }

/*!
 * \brief delay
 * \return
 */
int Animator::delay() const { return m_delay; }

/*!
 * \brief frame_set
 * \return
 */
FramesContainer Animator::frame_set() const { return m_frame_set; }

/*!
 * \brief frame_index
 * \return
 */
int Animator::frame_index() const { return m_frame_index; }

/*!
 * \brief frame_value
 * \return
 */
int Animator::frame_value() const { return m_frame_value; }

/*!
 * \brief current_frame_rect
 * \param ts
 * \return
 * ot sure what to do with this one yet, gives the current frame rectangle from the given
 * TileSet object
 */
QRectF Animator::current_frame_rect(const TileSetPtr ts) const { return ts->frames()->at(m_frame_value)->to_rect(); }
