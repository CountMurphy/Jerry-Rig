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
    if(!settings->value("hasSavedSettings").toBool())
    {
        //first run time!
        cerr<<"Showing first Run wizard"<<endl;
        smenu->ShowWizard();
    }

    ui->lbl_version->setText("Version: " + QString::number(this->versionNumber));


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
    connect(ui->BTNConvert,SIGNAL(clicked(bool)),this,SLOT(ConvertClick()));
    connect(ui->BTNOpen,SIGNAL(clicked(bool)),this,SLOT(diaglogIt()));
    connect(ui->chkBatch,SIGNAL(clicked(bool)),this,SLOT(toggleBatch(bool)));
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

void MainMenu::ConvertClick()
{
    if(this->inputLocal.count()==0)
    {
        QMessageBox::warning(this,"","You must first open a file to convert");
        return;
    }

    if(QFile::exists(inputLocal+"_converted.mkv"))
    {
        cerr<<"File Exits warning"<<endl;
        QMessageBox overwriteDialog;
        int retVal=overwriteDialog.warning(this,"File Exists", inputLocal+"_converted.mkv" + " already exists. Overwrite?",QMessageBox::Yes,QMessageBox::No);
        if(retVal!=QMessageBox::Yes)
        {
            return;
        }
        QFile::remove(inputLocal+"_converted.mkv");
    }
    BeginWork();

}


void MainMenu::BeginWork()
{
    convParams params;
    params.Quality=ui->qualBox->currentIndex();
    params.Size=ui->sizeBox->currentIndex();
    params.input=this->inputLocal;

    manager=new ProcessManager(this,settings,&params);
    //remove pesky close buttons and such
    manager->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
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
    if(ui->chkBatch->checkState()==Qt::Checked)
    {
        inputLocal=QFileDialog::getExistingDirectory(this,"Select directory for batch processing",QDir::homePath());
    }else{
        inputLocal=QFileDialog::getOpenFileName(this,tr("Select video to convert"),QDir::homePath(),tr("Video Files (*.avi *.mpg *.mkv *.mpeg *.qt *.wmv)"));
    }
}


void MainMenu::toggleBatch(bool isBatch)
{
    if(isBatch)
    {
        ui->BTNOpen->setText("Choose Directory");
    }else{
        ui->BTNOpen->setText("Open");
    }

    if(inputLocal!="")
    {
        QMessageBox::information(this,"FYI","Current selected file/directory cleared");
        inputLocal="";
    }
}
