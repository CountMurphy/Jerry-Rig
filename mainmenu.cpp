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
    smenu=new SettingMenu(this,settings);

    //create combo box values
    ui->qualBox->addItem("High");
    ui->qualBox->addItem("Medium");
    ui->qualBox->addItem("Low");

    ui->sizeBox->addItem("Small (slow conversion)");
    ui->sizeBox->addItem("Med (med conversion)");
    ui->sizeBox->addItem("Large (fast conversion)");

    //create connections
    connect(ui->action_Quit,SIGNAL(triggered(bool)),this,SLOT(Quit()));
    connect(ui->action_Prefrences,SIGNAL(triggered(bool)),this,SLOT(ShowPref()));
    connect(ui->BTNConvert,SIGNAL(clicked(bool)),this,SLOT(BeginWork()));
}

MainMenu::~MainMenu()
{
    delete ui;
}


void MainMenu::Quit()
{
    cerr<<"Jerry-Rig is Exiting"<<endl;
    qApp->quit();
}

void MainMenu::ShowPref()
{
    smenu->show();
}

void MainMenu::BeginWork()
{
    manager=new ProcessManager(this,settings);
    //remove pesky close buttons and such
    manager->show();
}


void MainMenu::disposeProcess(int status)
{
    QString output=status!=0?"Processed failed":"Conversion Complete";
    cerr<<output.toStdString()<<endl;
    manager->close();
}
