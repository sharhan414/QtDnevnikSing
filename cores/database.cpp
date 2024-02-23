#include "database.h"
#include <QFile>
#include <QDebug>
#include <QDir>
#include <QStringList>

#include <QJsonDocument>
#include <QDataStream>
#include <QByteArray>
#include <QJsonObject>
DataBase::DataBase(QObject *parent,int max_stud) : QObject(parent),m_maxCountStud(max_stud)
{
#ifdef Q_OS_WINDOWS
    m_PathDataBase = "./DataBase/data.json";
#endif

    QDir dir("./DataBase");
    if (!dir.exists())
    {
        if (dir.mkpath("./"))
        {
            QFile file(m_PathDataBase);
            if (file.open(QIODevice::ReadWrite))
            {
                QByteArray rawData = file.readAll();
                QJsonDocument doc(QJsonDocument::fromJson(rawData));
                m_JSData = doc.object();
             }
            file.close();
        }
        else
        {
           // qDebug() << "Fail to make the data path!";
            return ;
        }
    }

    QFile file(m_PathDataBase);
    if (file.open(QIODevice::ReadOnly))
    {
        QByteArray rawData = file.readAll();
        QJsonDocument doc(QJsonDocument::fromJson(rawData));
        m_JSData = doc.object();
     }
    file.close();

}

DataBase::~DataBase()
{
    saveDates();
}

void DataBase::insertStudent(QString student, QString login, QString password)
{
    if(getCountStud()> m_maxCountStud)
    {
        return;
    }
    QJsonObject logObject;
    logObject["login"] = login;
    logObject["password"] = password;

    m_JSData[student] = logObject;

    saveDates();

}

void DataBase::insertStudent(SingDates dt)
{
    insertStudent(dt.getStudentDates(),dt.getLogin(),dt.getPassword());

}

void DataBase::insertListStudents(std::vector<SingDates> students)
{
    for(auto stud:students)
    {
        insertStudent(stud);
    }

}

void DataBase::removeStudent(QString name)
{
    m_JSData.remove(name);
    saveDates();
}

void DataBase::updateDataStud(QString name, QString login, QString password)
{
    insertStudent(name,login,password);
}

void DataBase::updateDataStud(SingDates dt)
{
    insertStudent(dt);
}

std::vector<SingDates> DataBase::getStudDatesList()
{
    std::vector<SingDates> studList;

    auto stud_keys = m_JSData.keys();

    for(auto stud:stud_keys)
    {
        auto login = m_JSData[stud].toObject()["login"].toString();
        auto password = m_JSData[stud].toObject()["password"].toString();

        SingDates dt(stud,login,password);
        studList.push_back(dt);

    }

    return studList;
}

void DataBase::Test()
{
    qDebug()<<"+++++++++++++++++++++++++";

    qDebug()<<m_JSData.keys();

    qDebug()<<"-------------------------";

}

void DataBase::saveDates()
{
    m_JSonDataBase.setObject(m_JSData);
    QFile jsonFile(m_PathDataBase);
    if (jsonFile.open(QIODevice::WriteOnly))
    {

        jsonFile.write(m_JSonDataBase.toJson(QJsonDocument::Indented));
        jsonFile.close();
    }
}

int DataBase::getCountStud()
{
    return m_JSData.size();;
}
