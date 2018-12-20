#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H
#include <QDialog>
#include <QtWidgets>
#include <QMap>
#include <QPair>

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QFileInfo;
class QTabWidget;
QT_END_NAMESPACE

typedef QMap<QString,QString> DataMap;
typedef QPair<QString,QString> DataPair;

//! [0]
class GeneralTab : public QWidget
{
    Q_OBJECT

public:
    explicit GeneralTab(const DataMap &settings, QWidget *parent = nullptr);

private slots:
    void title_changed(const QString &title);

signals:
    void settings_changed(const DataPair &dp);
};
//! [0]


//! [1]
class SettingsDialog : public QDialog
{
    Q_OBJECT
    DataMap m_settings;

public:
    explicit SettingsDialog(const DataMap &dm,QWidget *parent = nullptr);

    DataMap get_settings() const;

private:
    QTabWidget *tabWidget;
    QDialogButtonBox *buttonBox;

public slots:
    void change_setting(const DataPair &pair);
};
//! [1]


#endif // SETTINGSDIALOG_H
