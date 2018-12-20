#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    start_scenario();
}

/*!
 * \brief MainWindow::start_scenario
 *
 * creates and connects the ScenarioManager to window events
 */
void MainWindow::start_scenario()
{
    m_sm = (new ScenarioManager(this))   // ScenarioManager runs for the lifetime of the Window
            ->connect_show_event(this)
            ->connect_hide_event(this)
            ->connect_close_event(this)
            ->connect_view_initialized(this)
            ->connect_resize_event(this)
        ;
}

/*!
 * \brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow()
{
    delete m_sm;
}

/*!
 * \brief MainWindow::keyPressEvent
 * \param e
 */
void MainWindow::keyPressEvent(QKeyEvent *e)
{
    emit key_event(e);
}

/*!
 * \brief MainWindow::keyReleaseEvent
 * \param e
 */
void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
    emit key_event(e);
}

/*!
 * \brief MainWindow::resizeEvent
 * \param e
 */
void MainWindow::resizeEvent(QResizeEvent *e)
{
    QMainWindow::resizeEvent(e);
    emit resize_event(e);
}

/*!
 * \brief MainWindow::showEvent
 * \param event
 */
void MainWindow::showEvent(QShowEvent *event)
{
    QMainWindow::showEvent(event);
    emit signal_show_event(event);
}

/*!
 * \brief MainWindow::hideEvent
 * \param event
 */
void MainWindow::hideEvent(QHideEvent *event)
{
    QMainWindow::hideEvent(event);
    emit signal_hide_event(event);
}

/*!
 * \brief MainWindow::closeEvent
 * \param event
 */
void MainWindow::closeEvent(QCloseEvent *event)
 {
    emit signal_close_event(event);
    QMainWindow::closeEvent(event);
}

/*!
 * \brief MainWindow::on_viewInitialized
 * \param view
 *
 * Will be called on a signal from the ScenarioManager that the view is ready
 */
void MainWindow::on_viewInitialized(ViewWidgetPtr view)
{
    setCentralWidget(view);
    view->update();
}
