#ifndef HELPDIALOG_H
#define HELPDIALOG_H
#include "scenesharedlib_global.h"

#include <QDialog>

namespace Ui {
class HelpDialog;
}

class SCENESHAREDLIB_EXPORT HelpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HelpDialog(QWidget *parent = nullptr);
    ~HelpDialog();

private:
    Ui::HelpDialog *ui;
};

#endif // HELPDIALOG_H
