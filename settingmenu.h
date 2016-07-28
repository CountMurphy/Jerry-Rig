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
    ~SettingMenu();

private:
    Ui::SettingMenu *ui;
};

#endif // SETTINGMENU_H
