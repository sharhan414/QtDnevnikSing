#include <QCoreApplication>

#include "cookieshandler.h"

#include <vector>
#include "dnevnikstudsing.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    DnevnikStudSing dn;
    dn.addSingData();
    dn.singDnevnik();

    return a.exec();
}

