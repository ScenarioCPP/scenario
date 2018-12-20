#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QComboBox>
#include <QDebug>
#include <QFileDialog>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDir>
#include "global_defines.h"
#include "viewwidget.h"

ViewWidget::ViewWidget(ViewPtr view, AssetsManagerPtr assets,QWidget *parent) :
    QWidget(parent),m_score(0),m_view(view),m_scene(view->get_scene()),m_assets(assets)
{
    QVBoxLayout *v = new QVBoxLayout();

    v->addSpacerItem(new QSpacerItem(10,10));
    auto *h1 = new QHBoxLayout();
    h1->addWidget(m_title = new QLabel("New Scene",this));
    h1->setAlignment(m_title,Qt::AlignHCenter);
    m_title->setStyleSheet(QString("color:")+TITLE_COLOR+";font-size:18px;");
    h1->addWidget(new QLabel("Root Path: ",this));
    h1->addWidget(m_asset_root = new QLabel(QDir::homePath()+"/Code/"+PROJECT+"/assets"));
    h1->addWidget(m_change_asset_root = new QPushButton("Change",this));
    internal_signal_change_root(this);
    v->addLayout(h1);
    auto *h1_1 = new QHBoxLayout();
    h1_1->addWidget(m_score_label = new QLabel(QString("Score: %1").arg(0),this));
    h1_1->setAlignment(m_score_label,Qt::AlignCenter);
    m_score_label->setStyleSheet("color:yellow;font-size:18px;");
    m_score_label->setStyleSheet(QString("color:")+TITLE_COLOR+";font-size:18px;");
    m_score_label->setMaximumWidth(200);
    auto *h1_1_1 = new QHBoxLayout();
    auto h1_l1 = new QLabel(QString("Speed:"),this);
    h1_1_1->addWidget(h1_l1);
    h1_1_1->addWidget(m_world_timer_sl = new QSlider(Qt::Horizontal));
    h1_1_1->setAlignment(m_world_timer_sl,Qt::AlignRight);
    m_world_timer_sl->setTickInterval(5);
    m_world_timer_sl->setMaximum(100);
    m_world_timer_sl->setTickPosition(QSlider::TicksBelow);
    h1_1_1->setAlignment(Qt::AlignCenter);
    m_world_timer_sl->setMinimumSize(QSize(200,25));
    m_world_timer_sl->setMaximumSize(QSize(200,25));
    m_world_timer_sl->setValue(DEFAULT_TIMER_START);
    h1_1_1->addWidget(m_fps = new QLabel(QString("FPS: %1").arg(DEFAULT_TIMER_START)));
    h1_1_1->addWidget(m_start_stop = new QPushButton("Start/Stop",this));
    m_start_stop->setCheckable(true);
    h1_1->addLayout(h1_1_1);
    v->addLayout(h1_1);

    v->addWidget(m_view);
    QHBoxLayout *h2 = new QHBoxLayout();
    QGridLayout *pos = new QGridLayout();
    pos->addWidget(new QLabel("X = "),0,0);
    m_x = new QLabel( "--" );
    pos->addWidget(m_x,0,1);

//    QGridLayout *qgb1 = new QGridLayout();
//    QVBoxLayout *qv1 = new QVBoxLayout();
//    QHBoxLayout *qh3 = new QHBoxLayout();
//    m_gravity_sl = new QSlider(Qt::Horizontal);
//    qv1->addWidget(m_gravity_sl,10);
//    qh3->addWidget(new QLabel("gravity ="),Qt::AlignRight);
//    m_gravity = new QLineEdit("");
//    m_gravity->setStyleSheet("color:black;");
//    m_gravity->setMaximumSize(QSize(50,25));
//    qh3->addWidget(m_gravity,Qt::AlignRight);
//    qv1->addLayout(qh3,25);
//    qgb1->addLayout(qv1,0,0);

    QGridLayout *qgb1 = new QGridLayout();
    m_gravity_sl = new QSlider(Qt::Horizontal);
    qgb1->addWidget(new QLabel("gravity ="),0,0,Qt::AlignRight);
    m_gravity = new QLineEdit("");
    m_gravity->setStyleSheet("color:black;");
    m_gravity->setMaximumSize(QSize(50,25));
    qgb1->addWidget(m_gravity,0,1,Qt::AlignRight);

    qgb1->addWidget(new QLabel("friction ="),0,2,Qt::AlignRight);
    m_friction = new QLineEdit("");
    m_friction->setStyleSheet("color:black;");
    m_friction->setMaximumSize(QSize(50,25));
    qgb1->addWidget(m_friction,0,3,Qt::AlignRight);

    qgb1->addWidget(new QLabel("x_vinc ="),1,0,Qt::AlignRight);
    m_xvinc = new QLineEdit("");
    m_xvinc->setStyleSheet("color:black;");
    m_xvinc->setMaximumSize(QSize(50,25));
    qgb1->addWidget(m_xvinc,1,1,Qt::AlignRight);

    qgb1->addWidget(new QLabel("y_vinc ="),1,2,Qt::AlignRight);
    m_yvinc = new QLineEdit("");
    m_yvinc->setStyleSheet("color:black;");
    m_yvinc->setMaximumSize(QSize(50,25));
    qgb1->addWidget(m_yvinc,1,3,Qt::AlignRight);

    pos->addLayout(qgb1,0,3,Qt::AlignLeft);

    pos->addWidget(new QLabel("Y = "),1,0);
    m_y = new QLabel( "--" );
    pos->addWidget(m_y,1,1);
    pos->addWidget(new QLabel("tile # = "),2,0);
    m_tile = new QLabel( "--" );
    pos->addWidget(m_tile,2,1);
    pos->addWidget(new QLabel("tile_value = "),3,0);
    m_tile_value = new QLabel( "--" );
    pos->addWidget(m_tile_value,3,1);
    pos->addWidget(new QLabel("collision # = "),4,0);
    m_tile_collision = new QLabel( "--" );
    pos->addWidget(m_tile_collision,4,1);
    pos->addWidget(new QLabel("doors = "),5,0);
    m_portal_info = new QLabel( "--" );
    pos->addWidget(m_portal_info,5,1);
    pos->addWidget(new QLabel("sprite = "),6,0);
    m_sprite_pos = new QLabel( "--" );
    pos->addWidget(m_sprite_pos,6,1);
    QHBoxLayout *qh1 = new QHBoxLayout();
    qh1->addWidget(new QLabel("sprite.x = "));
    m_reposition_x = new QLineEdit(this);
    m_reposition_x->setStyleSheet("color:black;");
    m_reposition_x->setMaximumSize(QSize(50,25));
    qh1->addWidget(m_reposition_x);
    qh1->addWidget(new QLabel("sprite.y = "));
    m_reposition_y = new QLineEdit(this);
    m_reposition_y->setMaximumSize(QSize(50,25));
    m_reposition_y->setStyleSheet("color:black;");
    qh1->addWidget(m_reposition_y);
    m_repo_button = new QPushButton("Reposition",this);
    qh1->addWidget(m_repo_button);
    pos->addLayout(qh1,6,2);

    QHBoxLayout *qh0 = new QHBoxLayout();
    qh0->addWidget(m_npc_type=new QComboBox(this));
    m_npc_type->addItem("Carrot","Carrot");
    m_npc_type->addItem("Grass","Grass");
    qh0->addWidget(new QLabel("NPC_X:"));
    qh0->addWidget(m_npc_x=new QLineEdit(this));
    m_npc_x->setStyleSheet("color:black;");
    m_npc_x->setMinimumSize(QSize(50,25));
    m_npc_x->setMaximumSize(QSize(100,25));
    qh0->addWidget(new QLabel("NPC_Y:"));
    qh0->addWidget(m_npc_y=new QLineEdit(this));
    m_npc_y->setMinimumSize(QSize(50,25));
    m_npc_y->setMaximumSize(QSize(100,25));
    m_npc_y->setStyleSheet("color:black;");
    qh0->addWidget(m_spawn_npc=new QPushButton("Spawn",this));
    pos->addLayout(qh0,5,2);

    h2->addLayout(pos);
    h2->setAlignment(pos,Qt::AlignLeft);
    m_cb = new QComboBox(this);
    for(auto z : assets->zones())
        m_cb->addItem(z);
    h2->addWidget(m_cb);
    h2->setAlignment(m_cb,Qt::AlignHCenter);
    h2->addWidget(new QLabel("Music"));
    h2->addWidget(m_music = new QCheckBox(this));
    h2->addSpacerItem(new QSpacerItem(10,100));
    v->addLayout(h2);
    setLayout(v);



    signal_reposition(m_repo_button,this);
    connect(m_cb,SIGNAL(currentIndexChanged(const QString &)),this,SLOT(on_scene_option_changed(const QString &)));
    connect(m_gravity,SIGNAL(returnPressed()),this,SLOT(on_gravity_changed()));
    connect(m_gravity_sl,SIGNAL(valueChanged(int)),this,SLOT(on_gravity_sl_changed(int)));
    connect(m_friction,SIGNAL(returnPressed()),this,SLOT(on_friction_changed()));
    connect(m_xvinc,SIGNAL(returnPressed()),this,SLOT(on_xinc_changed()));
    connect(m_yvinc,SIGNAL(returnPressed()),this,SLOT(on_yinc_changed()));
    connect(view->get_scene(),SIGNAL(scene_changed(const QString &)),this,SLOT(on_zone_changed(const QString &)));
    connect(view->get_scene(),SIGNAL(mouse_pos(const QPointF &)),this,SLOT(on_mouse_moved(const QPointF&)));
    connect(view->get_scene(),SIGNAL(current_sprite(const Actor *)),this,SLOT(on_offer_sprite(const Actor *)));

    connect(m_spawn_npc,SIGNAL(clicked(bool)),this,SLOT(on_spawn_npc(bool)));
    connect(m_music,SIGNAL(stateChanged(int)),this,SLOT(on_music(int)));
    signal_timer(m_world_timer_sl,this);

    connect_start_stop(this);
}

