#include "tileset.h"

/*!
 * \brief TileSet::TileSet
 * \param columns
 * \param tile_size
 */
TileSet::TileSet(int columns, int tile_size)
{
    m_columns = columns;
    m_tile_size = tile_size;
    /* An array of all the frames in the tile sheet image. */
}

/*!
 * \brief TileSet::set_frames
 * \param frames
 */
void TileSet::set_frames(FrameContainerPtr frames)
{
    m_frames = frames;
}

void TileSet::add_frame(FramePtr f)
{
    m_frames->push_back(f);
}

FrameContainerPtr TileSet::frames() const
{
   return m_frames;
}
