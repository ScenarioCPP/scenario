#include "svgengine.h"

#include <QDebug>
#include <QGraphicsSvgItem>
#include <QPainter>
#include <QSvgRenderer>
/*!
  This class creates an object that will parse, query and update svg files
  */

/*!
 * \brief SvgParser::SvgParser
 */
SvgEngine::SvgEngine(QString svgfile)
{
    read(new QFile(svgfile));
    m_renderer = new QSvgRenderer(svgfile);
}

/*!
 * \brief SvgParser::read
 * \param device
 * \return
 */
bool SvgEngine::read(QIODevice *device)
{
    QString errorStr;
    int errorLine;
    int errorColumn;

    if (!m_domDocument.setContent(device, true, &errorStr, &errorLine,
                                &errorColumn)) {
        qDebug() << errorStr;
        return false;
    }

    if(m_domDocument.documentElement().tagName() != "svg")
    {
        qDebug() << "Not an SVG file;";
        return false;
    }

    return true;
}

/*!
 * \brief SvgEngine::init_renderer
 * \param svgfile
 */
void SvgEngine::fill_scene(Scene* scene)
{
    QDomNodeList l = get_doc().elementsByTagName("path");
    for(int i=0;i < l.count();i++)
    {
        QDomElement el = l.at(i).toElement();
        QGraphicsSvgItem *it = new QGraphicsSvgItem();
        it->setSharedRenderer(m_renderer);
        it->setElementId(el.attributes().namedItem("id").nodeValue());
        it->setFlag(QGraphicsItem::ItemIsMovable,true);
        it->setFlag(QGraphicsItem::ItemIsSelectable,true);
        it->setToolTip(it->elementId());

        m_item_map.insert(el.attributes().namedItem("id").nodeValue(),it);
        QString start = el.attributes().namedItem("d").nodeValue().split(' ')[1];

        scene->addItem(it);
#if 0
                  qDebug() << el.tagName()
                           << el.attributes().namedItem("id").nodeName()
                           << el.attributes().namedItem("id").nodeValue()
                           << el.attributes().namedItem("style").nodeValue().split(';')
                           << el.attributes().namedItem("d").nodeValue().split(' ')[1].split(',')[0].toDouble();
#endif

        // Load your SVG
        // Prepare a QImage with desired characteritisc
        QImage image(static_cast<int>(it->boundingRect().width()*5), static_cast<int>(it->boundingRect().height()*5), QImage::Format_ARGB32);
        if(image.size().width() != 0)
        {
            image.fill(Qt::transparent);
            // Get QPainter that paints to the image
            QPainter painter(&image);
            QRectF r =it->boundingRect();
            m_renderer->render(&painter,it->elementId(),QRectF(r.top(),r.left(),r.width()*5,r.height()*5));
               // Save, image format based on file extension
            image.save(QString("/Users/paultonning/Pictures/svg/ant/%1.png").arg(it->elementId()));
        }
    }
}

/*!
 * \brief SvgParser::walk
 * \param node
 * \param key
 */
SvgElementList SvgEngine::walk(const QDomElement &node,const QString &key) const
{
    static SvgElementList els;
    QDomElement current = node;
    while (!current.isNull()) {
           if(current.tagName() == key) els.push_back(current);
           walk(current.firstChildElement(),key);
           current = current.nextSiblingElement();
    }
    return els;
}

/*!
 * \brief SvgParser::get_doc
 * \return
 */
QDomDocument SvgEngine::get_doc() const
{
    return m_domDocument;
}

/*!
 * \brief SvgParser::get_root
 * \return
 */
QDomElement SvgEngine::get_root() const
{
    return m_domDocument.documentElement();
}

ItemMap SvgEngine::get_item_map() const
{
    return m_item_map;
}

/*!
 * \brief SvgParser::get_paths
 * \return
 */
SvgElementList SvgEngine::get_paths() const
{
    return walk(get_root(),"path");
}

/*!
 * \brief SvgParser::write
 * \param device
 * \return
 *
 *  TODO
 */
bool SvgEngine::write(QIODevice *device) const
{
    Q_UNUSED(device)
    return true;
}
