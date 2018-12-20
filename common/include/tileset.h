#ifndef TILESET_H
#define TILESET_H

#include <QSharedPointer>
#include<QVector>
#include "frame.h"


class TileSet
{
   int m_columns;
   int m_tile_size;
   FrameContainerPtr m_frames;

public:
    TileSet(int columns,int tile_size);
    void set_frames(FrameContainerPtr m_frames);
    void add_frame(FramePtr f);
    FrameContainerPtr frames() const;
};

typedef QSharedPointer<TileSet> TileSetPtr;

#endif // TILESET_H
