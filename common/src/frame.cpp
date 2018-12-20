#include "frame.h"

/*!
 * \brief Frame::Frame
 * \param x
 * \param y
 * \param width
 * \param height
 * \param offset_x
 * \param offset_y
 */
Frame::Frame(int x, int y, int width, int height, int offset_x, int offset_y) :
    m_x(x),m_y(y),m_width(width),m_height(height),m_offset_x(offset_x),m_offset_y(offset_y)
{

}

/*!
 * \brief Frame::x
 * \return
 */
int Frame::x() const
{
    return m_x;

}

/*!
 * \brief Frame::y
 * \return
 */
int Frame::y() const
{

    return m_y;
}

/*!
 * \brief Frame::width
 * \return
 */
int Frame::width() const
{
    return m_width;
}

/*!
 * \brief Frame::height
 * \return
 */
int Frame::height() const
{
    return m_height;
}

/*!
 * \brief Frame::offset_x
 * \return
 */
int Frame::offset_x() const
{
    return m_offset_x;
}

/*!
 * \brief Frame::offset_y
 * \return
 */
int Frame::offset_y() const
{
    return m_offset_y;
}

/*!
 * \brief Frame::to_rect
 * \return
 */
QRectF Frame::to_rect() const
{
    return QRectF(QPointF(m_x,m_y),QSize(m_width,m_height));
}

/*!
 * \brief Frame::to_string
 * \return
 */
QString Frame::to_string() const
{
    return QString("[%1,%2,%3,%4,%5,%6]").arg(m_x).arg(m_y).arg(m_width).arg(m_height).arg(m_offset_x).arg(m_offset_y);
}
