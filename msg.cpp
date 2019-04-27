#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <array>
#include <unistd.h>

#include "msg.h"
//{{{{{

using namespace std;

bool Msg::parsMSG(ifstream &pa_read)
{
    int _pom;
    char* pozicia;
    char _buffer[200];
    char _pomBuff[LITLE20BUFF];

    pa_read >> _buffer;
    _buffer[strlen(_buffer)] = '\0';
    _pom = pocitajBodky(_buffer);
    if(_pom == 1)  { //jedna bodka == action MSG
        bzero(_pomBuff,LITLE20BUFF);
        cas_m = atoi(_buffer);
        pozicia = strchr(_buffer,'.');
        cod[2] = '\0';
        cod[0] = *(pozicia+1);
        cod[1] = *(pozicia+2);
        strncpy(_pomBuff,pozicia+3,POCET_ZNAKOV_ATOI_DATUM);
        rok = atoi(_pomBuff);
        rok = rok+2000;
        strncpy(_pomBuff,pozicia+5,POCET_ZNAKOV_ATOI_DATUM);
        mesiac = atoi(_pomBuff);
        strncpy(_pomBuff,pozicia+7,POCET_ZNAKOV_ATOI_DATUM);
        den = atoi(_pomBuff);
        strncpy(_pomBuff,pozicia+9,POCET_ZNAKOV_ATOI_DATUM);
        tele = atoi(_pomBuff);
        strncpy(_pomBuff,pozicia+3,3*POCET_ZNAKOV_ATOI_DATUM);
        datum = atoi(_pomBuff); //datum je integer použivaný pre sort napr.180730
        this->setTypeMess(_pom);
        if(*(pozicia+8) == 'Z')
        {
            tele = 0;
        } else {
            tele = atoi(pozicia+9);
        }
        cout << "Miestnost: " << tele << "   " << den << "." << mesiac << "." << rok << "\n";
        return true;
    } else if(_pom == 4)   {//nový formát: denna/mesacná message nemá nastavené den mesiac rok!!
        cas_m = 0;
        for(int j=0; j<5;j++) {//každá mes/den správa má min 5 častí
            switch(j)   {
                case 0:
                    parsDayMonthStatistic(_buffer,total_Time);
                    break;
                case 1:
                    parsDayMonthStatistic(_buffer,max_Time);
                    break;
                case 2:
                    parsDayMonthStatistic(_buffer,min_Time);
                    break;
                case 3:
                    parsDayMonthStatistic(_buffer,arit_Priemer);
                    break;
                case 4:
                    parsDayMonthStatistic(_buffer,couter);
                    break;
            }
            std::cout << endl;
            pa_read >> _buffer;
        }
        if(pocitajBodky(_buffer) == 2)  {//day message
            boot_Ernno[0] = atoi(_buffer);
            pozicia = strchr(_buffer,'.');
            boot_Ernno[1] = atoi(_buffer+1);
            typSpr = DAY_M;
        }
        return true;
    } else {
        return false;
    }
}

void Msg::parsDayMonthStatistic(char* pole_piatich_Statistik,int ciel_statistik[])
{
    char* znak;
    int i = 0;
    znak = &pole_piatich_Statistik[0];
    while(i != 5)   {
        ciel_statistik[i] = atoi(znak);
        if(ciel_statistik[i] == 65535)  {
            ciel_statistik[i] = 0;
        }
        znak = strchr(znak,'.');
        znak++;
        std::cout << ciel_statistik[i] << "__";
        i++;
    }
}

int Msg::pocitajBodky(char* pa_string) {
    int n = 0;
    while(*pa_string != '\0')   {
        if(*pa_string == '.')   {
            n++;
        }
        pa_string++;
    }
    return n;
}

void Msg::setTypeMess(int pa_n) {
    switch(pa_n)    {
        case 1:
            this->typSpr = ACTION_M;
            break;
        case 27:
            this->typSpr = DAY_M;
            break;
        case 32:
            this->typSpr = MONTH_M;
            break;
    }
}

Tele::~Tele() {
    while(--n_akcii >= 0) {
        delete array[n_akcii];
    }
}
