#ifndef COOKIESHANDLER_H
#define COOKIESHANDLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QNetworkCookieJar>
#include <QUrl>



class CookiesHandler : public QObject
{
    Q_OBJECT
public:
    CookiesHandler(QString studName,const QByteArray &data,QObject *parent = nullptr);
    virtual ~CookiesHandler(){}

    void sendPostRequest();
    void sendGetRequest(const QUrl &url);


private slots:
      void replyFinished(QNetworkReply *reply);
signals:
    void signalSingDnevnik(QString studData);//сигнал отпраляется если ученику удалось зайти на сайт
    void signalNotSingDnevnik(QString studData);//сигнал отпраляется если ученику не удалось зайти на сайт по какой-либо причине

private:
       void getFile(QNetworkReply *reply);//функция для сохранения страницы отправленной сервером в ответ в файл
private:

       QNetworkAccessManager*m_Manager;
       QUrl m_Url,m_rUrl,m_finishUrl;

       QByteArray m_Login,m_Test;
       QString m_studName;

};
#endif // COOKIESHANDLER_H
