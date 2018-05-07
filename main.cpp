#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>

QString token = "not init";

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    LoginDialog dlg;
    dlg.setWindowTitle("liongo manager login");
    w.setWindowTitle("liongo 后台管理");
    if (dlg.exec() == QDialog::Accepted)
    {
       w.show();
       return a.exec();
    }
    else return 0;
}
