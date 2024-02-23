#include "singdates.h"

SingDates::SingDates(QString stud, QString login, QString password)
{
    m_Student = stud;
    m_Login = login;
    m_Password = password;
}

void SingDates::setLogin(QString login)
{
    m_Login = login;
}

void SingDates::setPasswprd(QString password)
{
    m_Password = password;
}

void SingDates::setStudentDates(QString dates)
{
    m_Student = dates;
}

QString SingDates::getLogin()
{
    return m_Login;
}

QString SingDates::getPassword()
{
    return m_Password;
}

QString SingDates::getStudentDates()
{
    return m_Student;
}

QByteArray SingDates::getForSingStruct()
{
    QByteArray Data ;
    Data.append(QString("login=%1&password=%2&action=login").arg(m_Login).arg(m_Password));
    return Data;

}
