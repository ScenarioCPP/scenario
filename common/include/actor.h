#ifndef ACTOR_H
#define ACTOR_H
#include "scenesharedlib_global.h"
#include <QObject>
#include <QPixmap>
#include <QColor>
#include <QMap>
#include <QVector>
#include <QList>
#include <QMediaPlayer>
#include "sprite.h"
#include "frame.h"
#include "animator.h"
#include "tileset.h"

typedef QList<SpritePtr> CollidingList;
typedef QPointer<QMediaPlayer> MediaPlayerPtr;
/*!
 * \brief The Actor class
 *
 * An Actor is an asset( A useful or valuable quality, person, or thing; an advantage or resource. )
 * in the game.
 *
 */
class SCENESHAREDLIB_EXPORT Actor : public QObject
{
    Q_OBJECT

protected:
    SpritePtr m_sprite;
    QColor m_color;
    int m_height;
    int m_width;
    int m_direction_x;
    bool m_jumping;
    QString m_name;
    double m_gravity;
    double m_friction;
    double m_velocity_x;
    double m_velocity_y;
    double m_velocity_max;
    double m_x;
    double m_y;
    double m_base_x; // for animation purposes
    double m_base_y; // for animation purposes
    double  m_position_x;
    double  m_position_y;
    double m_x_old;
    double m_y_old;
    double m_v_inc;
    double m_jump_height;
    AssetsManagerPtr m_assets;
    AnimatorPtr m_animator;
    MediaPlayerPtr m_mplayer;
    QString m_jump_sound;
    CollidingList m_colliding_sprites;
    bool m_animate;


public:
    Actor(QObject *parent=nullptr);
    Actor(SpritePtr sprite,QObject *parent=nullptr);
    Actor(int width,int height,AssetsManagerPtr assets,TileSetPtr tile_set,QObject *parent=nullptr);

    virtual void act(qint64 t) = 0;
    virtual void render(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget) = 0;

    void sprite(SpritePtr sprite);
    QColor color() const;
    void animator(AnimatorPtr m_animator);
    AnimatorPtr animator() const;
    void add_animation(const QString &name,FramesContainer f);
    void current_animation(const QString &anim);
    QString current_animation() const;
    void accept_drops(bool v);
    bool accept_drops() const;

    virtual bool check_collisions();
    void color(QColor c);
    int height() const;
    int width() const;
    void height(int h);
    void width(int w);
    int direction_x() const;
    void direction_x(int x);
    void face_right();
    void face_left();
    void animate(bool a);
    double velocity_x();
    double velocity_y();
    double velocity_max() const;
    void velocity_x(double x);
    void velocity_y(double y);
    void velocity_max(double max);
    void inc_velocity_x(double x);
    void inc_velocity_y(double y);
    void mul_velocity_x(double x);
    void mul_velocity_y(double y);
    void base_x(double x);
    void base_y(double y);

    bool jumping();
    void jumping(bool);
    void jump_height(double h);
    void gravity(double g);
    double gravity() const;
    void friction(double f);
    double friction() const;
    void velocity_inc(double inc);
    double x() const;
    void x(double x);
    double y() const;
    void y(double y);

    QString name() const;
    void name(const QString name);

    virtual void jump();
    virtual void move_left();
    virtual void move_right();
    virtual void update();
    virtual void update_position(double gravity,double friction);
    virtual void update_animation();
    /* These functions are used to get and set the different side positions of the object. */
    double get_bottom();
    double get_left();
    double get_right();
    double get_top();
    double get_center_x() const;
    double get_center_y() const;
    double get_old_center_x();
    double get_old_center_y();
    double get_old_bottom();
    double get_old_left();
    double get_old_right();
    double get_old_top();
    void set_bottom(double y);
    void set_left(double x);
    void set_right(double x);
    void set_top(double y);
    void set_center_x(double x);
    void set_center_y(double y);
    void set_old_center_x(double x);
    void set_old_center_y(double y);
    void set_old_bottom(double y);
    void set_old_left(double x);
    void set_old_right(double x);
    void set_old_top(double y);
    void set_base(const QPointF p);

    void tooltip(const QString &tool_tip);

    AssetsManagerPtr assets() const;

    SpritePtr sprite() const;
    Actor *movable(bool m);
    bool movable() const;
    Actor *selectable(bool s);
    bool selectable() const;
    bool hitshape() const;
    Actor *hitshape(bool hs);
    QRectF rect() const;
    QRectF current_frame_rect() const;
    PixmapPtr tilemap() const;
    void signal_on_rendor(QObject *obj);
    void connect_on_collide(QObject *obj);
    void default_render(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget);
    QString getJump_sound() const;
    void setJump_sound(const QString &jump_sound);
    void play_jump_sound();
    CollidingList colliding_sprites() const;
    void set_type(int t);
    int get_type() const;
    bool is_a(int t) const;
    void has_sound(bool mp);

public slots:
    void set_pos(const QPointF &pos);
    void set_pos(double x,double y);
    virtual void on_update(qint64 t);
    virtual void on_sprite_moved(const QPointF &p);
    virtual void on_render(QPainter *painter,const QStyleOptionGraphicsItem *option, QWidget *widget);
    void on_gravity(double g);

signals:
    void sprite_moved(const QPointF &pos);
    void signal_collision(Sprite *,QGraphicsItem *);
    void current_sprite(const Actor *a);
    void signal_action(const QString &string);

};
typedef QPointer<Actor> ActorPtr;

#endif // ACTOR_H
