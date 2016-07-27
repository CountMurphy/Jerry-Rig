#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "settingmenu.h"
#include<iostream>

using namespace std;

MainMenu::MainMenu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);

    //create connections
    connect(ui->action_Quit,SIGNAL(triggered(bool)),this,SLOT(Quit()));
    connect(ui->action_Prefrences,SIGNAL(triggered(bool)),this,SLOT(ShowPref()));
}

MainMenu::~MainMenu()
{
    delete ui;
}


void MainMenu::Quit()
{
    cout<<"Jerry-Rig is Exiting"<<endl;
    qApp->quit();
}

void MainMenu::ShowPref()
{
    SettingMenu *smenu=new SettingMenu(this);
    smenu->show();
}
