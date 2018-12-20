#ifndef PORTAL_H
#define PORTAL_H

#include <QObject>
#include "actor.h"

class Portal : public QObject
{
    Q_OBJECT

    double m_x;
    double m_y;
    double m_width;
    double m_height;
    double m_destination_x;
    double m_destination_y;
    QString m_destination_zone;
public:

    explicit Portal(QObject *parent=nullptr);
    explicit Portal(const PortalMap &p,QObject *parent=nullptr);
    virtual ~Portal();
    bool collide_object(ActorPtr actor) const;
    double get_left() const;
    double get_right() const;
    double get_top() const;
    double get_bottom() const;
    double destination_x() const;
    double destination_y() const;
    QString destination_zone() const;
    QString to_string() const;
};

typedef QPointer<Portal> PortalPtr;

#endif // PORTAL_H
