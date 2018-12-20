#ifndef TILEMAPDIALOG_H
#define TILEMAPDIALOG_H
#include "scenesharedlib_global.h"

#include <QDialog>
#include "assetsmanager.h"

namespace Ui {
class TilemapDialog;
}

class SCENESHAREDLIB_EXPORT TilemapDialog : public QDialog
{
    Q_OBJECT

    QString     m_root;
    AssetsManager *m_assets;
public:
    explicit TilemapDialog(const QString &root,QWidget *parent = nullptr);
    ~TilemapDialog();

private:
    Ui::TilemapDialog *ui;
};

#endif // TILEMAPDIALOG_H
