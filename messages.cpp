#include "messages.h"

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

messages::messages() {

}

void actionMSG::setCode(char* pa_code)  {
    cod = pa_code[0]*100;
    cod += pa_code[1];
}

void actionMSG::setStringMode() {
    switch(cod)    {
        case E2:
            //strncpy(popis_codu,"Nastavenia\0",LITLE15BUFF);
            wcsncpy(popis_codu,L"Nastavenia\0",LITLE15BUFF);
            break;
        case  EA:
            wcsncpy(popis_codu,L"KK\0",LITLE15BUFF);
            break;
        case  EB:
            wcsncpy(popis_codu,L"Zoznam\0",LITLE15BUFF);
            break;
        case  A0:
            wcsncpy(popis_codu,L"Boot done\0",LITLE15BUFF);
            break;
        case  A2:
            wcsncpy(popis_codu,L"System zap.\0",LITLE15BUFF);
            break;
        case  AA:
            wcsncpy(popis_codu,L"System vyp.\0",LITLE15BUFF);
            break;
        case  D2:
            wcsncpy(popis_codu,L"Prez. mód\0",LITLE15BUFF);
            break;
        case  DA:
            wcsncpy(popis_codu,L"Viko mód\0",LITLE15BUFF);
            break;
        case  CA:
            wcsncpy(popis_codu,L"Menu mód\0",LITLE15BUFF);
            break;
        case  F2:
            wcsncpy(popis_codu,L"VGA zap.\0",LITLE15BUFF);
            break;
        case FA:
            wcsncpy(popis_codu,L"VGA vyp.\0",LITLE15BUFF);
            break;
        default:
            int pom2 =0;
            int pom = cod/1000;
            cod = (cod-(pom*1000));
            pom2 = (cod/100);
            pom = pom*10 + pom2;
            cod = (cod -(pom2 * 100));
            swprintf(popis_codu,L"ERRNO_%c%c",pom,cod);
            //wcsncpy(popis_codu,L"ERRNO\0",LITLE15BUFF);
            break;
    }
}

void day_Month_Message::parsDayMonthStatistic(char* pole_piatich_Statistik,int i)
{
    char* znak;
    int j = 0;
    znak = &pole_piatich_Statistik[0];
    switch (i) {
        case 0:
            while(j != 5)   {
                total_Time[j] = atoi(znak);
                znak = strchr(znak,'.');
                znak++;
              //  std::cout << total_Time[j] << "__";
                j++;
            }
            break;
        case 1:
            while(j != 5)   {
                max_Time[j] = atoi(znak);
                znak = strchr(znak,'.');
                znak++;
              //  std::cout << max_Time[j] << "__";
                j++;
            }
            break;
        case 2:
            while(j != 5)   {
                min_Time[j] = atoi(znak);
                if(min_Time[j] == 65535)
                    min_Time[j] = 0;
                znak = strchr(znak,'.');
                znak++;
            //    std::cout << min_Time[j] << "__";
                j++;
            }
            break;
        case 3:
            while(j != 5)   {
                arit_Priemer[j] = atoi(znak);
                znak = strchr(znak,'.');
                znak++;
            //    std::cout << arit_Priemer[j] << "__";
                j++;
            }
            break;
        case 4:
            while(j != 5)   {
                couter[j] = atoi(znak);
                znak = strchr(znak,'.');
                znak++;
            //    std::cout << arit_Priemer[j] << "__";
                j++;
            }
            break;
        case 5:
            while(j != 5)   {
                modus[j] = atoi(znak);
                znak = strchr(znak,'.');
                znak++;
               //std::cout << modus[j] << "mo\n";
                j++;
            }
            break;
    }
}

char* messages::pars_Old_Message(char* mesg)  {
    char* znak;
    int i;
    znak = mesg;
    i=0;
    while(i!=5) {
        znak = strchr(znak,'.');
        znak++;
        i++;
    }
   // *(--znak) = '\n';
    return znak;
}

void messages::stringDateToInts(char* pa_date) {
    //char buff[7];
    char *poz;

    std::cout << pa_date <<std::endl;
    den = atoi(pa_date+1);
    mesiac = atoi(pa_date+4);
    //rok = (a = atoi(pa_date+3)) < 2000 ? a+2000 : a;
    poz = strchr(pa_date+4,'.');
    rok = atoi(poz+1);
    /*buff[6] = '\0';
    buff[0] = pa_date[8];
    buff[1] = pa_date[9];
    buff[2] = pa_date[3];
    buff[3] = pa_date[4];
    buff[4] = pa_date[0];
    buff[5] = pa_date[1];
    //std::cout << "Raz a dva" << pa_date << " ---> " << buff << " \n";
    //datum = atoi(buff);*/
}

/*void messages::parsDatumNewMonthDayMSG(char* pa_str) {

}*/

