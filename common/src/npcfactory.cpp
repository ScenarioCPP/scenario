#include "npcfactory.h"
#include "carrot.h"
#include<QDebug>


NPCFactory::NPCFactory(AssetsManagerPtr assets) : IActorFactory (assets)
{
}

/*!
 * \brief NPCFactory::create
 * \param name
 * \param assets
 * \return
 *  where snowflakes are created
 */
Actor *NPCFactory::create(const QString &name)
{
    Q_UNUSED(name);
    return nullptr;
}
/*!
 * \brief NPCFactory::new_character
 * \param type
 * \return
 * they just keep coming
 */
NPCharacter *NPCFactory::new_character(const QString &type)
{
    if(type == "Carrot")
    {
        auto conf = assets()->npc_map(type.toLower());
        auto npc = new Carrot(new Sprite(conf["width"].toInt(),conf["height"].toInt(),assets(),assets()->npc_animations()[type.toLower()]),nullptr);
        npc->tooltip(conf["tooltip"].toString());
        auto tileset = assets()->npc_animations();
        auto p_anim_index = assets()->npc_animation_index()[type.toLower()];
        for(auto m : {"twirl"})
            npc->add_animation(m,p_anim_index[m]);
        npc->sprite()->current_animation("twirl");
        return npc;
    }
    return nullptr;
}
