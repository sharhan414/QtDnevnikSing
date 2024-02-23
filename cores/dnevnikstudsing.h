#ifndef DNEVNIKSTUDSING_H
#define DNEVNIKSTUDSING_H

#include <QObject>
#include "database.h"
#include "cookieshandler.h"


class DnevnikStudSing : public QObject
{
    Q_OBJECT
public:
    explicit DnevnikStudSing(QObject *parent = nullptr);

    void singDnevnik();
    void addSingData();
    std::vector<QString> getStudSing();
    std::vector<QString> getStudNotSing();


private slots:
    void slotStudSing(QString studname);
    void slotStudNotSing(QString studname);

private:
    DataBase *m_dataBase;
    std::vector<CookiesHandler*> m_SindData;
    std::vector<QString> m_StudSingDn;//ученики которые успешно зашли в дневник
    std::vector<QString> m_StudNotSingDn;//ученики которые не смогли  зайти в дневник

};

#endif // DNEVNIKSTUDSING_H
