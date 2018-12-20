#include "global_defines.h"
#include "npcharacter.h"
#include <QtMath>
#include <QDebug>


/*!
 * \brief NPCharacter::NPCharacter
 * \param sprite
 * \param parent
 */
NPCharacter::NPCharacter(SpritePtr sprite,QObject *parent) : Actor(sprite,parent) {
    signal_on_rendor(sprite);  // setup automatic rendering
    sprite->set_type(NPC);
}
