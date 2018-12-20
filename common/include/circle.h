#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"


class Circle : public Shape
{
public:
  Circle(double radius);
  void render(QPainter* painter);
};

#endif // CIRCLE_H
