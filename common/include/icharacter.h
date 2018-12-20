#ifndef ICHARACTER_H
#define ICHARACTER_H
#include "scenesharedlib_global.h"
#include <QtGlobal>

class SCENESHAREDLIB_EXPORT ICharacter
{
public:
    virtual void on_update(uint64_t t) = 0;
};

#endif // ICHARACTER_H
