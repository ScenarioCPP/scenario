#ifndef PATHS_H
#define PATHS_H
#include <QtGlobal>
#include <QPointF>
#include <QPainterPath>
#include <QString>
#include <QtMath>
const double pi = 3.14159;
QPointF pointy_hex_corner(const QPointF center,double size,int i);
QPointF flat_hex_corner(const QPointF center,double size,int i);
QPainterPath hex_tile(double size,const QString type);
#endif // PATHS_H
