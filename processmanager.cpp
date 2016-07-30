#include<iostream>
#include "processmanager.h"
#include "ui_processmanager.h"

using namespace std;

ProcessManager::ProcessManager(QWidget *parent, QSettings *settings) :
    QDialog(parent),
    ui(new Ui::ProcessManager)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    bool isFFMPEG=settings->value("FFMPEG").toBool();

    //kick off worker process
    cerr<<"Converstion Starting..."<<endl<<endl;
    //connect(ui->pushButton,SIGNAL(clicked(bool)),parentWidget(),SLOT(gc()));
}

ProcessManager::~ProcessManager()
{
    delete ui;
    cerr<<"process destoyed";
}

