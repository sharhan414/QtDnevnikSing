#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <vector>
#include "singdates.h"
class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = nullptr,int max_stud=30);
    virtual ~DataBase();

    enum class ErrorData{ExceededLimit,NotStudData};//типы ошибок

    void insertStudent(QString name,QString login,QString password);//для ставки данных ученика
    void insertStudent(SingDates dt);//для ставки данных ученика
    void insertListStudents(std::vector<SingDates> students);//для ставки списка данных учеников
    void removeStudent(QString name);//для удаление данных ученика
    void updateDataStud(QString name,QString login,QString password);//для обновление данных ученика
    void updateDataStud(SingDates dt);//для обновление данных ученика
    std::vector<SingDates> getStudDatesList(); //возвращает данные всех учеников


    void Test();//временная функция для тестирования различных функций

signals:

private:
    QJsonDocument m_JSonDataBase;
    QJsonObject m_JSData;
    QString m_PathDataBase;

    void saveDates(); //для сохранения данных
    int getCountStud(); // Возвращает количество сохраненных учеников
    int m_maxCountStud; // максимальное количество данных для хранения


};

#endif // DATABASE_H
