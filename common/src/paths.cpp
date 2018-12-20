#include "paths.h"
#include <QVector>
#include <QPolygon>
#include<QDebug>

/*!
  A collection of interesting shape paths that will be used for screen output
**/
//#include "paths.h"
#if 0
    cool but not needed in this dialog
    double size = 16;
    for(int i=0;i<10;i++)
    {
        auto path = scene->addPath(hex_tile(size,"pointy"),QPen(Qt::black,0.5),QBrush(Qt::cyan));
        path->setFlag(QGraphicsItem::ItemIsMovable,true);
        path->setFlag(QGraphicsItem::ItemIsSelectable,true);
        path->setOpacity(0.25);
    }
#endif

double rad(double angle_deg)
{
    return  pi / 180 * angle_deg;
}
// from https://www.redblobgames.com/grids/hexagons/
QPointF hex_corner(const QString &type,const QPointF &center,double size,int i)
{

        double deg = (type == "pointy") ? 60 * i - 30 : 60 * i;
        return QPointF(qRound(center.x() + size * cos(rad(deg))),
                       qRound(center.y() + size * sin(rad(deg))));
}

/*!
 * \brief hex_tile returns a hexagonal path
 * \param size
 * \param type
 * \return
 *
 *
 */
QPainterPath hex_tile(double size,const QString type)
{

    QPainterPath qp;
    QPointF center(size/2,size/2);
    QVector<QPointF> points;
    points.push_back(hex_corner(type,center,size,0));
    for(int i=1;i<7;i++)
        points.push_back(hex_corner(type,center,size,i));
    qp.addPolygon(QPolygonF(points));
    return qp;
}
