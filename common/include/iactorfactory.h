#ifndef IACTORFACTORY_H
#define IACTORFACTORY_H
#include "scenesharedlib_global.h"

#include "actor.h"
#include "assetsmanager.h"

class SCENESHAREDLIB_EXPORT IActorFactory
{
  AssetsManagerPtr m_assets;

protected:
  virtual Actor *create(const QString &name) = 0;

public:
  IActorFactory(AssetsManagerPtr assets) : m_assets(assets) {}
  AssetsManagerPtr assets() const {return m_assets;}
  virtual ~IActorFactory(){}
};

#endif // IACTORFACTORY_H
