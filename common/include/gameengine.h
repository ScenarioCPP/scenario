#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "scenesharedlib_global.h"

#include<QObject>
#include<QPointer>
#include<QtGlobal>
#include<QTimer>
#include <QEvent>


/* This is a fixed time step game loop. It can be used for any game and will ensure
that game state is updated at the same rate across different devices which is important
for uniform gameplay. Imagine playing your favorite game on a new phone and suddenly
it's running at a different speed. That would be a bad user experience, so we fix
it with a fixed step game loop. In addition, you can do things like frame dropping
and interpolation with a fixed step loop, which allow your game to play and look
smooth on slower devices rather than freezing or lagging to the point of unplayability. */
class SCENESHAREDLIB_EXPORT GameEngine : public QObject
{
    Q_OBJECT

    int m_time_step; // default 1000/30 = 30 frames per second;
    int m_accumulated_time; // Amount of time that's accumulated since the last update.
    qint64 m_time; // The most recent timestamp of loop execution.
    bool m_updated = false;  // Whether or not the update function has been called since the last cycle
    int m_timer_id;

protected:

    void run(qint64 time_stamp);
    virtual void timerEvent(QTimerEvent *event) override;

protected slots:
    void handle_run(QTimerEvent *event);

public:
    GameEngine(int time_step,QObject *parent = nullptr);
    GameEngine* connect_update(QObject*);
    void time_step(int step);
    int time_step() const;
    void start();
    void stop();

signals:
    void update(qint64 time);
    void render(qint64 time);

};

typedef QPointer<GameEngine> GameEnginePtr;
#endif // GAMEENGINE_H
