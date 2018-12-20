#ifndef ASSETSMANAGER_H
#define ASSETSMANAGER_H
#include "scenesharedlib_global.h"

#include <QObject>
#include <QString>
#include <QPixmap>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMap>
#include <QVector>
#include <QPair>
#include <QPointer>
#include <QUrl>
#include "frame.h"
#include "tileset.h"

typedef QVector<int> TileMapContainer;
typedef QSharedPointer<TileMapContainer> TileMapContainerPtr;
typedef QSharedPointer<QPixmap> PixmapPtr;
typedef QMap<QString,QString> PortalMap;
typedef QVector<PortalMap> PortalContainer;
typedef QVector<QString> ZonesList;

typedef QMap<QString,TileSetPtr> AnimationMap;
typedef QVector<int> AnimationIndex;
typedef QPair<QString,AnimationIndex> AnimationIndexPair;
typedef QMap<QString,AnimationIndex> AnimationIndexContainer;
typedef QMap<QString,AnimationIndexContainer> PlayerAnimationIndexMap;
typedef QJsonObject PlayerObject;
typedef QMap<QString,PlayerObject> PlayerMap;

class SCENESHAREDLIB_EXPORT AssetsManager : public QObject
{
    Q_OBJECT

    QString m_root;
    QString m_zone;
    QString m_world;
    ZonesList m_zones;
    QJsonObject m_sounds;
    PixmapPtr m_tile_map_image;
    QString m_tile_map_name;
    TileMapContainer m_graphical_map;
    TileMapContainer m_collision_map;
    PortalContainer m_portals;
    TileSetPtr m_tileset;
    AnimationMap m_player_animations;
    PlayerAnimationIndexMap m_player_animation_index;
    AnimationMap m_npc_animations;
    PlayerAnimationIndexMap m_npc_animation_index;
    QString m_tile_map;
    QString m_scene_title;
    PlayerMap m_player_map;
    PlayerMap m_npc_map;
    int m_columns;
    int m_rows;
    int m_cell_size;
    double m_friction;
    double m_gravity;

public:
    enum SaveFormat {
       Json, Binary
    };
    explicit AssetsManager(const QString &root,const QString &world,QObject *parent = nullptr);
    PixmapPtr tile_map_image();
    void load_default_config(const QString &file);
    bool load(const QString &zone,AssetsManager::SaveFormat saveFormat = Json);
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
    TileMapContainer graphical_map() const;
    TileMapContainer collision_map() const;
    TileSetPtr tileset() const;
    AnimationMap player_animations() const;
    PlayerAnimationIndexMap player_animation_index() const;
    PlayerAnimationIndexMap npc_animation_index() const;
    AnimationMap npc_animations() const;
    QString root() const;
    QString world() const;
    void world(const QString &w);
    void change_root(const QString &root);
    QString zone() const;
    QString scene_title() const;
    PortalContainer portals() const;
    ZonesList zones() const;
    int columns() const;
    int rows() const;
    int cell_size() const;
    QString tile_map_name() const;
    QJsonObject player_map(const QString &name) const;
    QJsonObject npc_map(const QString &name) const;
    QRectF grid_rect() const;
    int world_width() const;
    int world_height() const;
    QUrl get_sound(const QString &type,const QString &name);
    QUrl background_sound(const QString &name);
    QUrl jump_sound(const QString &name);
    QUrl pickup_sound(const QString &name);
    double gravity() const;
    double friction() const;



protected:
    TileMapContainer toMapContainer(const QJsonArray &a);
    PortalContainer toPortalContainer(const QJsonArray &a);
    ZonesList toZonesList(const QJsonArray &a);
    AnimationMap get_animations(const QJsonObject &a);
    PlayerAnimationIndexMap get_animation_index(const QJsonObject &character) const;
    PlayerMap make_player_map(const QJsonObject &p) const;
};

typedef QPointer<AssetsManager> AssetsManagerPtr;

#endif // ASSETSMANAGER_H
