#include "parser_window.h"
#include "ui_parser_window.h"
#include "miestnosti_tele.h"
#include <QMessageBox>
#include <iostream>

void createObjectStructure();

parser_window::parser_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::parser_window)
{
    ui->setupUi(this);
    alocateTable(0);
    for(int i = 1;i<23;i++) {
       // if(i != 15 && i != 16){     //nee
            ui->pw_selectTele_comboBox->addItem("tele-"+QString::number(i));
       // }
    }
    createObjectStructure();
    ui->pw_actionFilter_checBox->setChecked(true);
    ui->pw_dayFilter_checBox->setChecked(false);
    ui->pw_tatoMiestnost_checkBox->setChecked(true);
}

parser_window::~parser_window()
{
    delete ui;
}

void parser_window::on_pw_okTele_button_clicked()
{
    char buffer[80];
    subStruct.read >> buffer;
    ui->pw_label1->setText(buffer);
}

void createObjectStructure()
{
    int numTele;
    char buffer[200];

    messages sprava;

    while(!subStruct.read.eof())
    {
        subStruct.read >> buffer;
        if(!strcmp(buffer,"Sm:"))
        {
            if(sprava.parsMSG(subStruct.read))    {
                //std::cout << "start write\n";
                numTele = sprava.getNumtele();
                teleMiestnosti[numTele].array[teleMiestnosti[numTele].n_akcii] = new messages;
                *(teleMiestnosti[numTele].array[teleMiestnosti[numTele].n_akcii]) = sprava;
                teleMiestnosti[numTele].n_akcii++;
                //std::cout << "NUmtele_" << teleMiestnosti[numTele].n_akcii << std::endl;
                //std::cout << "end write\n";
            }
        } else if(!strcmp(buffer,"Predmet:"))    {
            subStruct.read >> buffer;
            strcpy(tmp.predmet,buffer);
        } else if(!strcmp(buffer,"Dátum:"))    {
            //subStruct.read >> buffer;
            subStruct.read.getline(tmp.date,40);
            std::cout << "M_" <<tmp.predmet << "__!" <<tmp.date <<"\n";
            //strcpy(tmp.date,buffer);
        }
    }
}

void parser_window::on_pw_selectTele_comboBox_activated(int index)
{
    writeToTable(index+1,ui->pw_actionFilter_checBox->isChecked(),ui->pw_dayFilter_checBox->isChecked(),ui->pw_monthFilter_checBox->isChecked());
    ui->pw_label1->setText("Zobrazené správy: tele-"+QString::number(index+1));
}

void parser_window::alocateTable(int pa_riadkov)
{
    int count_row = 28;
  //QStyleOptionViewItem opt;
    tableModel = new QStandardItemModel(pa_riadkov,count_row,this);
    ui->tableView->setColumnWidth(0,70);
    ui->tableView->setColumnWidth(1,35);
    //opt.backgroundBrush.setColor(Qt::blue);
    for(int i = 3;i<(count_row+1);i++) {
        ui->tableView->setColumnWidth(i,40);
    }
}

void parser_window::writeToTable(int miestnost,bool action_MSG,bool day_MSG, bool month_MSG) {
    char buffer[200];
    int col = 0, row = -1;
    QStringList datum,cas;
    QString mod;
    QModelIndex index;
    //BackgroundColorRole backg;

    freeTable();
    alocateTable(teleMiestnosti[miestnost].n_akcii);

    for(int i = 0;i<teleMiestnosti[miestnost].n_akcii;i++)   {
        if(teleMiestnosti[miestnost].array[i]->getType_MSG() == ACTION_MSG && action_MSG)       {
            sprintf(buffer,"%d.%d.%d",teleMiestnosti[miestnost].array[i]->den,teleMiestnosti[miestnost].array[i]->mesiac,teleMiestnosti[miestnost].array[i]->rok);
            index = tableModel->index(++row,col,QModelIndex());
            tableModel->setData(index,buffer);
/*            QVariant aa = index.data(Qt::BackgroundRole);

            //QBrush(Qt::red);
            QBrush a;
            a.setColor(Qt::red);*/


            index = tableModel->index(row,++col,QModelIndex());
            sprintf(buffer,"%d:%d",teleMiestnosti[miestnost].array[i]->cas_m/60,teleMiestnosti[miestnost].array[i]->cas_m%60);
            tableModel->setData(index,buffer);

            index = tableModel->index(row,++col,QModelIndex());
            mod = QString::fromWCharArray(teleMiestnosti[miestnost].array[i]->_action_MSG->getPopisCodu());
            tableModel->setData(index,mod);
            col=0;
        } else if(teleMiestnosti[miestnost].array[i]->getType_MSG() == DAY_MSG && day_MSG) {
            sprintf(buffer,"%d.%d.%d",teleMiestnosti[miestnost].array[i]->den,teleMiestnosti[miestnost].array[i]->mesiac,teleMiestnosti[miestnost].array[i]->rok);
            index = tableModel->index(++row,col,QModelIndex());
            tableModel->setData(index,buffer);

            index = tableModel->index(row,++col,QModelIndex());
            sprintf(buffer,"--:--");
            tableModel->setData(index,buffer);

            index = tableModel->index(row,++col,QModelIndex());
            sprintf(buffer,"--");
            tableModel->setData(index,buffer);
            int j = 0;
            while(j != 5)   {
                index = tableModel->index(row,++col,QModelIndex());
                tableModel->setData(index,teleMiestnosti[miestnost].array[i]->_dayMonth_MSG->total_Time[j++]);
            }
            j = 0;
            while(j != 5)   {
                index = tableModel->index(row,++col,QModelIndex());
                tableModel->setData(index,teleMiestnosti[miestnost].array[i]->_dayMonth_MSG->min_Time[j++]);
            }
            j = 0;
            while(j != 5)   {
                index = tableModel->index(row,++col,QModelIndex());
                tableModel->setData(index,teleMiestnosti[miestnost].array[i]->_dayMonth_MSG->max_Time[j++]);
            }
            j = 0;
            while(j != 5)   {
                index = tableModel->index(row,++col,QModelIndex());
                tableModel->setData(index,teleMiestnosti[miestnost].array[i]->_dayMonth_MSG->arit_Priemer[j++]);
            }
            j = 0;
            while(j != 5)   {
                index = tableModel->index(row,++col,QModelIndex());
                tableModel->setData(index,teleMiestnosti[miestnost].array[i]->_dayMonth_MSG->couter[j++]);
            }
            col=0;
        } else if(teleMiestnosti[miestnost].array[i]->getType_MSG() == MONTH_MSG && month_MSG) {
            sprintf(buffer,"MONTH_M");
            index = tableModel->index(++row,col,QModelIndex());
            tableModel->setData(index,buffer);

            index = tableModel->index(row,++col,QModelIndex());
            sprintf(buffer,"--:--");
            tableModel->setData(index,buffer);

            index = tableModel->index(row,++col,QModelIndex());
            sprintf(buffer,"--");
            tableModel->setData(index,buffer);
            col=0;
        }
    }
    QStringList head;
    head << "Dátum" << "Čas" << "Code" << "Total" << "VGA" << "menu" << "prez" << "viko" << "-Total" << "-VGA"
         << "-menu" << "-prez" << "-viko" <<"+Total" << "+VGA" << "+menu" << "+prez" << "+viko" << "ATotal" << "AVGA"
         << "Amenu" << "Aprez" << "Aviko" << "CTotal" << "CVGA" << "Cmenu" << "Cprez" << "Cviko";
    tableModel->setHorizontalHeaderLabels(head);
    ui->tableView->setModel(tableModel);
}

