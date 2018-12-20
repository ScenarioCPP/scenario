#ifndef SHAPE_H
#define SHAPE_H

#include <QGraphicsItem>
#include <QObject>

class Shape : public QObject,public QGraphicsItem
{
  Q_OBJECT
  Q_INTERFACES(QGraphicsItem)
  QRectF m_bounding_rect;
public:
  explicit Shape(const QRectF &bounds,QGraphicsItem *parent = nullptr);
  virtual QRectF boundingRect() const override {return m_bounding_rect;}
  virtual void render(QPainter *painter) = 0;

protected:
  virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

};

#endif // SHAPE_H
