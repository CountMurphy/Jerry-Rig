#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include<settingmenu.h>

namespace Ui {
class MainMenu;
}

class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = 0);
    ~MainMenu();

public slots:
    void Quit();

private:
    Ui::MainMenu *ui;
    SettingMenu *smenu;
private slots:
    void ShowPref();
};

#endif // MAINMENU_H
