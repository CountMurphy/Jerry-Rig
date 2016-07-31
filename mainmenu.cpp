#include<iostream>
#include<QFileDialog>
#include<QMessageBox>
#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "settingmenu.h"

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
    connect(ui->BTNOpen,SIGNAL(clicked(bool)),this,SLOT(diaglogIt()));
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
    if(this->inputLocal.count()==0)
    {
        QMessageBox::warning(this,"","You must first open a file to convert");
        return;
    }
    convParams params;
    params.Quality=ui->qualBox->currentIndex();
    params.Size=ui->sizeBox->currentIndex();
    params.input=this->inputLocal;
    manager=new ProcessManager(this,settings,&params);
    //remove pesky close buttons and such
    manager->setWindowFlags(Qt::Popup);
    manager->show();
}


void MainMenu::disposeProcess(int status)
{
    QString output;
    if(status!=0)
    {
        output="Processed failed";
        QMessageBox::information(this,"Failure","Video Conversion Failed!");
    }
    else
    {
        output="Conversion Complete";
        QMessageBox::information(this,"Finished","Video Converted!");
    }
    cerr<<output.toStdString()<<endl;
    manager->close();
}


void MainMenu::diaglogIt()
{
    inputLocal=QFileDialog::getOpenFileName(this,tr("Select video to convert"),QDir::homePath(),tr("Video Files (*.avi *.mpg *.mkv *.mpeg *.qt *.wmv)"));
}
