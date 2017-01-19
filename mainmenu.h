#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include<settingmenu.h>
#include<processmanager.h>

namespace Ui {
class MainMenu;
}

class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = 0);
    ~MainMenu();

public slots:
    void Quit();
    void disposeProcess(int status);//probably didn't need this, but it was fun

private:
    Ui::MainMenu *ui;
    SettingMenu *smenu;
    ProcessManager *manager;
    QSettings *settings=new QSettings("Jerry-Rig");
    QString inputLocal;
    QList<QString> batchFiles;
    QList<QString> FetchFileList(QString path);
    void BeginWork();
    const double versionNumber=2.2;
private slots:
    void ShowPref();
    void ConvertClick();
    void diaglogIt();
    void toggleBatch(bool isBatch);
};

#endif // MAINMENU_H
