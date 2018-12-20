#ifndef SCENARIOMANAGER_H
#define SCENARIOMANAGER_H
#include "scenesharedlib_global.h"

#include "scenario.h"
#include "gameengine.h"
#include "viewwidget.h"
#include <QObject>
#include <QShowEvent>
#include <QHideEvent>
#include <QCloseEvent>
#include <QPointer>
#include <QMap>

typedef QMap<QString,ScenarioPtr> ScenarioContainer;
typedef QPointer<QObject> ObjectPtr;
typedef QShowEvent ShowEvent;
typedef QHideEvent HideEvent;
typedef QCloseEvent CloseEvent;

class SCENESHAREDLIB_EXPORT ScenarioManager : public QObject
{
  Q_OBJECT

  ScenarioContainer m_scenarios;
  ScenarioPtr m_start_scenario;
  QString m_current_scenario;
  GameEnginePtr m_gameengine;
  bool m_firstshow;
  bool m_closed;
  QString m_current_world_name;

public:
  explicit ScenarioManager(ObjectPtr parent = nullptr);
  ~ScenarioManager();
  ScenarioManager *add_scenario(ScenarioPtr scenario);
  ScenarioContainer scenarios() const;
  ScenarioPtr scenario(const QString &name) const;
  ScenarioManager *start(ScenarioPtr mainscene);
  void start_game_engine();
  void stop_game_engine();
  QString get_asset_root();
  void save_settings();
  QString current() const;
  ScenarioManager *connect_show_event(ObjectPtr obj); // will alert the manager when the MainWindow is shown
  ScenarioManager *connect_close_event(ObjectPtr obj); // will alert the manager when the MainWindow is closing
  ScenarioManager *connect_hide_event(ObjectPtr obj); // will alert the manager when the MainWindow is hidden
  ScenarioManager *connect_resize_event(ObjectPtr obj); // will alert the manager when the MainWindow is resized
  ScenarioManager *connect_view_initialized(ObjectPtr obj); // will alert the manager when the MainWindow is hidden

signals:
  void signal_view_initialized(ViewWidgetPtr);

public slots:
  void on_show(QShowEvent *obj);
  void on_hide(QHideEvent *obj);
  void on_close(QCloseEvent *evt);
  void on_resize(QResizeEvent *evt);

};

typedef QPointer<ScenarioManager> ScenarioManagerPtr;
#endif // SCENARIOMANAGER_H
