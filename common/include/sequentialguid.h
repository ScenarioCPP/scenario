#ifndef SEQUENTIALGUID_H
#define SEQUENTIALGUID_H
#include "scenesharedlib_global.h"

#include <QObject>
#include <QUuid>
#include <QByteArray>
#include <QDateTime>
#include <QDataStream>
#include <QTime>


/**
 * @brief The SequentialGUID class - define a class for creating a Sequential GUID
 */
class SCENESHAREDLIB_EXPORT SequentialGUID : public QObject
{
    Q_OBJECT
public:
    explicit SequentialGUID(QObject *parent = nullptr);

    enum SequentialGUIDType {
        SequentialAsString = 0,
        SequentialAsBinary = 1,
        SequentialAtEnd = 2
    };

    static QUuid GetSequentialGUID(SequentialGUIDType guid_type);


signals:

public slots:

private:
    static void InitRand();
    static int randInt(int low, int high);

    static bool rand_init;
};

#endif // SEQUENTIALGUID_H
