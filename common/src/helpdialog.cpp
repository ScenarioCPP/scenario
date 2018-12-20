#include "helpdialog.h"
#include "ui_helpdialog.h"
#include <QVBoxLayout>
//#include <QWebEngineView>

HelpDialog::HelpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpDialog)
{
    ui->setupUi(this);
    /*!
      Windows has an issue with this and only works with VS
      so we'll work with it later
      */

    //QWebEngineView *view = new QWebEngineView(this);
    //view->load(QUrl("https://www.w3schools.com/"));
    //view->load(QUrl("https://boss.vvc.edu/cisclass/tonningp/steve/help"));
    //view->load(QUrl("https://boss.vvc.edu/cisclass/tonningp/wasm/tutorial1/main.html"));
    //view->setHtml("<h1>Help System</h1>");
    //QVBoxLayout *vbox = new QVBoxLayout(this);
    //vbox->addWidget(view);
    //vbox->addWidget(ui->buttonBox);
    //view->show();
}

HelpDialog::~HelpDialog()
{
    delete ui;
}
