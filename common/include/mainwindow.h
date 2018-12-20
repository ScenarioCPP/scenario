#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "scenariomanager.h"
#include "viewwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    ScenarioManagerPtr m_sm;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    void start_scenario();
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
    void resizeEvent(QResizeEvent *e);
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);
    void closeEvent(QCloseEvent *event);

public slots:
    void on_viewInitialized(ViewWidgetPtr);

signals:
    void key_event(QKeyEvent *e);
    void resize_event(QResizeEvent *e);
    void signal_show_event(QShowEvent *e);
    void signal_hide_event(QHideEvent *e);
    void signal_close_event(QCloseEvent *e);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
