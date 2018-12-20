#include "portal.h"
#include <QDebug>

Portal::Portal(QObject *parent) : QObject(parent)
{
    m_x = 0;
    m_y = 0;
}

Portal::Portal(const PortalMap &p,QObject *parent) : Portal(parent)
{
    m_x = p["x"].toDouble();
    m_y = p["y"].toDouble();
    m_width = p["width"].toDouble();
    m_height = p["height"].toDouble();
    m_destination_x = p["destination_x"].toDouble();
    m_destination_y = p["destination_y"].toDouble();
    m_destination_zone = p["destination_zone"];
}

Portal::~Portal()
{

}


bool Portal::collide_object(ActorPtr actor) const
{
    double center_x = actor->get_center_x();
    double center_y = actor->get_center_y();
    if ( center_x < get_left() || center_x > get_right() ||
         center_y < get_top()  || center_y > get_bottom()) return false;
    return true;
}

double Portal::get_left() const
{
   return m_x;
}

double Portal::get_right() const
{
   return m_x + m_width;
}

double Portal::get_top() const
{
    return m_y;
}

double Portal::get_bottom() const
{
    return m_y + m_height;
}

/*!
 * \brief Portal::destination_x
 * \return
 */
double Portal::destination_x() const
{
    return m_destination_x;
}

/*!
 * \brief Portal::destination_y
 * \return
 */
double Portal::destination_y() const
{
    return m_destination_y;
}

/*!
 * \brief Portal::destination_zone
 * \return
 */
QString Portal::destination_zone() const
{
    return m_destination_zone;
}

QString Portal::to_string() const
{
   return QString("%1 -> (%2,%3)").arg(m_destination_zone).arg(m_destination_x).arg(m_destination_y);
}
