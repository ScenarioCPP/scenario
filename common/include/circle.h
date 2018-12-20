#ifndef CIRCLE_H
#define CIRCLE_H
#include "scenesharedlib_global.h"

#include "shape.h"


class SCENESHAREDLIB_EXPORT Circle : public Shape
{
public:
  Circle(double radius);
  void render(QPainter* painter);
};

#endif // CIRCLE_H
