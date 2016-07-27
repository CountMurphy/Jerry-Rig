#include "mainmenu.h"
#include <QApplication>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    cerr<<"Starting Jerry-Rig"<<endl;
    QApplication a(argc, argv);
    MainMenu w;
    w.show();

    return a.exec();
}
