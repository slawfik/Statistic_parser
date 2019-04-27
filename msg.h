#ifndef MSG_H
#define MSG_H

#include <iostream>
#include <fstream>

#define POCET_ZNAKOV_ATOI_DATUM 2   //kopiruje pocet znakov pre atoi Funkciu
#define LITLE20BUFF 20
#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)

// asci hodnôty znakov 'E' a '2'
#define E2 6950
#define EA 6965
#define EB 6966
//vsetky tieto tri rátajú menu-mód
#define A0 6548
#define A2 6550
#define AA 6565
#define D2 6850
#define DA 6865
#define CA 6765
#define F2 7050
#define FA 7065

enum Type_Message {
    DAY_M,
    MONTH_M,
    ACTION_M,
};

class Msg {
    int tele;   //cislo miestnosti
    int datum;
    Type_Message typSpr;
    char message[200];
    char cod[3];

    int total_Time[5];
    int max_Time[5];
    int min_Time[5];
    int arit_Priemer[5];
    int couter[5];
    int modus[5];
    int boot_Ernno[2];
public:
    int cas_m;  //cas v minutách
    int den;
    int mesiac;
    int rok;

    bool parsMSG(std::ifstream &pa_read);
    int pocitajBodky(char* pa_string);
    void setTypeMess(int pa_n);
    void parsDayMonthStatistic(char* pole_piatich_Statistik,int ciel_statistik[]);

    int getNumNtele()   {return tele;}
};

class Tele : public Msg{
public:
    int n_akcii;
    Msg* array[350];
    int tele;
    /*int month_count[5];
    int month_total[5];*/

    Tele(){n_akcii = 0;}
    ~Tele();
};

extern Tele database[23];
#endif // MSG_H
