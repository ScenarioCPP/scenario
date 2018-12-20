#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "scenesharedlib_global.h"

#include <QObject>
#include <QPointer>
#include <QKeyEvent>
#include <QMap>

typedef QMap<QString,int> ButtonKeyMap;

class SCENESHAREDLIB_EXPORT ButtonInput : public QObject
{
    Q_OBJECT

    bool m_active,m_down;

public:
    ButtonInput(QObject *parent=nullptr) : QObject(parent)
    {
        m_active = m_down = false;
    }

    void getInput(bool down) {

        if (m_down != down) m_active = down;
        m_down = down;
    }

    bool down() {return m_down;}
    bool active() {return m_active;}
    void active(bool a) {m_active=a;}
};
typedef QPointer<ButtonInput> ButtonInputPtr;
typedef QMap<int,ButtonInputPtr> InputButtonMap;

class Controller : public QObject
{
    Q_OBJECT
    ButtonKeyMap m_button_key_map;

    ButtonInputPtr m_down;
    ButtonInputPtr m_left;
    ButtonInputPtr m_right;
    ButtonInputPtr m_up;
    InputButtonMap m_input_button_map;

public:
    explicit Controller(const ButtonKeyMap &bk_map,QObject *parent = nullptr);
    ButtonKeyMap button_key_map() const;
    void button_map(const ButtonKeyMap &map);
    ButtonInputPtr btn_down();
    ButtonInputPtr btn_left();
    ButtonInputPtr btn_right();
    ButtonInputPtr btn_up();
    void key_down_up(QKeyEvent *e);

signals:
    void btn_down_signal(int);
    void btn_left_signal(int);
    void btn_right_signal(int);
    void btn_up_signal(int);
public slots:
};

typedef QPointer<Controller> ControllerPtr;
#endif // CONTROLLER_H
