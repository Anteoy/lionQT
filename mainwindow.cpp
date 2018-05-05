#include "mainwindow.h"
#include "logindialog.h"
#include "ui_mainwindow.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include <iostream>
using namespace std;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    manager = new QNetworkAccessManager(this);
    ui->setupUi(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)),
    this,SLOT(replyFinished(QNetworkReply*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    qDebug() << token << endl;
}

void MainWindow::on_pushButton_4_clicked()
{
    if (ui->lineEdit->text().trimmed() == "") {
        QMessageBox::warning(this, tr("Waring"),
                              tr("请输入title!"),
                              QMessageBox::Yes);

        return;
    }
    qDebug() << ui->lineEdit->text().trimmed() << endl;
    QNetworkRequest network_request;
    QUrl url("http://127.0.0.1:8080/get_blog");
    QJsonObject json;
    json.insert("title", ui->lineEdit->text().trimmed());
    json.insert("token", token);
    QJsonDocument document;
    document.setObject(json);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);

    network_request.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    network_request.setUrl(url);
    QByteArray postDataSize = QByteArray::number(byteArray.size());
    network_request.setRawHeader("Content-Length", postDataSize);
    QNetworkReply *reply = manager->post(network_request,byteArray);
//    cout << "getted reply" << endl;
//    QTextCodec *codec = QTextCodec::codecForName("utf8");
//    QString all = codec->toUnicode(reply->readAll());
//    qDebug() << all << endl;
//    QByteArray rs = all.toUtf8();
//    qDebug() << rs.data() << endl;
//    QJsonParseError jsonError;
//    QJsonDocument doucment = QJsonDocument::fromJson(rs, &jsonError);  // 转化为 JSON 文档
//    qDebug() << doucment << endl;


//    if (doucment.isObject()) { // JSON 文档为对象
//        QJsonObject object = doucment.object();  // 转化为对象
//        if (object.contains("code")) {  // 包含指定的 key
//            QJsonValue value = object.value("code");  // 获取指定 key 对应的 value
//            if (value.isString()) {  // 判断 value 是否为字符串
//                QString code = value.toString();  // 将 value 转化为字符串
//                qDebug() << "code : " << code;
//                if (code != "200"){
//                    QMessageBox::warning(this, tr("Waring"),
//                                          tr("request is not 200!"),
//                                          QMessageBox::Yes);
//                    return;
//                }else{
//                    QJsonValue data = object.value("data");
//                    if (data.isString()){
//                        QString getToken = data.toString();
//                        qDebug() << "token : " << getToken;

//                    }else{

//                    }
//                }
//            }
//        }

//    }else{
//        qDebug() << "debug" << endl;
//    }
}

void MainWindow::replyFinished(QNetworkReply *reply)
{
    cout << "go in replyFinished22" << endl;
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
                                              tr("request is not 200!"),
                                              QMessageBox::Yes);
                        return;
                    }else{
                        QJsonValue data = object.value("data");
                        if (data.isString()){
                            QString datastr = data.toString();
                            qDebug() << "data : " << datastr;
                            ui->textEdit->setPlainText(datastr);
                        }else{

                        }
                    }
                }
            }

        }else{
            qDebug() << "debug" << endl;
        }
    }else {
        qDebug() << "pase json err or no res" <<endl;
        qDebug() << jsonError.errorString() <<endl;
    }
}
