#ifndef ICHARACTER_H
#define ICHARACTER_H
#include <QtGlobal>

class ICharacter
{
public:
    virtual void on_update(uint64_t t) = 0;
};

#endif // ICHARACTER_H
