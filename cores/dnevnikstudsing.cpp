#include "dnevnikstudsing.h"

DnevnikStudSing::DnevnikStudSing(QObject *parent) : QObject(parent)
{
    m_dataBase = new DataBase(this);
}

void DnevnikStudSing::singDnevnik()
{
    for(auto stud:m_SindData)
    {
        stud->sendPostRequest();
    }
}

void DnevnikStudSing::addSingData()
{
    auto logs =  m_dataBase->getStudDatesList();
    for(auto& stud:logs)
    {
        auto sing = new CookiesHandler(stud.getStudentDates(),stud.getForSingStruct());
        connect(sing,SIGNAL(signalSingDnevnik(QString)),this,SLOT(slotStudSing(QString)));
        connect(sing,SIGNAL(signalNotSingDnevnik(QString)),this,SLOT(slotStudNotSing(QString)));

        m_SindData.push_back(sing);
    }
}

std::vector<QString> DnevnikStudSing::getStudSing()
{
    return m_StudSingDn;
}

std::vector<QString> DnevnikStudSing::getStudNotSing()
{
    return m_StudNotSingDn;
}

void DnevnikStudSing::slotStudSing(QString studName)
{
    m_StudSingDn.push_back(studName);
}

void DnevnikStudSing::slotStudNotSing(QString studName)
{
    m_StudNotSingDn.push_back(studName);
}


















