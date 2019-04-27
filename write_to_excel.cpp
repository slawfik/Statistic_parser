#include "write_to_excel.h"

#define MONTH_SHEET 23
#define GRAF_SHEET 24

static Book* book;
static Sheet* sheet[25];
static Font *black_font;
static Format* blackBlodFormat;
static Format* blascNormal;
static Format* dateFormat;
static Format* timeFormat;

void setFont_formath() {
    black_font = book->addFont();
    black_font->setColor(COLOR_BLACK);
    black_font->setBold(true);

    blackBlodFormat = book->addFormat();
    blackBlodFormat->setFont(black_font);
    blackBlodFormat->setAlignH(ALIGNH_CENTER);
    blackBlodFormat->setAlignV(ALIGNV_CENTER);
    blackBlodFormat->setBorder(BORDERSTYLE_MEDIUM);

    blascNormal = book->addFormat();
    blascNormal->setAlignH(ALIGNH_CENTER);
    blascNormal->setAlignV(ALIGNV_CENTER);
    blascNormal->setBorder(BORDERSTYLE_MEDIUM);

    dateFormat = book->addFormat();
    dateFormat->setNumFormat(NUMFORMAT_DATE);
    dateFormat->setAlignV(ALIGNV_CENTER);
    dateFormat->setBorder(BORDERSTYLE_MEDIUM);

    timeFormat = book->addFormat();
    timeFormat->setNumFormat(NUMFORMAT_CUSTOM_HMM);
}

