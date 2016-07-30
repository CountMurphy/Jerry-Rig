#include<iostream>
#include<QProcess>
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
    converter = new QProcess(parent);

    connect(converter,SIGNAL(finished(int)),parentWidget(),SLOT(disposeProcess(int)));
    connect(converter,SIGNAL(readyRead()),this,SLOT(readReady()));

    QString program="ls";
    converter->start(program);
}

ProcessManager::~ProcessManager()
{
    delete ui;
    cerr<<"process destoyed"<<endl;
}

void ProcessManager::readReady()
{
    QByteArray data=converter->readAllStandardOutput();
}
