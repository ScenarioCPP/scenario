#ifndef IMAGE_H
#define IMAGE_H
#include "scenesharedlib_global.h"

#include<QGraphicsItem>
#include <QPainter>

class SCENESHAREDLIB_EXPORT Image : public QObject,public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

    QRectF m_rect;

public:
    Image(const QRectF &rect, QGraphicsItem *parent=nullptr);
    virtual QRectF boundingRect() const override;

protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

#endif // IMAGE_H
