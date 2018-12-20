#ifndef PATHS_H
#define PATHS_H
#include "scenesharedlib_global.h"

#include <QtGlobal>
#include <QPointF>
#include <QPainterPath>
#include <QString>
#include <QtMath>
const double pi = 3.14159;
SCENESHAREDLIB_EXPORT QPointF pointy_hex_corner(const QPointF center,double size,int i);
SCENESHAREDLIB_EXPORT QPointF flat_hex_corner(const QPointF center,double size,int i);
SCENESHAREDLIB_EXPORT QPainterPath hex_tile(double size,const QString type);
#endif // PATHS_H
