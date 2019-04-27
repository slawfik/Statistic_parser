#include "openfile.h"
#include "miestnosti_tele.h"
#include <QApplication>

miestnosti_tele teleMiestnosti[23];
SUBOR subStruct;
DATAOLDMSG tmp;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    openFile w;

    w.show();
    return a.exec();
}
