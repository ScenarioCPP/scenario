#ifndef FRAME_H
#define FRAME_H

#include<QRectF>
#include <QVector>
#include <QMap>
#include <QSharedPointer>
typedef QVector<int> FramesContainer;
typedef QMap<QString,FramesContainer > AnimMap;

class Frame
{
    int m_x,m_y,m_width,m_height,m_offset_x,m_offset_y;
public:
    Frame(int x, int y, int width, int height, int offset_x, int offset_y);
    int x() const;
    int y() const;
    int width() const;
    int height() const;
    int offset_x() const;
    int offset_y() const;
    QRectF to_rect() const;
    QString to_string() const;
};

typedef QSharedPointer<Frame> FramePtr;
typedef QVector<FramePtr> FrameContainer;
typedef QSharedPointer<FrameContainer> FrameContainerPtr;

#endif // FRAME_H
