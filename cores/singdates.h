#ifndef SINGDATES_H
#define SINGDATES_H

#include <QByteArray>
#include <QString>

class SingDates
{
public:
    SingDates(QString stud,QString login,QString password);

    void setLogin(QString login);
    void setPasswprd(QString password);
    void setStudentDates(QString dates);
    QString getLogin();
    QString getPassword();
    QString getStudentDates();

    QByteArray getForSingStruct();


private:
    QString m_Login;
    QString m_Password;
    QString m_Student;


};

#endif // SINGDATES_H
