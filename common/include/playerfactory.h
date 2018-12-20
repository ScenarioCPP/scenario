#ifndef PLAYERFACTORY_H
#define PLAYERFACTORY_H
#include "iactorfactory.h"
#include "assetsmanager.h"
#include "pcharacter.h"

class PlayerFactory : public IActorFactory
{
public:
  PlayerFactory(AssetsManagerPtr assets);
  virtual Actor* create(const QString &name);
  Actor *new_character(const QString &name);
};

#endif // PLAYERFACTORY_H
