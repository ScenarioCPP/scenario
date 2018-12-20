#include "view.h"

/*!
 * \brief View::View
 * \param parent
 */
View::View(QWidget *parent) : QGraphicsView (parent)
{
  setRenderHints(QPainter::Antialiasing);
  setMouseTracking(true);
}

/*!
 * \brief View::View
 * \param scene
 * \param parent
 */
View::View(ScenePtr scene, QWidget *parent) : QGraphicsView(scene,parent),m_scene(scene)
{
  setRenderHints(QPainter::Antialiasing);
  setMouseTracking(true);
}

ScenePtr View::get_scene() const
{
  return m_scene;
}

void View::connect_keypress_event(QObject *obj)
{
  connect(this,SIGNAL(signal_key_event(QKeyEvent *)),obj,SLOT(on_key_event(QKeyEvent *)));
}

/*!
 * \brief View::dragMoveEvent
 * \param event
 */
void View::dragMoveEvent(QDragMoveEvent *event)
{
    QGraphicsView::dragMoveEvent(event);
    qDebug() << "View::dragMoveEvent" << event->pos();
}

/*!
 * \brief View::keyPressEvent
 * \param e
 */
void View::keyPressEvent(QKeyEvent *e)
{
    emit signal_key_event(e);
}

/*!
 * \brief View::keyReleaseEvent
 * \param e
 */
void View::keyReleaseEvent(QKeyEvent *e)
{
    emit signal_key_event(e);
}
