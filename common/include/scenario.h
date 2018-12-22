#ifndef SCENARIO_H
#define SCENARIO_H
#include "scenesharedlib_global.h"

#include <QObject>
#include <QMap>
#include <QString>
#include <QPointer>
#include <QMediaPlayer>
#include "world.h"
#include "viewwidget.h"

typedef QMap<QString,WorldPtr> WorldContainer;
typedef QMap<QString,ViewWidgetPtr> ViewContainer;
typedef QPointer<QMediaPlayer> MediaPlayerPtr;

class SCENESHAREDLIB_EXPORT Scenario : public QObject
{
  Q_OBJECT

  QString m_name;
  WorldContainer m_worlds;
  QString m_default_world;
  QString m_asset_root;
  ViewContainer m_views;
  bool m_auto_start;
  qint64 m_currenttimestamp;
  qint64 m_lasttimestamp;

public:
  enum ActorType {PLAYER,NPC};

  explicit Scenario(QObject *parent = nullptr);
  virtual void init() = 0;
  virtual void create() = 0;
  virtual void configure() = 0;
  virtual void act(qint64 time) = 0;
  void scenario_name(const QString &scenario_name);
  QString scenario_name() const;
  void loop_start(bool as);
  bool loop_start() const;
  ViewContainer views() const;
  ViewWidgetPtr create_view(AssetsManagerPtr assets,const QString &scenario_name);
  void add_view(const QString &scenario_name,ViewWidgetPtr view);
  ViewWidgetPtr view(const QString &scenario_name) const;
  void add_world(WorldPtr world);
  void add_world(const QString &scenario_name,WorldPtr world);
  WorldPtr world(const QString &scenario_name) const;
  void main_world(const QString &scenario_name);
  void remove(SpritePtr s);
  void add_actor(const QString &world_name,ActorPtr a,ActorType t);
  QString main_world() const;
  QString world_zone(const QString &world_name) const;
  qint64 last_time() const;
  qint64 frame_rate() const;
  void connect_key_down_up(const QString &world_name,ActorPtr a);
  AssetsManagerPtr assets(const QString &w) const;
  void music_play_list(const QString &world_name,QVector<QString> list);
  void play_pickup_sound(const QString &sound="qrc:/assets/sounds/pickup1.mp3");
  QString asset_root() const;
  void asset_root(const QString &asset);
  QGraphicsItem* add_graphics_item(QGraphicsItem *item);
  void install(WorldPtr world);

protected:
  void play_sound(const QUrl &url);

signals:

private slots:
  virtual void on_update(qint64 time);
};

typedef QPointer<Scenario> ScenarioPtr;

#endif // SCENARIO_H