/*!
 * \brief ViewWidget::view
 * \return
 */
ViewPtr ViewWidget::view() const
{
    return m_view;
}

/*!
 * \brief ViewWidget::setScene
 * \param scene
 *
 * Sets the scene for the graphics view
 */
void ViewWidget::setScene(Scene *scene)
{
   m_view->setScene(scene);
}


/*!
 * \brief ViewWidget::title
 * \param t
 */
void ViewWidget::title(const QString &t)
{
    m_title->setText(t);
}

/*!
 * \brief ViewWidget::title
 * \return
 */
QString ViewWidget::title() const
{
    return m_title->text();
}

/*!
 * \brief ViewWidget::scene
 * \return
 */
ScenePtr ViewWidget::scene() const
{
    return m_view->get_scene();
}

/*!
 * \brief ViewWidget::center_actor_in_view
 * \param a
 */
void ViewWidget::center_actor_in_view(const ActorPtr a)
{
    m_view->centerOn(a->sprite());
}

/*!
 * \brief ViewWidget::update
 *
 * update the view and the scene background,
 *
 * This looks like an expensive update, need to look more closely at
 * the updating process for QGraphicsScene's
 */
void ViewWidget::update()
{
   m_view->update();
   m_scene->update_background();
   m_view->fitInView(m_scene->sceneRect());
}

