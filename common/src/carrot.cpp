#include "global_defines.h"
#include "carrot.h"
#include <QtMath>
#include <QDebug>
#include <QMediaPlayer>


Carrot::Carrot(SpritePtr sprite,QObject *parent) : NPCharacter(sprite,parent) {
    m_delay = 10;
    m_toggle = qrand() % 2;
    m_conf = assets()->npc_map("carrot");
    m_position_x = qrand()%360 * M_PI * 2;
    m_position_y = m_position_x * 2;
}

void Carrot::render(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    auto a = m_conf["animations"].toArray()[m_toggle].toArray();
    //qDebug() << "Carrot::act " << sprite()->current_frame_rect()<< m_toggle;
    QRectF r(QPointF(a[0].toInt(),a[1].toInt()),QSize(a[2].toInt(),a[3].toInt()));
    painter->drawPixmap(rect(),*(tilemap()),r);
}

void Carrot::act(qint64 t)
{
    m_count++;
    m_position_x += 0.1;
    m_position_y += 0.2;
    sprite()->changeFrameSet("twirl","loop",1);
    update_animation();
    if(!check_collisions())
    {
        if(m_animate && m_count > m_delay)
        {
            m_count = 0;
            set_pos(QPointF(m_base_x + cos(m_position_x) * 2,m_base_y + sin(m_position_y)));
        }
    }
    else
    {
    }
    m_toggle = m_toggle ? 0 : 1;
    m_current_tick = t;
}

