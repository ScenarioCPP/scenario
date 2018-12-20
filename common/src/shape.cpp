#include "shape.h"


Shape::Shape(const QRectF &bounds, QGraphicsItem *parent) :  QObject(dynamic_cast<QObject*>(parent)), QGraphicsItem(parent),m_bounding_rect(bounds)
{

}

void Shape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    render(painter);
}