void ViewWidget::assets(AssetsManagerPtr assets)
{
  m_assets = assets;
}

AssetsManagerPtr ViewWidget::assets() const
{
  return m_assets;

}

/*!
 * \brief ViewWidget::signal_scene_changed
 * \param obj
 * \return
 */
ViewWidget *ViewWidget::connect_scene_changed(QObject *obj)
{
   connect(this,SIGNAL(scene_changed(const QString&)),obj,SLOT(load_scene(const QString &)));
   return this;
}

/*!
 * \brief ViewWidget::signal_reposition
 * \param obj1
 * \param obj2
 * \return
 */
ViewWidget *ViewWidget::signal_reposition(QObject *obj1, QObject *obj2)
{
  connect(obj1,SIGNAL(clicked(bool)),obj2,SLOT(on_reposition(bool)));
  return this;

}

/*!
 * \brief ViewWidget::signal_gravity_changed
 * \param obj
 * \return
 */
ViewWidget *ViewWidget::connect_gravity_changed(QObject *obj)
{
    connect(this,SIGNAL(gravity_changed(double)),obj,SLOT(on_gravity(double)));
    return this;
}

/*!
 * \brief ViewWidget::signal_frictiion_changed
 * \param obj
 * \return
 */
ViewWidget *ViewWidget::connect_friction_changed(QObject *obj)
{
    connect(this,SIGNAL(friction_changed(double)),obj,SLOT(on_friction(double)));
    return this;
}