bool messages::parsMSG(std::ifstream &pa_read)    {
    int _pom;
    char* pozicia;
    char _buffer[200];
    char _pomBuff[LITLE20BUFF];

    pa_read >> _buffer;
    _buffer[strlen(_buffer)] = '\0';
    _pom = pocitajBodky(_buffer);
    if(_pom == 1 && strlen(_buffer) > 11 /*&& strlen(_buffer) < 16*/)  { //jedna bodka == action MSG
        //11 ODFILTROVALA LOGOVACIE SPRáVY KTORE OBSAHUJU MEDZERU
        setTypeMess(_pom);
        _action_MSG = new actionMSG;
        bzero(_pomBuff,LITLE20BUFF);
        cas_m = atoi(_buffer);
        if(cas_m > 1440){
            cas_m = cas_m/60;
        }
        pozicia = strchr(_buffer,'.');
        _action_MSG->setCode((pozicia+1));
        _action_MSG->setStringMode();

        //if(!wcsncmp(_action_MSG->getPopisCodu(),L"ERRNO\0",15)){ //logovacia správa vyhodí errno
            stringDateToInts(tmp.date);
            tele = atoi(tmp.predmet);
       /* }   else {
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
        }*/
        //std::cout << "end_1\n";
        //std::cout << "Miestnost: " << tele << "   " << den << "." << mesiac << "." << rok << _action_MSG->getPopisCodu() <<"\n";
    } else if(_pom == 4)   {//nový v riadkoch formát: denna/mesacná message nemá nastavené den mesiac rok!!
        //std::cout << "start_2\n";
        cas_m = 1;
        _dayMonth_MSG = new day_Month_Message;
        _dayMonth_MSG->parsDayMonthStatistic(_buffer,0);
        pa_read >> _buffer;
        _dayMonth_MSG->parsDayMonthStatistic(_buffer,1);
        pa_read >> _buffer;
        _dayMonth_MSG->parsDayMonthStatistic(_buffer,2);
        pa_read >> _buffer;
        _dayMonth_MSG->parsDayMonthStatistic(_buffer,3);
        pa_read >> _buffer;
        _dayMonth_MSG->parsDayMonthStatistic(_buffer,4);
        pa_read >> _buffer;/**/

        if(pocitajBodky(_buffer) == 2)  {//day message
            _dayMonth_MSG->boot_Ernno[0] = atoi(_buffer);
            pozicia = strchr(_buffer,'.');
            _dayMonth_MSG->boot_Ernno[1] = atoi(pozicia+1);
            pozicia = strchr(pozicia+1,'.');
            _pom = 22;
        } else {
            _dayMonth_MSG->parsDayMonthStatistic(_buffer,5);
            pa_read >> _buffer;
            _dayMonth_MSG->boot_Ernno[0] = atoi(_buffer);
            pozicia = strchr(_buffer,'.');
            _dayMonth_MSG->boot_Ernno[1] = atoi(pozicia+1);
             pozicia = strchr(pozicia+1,'.');
            _pom = 26;
        }
        tele = atoi(tmp.predmet);
        stringDateToInts(tmp.date);
        this->setTypeMess(_pom);
        //std::cout << "END_2\n";
    } else if(_pom == 27) {//stará denná statistika
        //std::cout << "start_3\n";
        cas_m = 0;
        _dayMonth_MSG = new day_Month_Message;
        _dayMonth_MSG->parsDayMonthStatistic(_buffer+1,0);    //posunutie +1 kôli bodke na začiatku
        pozicia = pars_Old_Message(_buffer+1);
        _dayMonth_MSG->parsDayMonthStatistic(pozicia,1);
        pozicia = pars_Old_Message(pozicia);
        _dayMonth_MSG->parsDayMonthStatistic(pozicia,2);
        pozicia = pars_Old_Message(pozicia);
        _dayMonth_MSG->parsDayMonthStatistic(pozicia,3);
        pozicia = pars_Old_Message(pozicia);
        _dayMonth_MSG->parsDayMonthStatistic(pozicia,4);
        pozicia = pars_Old_Message(pozicia);
        _dayMonth_MSG->boot_Ernno[0] = atoi(pozicia);
        pozicia = strchr(pozicia,'.');
        _dayMonth_MSG->boot_Ernno[1] = atoi(pozicia+1);
        stringDateToInts(tmp.date);
        tele = atoi(tmp.predmet);
        this->setTypeMess(_pom);
        //std::cout << "END_3\n";
    } else if(_pom == 32) {//stará mesacna statistika
        //std::cout << "OLD mes_statistic !!! " << tele << " " << tmp.predmet << std::endl;
        cas_m = 0;
        _dayMonth_MSG = new day_Month_Message;
        _dayMonth_MSG->parsDayMonthStatistic(_buffer+1,0);    //posunutie +1 kôli bodke na začiatku
        pozicia = pars_Old_Message(_buffer+1);
        _dayMonth_MSG->parsDayMonthStatistic(pozicia,1);
        pozicia = pars_Old_Message(pozicia);
        _dayMonth_MSG->parsDayMonthStatistic(pozicia,2);
        pozicia = pars_Old_Message(pozicia);
        _dayMonth_MSG->parsDayMonthStatistic(pozicia,3);
        pozicia = pars_Old_Message(pozicia);
        _dayMonth_MSG->parsDayMonthStatistic(pozicia,4);
        pozicia = pars_Old_Message(pozicia);
        _dayMonth_MSG->parsDayMonthStatistic(pozicia,5);
        pozicia = pars_Old_Message(pozicia);
        _dayMonth_MSG->boot_Ernno[0] = atoi(pozicia);
        pozicia = strchr(pozicia,'.');
        _dayMonth_MSG->boot_Ernno[1] = atoi(pozicia+1);
        std::cout << "Boot:_" << _dayMonth_MSG->boot_Ernno[0] << " ERRNO:_" << _dayMonth_MSG->boot_Ernno[0] << std::endl;
        stringDateToInts(tmp.date);
        tele = atoi(tmp.predmet);
        this->setTypeMess(32);
        //std::cout << "END OLD mes_statistic !!! " << std::endl;
    } else {
        return false;
    }
    return true;
}

int messages::pocitajBodky(char* pa_string) {
    int n = 0;
    while(*pa_string != '\0')   {
        if(*pa_string == '.')   {
            n++;
        }
        pa_string++;
    }
    return n;
}

void messages::setTypeMess(int pa_n) {
    switch(pa_n)    {
        case 1:
            this->type_MSG = ACTION_MSG;
            break;
        case 27:
        case 22:
            this->type_MSG = DAY_MSG;
            break;
        case 32:
        case 26:
            this->type_MSG = MONTH_MSG;
            break;
    }
}
