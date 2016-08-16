#ifndef SETTINGMENU_H
#define SETTINGMENU_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class SettingMenu;
}

class SettingMenu : public QDialog
{
    Q_OBJECT

public:
    explicit SettingMenu(QWidget *parent = 0, QSettings *settings=0);
    void ShowWizard();
    ~SettingMenu();

private:
    Ui::SettingMenu *ui;
    QSettings *_settings;

private slots:
    void OkClick();
};

#endif // SETTINGMENU_H
