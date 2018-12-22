#include "scenariomanager.h"
#include "scene.h"
#include "global_defines.h"
#include <QtMath>
#include <QDebug>
#include <QSettings>

/*!
 * \brief ScenearioManager::ScenearioManager
 * \param parent
 *
 * Responsibility: Manage lists of Scenario Objects, this is a director
 * which loads and unloads Scenarios
 */
ScenarioManager::ScenarioManager(ObjectPtr parent) :
  QObject(parent),
  m_gameengine( new GameEngine(DEFAULT_FRAME_RATE)),
  m_firstshow(false),
  m_closed(false)
{
}

/*!
 * \brief ScenarioManager::~ScenarioManager
 */
ScenarioManager::~ScenarioManager()
{
}

/*!
 * \brief ScenarioManager::add_scenario
 * \param name
 * \param scenario
 */
ScenarioManager *ScenarioManager::add_scenario(ScenarioPtr scenario)
{
    m_scenarios.insert(scenario->scenario_name(),scenario);
    return this;
}

/*!
 * \brief ScenarioManager::scenarios
 * \return
 */
ScenarioContainer ScenarioManager::scenarios() const
{
  return m_scenarios;
}

/*!
 * \brief ScenarioManager::scenario
 * \param name
 * \return
 */
ScenarioPtr ScenarioManager::scenario(const QString &name) const
{
  return m_scenarios[name];
}

/*!
 * \brief ScenarioManager::start
 * \param mainscene
 *
 * The first scenario to start
 */
ScenarioManager *ScenarioManager::start(ScenarioPtr mainscene)
{
    m_start_scenario = mainscene;
    return this;
}

/*!
 * \brief ScenarioManager::start_game_engine
 */
void ScenarioManager::start_game_engine()
{
    assert(m_gameengine != nullptr);
    m_gameengine->start();
}

/*!
 * \brief ScenarioManager::stop_game_engine
 */
void ScenarioManager::stop_game_engine()
{
    assert(m_gameengine != nullptr);
    m_gameengine->stop();
}

/*!
 * \brief ScenarioManager::get_asset_root
 * \return
 */
QString ScenarioManager::get_asset_root()
{
    QSettings settings(COMPANY, APPLICATION);
    return settings.value("assetpath",DEFAULT_ASSET_ROOT).toString();
}

/*!
 * \brief ScenarioManager::save_settings
 */
void ScenarioManager::save_settings()
{
    QSettings settings(COMPANY, APPLICATION);
    settings.setValue("assetpath", scenario(current())->asset_root());
}

/*!
 * \brief ScenarioManager::current
 * \return
 */
QString ScenarioManager::current() const
{
    return m_current_scenario;
}

/*!
 * \brief ScenarioManager::connect_show_event
 * \param obj
 * \return
 */
ScenarioManager *ScenarioManager::connect_show_event(ObjectPtr obj)
{
  connect(obj,SIGNAL(signal_show_event(QShowEvent*)),this,SLOT(on_show(QShowEvent*)));
  return this;
}

/*!
 * \brief ScenarioManager::connect_hide_event
 * \param obj
 * \return
 */
ScenarioManager *ScenarioManager::connect_hide_event(ObjectPtr obj)
{
  connect(obj,SIGNAL(signal_hide_event(QHideEvent*)),this,SLOT(on_hide(QHideEvent*)));
  return this;
}

/*!
 * \brief ScenarioManager::connect_resize_event
 * \param obj
 * \return
 */
ScenarioManager *ScenarioManager::connect_resize_event(ObjectPtr obj)
{
  connect(obj,SIGNAL(resize_event(QResizeEvent*)),this,SLOT(on_resize(QResizeEvent*)));
  return this;
}

/*!
 * \brief ScenarioManager::connect_view_initialized
 * \param obj
 * \return
 * connect the view_initialized event to whoever needs it
 */
ScenarioManager *ScenarioManager::connect_view_initialized(ObjectPtr obj)
{
  connect(this,SIGNAL(signal_view_initialized(ViewWidgetPtr)),obj,SLOT(on_viewInitialized(ViewWidgetPtr)));
  return this;
}

/*!
 * \brief ScenarioManager::connect_close_event
 * \param obj
 * \return ScenarioManager*
 *
 * connect this close event to this ScenarioManager
 */
ScenarioManager *ScenarioManager::connect_close_event(ObjectPtr obj)
{
  connect(obj,SIGNAL(signal_close_event(QCloseEvent*)),this,SLOT(on_close(QCloseEvent*)));
  return this;
}

const QString DEFAULT_SCENARIO = "main";  //
/*!
 * \brief ScenarioManager::on_show
 * \param evt
 *
 * This event is called when the MainWindow is shown, it is here that the scenario is added
 * and then executed
 */
void ScenarioManager::on_show(QShowEvent *evt)
{
    Q_UNUSED(evt)

    if(!m_firstshow)
    {

        //auto main_scenario = new scene::Main();
        m_start_scenario->create(); // run the user defined create for the main scenario
        m_start_scenario->asset_root(get_asset_root());
        assert(!m_start_scenario->scenario_name().isEmpty());
        m_current_scenario = m_start_scenario->scenario_name();
        m_current_world_name = (m_start_scenario->main_world().isEmpty()) ? "main" : m_start_scenario->main_world();
        auto assets = new AssetsManager(m_start_scenario->asset_root(),m_current_world_name);
        auto viewwidget = m_start_scenario->create_view(assets,m_current_world_name);
        m_start_scenario->add_view(m_current_world_name,viewwidget);

        auto w = m_start_scenario->world(m_current_world_name);

        w->view_widget(viewwidget);
        w->assets(m_start_scenario->view(m_current_world_name)->assets());
        w->game_engine(m_gameengine);
        m_gameengine->connect_update(w);
        viewwidget->view()->connect_keypress_event(w);
        m_gameengine->connect_update(m_start_scenario);
        w->setup();  // call the World setup function
        w->setup_display(); // set up the display for the world (user defined)

        m_start_scenario->configure(); // configure the main scenario

        if(m_start_scenario->loop_start()) start_game_engine(); // if it is auto_start the processing loop starts
        add_scenario(m_start_scenario); // add it to the scenario container
        m_firstshow = true;

        emit signal_view_initialized(viewwidget);
    }
    else{
        //qDebug() << "ScenarioManager::on_show() -- subsequent show";
    }
}

void ScenarioManager::on_hide(QHideEvent *evt)
{
    Q_UNUSED(evt)
    if(!m_closed)  // not sure why the hideEvent is sent after the closeEvent, this fixes that
      ;
        // TODO thinking about turning the timer off to save on CPU cycles
        //qDebug() << "ScenarioManager::on_hide()";
}

void ScenarioManager::on_close(QCloseEvent *evt)
{
    Q_UNUSED(evt)
    disconnect(this,nullptr,nullptr,nullptr); // unhook from everything that we might be signalling
    save_settings();
    m_closed = true;
}

/*!
 * \brief ScenarioManager::on_resize
 * \param evt
 */
void ScenarioManager::on_resize(QResizeEvent *evt)
{
  if(m_firstshow)
  {
      auto vwidget = scenario(current())->view(m_current_world_name);
      double width = evt->size().width();
      double swidth = vwidget->scene()->sceneRect().width();
      qreal scale = abs(width/swidth - .005 * swidth);
      vwidget->view()->setMatrix(QMatrix().scale(scale,scale));
  }
}