void writeTele(miestnosti_tele* pa_miestnost,int c_miestnosti,bool action,bool month,bool day) {
    wchar_t buffer[30];
    int coll, row = 3 ,row_M = c_miestnosti+3;
    std::cout << "hohoh_" <<c_miestnosti << "_mestno" << std::endl;
    for(int i = 0;i<pa_miestnost->n_akcii;i++)  {
        coll = 0;
        switch(pa_miestnost->array[i]->getType_MSG())   {
            case DAY_MSG:
            {
                if(day) {
                    sheet[c_miestnosti]->writeNum(row, coll++, book->datePack(pa_miestnost->array[i]->rok, pa_miestnost->array[i]->mesiac, pa_miestnost->array[i]->den), dateFormat);
                    swprintf(buffer,L"00:05");
                    sheet[c_miestnosti]->writeStr(row, coll++,buffer,blascNormal);
                    sheet[c_miestnosti]->writeStr(row, coll++,L"--",blascNormal);
                    for(int j = 0;j<5;j++)  {
                        sheet[c_miestnosti]->writeNum(row,coll,pa_miestnost->array[i]->_dayMonth_MSG->total_Time[j],blascNormal);
                        sheet[c_miestnosti]->writeNum(row,coll+5,pa_miestnost->array[i]->_dayMonth_MSG->min_Time[j],blascNormal);
                        sheet[c_miestnosti]->writeNum(row,coll+10,pa_miestnost->array[i]->_dayMonth_MSG->max_Time[j],blascNormal);
                        sheet[c_miestnosti]->writeNum(row,coll+15,pa_miestnost->array[i]->_dayMonth_MSG->arit_Priemer[j],blascNormal);
                        sheet[c_miestnosti]->writeNum(row,coll+20,pa_miestnost->array[i]->_dayMonth_MSG->couter[j],blascNormal);
                        coll++;
                    }
                    coll = coll+20;
                    sheet[c_miestnosti]->writeNum(row,coll++,pa_miestnost->array[i]->_dayMonth_MSG->boot_Ernno[0],blascNormal);
                    sheet[c_miestnosti]->writeNum(row,coll++,pa_miestnost->array[i]->_dayMonth_MSG->boot_Ernno[1],blascNormal);
                    row++;
                }
                break;
            }
            case MONTH_MSG:
            {
                if(month) {
                    //coll++;//tele
                    swprintf(buffer,L"tele-%d",c_miestnosti+1);
                    sheet[MONTH_SHEET]->writeStr(row_M, coll++,buffer,blascNormal);
                    sheet[MONTH_SHEET]->writeNum(row_M, coll++, book->datePack(pa_miestnost->array[i]->rok, pa_miestnost->array[i]->mesiac, pa_miestnost->array[i]->den), dateFormat);
                    swprintf(buffer,L"00:05");
                    sheet[MONTH_SHEET]->writeStr(row_M, coll++,buffer,blascNormal);
                    sheet[MONTH_SHEET]->writeStr(row_M, coll++,L"--",blascNormal);
                    for(int j = 0;j<5;j++)  {
                        sheet[MONTH_SHEET]->writeNum(row_M,coll,pa_miestnost->array[i]->_dayMonth_MSG->total_Time[j]/60.,blascNormal);
                        sheet[MONTH_SHEET]->writeNum(row_M,coll+5,pa_miestnost->array[i]->_dayMonth_MSG->min_Time[j]/60.,blascNormal);
                        sheet[MONTH_SHEET]->writeNum(row_M,coll+10,pa_miestnost->array[i]->_dayMonth_MSG->max_Time[j]/60.,blascNormal);
                        sheet[MONTH_SHEET]->writeNum(row_M,coll+15,pa_miestnost->array[i]->_dayMonth_MSG->arit_Priemer[j],blascNormal);
                        sheet[MONTH_SHEET]->writeNum(row_M,coll+20,pa_miestnost->array[i]->_dayMonth_MSG->couter[j],blascNormal);
                        sheet[MONTH_SHEET]->writeNum(row_M,coll+25,pa_miestnost->array[i]->_dayMonth_MSG->modus[j],blascNormal);
                        coll++;
                    }
                    coll = coll+25;
                    sheet[MONTH_SHEET]->writeNum(row_M,coll++,pa_miestnost->array[i]->_dayMonth_MSG->boot_Ernno[0],blascNormal);
                    sheet[MONTH_SHEET]->writeNum(row_M,coll++,pa_miestnost->array[i]->_dayMonth_MSG->boot_Ernno[1],blascNormal);
                }
                break;
            }
            case ACTION_MSG:
            {
                if(action) {
                    sheet[c_miestnosti]->writeNum(row, coll++, book->datePack(pa_miestnost->array[i]->rok, pa_miestnost->array[i]->mesiac, pa_miestnost->array[i]->den), dateFormat);
                    swprintf(buffer,L"%d:%d",pa_miestnost->array[i]->cas_m/60,pa_miestnost->array[i]->cas_m%60);
                    sheet[c_miestnosti]->writeStr(row, coll++,buffer,blascNormal);
                    sheet[c_miestnosti]->writeStr(row, coll++,pa_miestnost->array[i]->_action_MSG->getPopisCodu(),blascNormal);
                    row++;
                }
                break;
            }
        }
    }
    //sheet[0]->writeStr(2, 1, L"Hello, World !");
  /*  sheet->writeNum(4, 1, 1000);
    sheet->writeNum(5, 1, 2000);*/
    //sheet->writeFormula(6, 1, L"SUM(B5:B6)", boldFormat);
    //sheet->writeNum(8, 1, book->datePack(2011, 7, 20), dateFormat);

    //sheet->setCol(1, 1, 12);
}

void saveExcel_file(wchar_t* pa_filename)   {
    book->delSheet(4);  //tele-5 dont exist
    book->delSheet(14); //tele-16 dont exist
    book->save(pa_filename);
    book->release();
}

