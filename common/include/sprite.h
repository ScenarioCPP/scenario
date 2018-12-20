#ifndef SPRITE_H
#define SPRITE_H
#include "scenesharedlib_global.h"

#include <QPointer>
#include<QGraphicsItem>
#include<QPixmap>
#include<QString>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include "assetsmanager.h"
#include "frame.h"
#include "animator.h"
#include "tileset.h"

/*!
 * \brief The Sprite class
 *
 *
 * NOTES:
 *
 */
class SCENESHAREDLIB_EXPORT Sprite : public QObject,public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

    bool m_movable;
    QString m_name;
    QGraphicsItem *m_parent;
    QRectF m_rect;
    AnimMap m_anim_map;
    PixmapPtr m_tilemap;
    AnimatorPtr m_animator;
    TileSetPtr m_tile_set;
    AssetsManagerPtr m_assets;
    QString m_current_animation;
    int m_type;
    bool m_animating;
    bool m_hitshape;

public:
    explicit Sprite(const QRectF &rect,QGraphicsItem *parent = nullptr);
    explicit Sprite(int width,int height,AssetsManagerPtr am,TileSetPtr tile_set,QGraphicsItem *parent = nullptr);
    virtual ~Sprite() override;

    virtual QRectF boundingRect() const override;

    AnimatorPtr animator() const;
    void animator(AnimatorPtr a);
    void update_animation();
    void add_animation(const QString &name,const FramesContainer &f);
    void changeFrameSet(const QString &frame_set, const QString &mode, int delay = 10, int frame_index = 0);
    bool animating() const;
    void animating(bool a);
    QRectF rect() const;
    void character_type(int ctype);
    int character_type() const;
    void current_animation(const QString &ca);
    QString current_animation() const;
    bool hitshape() const;
    void hitshape(bool hs);
    AssetsManagerPtr assets() const;
    PixmapPtr tilemap() const;
    QRectF current_frame_rect() const;
    void default_render(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget);
    void set_type(int);
    int get_type() const;
    void set_hit(bool hit);
    void collidable(bool c);
    bool collidable() const;
    QString name() const;
    void connect_sprite_moving(QObject *obj);
    void connect_sprite_moved(QObject *obj);


protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *) override;
    void dragMoveEvent(QGraphicsSceneDragDropEvent *event) override;

signals:
    void signal_render(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget);
    void signal_moving(const QPointF &p);
    void signal_moved(const QPointF &p);
};

typedef QPointer<Sprite> SpritePtr;

#endif // SPRITE_H
