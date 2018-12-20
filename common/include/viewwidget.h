#ifndef VIEWWIDGET_H
#define VIEWWIDGET_H

#include <QPointer>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QSlider>
#include <QCheckBox>
#include "view.h"
#include "scene.h"
#include "actor.h"
#include "assetsmanager.h"

class ViewWidget : public QWidget
{
    Q_OBJECT
    int         m_tile_size;
    int         m_score;
    ViewPtr     m_view;
    ScenePtr    m_scene;
    QLabel      *m_title;
    QLabel      *m_score_label;
    QLabel      *m_x;
    QLabel      *m_y;
    QLabel      *m_tile;
    QLabel      *m_tile_value;
    QLabel      *m_tile_collision;
    QLabel      *m_portal_info;
    QLabel      *m_sprite_pos;
    QLabel      *m_fps;
    QLineEdit   *m_reposition_x;
    QLineEdit   *m_reposition_y;
    QLineEdit   *m_gravity;
    QLineEdit   *m_friction;
    QLineEdit   *m_xvinc;
    QLineEdit   *m_yvinc;
    QLabel      *m_asset_root;
    QPushButton *m_change_asset_root;
    QPushButton *m_repo_button;
    QComboBox   *m_cb;
    QPushButton *m_spawn_npc;
    QLineEdit   *m_npc_x;
    QLineEdit   *m_npc_y;
    QComboBox   *m_npc_type;
    QCheckBox   *m_music;
    QSlider     *m_gravity_sl;
    QSlider     *m_world_timer_sl;
    QPushButton *m_start_stop;

    AssetsManagerPtr m_assets;


public:
    explicit ViewWidget(ViewPtr view,AssetsManagerPtr assets=nullptr,QWidget *parent = nullptr);
    ViewPtr view() const;
    void setScene(Scene *scene);
    void title(const QString &t);
    QString title() const;
    ScenePtr scene() const;
    void center_actor_in_view(const ActorPtr a);
    void update();
    void assets(AssetsManagerPtr assets);
    AssetsManagerPtr assets() const;
    ViewWidget *connect_scene_changed(QObject *obj);
    ViewWidget *signal_reposition(QObject *obj1,QObject *obj);
    ViewWidget *connect_gravity_changed(QObject *obj);
    ViewWidget *connect_friction_changed(QObject *obj);
    ViewWidget *signal_xinc_changed(QObject *obj);
    ViewWidget *signal_yinc_changed(QObject *obj);
    ViewWidget *connect_spawn_npc(QObject *obj);
    ViewWidget *connect_music(QObject *obj);
    ViewWidget *connect_score(QObject *obj1,QObject *obj2);
    ViewWidget *signal_timer(QObject *obj1,QObject *obj2);
    ViewWidget *connect_timer_change(QObject *obj1,QObject *obj2);
    ViewWidget *connect_focus(QObject *obj1,QObject *obj2);
    ViewWidget *connect_change_root(QObject *obj1,QObject *obj2);
    ViewWidget *internal_signal_change_root(QObject *obj1);
    ViewWidget *connect_start_stop(QObject *obj1);

protected:
    QString map_collision(int v) const;
    void update_score_label(const QString &player,int);

signals:
    void scene_changed(const QString &scene);
    void gravity_changed(double g);
    void friction_changed(double g);
    void xinc_changed(double g);
    void yinc_changed(double g);
    void spawn_npc(double x,double y,const QString &type);
    void music(bool);
    void timer_change(int);
    void change_root(const QString &root);
    void focus();

protected slots:
    void on_gravity_changed();
    void on_gravity_sl_changed(int);
    void on_friction_changed();
    void on_xinc_changed();
    void on_yinc_changed();
    void on_scene_option_changed(const QString &scene);
    void on_zone_changed(const QString &zone);
    void on_mouse_moved(const QPointF &pos);
    void on_sprite_moved(const QPointF &pos);
    void on_offer_sprite(const Actor *a);
    void on_item_collision(Sprite*,QGraphicsItem*);
    void on_reposition(bool checked);
    void on_spawn_npc(bool checked);
    void on_music(int checked);
    void on_score(const QString &name,int score);
    void on_timer_change(int tick);
    void on_change_root(bool checked);
    void on_start_stop(bool checked);
};

typedef QPointer<ViewWidget> ViewWidgetPtr;
#endif // VIEWWIDGET_H
