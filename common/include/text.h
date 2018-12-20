#ifndef TEXT_H
#define TEXT_H

#include <QGraphicsTextItem>

class Text : public QGraphicsTextItem
{
    Q_OBJECT
public:
    Text(const QString &text, QGraphicsItem *parent = nullptr);
};

#endif // TEXT_H
