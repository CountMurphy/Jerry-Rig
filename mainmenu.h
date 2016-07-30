#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include<settingmenu.h>
#include<processmanager.h>

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
    void disposeProcess(int status);

private:
    Ui::MainMenu *ui;
    SettingMenu *smenu;
    ProcessManager *manager;
    QSettings *settings=new QSettings();
private slots:
    void ShowPref();
    void BeginWork();
};

#endif // MAINMENU_H
