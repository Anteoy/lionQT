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
    if (ui->usrLineEdit->text().trimmed() == "") {
        QMessageBox::warning(this, tr("Waring"),
                              tr("请输入用户名!"),
                              QMessageBox::Yes);

        return;
    }
    if (ui->pwdLineEdit->text() == ""){
        QMessageBox::warning(this, tr("Waring"),
                              tr("请输入密码!"),
                              QMessageBox::Yes);

        return;
    }
    QNetworkRequest network_request;
    QUrl url("http://127.0.0.1:8080/loginR");
    QJsonObject json;
    json.insert("user_name", ui->usrLineEdit->text().trimmed());
    json.insert("pass_word", ui->pwdLineEdit->text());
    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    QByteArray append("{\"user_name\"=");
    append.append(ui->usrLineEdit->text().trimmed());
    append.append("&\"pass_word\"=}");
    append.append(ui->pwdLineEdit->text());

    network_request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    network_request.setUrl(url);
    QByteArray postDataSize = QByteArray::number(byteArray.size());
    network_request.setRawHeader("Content-Length", postDataSize);
    QNetworkReply *reply = manager->post(network_request,byteArray);
    cout << "getted reply" << endl;
    QTextCodec *codec = QTextCodec::codecForName("utf8");
//    QString all = codec->toUnicode(reply->readAll());
//    qDebug() << all;
//    reply->deleteLater();
//    manager->get(QNetworkRequest(QUrl("http://www.qter.org")));

}

void LoginDialog::replyFinished(QNetworkReply *reply)
{
    cout << "go in replyFinished" << endl;
    QTextCodec *codec = QTextCodec::codecForName("utf8");
    QString all = codec->toUnicode(reply->readAll());
    qDebug() << all;
    reply->deleteLater();
    QJsonParseError jsonError;
    QByteArray json = all.toUtf8();
    QJsonDocument doucment = QJsonDocument::fromJson(json, &jsonError);  // 转化为 JSON 文档
    if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError)) {  // 解析未发生错误
        qDebug() << "pase json ok" <<endl;
        if (doucment.isObject()) { // JSON 文档为对象
            QJsonObject object = doucment.object();  // 转化为对象
            if (object.contains("code")) {  // 包含指定的 key
                QJsonValue value = object.value("code");  // 获取指定 key 对应的 value
                if (value.isString()) {  // 判断 value 是否为字符串
                    QString code = value.toString();  // 将 value 转化为字符串
                    qDebug() << "code : " << code;
                    if (code != "200"){
                        QMessageBox::warning(this, tr("Waring"),
                                              tr("用户名或密码不正确!"),
                                              QMessageBox::Yes);
                        // 清空内容并定位光标
                        ui->usrLineEdit->clear();
                        ui->pwdLineEdit->clear();
                        ui->usrLineEdit->setFocus();
                        return;
                    }else{
                        QJsonValue token_ = object.value("token");
                        if (token_.isString()){
                            QString getToken = token_.toString();
                            qDebug() << "token : " << getToken;
                            token = getToken;
                            accept();
                        }else{
                            QMessageBox::warning(this, tr("Waring"),
                                                  tr("user name or password error!"),
                                                  QMessageBox::Yes);
                            // 清空内容并定位光标
                            ui->usrLineEdit->clear();
                            ui->pwdLineEdit->clear();
                            ui->usrLineEdit->setFocus();

                        }
                    }
                }
            }

        }
    }else {
        qDebug() << "pase json err or no res" <<endl;
        qDebug() << jsonError.errorString() <<endl;
    }
}
