#ifndef MIESTNOSTI_TELE_H
#define MIESTNOSTI_TELE_H

#include "messages.h"
#include "QString"

typedef struct subor {
    QString file;
    std::ifstream read;
}SUBOR;

class miestnosti_tele
{
public:
    int n_akcii;
    messages* array[500];

    miestnosti_tele();
    ~miestnosti_tele();
};

extern SUBOR subStruct;
extern miestnosti_tele teleMiestnosti[23];
#endif // MIESTNOSTI_TELE_H
