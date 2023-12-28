#ifndef SYSTEMFOUR_H
#define SYSTEMFOUR_H

#include <QMainWindow>
#define N 50//最大人数
#include"four_fix.h"
#include"four_new.h"

class person
{
public:
    QString _name;
    QString _phone;
    QString _address;
    QString _detail;

};



namespace Ui {
class SystemFour;
}

class SystemFour : public QMainWindow
{
    Q_OBJECT

public:
    explicit SystemFour(QWidget *parent = nullptr);
    ~SystemFour();
    void Pread();
    static person per[N];
    static int existing;

    int min=0;

    void paintEvent(QPaintEvent*);
private:
    Ui::SystemFour *ui;
    four_new *_new=NULL;
    four_fix *_fix=NULL;
signals:
    void sceneback();
};

#endif // SYSTEMFOUR_H
