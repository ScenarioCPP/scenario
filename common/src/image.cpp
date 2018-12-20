#include "image.h"


Image::Image(const QRectF &rect,QGraphicsItem *parent):QObject(dynamic_cast<QObject*>(parent)),QGraphicsItem (parent)
{
    m_rect = rect;
}

QRectF Image::boundingRect() const
{
    return m_rect;
}

void Image::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawRect(boundingRect());
}
