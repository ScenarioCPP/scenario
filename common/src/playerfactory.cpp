#include "playerfactory.h"
#include<QDebug>

PlayerFactory::PlayerFactory(AssetsManagerPtr assets) : IActorFactory (assets) { }

Actor *PlayerFactory::create(const QString &name)
{
        auto conf = assets()->player_map(name);
        assert(conf.size() !=0);
        ButtonKeyMap key_map;
        key_map.insert("Left",Qt::Key_A);
        key_map.insert("Right",Qt::Key_D);
        key_map.insert("Down",Qt::Key_S);
        key_map.insert("Up",Qt::Key_Space);
        PCharacter *player = new PCharacter(new Sprite(conf["width"].toInt(),conf["height"].toInt(),assets(),
                                            assets()->player_animations()[name]),new Collider(),new Controller(key_map),nullptr);
        assert(player->sprite() != nullptr);
        player->velocity_inc(conf["velocity"].toDouble());
        player->jump_height(conf["jumppower"].toDouble());
        player->gravity(conf["gravity"].toDouble());
        player->friction(conf["friction"].toDouble());
        player->tooltip(conf["tooltip"].toString());
        player->current_animation(conf["start_animation"].toString());
        auto p_anim_index = assets()->player_animation_index()[name];
        for(auto m : {"idle-left","jump-left","move-left","idle-right","jump-right","move-right"})
        {
            // add_animation requires a name for the animation and the index numbers in the tile set
            player->add_animation(m,p_anim_index[m]);
        }
        return player;
}

Actor *PlayerFactory::new_character(const QString &name)
{
    return create(name.toLower());
}
