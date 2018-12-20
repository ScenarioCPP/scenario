#ifndef VIEW_H
#define VIEW_H
#include "scenesharedlib_global.h"

#include <QWidget>
#include <QGraphicsView>
#include <QDragMoveEvent>
#include <QPointer>

#include "scene.h"

class SCENESHAREDLIB_EXPORT View : public QGraphicsView
{
    Q_OBJECT
    ScenePtr m_scene;
public:

    View(QWidget *parent = nullptr);

    View(ScenePtr scene, QWidget *parent = nullptr);

    ScenePtr get_scene() const;
    void connect_keypress_event(QObject *obj);

protected:
    virtual void dragMoveEvent(QDragMoveEvent *event) override;
signals:
    void signal_key_event(QKeyEvent*);
public slots:
    void keyPressEvent(QKeyEvent *e) override;
    void keyReleaseEvent(QKeyEvent *e) override;
};

typedef QPointer<View> ViewPtr;

#endif // VIEW_H
