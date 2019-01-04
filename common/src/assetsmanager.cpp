#include "assetsmanager.h"

#include <QFile>
#include <QIODevice>
#include <QStringLiteral>
#include <QTextStream>
#include <QDebug>
#include <QDir>
#include <QMessageBox>
#include <QApplication>

const QString DEFAULT_FOLDER= "~/Code/qt/sceneario/assets";
AssetsManager::AssetsManager(const QString &root,const QString &world,QObject *parent) : QObject(parent)

{
    m_root =root;
    m_world = world;
    if(! QDir(m_root).exists())
    {
        QMessageBox msgBox;
        msgBox.setText("Assets folder cannot be found.");
        msgBox.setInformativeText("The assets folder cannot be found.  It needs to be in the location :\n\n"+DEFAULT_FOLDER+"\n\nThis probably means that the source code is not cloned in the right directory.  Make sure that you clone the Scenario repository in the directory Code/qt in your home directory.\n\nProgram will shut down now.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        Q_ASSERT(QDir(m_root).exists());

    }
    QString file =  m_root+"/worlds/"+world + "/config.json";
    if(! QFile(file).exists())
    {
        QMessageBox msgBox;
        msgBox.setText("Config file cannot be found.");
        msgBox.setInformativeText("The config file (" + file + ") cannot be found.\nProgram will shut down now.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        Q_ASSERT(QFile(file).exists());

    }
    load_default_config(file);

}



bool AssetsManager::load(const QString &zone,AssetsManager::SaveFormat saveFormat)
{

    QString f = m_root+"/maps/"+m_world + "/zone"+zone+".json";
    Q_ASSERT(QFile(f).exists());

    QFile loadFile(f);

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("AssetsManager::load -- couldn't open resource file");
        return false;
    }

    QByteArray loadData = loadFile.readAll();
    QJsonDocument loadDoc(saveFormat == Json
        ? QJsonDocument::fromJson(loadData)
        : QJsonDocument::fromBinaryData(loadData));
    Q_ASSERT(!loadData.isEmpty());
    read(loadDoc.object());

    return true;
}

/*!
 * \brief AssetsManager::read
 * \param json
 */
void AssetsManager::read(const QJsonObject &json)
{
    m_portals = toPortalContainer(json["portals"].toArray());
    m_columns = json["columns"].toInt();
    m_rows = json["rows"].toInt();
    m_cell_size = json["cell_size"].toInt();
    m_graphical_map = toMapContainer(json["graphical_map"].toArray());
    m_collision_map = toMapContainer(json["collision_map"].toArray());
    m_tile_map_name = json["tile_map_image"].toString();
    if(! QFile(m_tile_map_name).exists())
    {
           m_tile_map_name = m_root+"/maps/"+m_world+"/" + m_tile_map_name; // try local directory
           Q_ASSERT(QFile(m_tile_map_name).exists()); // if not Q_ASSERT and end
    }
    m_tile_map_image = PixmapPtr(new QPixmap(m_tile_map_name));
    m_scene_title = json["scene_title"].toString();
    m_player_map = make_player_map(json["player"].toObject());
    m_npc_map = make_player_map(json["npc"].toObject());
    m_player_animations = get_animations(json["player"].toObject());
    m_npc_animations = get_animations(json["npc"].toObject());
    m_player_animation_index = get_animation_index(json["player"].toObject());
    m_npc_animation_index = get_animation_index(json["npc"].toObject());
    m_zone = json["id"].toString();
}

/*!
 * \brief AssetsManager::write
 * \param json
 *
 * TODO
 */
void AssetsManager::write(QJsonObject &json) const
{
  Q_UNUSED(json);
   /*
    *
    // example
    QJsonObject playerObject;
    mPlayer.write(playerObject);
    json["player"] = playerObject;

    QJsonArray levelArray;
    foreach (const Level level, mLevels) {
        QJsonObject levelObject;
        level.write(levelObject);
        levelArray.append(levelObject);
    }
    json["levels"] = levelArray;
    *
    */
}

/*!
 * \brief AssetsManager::tile_map_image
 * \return
 */
PixmapPtr AssetsManager::tile_map_image()
{
  Q_ASSERT(m_tile_map_image != nullptr || m_tile_map_image->height() != 0|| m_tile_map_image->width() != 0);
  return m_tile_map_image;
}

void AssetsManager::load_default_config(const QString &file)
{
    QFile configFile(file);

    if (!configFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open file.");
    }

    QByteArray loadData = configFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(loadData));

    m_zones = toZonesList(loadDoc.object()["zones"].toArray());
    m_gravity = loadDoc.object()["gravity"].toDouble();
    m_friction = loadDoc.object()["friction"].toDouble();
    m_sounds = loadDoc.object()["sounds"].toObject();

}

