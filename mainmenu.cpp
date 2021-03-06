#include<iostream>
#include<QFileDialog>
#include<QMessageBox>
#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "settingmenu.h"
#include <QList>
#include <QDirIterator>

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
    connect(ui->BTNOpen,SIGNAL(clicked(bool)),this,SLOT(diaglogBatch()));
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

    if(ui->chkBatch->checkState()!=Qt::Checked)
    {
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
    }else{
        convertDir=QDir(inputLocal).absoluteFilePath(QDir(inputLocal).dirName()+"_converted");
        if(QDir().mkdir(convertDir) ==false)
        {
            QMessageBox overwriteDialog;
            int retVal=overwriteDialog.warning(this,"Convert DirectoryExists", inputLocal+"_converted" + " already exists. Overwrite?",QMessageBox::Yes,QMessageBox::No);
            if(retVal!=QMessageBox::Yes)
            {
                return;
            }
            QDir(convertDir).removeRecursively();
            QDir().mkdir(convertDir);
        }
        batchFiles=FetchFileList(inputLocal);
    }
    BeginWork();

}


void MainMenu::BeginWork()
{
    convParams params;
    params.Quality=ui->qualBox->currentIndex();
    params.Size=ui->sizeBox->currentIndex();
    if(this->batchFiles.count()>0)
    {
        params.input=batchFiles.first();
        batchFiles.removeFirst();
    }else{
        params.input=this->inputLocal;
    }

    params.batchDir=this->convertDir;

    manager=new ProcessManager(this,settings,&params);
    //remove pesky close buttons and such
    manager->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    manager->show();

}


void MainMenu::disposeProcess(int status)
{
    manager->close();

    if(this->batchFiles.count()>0)
    {
        //if batch, swallow errors and continue
        if(status!=0)
        {
            cerr<<"Last video failed"<<endl;
        }

        //repeat until there are no more items
        BeginWork();

    }else{
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
    }
}


void MainMenu::diaglogBatch()
{
    if(ui->chkBatch->checkState()==Qt::Checked)
    {
        inputLocal=QFileDialog::getExistingDirectory(this,"Select directory for batch processing",QDir::homePath());
    }else{
        inputLocal=QFileDialog::getOpenFileName(this,tr("Select video to convert"),QDir::homePath(),tr("Video Files (*.avi *.mpg *.mkv *.mpeg *.qt *.wmv *.mp4)"));
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
        //just in case..
        batchFiles.clear();
        convertDir="";
    }
}


QList<QString> MainMenu::FetchFileList(QString path)
{
    QList<QString> fileList;

    if(QDir(path).exists())
    {
        QDirIterator it(path);
        cerr<<"Traversing directory..."<<endl;
        QFileInfo info;
        while(it.hasNext())
        {
            it.next();
            info=it.fileInfo();
            if(!info.isDir() && (info.suffix()=="mkv" || info.suffix()=="avi" || info.suffix()=="mpg" || info.suffix()=="mpeg" || info.suffix()=="qt" || info.suffix()=="wmv" || info.suffix()=="mp4" ))
            {
                fileList.append(QDir(path).absoluteFilePath(info.fileName()));
                cerr<<it.fileName().toStdString()<<endl;
            }
        }
    }
    return fileList;
}
