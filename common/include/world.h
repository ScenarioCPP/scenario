#ifndef WORLD_H
#define WORLD_H
#include "scenesharedlib_global.h"

#include <QPointer>
#include <QList>
#include <QVector>
#include <vector>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QMediaPlayer>
#include "global_defines.h"
#include "viewwidget.h"
#include "scene.h"
#include "gameengine.h"
#include "controller.h"
#include "collider.h"
#include "actor.h"
#include "assetsmanager.h"
#include "tileset.h"
#include "pcharacter.h"
#include "portal.h"

typedef QString String;
typedef const char* CStr;
typedef QList<QGraphicsItem> ItemList;
typedef QVector<ActorPtr> PlayerContainer;
typedef QMap<QString,QString> DataMap;
typedef QVector<PortalPtr> PortalList;
typedef QVector<QString> Strings;


class SCENESHAREDLIB_EXPORT World : public QObject
{
    Q_OBJECT


    QString m_name;
    QString m_zone;
    int m_width,m_height;
    int m_rows;
    int m_columns;
    int m_cell_size;
    double m_friction;
    double m_gravity;
    double m_xinc;
    double m_yinc;
    bool m_bounded;
    ViewPtr m_view;
    ScenePtr m_scene;
    ViewWidgetPtr m_display;
    GameEnginePtr m_game_engine;
    PCharacter *m_player;
    ColliderPtr m_collider;
    TileMapContainer m_collision_map;
    AssetsManagerPtr m_assets;
    TileSetPtr m_tileset;
    PlayerContainer m_players;
    DataMap m_settings;
    PortalList m_portals;
    PortalPtr m_portal;
    QMediaPlayer *m_mediaplayer;

public:
    World(GameEnginePtr ge=nullptr,AssetsManagerPtr assets=nullptr,ViewWidgetPtr display=nullptr,QObject* parent=nullptr);

    virtual void setup() =0;
    virtual void setup_display() = 0;
    virtual void act(qint64 timestamp) = 0;

    void game_engine(GameEnginePtr ge);
    void view_widget(ViewWidgetPtr vw);
    void assets(AssetsManagerPtr assets);
    void add_player(ActorPtr actor, int x, int y);
    World *add_actor(ActorPtr actor, int x, int y);
    void set_background(QColor color);
    void set_background(CStr filename);
    int get_height() const;
    int get_width() const;
    void set_view(ViewPtr view);
    ScenePtr get_scene();
    void set_scene(ScenePtr scene);
    void fill_scene(QString file);
    void set_collision_map(TileMapContainer collision_map);
    int rows() const;
    int columns() const;
    int cell_size() const;
    void set_display(ViewWidgetPtr display);
    double on_gravity() const;
    double on_friction() const;
    bool is_npc(const QGraphicsItem *item) const;
    bool is_player(const QGraphicsItem *item) const;
    bool is_hit(const QGraphicsItem *item) const;
    ViewWidgetPtr view();
    DataMap settings();
    void settings(const DataMap&);
    QString name() const;
    void add_portals(const PortalContainer &portals);
    void clear_portals();
    World *signal_portal_entry(QObject* obj);
    World *signal_key_down_up(QObject* obj);
    World *music(bool state);
    ViewWidgetPtr display() const;
    AssetsManagerPtr assets() const;
    void remove(SpritePtr s);
    bool music() const;
    void init_world();
    void broadcast_score(const QString &name,int);
    QString zone() const;
    void music_play_list(Strings m);

 public slots:
    void reposition_player(const QPointF &p);
    void start_world();
    void stop_world();

protected slots:
    void on_init();
    void on_gravity(double g);
    void on_friction(double g);
    void on_x_inc(double x);
    void on_y_inc(double y);
    void on_key_event(QKeyEvent *e);
    void on_resize_event(QResizeEvent *e);
    void on_spawn_npc(double x,double y,const QString &type);
    void on_music(bool);
    void start_game();
    void stop_game();
    void on_start_world();
    void on_stop_world();
    void on_start_stop(bool);
    void show_grid(bool toggle);
    void settings_change(DataMap &dm);
    void load_scene(const QString &scene);
    void on_update(qint64 timestamp);
    void portal_collision_check(qint64 timestamp);
    void on_portal_entry(const Portal &p);
    void on_timer_change(int);
    void on_change_root(const QString &root);
    void on_focus();

signals:
    void portal_entry(const Portal &p);
    void key_down_up(QKeyEvent *e);
    void signal_score(const QString &name,int);
};

typedef QPointer<World> WorldPtr;

#endif // WORLD_H