/*!
 * \brief AssetsManager::graphical_map
 * \return
 */
TileMapContainer AssetsManager::graphical_map() const
{
    return m_graphical_map;
}

/*!
 * \brief AssetsManager::collision_map
 * \return
 */
TileMapContainer AssetsManager::collision_map() const
{
    return m_collision_map;
}

/*!
 * \brief AssetsManager::tileset
 * \return
 */
TileSetPtr AssetsManager::tileset() const
{
    return m_player_animations["player1"];
}

/*!
 * \brief AssetsManager::player_animations
 * \return
 */
AnimationMap AssetsManager::player_animations() const
{
    return m_player_animations;
}

/*!
 * \brief AssetsManager::player_animation_index
 * \return
 */
PlayerAnimationIndexMap AssetsManager::player_animation_index() const
{
    return m_player_animation_index;
}

/*!
 * \brief AssetsManager::npc_animation_index
 * \return
 */
PlayerAnimationIndexMap AssetsManager::npc_animation_index() const
{

    return m_npc_animation_index;
}

/*!
 * \brief AssetsManager::npc_animations
 * \return
 */
AnimationMap AssetsManager::npc_animations() const
{
  return m_npc_animations;
}

/*!
 * \brief AssetsManager::root
 * \return
 */
QString AssetsManager::root() const
{
  return m_root;
}

/*!
 * \brief AssetsManager::world
 * \return
 */
QString AssetsManager::world() const
{
  return m_world;
}

/*!
 * \brief AssetsManager::world
 * \param w
 */
void AssetsManager::world(const QString &w)
{
    m_world = w;
}

/*!
 * \brief AssetsManager::change_root
 * \param root
 */
void AssetsManager::change_root(const QString &root)
{
    Q_ASSERT(QDir(root).exists());
    m_root = root;
    qDebug() << "AssetsManager::change_root" << root << " -- currently unimplemented";
    //load_default_config(root);
}

/*!
 * \brief AssetsManager::zone
 * \return
 */
QString AssetsManager::zone() const
{
    return m_zone;
}

/*!
 * \brief AssetsManager::scene_title
 * \return
 */
QString AssetsManager::scene_title() const
{
    return m_scene_title;
}

/*!
 * \brief AssetsManager::portals
 * \return
 */
PortalContainer AssetsManager::portals() const
{
    return m_portals;
}

/*!
 * \brief AssetsManager::zones
 * \return
 */
ZonesList AssetsManager::zones() const
{
    return m_zones;
}

/*!
 * \brief AssetsManager::columns
 * \return
 */
int AssetsManager::columns() const
{
   return m_columns;
}

/*!
 * \brief AssetsManager::rows
 * \return
 */
int AssetsManager::rows() const
{
    return m_rows;
}

/*!
 * \brief AssetsManager::cell_size
 * \return
 */
int AssetsManager::cell_size() const
{
    return m_cell_size;
}

/*!
 * \brief AssetsManager::tile_map_name
 * \return
 */
QString AssetsManager::tile_map_name() const
{
  return m_tile_map_name;
}

/*!
 * \brief AssetsManager::player_map
 * \return
 */
QJsonObject AssetsManager::player_map(const QString &name) const
{
  return m_player_map[name][name].toObject();
}

/*!
 * \brief AssetsManager::npc_map
 * \param name
 * \return
 */
QJsonObject AssetsManager::npc_map(const QString &name) const
{
  return m_npc_map[name][name].toObject();
}

/*!
 * \brief AssetsManager::grid_rect
 * \return
 */
QRectF AssetsManager::grid_rect() const
{
  return QRectF(QPointF(0,0),QSizeF(world_width(),world_height()));
}

/*!
 * \brief AssetsManager::world_width
 * \return
 */
int AssetsManager::world_width() const
{
    return columns() * cell_size();
}

/*!
 * \brief AssetsManager::world_height
 * \return
 */
int AssetsManager::world_height() const
{
  return rows() * cell_size();
}

/*!
 * \brief AssetsManager::get_sound
 * \param type
 * \param $name
 * \return
 */
QUrl AssetsManager::get_sound(const QString &type, const QString &name)
{
    QString s = m_sounds[type].toObject()[name].toString();
    return QUrl("file:"+m_root+"/sounds/"+type+ "/" +s);
}

