#include "openfile.h"           //wind
#include "parser_window.h"      //wind
#include "miestnosti_tele.h"    //class
#include <QFileDialog>
#include "ui_openfile.h"

openFile::openFile(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::openFile)
{
    ui->setupUi(this);
}

openFile::~openFile()
{
    delete ui;
}

void openFile::on_F_openFile_button_clicked()
{
    subStruct.file = QFileDialog::getOpenFileName(this,tr("Open .txt file"),"C:/Users/Tomas/Documents/qtProject","All files (*.*)");
    ui->F_label_filename->setText(subStruct.file);
}

void openFile::on_F_ok_button_clicked()
{
    this->hide();
    /*conwert Qstring to char array*/
    QByteArray ba;
    ba = subStruct.file.toLatin1();
    subStruct.read.open(ba.data());
    /*open filestream*/
    parser_window p_wind;
    p_wind.setModal(true);
    p_wind.exec();
    this->close();
}
