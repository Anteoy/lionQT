#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include <iostream>
using namespace std;

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
    this,SLOT(replyFinished(QNetworkReply*)));
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_loginBtn_clicked()
{
    QNetworkRequest network_request;
    QUrl url("http://127.0.0.1:8080/loginR");
    QByteArray append("user_name=anteoy&pass_word=123");
    network_request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    network_request.setUrl(url);
    QByteArray jsonString = "{\"user_name\": \"anteoy\", \"pass_word\": \"123\"}";
    QByteArray postDataSize = QByteArray::number(jsonString.size());
    network_request.setRawHeader("Content-Length", postDataSize);
    manager->post(network_request,jsonString);
//    manager->get(QNetworkRequest(QUrl("http://www.qter.org")));
    // 判断用户名和密码是否正确，
    // 如果错误则弹出警告对话框
    if(ui->usrLineEdit->text().trimmed() == tr("zdz") &&
           ui->pwdLineEdit->text() == tr("123456"))
    {
       accept();
    } else {
       QMessageBox::warning(this, tr("Waring"),
                             tr("user name or password error!"),
                             QMessageBox::Yes);
       // 清空内容并定位光标
       ui->usrLineEdit->clear();
       ui->pwdLineEdit->clear();
       ui->usrLineEdit->setFocus();
    }
}

void LoginDialog::replyFinished(QNetworkReply *reply)
{
    cout << "go in replyFinished" << endl;
    QTextCodec *codec = QTextCodec::codecForName("utf8");
    QString all = codec->toUnicode(reply->readAll());
    qDebug() << all;
    reply->deleteLater();
}