/*!
 * \brief AssetsManager::background_sound
 * \param name
 * \return
 */
QUrl AssetsManager::background_sound(const QString &name)
{
    return get_sound("background",name);
}

/*!
 * \brief AssetsManager::jump_sound
 * \param name
 * \return
 */
QUrl AssetsManager::jump_sound(const QString &name)
{
    return get_sound("jump",name);
}

/*!
 * \brief AssetsManager::pickup_sound
 * \param name
 * \return
 */
QUrl AssetsManager::pickup_sound(const QString &name)
{
    return get_sound("pickup",name);
}

/*!
 * \brief AssetsManager::gravity
 * \return
 */
double AssetsManager::gravity() const
{
    return m_gravity;
}

/*!
 * \brief AssetsManager::friction
 * \return
 */
double AssetsManager::friction() const
{
    return m_friction;
}

/*!
 * \brief AssetsManager::toMapContainer
 * \param a
 * \return
 */
TileMapContainer AssetsManager::toMapContainer(const QJsonArray &a)
{
    TileMapContainer map;
    for(auto i : a)
        map.push_back(i.toInt());
    return map;
}

/*!
 * \brief AssetsManager::toPortalContainer
 * \param portals
 * \return
 */
PortalContainer AssetsManager::toPortalContainer(const QJsonArray &portals)
{
    PortalContainer pc;
    for(auto portal : portals)
        if(portal.isObject())
        {
            PortalMap p;
            QString f("%1");
            p.insert("destination_x",f.arg(portal.toObject()["destination_x"].toDouble()));
            p.insert("destination_y",f.arg(portal.toObject()["destination_y"].toDouble()));
            p.insert("destination_zone",f.arg(portal.toObject()["destination_zone"].toString()));
            p.insert("height",f.arg(portal.toObject()["height"].toInt()));
            p.insert("width",f.arg(portal.toObject()["width"].toInt()));
            p.insert("x",f.arg(portal.toObject()["x"].toInt()));
            p.insert("y",f.arg(portal.toObject()["y"].toInt()));
            pc.push_back(p);
        }

    return pc;
}

/*!
 * \brief AssetsManager::toZonesList
 * \param a
 * \return
 */
ZonesList AssetsManager::toZonesList(const QJsonArray &zones)
{
    ZonesList zl;
    for(auto zone : zones)
        if(zone.isString())
            zl.push_back(zone.toString());
    return zl;
}

/*!
 * \brief AssetsManager::get_player_animation
 * \param a
 * \return
 */
AnimationMap AssetsManager::get_animations(const QJsonObject &character)
{
    AnimationMap m;

    for(auto p :character.keys())
    {
        auto c = character[p].toObject();
        TileSetPtr ts(new TileSet(m_columns,m_cell_size));
        ts->set_frames(FrameContainerPtr(new FrameContainer()));
        for(auto anim_f : c["animations"].toArray())
        {
            if(anim_f.isArray())
            {
                int x = anim_f.toArray()[0].toInt();
                int y = anim_f.toArray()[1].toInt();
                int width = anim_f.toArray()[2].toInt();
                int height = anim_f.toArray()[3].toInt();
                int x_offset = anim_f.toArray()[4].toInt();
                int y_offset = anim_f.toArray()[5].toInt();
                FramePtr frame(new Frame(x,y,width,height,x_offset,y_offset));
                ts->add_frame(frame);
            }
        }
        m.insert(p,ts);
    }

    return m;
}

/*!
 * \brief AssetsManager::get_animation_index
 * \param character
 * \return
 */
PlayerAnimationIndexMap AssetsManager::get_animation_index(const QJsonObject &character) const
{
     PlayerAnimationIndexMap p_map;
     for(auto p :character.keys())
     {
         AnimationIndexContainer m;
         auto c = character[p].toObject();
         auto ai = c["animation_index"].toObject();
         for(auto anim_key : ai.keys())
         {
                if(ai[anim_key].isArray())
                {
                    AnimationIndex v;
                    for(auto i : ai[anim_key].toArray())
                        v.push_back(i.toInt());
                    m.insert(anim_key,v);
                }
         }
         p_map.insert(p,m);
     }
     return p_map;

}

/*!
 * \brief AssetsManager::make_player_map
 * \param p
 * \return
 */
PlayerMap AssetsManager::make_player_map(const QJsonObject &p) const
{
    PlayerMap m;
    for(auto key : p.keys())
    {
        m.insert(key,p);
    }
    return m;
}
