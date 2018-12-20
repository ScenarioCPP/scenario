#ifndef SCENE_H
#define SCENE_H
#include "scenesharedlib_global.h"

#include <QPointer>
#include<QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include<QPainterPath>
#include<QPixmap>
#include<QVector>
#include<vector>
#include "assetsmanager.h"
#include "actor.h"

typedef QVector<int> TileMapContainer;
typedef QVector<QRectF> TileRectContainer;
typedef QPointer<TileRectContainer> TileRectContainerPtr;
typedef QPixmap Picture;
typedef QImage Image;
typedef QSharedPointer<Image> ImagePtr;


class SCENESHAREDLIB_EXPORT Scene : public QGraphicsScene
{
    Q_OBJECT
    AssetsManagerPtr m_assets;
    int m_rows;
    int m_columns;
    int m_tile_size;
    TileMapContainer m_map;
    TileRectContainerPtr m_scene_tiles;
    bool m_show_grid;
    QBrush m_bkg_brush;
    Image m_bkg_img;
    Image m_grid_img;
    QPainterPath m_grid_numbers;
    bool m_animating;
    QString m_world;
    QString m_zone;
    bool m_update;


public:

    Scene(QObject *parent = nullptr);
    Scene(const QString &world,AssetsManagerPtr assets,QObject *parent = nullptr);
    void add_actor(ActorPtr a);
    void set_background(QString filename);
    void set_background(QColor color);
    void set_tile_map(TileMapContainer map);
    TileMapContainer get_tile_map() const;
    void show_grid(bool toggle);
    bool animating() const;
    void animating(bool a);
    void reposition_players(const QPointF& p);
    void connect_teleport(ActorPtr a);

public slots:
    virtual void update_background();

protected:
    void create_bk_image(const QString &zone);
    void create_grid(const QString &zone);
    virtual void drawBackground(QPainter *painter, const QRectF &rect) override;
    virtual void dragMoveEvent(QGraphicsSceneDragDropEvent *event) override;


public slots:
    void scene_change(const QString &zone);

protected slots:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    virtual void sprite_move(const QPointF &pos);
    virtual void offer_sprite(const Actor *a);

signals:
    void scene_changed(const QString &zone);
    void mouse_pos(const QPointF &pos);
    void sprite_pos(const QPointF &pos);
    void current_sprite(const Actor *a);
    void move_player(const QPointF &);
};

typedef QPointer<Scene> ScenePtr;
#endif // SCENE_H
