#ifndef OPENFILE_H
#define OPENFILE_H

#include <QMainWindow>

namespace Ui {
class openFile;
}

class openFile : public QMainWindow
{
    Q_OBJECT

public:
    explicit openFile(QWidget *parent = nullptr);
    ~openFile();

private slots:

    void on_F_openFile_button_clicked();

    void on_F_ok_button_clicked();

private:
    Ui::openFile *ui;
};

#endif // OPENFILE_H
