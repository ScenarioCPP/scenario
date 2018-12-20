

#include <QtWidgets>

#include "settingsdialog.h"

//! [0]
SettingsDialog::SettingsDialog(const DataMap &dm,QWidget *parent)
    : QDialog(parent)
{

    m_settings = dm;
    tabWidget = new QTabWidget;
    tabWidget->addTab(new GeneralTab(dm,this), tr("General"));
//! [0]

//! [1] //! [2]
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
//! [1] //! [3]
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
//! [2] //! [3]

//! [4]
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);
//! [4]

//! [5]
    setWindowTitle(tr("Settings"));
}

DataMap SettingsDialog::get_settings() const
{
    return m_settings;
}

void SettingsDialog::change_setting(const DataPair &pair)
{
   m_settings.insert(pair.first,pair.second);
}

//! [5]

//! [6]
GeneralTab::GeneralTab(const DataMap &settings, QWidget *parent)
    : QWidget(parent)
{
    QLabel *titleLabel = new QLabel(tr("Title:"));
    QLineEdit *title = new QLineEdit(settings["scene-title"],this);
    title->setStyleSheet("color:black;"); // MacOSX bug fix


    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(title);
    mainLayout->addStretch(1);
    setLayout(mainLayout);

    connect(title,&QLineEdit::textChanged,this,&GeneralTab::title_changed);
    connect(this,SIGNAL(settings_changed(const DataPair&)),parent,SLOT(change_setting(const DataPair&)));
}

void GeneralTab::title_changed(const QString &title)
{
    emit settings_changed(DataPair("scene-title",title));
}
//! [6]