/*!
 * \brief ViewWidget::signal_xinc_changed
 * \param obj
 * \return
 */
ViewWidget *ViewWidget::signal_xinc_changed(QObject *obj)
{
    connect(this,SIGNAL(xinc_changed(double)),obj,SLOT(on_x_increment(double)));
    return this;
}

/*!
 * \brief ViewWidget::signal_xinc_changed
 * \param obj
 * \return
 */
ViewWidget *ViewWidget::signal_yinc_changed(QObject *obj)
{
    connect(this,SIGNAL(yinc_changed(double)),obj,SLOT(on_y_increment(double)));
    return this;
}

/*!
 * \brief ViewWidget::connect_spawn_npc
 * \param obj
 * \return
 */
ViewWidget *ViewWidget::connect_spawn_npc(QObject *obj)
{
    connect(this,SIGNAL(spawn_npc(double,double,const QString &)),obj,SLOT(on_spawn_npc(double,double,const QString &)));
    return this;
}

/*!
 * \brief ViewWidget::connect_music
 * \param obj
 * \return
 */
ViewWidget *ViewWidget::connect_music(QObject *obj)
{
    connect(this,SIGNAL(music(bool)),obj,SLOT(on_music(bool)));
    return this;
}

/*!
 * \brief ViewWidget::connect_score
 * \param obj1
 * \param obj2
 * \return
 */
ViewWidget *ViewWidget::connect_score(QObject *obj1,QObject *obj2)
{
  connect(obj1,SIGNAL(signal_score(const QString&,int)),obj2,SLOT(on_score(const QString&,int)));
  return this;
}

/*!
 * \brief ViewWidget::signal_timer
 * \param obj1
 * \param obj2
 * \return
 */
ViewWidget *ViewWidget::signal_timer(QObject *obj1, QObject *obj2)
{
  connect(obj1,SIGNAL(valueChanged(int)),obj2,SLOT(on_timer_change(int)));
  return this;
}

/*!
 * \brief ViewWidget::connect_timer_change
 * \param obj1
 * \param obj2
 * \return
 */
ViewWidget *ViewWidget::connect_timer_change(QObject *obj1, QObject *obj2)
{
  connect(obj1,SIGNAL(timer_change(int)),obj2,SLOT(on_timer_change(int)));
  return this;
}

/*!
 * \brief ViewWidget::connect_focus
 * \param obj1
 * \param obj2
 * \return
 */
ViewWidget *ViewWidget::connect_focus(QObject *obj1, QObject *obj2)
{

  connect(obj1,SIGNAL(focus()),obj2,SLOT(on_focus()));
  return this;
}

/*!
 * \brief ViewWidget::connect_change_root
 * \param obj1
 * \param obj2
 * \return
 */
ViewWidget *ViewWidget::connect_change_root(QObject *obj1, QObject *obj2)
{
  connect(obj1,SIGNAL(change_root(const QString &)),obj2,SLOT(on_change_root(const QString &)));
  return this;
}

/*!
 * \brief ViewWidget::internal_signal_change_root
 * \param obj1
 * \return
 */