void formatHead(Sheet* pa_sheet)    {
    int coll = 0;
    pa_sheet->setCol(0,0,10.1);
    pa_sheet->setCol(2,2,12.1);
    pa_sheet->writeStr(2,coll++,L"Dátum",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Čas",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Code",blackBlodFormat);

    pa_sheet->setCol(3,28,6.1);
    pa_sheet->setMerge(1,1,3,7);
    pa_sheet->writeStr(1,3,L"Total Time",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Total",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"VGA",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Menu",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Prezent",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Viko",blackBlodFormat);

    pa_sheet->setMerge(1,1,8,12);
    pa_sheet->writeStr(1,8,L"Min Time",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Total",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"VGA",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Menu",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Prezent",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Viko",blackBlodFormat);

    pa_sheet->setMerge(1,1,13,17);
    pa_sheet->writeStr(1,13,L"Max Time",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Total",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"VGA",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Menu",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Prezent",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Viko",blackBlodFormat);

    pa_sheet->setMerge(1,1,18,22);
    pa_sheet->writeStr(1,18,L"Arit. priemer",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Total",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"VGA",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Menu",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Prezent",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Viko",blackBlodFormat);

    pa_sheet->setMerge(1,1,23,27);
    pa_sheet->writeStr(1,23,L"Counter",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Total",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"VGA",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Menu",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Prezent",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Viko",blackBlodFormat);

    pa_sheet->writeStr(2,coll++,L"Boot",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Errno",blackBlodFormat);
}

void formatHeadMonth(Sheet* pa_sheet)  {
    int coll = 0;
    pa_sheet->setCol(1,1,10.1);
    pa_sheet->setCol(2,2,12.1);
    pa_sheet->writeStr(2,coll++,L"Tele",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Dátum",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Čas",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Code",blackBlodFormat);

    pa_sheet->setCol(3,28,6.1);
    pa_sheet->setMerge(1,1,coll,coll+4);
    pa_sheet->writeStr(1,coll,L"Total Time",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Total",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"VGA",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Menu",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Prezent",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Viko",blackBlodFormat);

    pa_sheet->setMerge(1,1,coll,coll+4);
    pa_sheet->writeStr(1,coll,L"Min Time",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Total",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"VGA",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Menu",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Prezent",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Viko",blackBlodFormat);

    pa_sheet->setMerge(1,1,coll,coll+4);
    pa_sheet->writeStr(1,coll,L"Max Time",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Total",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"VGA",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Menu",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Prezent",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Viko",blackBlodFormat);

    pa_sheet->setMerge(1,1,coll,coll+4);
    pa_sheet->writeStr(1,coll,L"Arit. priemer",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Total",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"VGA",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Menu",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Prezent",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Viko",blackBlodFormat);

    pa_sheet->setMerge(1,1,coll,coll+4);
    pa_sheet->writeStr(1,coll,L"Counter",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Total",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"VGA",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Menu",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Prezent",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Viko",blackBlodFormat);

    pa_sheet->setMerge(1,1,coll,coll+4);
    pa_sheet->writeStr(1,coll,L"Modus",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Total",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"VGA",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Menu",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Prezent",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Viko",blackBlodFormat);

    pa_sheet->writeStr(2,coll++,L"Boot",blackBlodFormat);
    pa_sheet->writeStr(2,coll++,L"Errno",blackBlodFormat);
}

void createExcel_file(bool all_tele,int cislo_jednej_miestnosti,bool grafy,bool monthMSG) {
    wchar_t buff[25];
    book = xlCreateBook(); // use xlCreateXMLBook() for working with xlsx files
    setFont_formath();

    if(all_tele)    {
        for(int i = 0;i<22;i++)  {//tele 22 je este miestnosť!!!
            //if(i != 15 && i != 16){
                swprintf(buff,25,L"tele-%d",i+1);
                sheet[i] = book->addSheet(buff);
                formatHead(sheet[i]);
           //}
        }
        if(monthMSG)    {
             sheet[MONTH_SHEET] = book->addSheet(L"Month_Stat");
             formatHeadMonth(sheet[MONTH_SHEET]);
        }
        if(grafy) {
            sheet[GRAF_SHEET] = book->addSheet(L"Grafy");
        }
    } else {
        swprintf(buff,25,L"tele-%d",cislo_jednej_miestnosti+1);
        sheet[cislo_jednej_miestnosti] = book->addSheet(buff);
        formatHead(sheet[cislo_jednej_miestnosti]);
        if(monthMSG)    {
             sheet[MONTH_SHEET] = book->addSheet(L"Month_Stat");
             formatHeadMonth(sheet[MONTH_SHEET]);
        }
        if(grafy) {
            sheet[GRAF_SHEET] = book->addSheet(L"Grafy");
        }
    }
}
