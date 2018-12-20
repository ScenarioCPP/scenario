#include "global_defines.h"
#include "tilemapdialog.h"
#include "ui_tilemapdialog.h"
#include <QGraphicsPixmapItem>
#include <QtMath>
#include <QDir>
#include <QDebug>


TilemapDialog::TilemapDialog(const QString &root,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TilemapDialog)
{

    ui->setupUi(this);
    m_root = root;
    m_assets = new AssetsManager(m_root,"rabbit-trap");
    m_assets->load("00");
    ui->graphicsView->setMouseTracking(true);
    QString a  = m_assets->tile_map_name();
    int cell_size = m_assets->cell_size();
    QPixmap pm(a);
    QGraphicsScene *scene = new QGraphicsScene(QRectF(QPointF(0,0),QSizeF(pm.width(),pm.height())));


    for(int row=0;row<pm.height()/cell_size;row++)
        for(int col=0;col<pm.width()/cell_size;col++)
        {
            QRectF rect(QPointF(col*cell_size,row*cell_size),QSize(cell_size,cell_size));
            QPen pen(Qt::black);
            QBrush brush(Qt::transparent);
            auto item = scene->addRect(rect,pen,brush);
            item->setFlag(QGraphicsItem::ItemIsSelectable,true);
        }
    ui->graphicsView->setScene(scene);
    ui->graphicsView->scale(4.0,4.0);
}

TilemapDialog::~TilemapDialog()
{
    delete ui;
}