ViewWidget *ViewWidget::internal_signal_change_root(QObject *obj1)
{
  connect(m_change_asset_root,SIGNAL(clicked(bool)),obj1,SLOT(on_change_root(bool)));
  return this;
}

ViewWidget *ViewWidget::connect_start_stop(QObject *obj1)
{
  connect(m_start_stop,SIGNAL(clicked(bool)),obj1,SLOT(on_start_stop(bool)));
  return this;
}

/*!
 * \brief ViewWidget::map_collision
 * \param v
 * \return
 */
QString ViewWidget::map_collision(int v) const
{
    QString value = "none";
    switch(v)
    {
          case  1: value = "Top";break;
          case  2: value = "Right";break;
          case  3: value = "Top:Right";break;
          case  4: value ="Bottom";break;
          case  5: value = "Top:Bottom";break;
          case  6: value = "Right:Bottom";break;
          case  7: value = "Top:Right:Bottom";break;
          case  8: value = "Left";break;
          case  9: value = "Top:Left";break;
          case 10: value =  "Left:Right";break;
          case 11: value = "Top:Left:Right";break;
          case 12: value = "Left:Bottom";break;
          case 13: value = "Top:Left:Bottom";break;
          case 14: value = "Left:Right:Bottom";break;
          case 15: value = "Top:Left:Right:Bottom";break;
    }
    return value;

}

/*!
 * \brief ViewWidget::update_score_label
 * \param player
 * \param score
 */
void ViewWidget::update_score_label(const QString &player, int score)
{
    m_score_label->setText(QString("%1 : %2").arg(player).arg(score));
}

/*!
 * \brief ViewWidget::on_gravity_changed
 */
void ViewWidget::on_gravity_changed()
{
    emit gravity_changed(m_gravity->text().toDouble());
    emit focus();
}

/*!
 * \brief ViewWidget::on_gravity_sl_changed
 * \param value
 */
void ViewWidget::on_gravity_sl_changed(int value)
{
    double v = m_gravity->text().toDouble();
    v += value/10.0;
    m_gravity->setText(QString("%1").arg(v));

    emit gravity_changed(m_gravity->text().toDouble());
    emit focus();
}

/*!
 * \brief ViewWidget::on_friction_changed
 */
void ViewWidget::on_friction_changed()
{
   emit friction_changed(m_friction->text().toDouble());
   emit focus();
}

/*!
 * \brief ViewWidget::on_xinc_changed
 */
void ViewWidget::on_xinc_changed()
{
    emit xinc_changed(m_xvinc->text().toDouble());
    emit focus();
}

/*!
 * \brief ViewWidget::on_yinc_changed
 */
void ViewWidget::on_yinc_changed()
{
    emit yinc_changed(m_yvinc->text().toDouble());
    emit focus();
}

/*!
 * \brief ViewWidget::on_sceneChanged
 * \param zone
 */
void ViewWidget::on_scene_option_changed(const QString &zone)
{
    m_scene->scene_change(zone);
    emit scene_changed(zone);
    emit focus();
}

/*!
 * \brief ViewWidget::on_zone_changed
 * \param zone
 */
void ViewWidget::on_zone_changed(const QString &zone)
{
    disconnect(m_cb,SIGNAL(currentIndexChanged(const QString &)),this,SLOT(on_scene_option_changed(const QString &)));
    m_cb->setCurrentIndex(m_cb->findText(zone));
    connect(m_cb,SIGNAL(currentIndexChanged(const QString &)),this,SLOT(on_scene_option_changed(const QString &)));
    emit focus();
}

/*!
 * \brief ViewWidget::on_sprite_moved
 * \param pos
 *
 * Do something if the sprite moves
 */
void ViewWidget::on_sprite_moved(const QPointF &pos)
{
  Q_UNUSED(pos)
//    m_sprite_pos->setText(QString("(%1,%2)").arg(pos.x(),5,'f',1).arg(pos.y(),5,'f',1));
}

/*!
 * \brief ViewWidget::on_offer_sprite
 * \param a
 */
