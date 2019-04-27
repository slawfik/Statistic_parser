#ifndef PARSER_WINDOW_H
#define PARSER_WINDOW_H

#include <QDialog>
#include <QtGui>
#include "write_to_excel.h"


namespace Ui {
class parser_window;
}

class parser_window : public QDialog
{
    Q_OBJECT

public:
    QStandardItemModel* tableModel;

    explicit parser_window(QWidget *parent = nullptr);
    void alocateTable(int pa_riadkov);
    void writeToTable(int miestnost,bool action_MSG,bool day_MSG, bool month_MSG);
    void freeTable() { delete tableModel; }
    ~parser_window();

private slots:
    void on_pw_okTele_button_clicked();

    void on_pw_selectTele_comboBox_activated(int index);

    void on_pw_actionFilter_checBox_stateChanged(int arg1);

    void on_pw_dayFilter_checBox_stateChanged(int arg1);

    void on_pw_monthFilter_checBox_stateChanged(int arg1);

    void on_wp_exportExcel_button_clicked();

    void on_pw_tatoMiestnost_checkBox_stateChanged(int arg1);

    void on_pw_vsetkyMiestnosti_checkBox_stateChanged(int arg1);

    void on_pw_info_button_clicked();

private:
    Ui::parser_window *ui;
};

#endif // PARSER_WINDOW_H
