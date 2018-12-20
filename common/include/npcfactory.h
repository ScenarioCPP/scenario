#ifndef NPCFACTORY_H
#define NPCFACTORY_H
#include "scenesharedlib_global.h"

#include "iactorfactory.h"
#include "assetsmanager.h"
#include "npcharacter.h"

class SCENESHAREDLIB_EXPORT NPCFactory : public IActorFactory
{
// aka academia
public:
  NPCFactory(AssetsManagerPtr assets);
  virtual Actor* create(const QString &name);
  NPCharacter *new_character(const QString &type);
};

#endif // NPCFACTORY_H