void ViewWidget::on_offer_sprite(const Actor *a)
{
   double x = a->x();
   double y = a->y();
   double center_x = a->get_center_x();
   double center_y = a->get_center_y();
   m_sprite_pos->setText(QString("(%1,%2) - (%3,%4)")
                         .arg(center_x,5,'f',1).arg(center_y,5,'f',1)
                         .arg(x,5,'f',1).arg(y,5,'f',1)
                         );
}

void ViewWidget::on_item_collision(Sprite* sprite, QGraphicsItem *item)
{
    qDebug() << sprite->name() << "hit" << item->data(0);
}

/*!
 * \brief ViewWidget::on_reposition
 * \param checked
 */
void ViewWidget::on_reposition(bool checked)
{
    Q_UNUSED(checked)

    double x = m_reposition_x->text().toDouble();
    double y = m_reposition_y->text().toDouble();
    m_scene->reposition_players(QPointF(x,y));
    emit focus();
}

/*!
 * \brief ViewWidget::on_spawn_npc
 * \param checked
 */
void ViewWidget::on_spawn_npc(bool checked)
{
    Q_UNUSED(checked)
    QString type = m_npc_type->currentText();
    double x = m_npc_x->text().toDouble();
    double y = m_npc_y->text().toDouble();
    emit spawn_npc(x,y,type);
    emit focus();
}

/*!
 * \brief ViewWidget::on_music
 * \param checked
 */
void ViewWidget::on_music(int checked)
{
  emit music(checked == Qt::Checked);
  emit focus();
}

/*!
 * \brief ViewWidget::on_score
 * \param name
 * \param score
 */
void ViewWidget::on_score(const QString &name, int score)
{
    update_score_label(name,score);
}

/*!
 * \brief ViewWidget::on_timer_change
 * \param tick
 */
void ViewWidget::on_timer_change(int tick)
{
  m_fps->setText(QString("FPS: %1").arg(tick));
  emit timer_change(tick);
}

/*!
 * \brief ViewWidget::on_change_root
 * \param checked
 */
void ViewWidget::on_change_root(bool checked)
{
    Q_UNUSED(checked)

    QString root = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    m_asset_root->text(),
                                                    QFileDialog::ShowDirsOnly
                                                    | QFileDialog::DontResolveSymlinks);
    if(root != "")
    {
       m_asset_root->setText(root);
       emit change_root(root);
      }
}

/*!
 * \brief ViewWidget::on_start_stop
 * \param checked
 */
void ViewWidget::on_start_stop(bool checked)
{
  Q_UNUSED(checked)
}

/*!
 * \brief ViewWidget::on_mouse_moved
 * \param pos
 */
void ViewWidget::on_mouse_moved(const QPointF &pos)
{
    assert(m_assets!=nullptr);
    int tile_size = m_assets->cell_size();
    double real_x = pos.x();
    double real_y = pos.y();
    int x = static_cast<int>(pos.x())/tile_size;
    int y = static_cast<int>(pos.y())/tile_size;
    int cols = m_assets->columns();
    int tile = y * cols + x;
    auto grid = m_assets->graphical_map();
    auto collisions = m_assets->collision_map();

    m_x->setText(QString("%1:%2").arg(x).arg(real_x,5,'f',1));
    m_y->setText(QString("%1:%2").arg(y).arg(real_y,5,'f',1));
    m_tile->setText(QString("%1").arg(tile));
    if(tile >= 0 && tile < grid.size())
        m_tile_value->setText(QString("%1").arg(grid.at(tile)));
    if(tile >= 0 && tile < collisions.size())
    {
        int coll_tile = collisions.at(tile);
        m_tile_collision->setText(QString("%1 - %2").arg(coll_tile).arg(map_collision(coll_tile)));
    }
    auto portals = m_assets->portals();
    QString p_info;
    for(auto portal : portals)
        p_info += QString(" (%1,%2)").arg(portal["x"]).arg(portal["y"]);
    m_portal_info->setText(QString("%1 %2").arg(portals.size()).arg(p_info));
}
