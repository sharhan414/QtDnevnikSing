#include "cookieshandler.h"
#include <QFile>
#include <QNetworkCookie>
CookiesHandler::CookiesHandler(QString studName,const QByteArray &data,QObject *parent) : QObject(parent)
{
    m_Manager = new QNetworkAccessManager(this);
    m_Manager->setCookieJar(new QNetworkCookieJar(this));
    m_finishUrl = QUrl("https://dnevnik.ru/userfeed");//конечный адрес сайта которому мы должны подключиться

    m_Url = "https://login.dnevnik.ru/login";
    m_Login = data;
    m_studName = studName;
    connect(m_Manager, SIGNAL(finished(QNetworkReply*)), SLOT(replyFinished(QNetworkReply*)));
}
void CookiesHandler::sendPostRequest()
{
    QNetworkRequest reg(m_Url);
    reg.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/x-www-form-urlencoded"));

    m_Manager->post(reg, m_Login);
}

void CookiesHandler::sendGetRequest(const QUrl &url)
{
    m_Url = url;
    QNetworkRequest reg(m_Url);
    reg.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/x-www-form-urlencoded"));

    m_Manager->get(reg);
}

void CookiesHandler::replyFinished(QNetworkReply *reply)
{
    qDebug()<<"***********************FINISHED***************************";
    if (reply->error() != QNetworkReply::NoError)
    {
        qWarning() << "ERROR:" << reply->errorString();
        return;
    }

    QList<QNetworkCookie>  cookies = m_Manager->cookieJar()->cookiesForUrl(m_Url);

    int code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug()<<"code:"<<code;
    if (code >= 200 and code < 300) // Success
    {
        getFile(reply);
        qDebug() << "++++++++++successfully+++++";
        if(m_rUrl == m_finishUrl)//точно мы зашли на сайт
        {
            emit signalSingDnevnik(m_studName);
            qDebug() <<"Зашёл на сайт";
        }
        else
        {
            signalNotSingDnevnik(m_studName);
            qDebug() <<"Не зашёл на сайт, данные не верные:"<<m_Login;
        }
        return;
    }
    else if (code >= 300 and code < 400) // Redirection
    {
        //qDebug() << "--------ERROR SING------------";
        /* Use Cookies for Login */


        m_rUrl = reply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
        qDebug()<<"return:"<<m_rUrl;
        //qDebug()<<"rURL:"<<m_rUrl<<"    "<<m_Url;

        if(m_rUrl != m_finishUrl)
        {
            QNetworkRequest reg(m_rUrl);
            reg.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/x-www-form-urlencoded"));
            m_Manager->post(reg,m_Login);
            return;
        }


//qDebug()<<"*****************";
        QNetworkRequest reg(m_rUrl);
        QVariant var;
        var.setValue(cookies);

        reg.setHeader(QNetworkRequest::CookieHeader, var);
        reg.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/x-www-form-urlencoded"));
        m_Manager->get(reg);
        return;

    }
}

void CookiesHandler::getFile(QNetworkReply *reply)
{
    const QByteArray reply_text = reply->readAll();

    static int nomer = 1;

    QFile file(QString("C:\\Users\\user\\Desktop\\Dates\\DataTest_%1.html").arg(nomer));
    if (!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "Ошибка при открытии файла";
    }
    else
    {
        file.write(reply_text);
    }
    nomer += 1;
}
