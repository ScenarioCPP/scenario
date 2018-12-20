#ifndef SVGENGINE_H
#define SVGENGINE_H
#include "scenesharedlib_global.h"

#include <QDomDocument>
#include <QGraphicsSvgItem>
#include <QIODevice>
#include <QList>
#include <QMap>
#include <QSvgRenderer>
#include "scene.h"

typedef QList<QDomElement> SvgElementList;
typedef QMap<QString,QGraphicsSvgItem*> ItemMap;

class SCENESHAREDLIB_EXPORT SvgEngine
{
    QDomDocument m_domDocument;
    QSvgRenderer *m_renderer;
    ItemMap m_item_map;
public:
    SvgEngine(QString svgfile);
    bool read(QIODevice *device);
    bool write(QIODevice *device) const;
    SvgElementList walk(const QDomElement &node,const QString &key) const;
    QDomDocument get_doc() const;
    QDomElement get_root() const;
    ItemMap get_item_map() const;
    SvgElementList get_paths() const;
    void fill_scene(Scene* scene);

};


#endif // SVGENGINE_H
