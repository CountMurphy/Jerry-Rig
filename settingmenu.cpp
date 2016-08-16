#include "settingmenu.h"
#include "ui_settingmenu.h"
#include <iostream>
#include <QSettings>
#include <QMessageBox>

using namespace std;

SettingMenu::SettingMenu(QWidget *parent, QSettings *settings) :
    QDialog(parent),
    ui(new Ui::SettingMenu)
{
    ui->setupUi(this);
    this->_settings=settings;

    cerr<<"Settings Menu Created"<<endl;
    cerr<<"Loading Settings"<<endl;

    bool ffmpeg=this->_settings->value("FFMPEG").toBool();

    ui->ffmpeg->setChecked(ffmpeg);
    ui->libav->setChecked(!ffmpeg);

    //setup connections
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(OkClick()));
}

SettingMenu::~SettingMenu()
{
    cerr<<"Destroying Settings Menu"<<endl;
    delete ui;
}

void SettingMenu::OkClick()
{
    //save settings and such
    this->_settings->setValue("FFMPEG",ui->ffmpeg->isChecked());
    this->_settings->sync();
    cerr<<"Saving User Settings"<<endl;
}

void SettingMenu::ShowWizard()
{
    this->setModal(true);
    this->setVisible(true);
    this->_settings->setValue("hasSavedSettings",true);
    QMessageBox::information(this,"Welcome To Jerry-Rig!","Welcome to Jerry-Rig! You need to specify which base converting program you want to use. If you are unsure, just leave it checked for 'FFMPEG'");

    ui->ffmpeg->setChecked(true);// <3 ffmpeg
    ui->libav->setChecked(false);
}
