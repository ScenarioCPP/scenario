#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <QPointer>
#include <QObject>
#include <QString>
#include "frame.h"
#include "tileset.h"

class Animator : public QObject
{
    Q_OBJECT

    int m_count;
    int m_frame_index;
    int m_frame_value;
    QString m_mode;
    int m_delay;
    FramesContainer m_frame_set;

public:

    Animator(QObject* parent=nullptr);

    void animate();
    void changeFrameSet(FramesContainer frame_set, QString mode, int delay, int frame_index);
    void loop();
    QString mode() const;
    int count() const;
    int delay() const;
    FramesContainer frame_set() const;
    int frame_index() const;
    int frame_value() const;
    QRectF current_frame_rect(const TileSetPtr ts) const;
};

typedef QPointer<Animator> AnimatorPtr;


#endif // ANIMATOR_H
