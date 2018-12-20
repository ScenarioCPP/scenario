#ifndef NPCFACTORY_H
#define NPCFACTORY_H
#include "iactorfactory.h"
#include "assetsmanager.h"
#include "npcharacter.h"

// aka academia
class NPCFactory : public IActorFactory
{
public:
  NPCFactory(AssetsManagerPtr assets);
  virtual Actor* create(const QString &name);
  NPCharacter *new_character(const QString &type);
};

#endif // NPCFACTORY_H
