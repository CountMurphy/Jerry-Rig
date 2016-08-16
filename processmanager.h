#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <QDialog>
#include<QSettings>
#include<QProcess>
#include"convparams.h"

namespace Ui {
class ProcessManager;
}

class ProcessManager : public QDialog
{
    Q_OBJECT

public:
    explicit ProcessManager(QWidget *parent = 0, QSettings *settings = 0, convParams *params=0);
    QProcess *converter;
    ~ProcessManager();
private slots:
    void readReady();
    void cancel();
    void Error(QProcess::ProcessError perror);

private:
    Ui::ProcessManager *ui;
};

#endif // PROCESSMANAGER_H
