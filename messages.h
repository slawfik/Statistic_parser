#ifndef MESSAGES_H
#define MESSAGES_H

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include "string.h"
#include <unistd.h>

#define LITLE15BUFF 15
#define POCET_ZNAKOV_ATOI_DATUM 2   //kopiruje pocet znakov pre atoi Funkciu
#define LITLE20BUFF 20
#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)

/*struktura pre docasne uloženie dat zo starých mesačných a denných statistik*/
typedef struct forOldMesg  {
    char date[40];
    char predmet[40];
}DATAOLDMSG;

enum Type_Message
{
    DAY_MSG,
    MONTH_MSG,
    ACTION_MSG,
};

class day_Month_Message
{
public:
    int total_Time[5];      //0
    int max_Time[5];        //1
    int min_Time[5];        //2
    int arit_Priemer[5];    //3
    int couter[5];          //4
    int modus[5];           //5
    int boot_Ernno[2];

    void parsDayMonthStatistic(char* pole_piatich_Statistik,int i);
};

class date_time
{
public:
    int cas_m;  //cas v minutách
    int den;
    int mesiac;
    int rok;
    int datum;
};

class actionMSG
{
private:
    int cod;
    wchar_t popis_codu[15];
public:
    void setStringMode();
    void setCode(char* pa_code);
    int getCode()     {return cod;}
    wchar_t* getPopisCodu()    {return &popis_codu[0];}
};

class messages : public date_time
{
    int tele;
    Type_Message type_MSG;
public:
    messages();
    actionMSG* _action_MSG;
    day_Month_Message* _dayMonth_MSG;
    Type_Message getType_MSG()  { return type_MSG;}
    bool parsMSG(std::ifstream &pa_read);
    void setTypeMess(int pa_n);
    int pocitajBodky(char* pa_string);
    int getNumtele()    { return tele; }
    char* pars_Old_Message(char* mesg);
    void stringDateToInts(char* pa_date);
    //void parsDatumNewMonthDayMSG(char* pa_str);
};


extern DATAOLDMSG tmp;
#endif // MESSAGES_H
