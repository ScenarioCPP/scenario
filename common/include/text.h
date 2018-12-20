#ifndef TEXT_H
#define TEXT_H
#include "scenesharedlib_global.h"

#include <QGraphicsTextItem>

class SCENESHAREDLIB_EXPORT Text : public QGraphicsTextItem
{
    Q_OBJECT
public:
    Text(const QString &text, QGraphicsItem *parent = nullptr);
};

#endif // TEXT_H
