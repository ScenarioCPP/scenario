#include "circle.h"

#include <QPainter>


Circle::Circle(double radius) : Shape(QRectF(QPointF(0,0),QSizeF(radius*2,radius*2)))
{

}

void Circle::render(QPainter *painter)
{
    painter->setPen(QPen(Qt::black));
    painter->drawEllipse(boundingRect());
}