void parser_window::on_pw_actionFilter_checBox_stateChanged(int arg1)
{
    writeToTable(ui->pw_selectTele_comboBox->currentIndex()+1,
                 arg1,
                 ui->pw_dayFilter_checBox->isChecked(),
                 ui->pw_monthFilter_checBox->isChecked());
}

void parser_window::on_pw_dayFilter_checBox_stateChanged(int arg1)
{
    writeToTable(ui->pw_selectTele_comboBox->currentIndex()+1,
                 ui->pw_actionFilter_checBox->isChecked(),
                 arg1,
                 ui->pw_monthFilter_checBox->isChecked());
}

void parser_window::on_pw_monthFilter_checBox_stateChanged(int arg1)
{
    writeToTable(ui->pw_selectTele_comboBox->currentIndex()+1,
                 ui->pw_actionFilter_checBox->isChecked(),
                 ui->pw_dayFilter_checBox->isChecked(),
                 arg1);
}

void parser_window::on_wp_exportExcel_button_clicked()
{
    char buffer[50];
    char filename[20];
    wchar_t fileName[20];

    if(ui->pw_tatoMiestnost_checkBox->isChecked()) {
        createExcel_file(false,ui->pw_selectTele_comboBox->currentIndex(),
                         ui->pw_grafy_checkBox->isChecked(),
                         true);
        swprintf(fileName,L"excel_tele_%d.xls",ui->pw_selectTele_comboBox->currentIndex()+1);
        sprintf(filename,"excel_tele_%d.xls",ui->pw_selectTele_comboBox->currentIndex()+1);
        sprintf(buffer,"Bol vytvorený súbor excel s názvom \"%s\" .",filename);
        writeTele(&teleMiestnosti[ui->pw_selectTele_comboBox->currentIndex()+1],
                ui->pw_selectTele_comboBox->currentIndex(),
                true,
                true,
                true);
    } else if(ui->pw_vsetkyMiestnosti_checkBox->isChecked()) {
        swprintf(fileName,L"excel_ALL_tele.xls");
        sprintf(filename,"excel_ALL_tele.xls");
        sprintf(buffer,"Bol vytvorený súbor excel s názvom \"%s\" .",filename);
        createExcel_file(true,0,ui->pw_grafy_checkBox->isChecked(),true);
        for(int i = 1;i<23;i++) {
            writeTele(&teleMiestnosti[i],i-1,true,true,true);
        }
    }
    saveExcel_file(fileName);
    QMessageBox::information(this,tr("Export info:"),tr(buffer));
}

void parser_window::on_pw_tatoMiestnost_checkBox_stateChanged(int arg1)
{
    if(arg1)    {
        ui->pw_vsetkyMiestnosti_checkBox->setChecked(false);
    }   else {
        ui->pw_vsetkyMiestnosti_checkBox->setChecked(true);
    }
}

void parser_window::on_pw_vsetkyMiestnosti_checkBox_stateChanged(int arg1)
{
    if(arg1)    {
        ui->pw_tatoMiestnost_checkBox->setChecked(false);
    }   else {
         ui->pw_tatoMiestnost_checkBox->setChecked(true);
    }
}

void parser_window::on_pw_info_button_clicked()
{
    QMessageBox::information(this,tr("Export info:"),tr("Program vyexportuje vždy všetky správy! Možnosti exportu excelu sú len "
                                                        "v tom či chceme exportovať všetky miestnosti alebo len jednu + dá sa"
                                                        " zvoliť či chceme vytvoriť zošit pre grafy.\n\n"
                                                        "Nepridaná funkcionalita parsovania logových správ!"));
}
