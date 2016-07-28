#include "mainmenu.h"
#include <QApplication>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    if(argc > 1)
    {
        //damn kids....
        cout<<"If you're passing command line arguments to Jerry-Rig, you are more than capable of running ffmpeg directly"<<endl<<endl;
        cout<<"Aborting..."<<endl<<endl;
        return -1;
    }

    cerr<<"Starting Jerry-Rig"<<endl;
    QApplication a(argc, argv);
    MainMenu w;
    w.show();

    return a.exec();
}
