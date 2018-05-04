#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QtNetwork>

extern QString token;

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

private slots:
    void on_loginBtn_clicked();
    void replyFinished(QNetworkReply *);

private:
    Ui::LoginDialog *ui;
    QNetworkAccessManager *manager;
};

#endif // LOGINDIALOG_H
