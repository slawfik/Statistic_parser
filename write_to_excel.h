#ifndef WRITE_TO_EXCEL_H
#define WRITE_TO_EXCEL_H

#include <conio.h>
#include "libxl.h"
#include <windows.h>
#include <stdio.h>
#include "miestnosti_tele.h"

using namespace libxl;

void createExcel_file(bool all_tele,int cislo_jednej_miestnosti,bool grafy,bool monthMSG);
void writeTele(miestnosti_tele* pa_miestnost,int c_miestnosti,bool action,bool month,bool day);
void setFont_formath();
void saveExcel_file(wchar_t* pa_filename);

#endif // WRITE_TO_EXCEL_H
