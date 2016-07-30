#include<iostream>
#include<QProcess>
#include<QTextCodec>
#include "processmanager.h"
#include "ui_processmanager.h"

using namespace std;

ProcessManager::ProcessManager(QWidget *parent, QSettings *settings, convParams *params) :
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
    connect(converter,SIGNAL(readyReadStandardError()),this,SLOT(readReady()));

    QString program= isFFMPEG ? "ffmpeg":"avconv";
    QStringList args;

    args<<"-i" << params->input;
    args<<"-c:v"<< "libx264";

    switch(params->Quality)
    {
    case 0:
        args<<"-crf"<< "18";
        break;
    case 1:
        args<<"-crf"<< "22";
        break;
    case 2:
        args<<"-crf"<< "25";
        break;
    }

    switch(params->Size)
    {
    case 0:
        args<<"-preset"<< "veryslow";
        break;
    case 1:
        args<<"-preset"<< "fast";
        break;
    case 2:
        args<<"-preset"<< "ultrafast";
        break;
    }

    args<<params->input+"_converted.mkv";

    converter->start(program, args);
}

ProcessManager::~ProcessManager()
{
    delete ui;
    cerr<<"process destoyed"<<endl;
}

void ProcessManager::readReady()
{
    QByteArray data=converter->readAllStandardError();
    QString DataAsString;
    DataAsString.append(data.data());
    ui->label->setText(DataAsString);
}
