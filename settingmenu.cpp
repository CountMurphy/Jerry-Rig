#include "settingmenu.h"
#include "ui_settingmenu.h"
#include <iostream>
#include <QSettings>

using namespace std;

SettingMenu::SettingMenu(QWidget *parent, QSettings *settings) :
    QDialog(parent),
    ui(new Ui::SettingMenu)
{
    ui->setupUi(this);

    cerr<<"Settings Menu Created"<<endl;
}

SettingMenu::~SettingMenu()
{
    cerr<<"Destroying Settings Menu"<<endl;
    delete ui;
}
