#ifndef SYSTEMTWO_H
#define SYSTEMTWO_H

#include <QMainWindow>
#include"two_new.h"
#include"two_delete.h"
#include"two_fix.h"
#include"password.h"
#define N 50//职工个数
class worker
{
public:
    QString _id;
    QString _name;
    QString _gender;
    int _year;
    int _month;
    int _age;
    QString _partment;
    QString _title;
    QString _level;
    QString _phone;

};


namespace Ui {
class SystemTwo;
}

class SystemTwo : public QMainWindow
{
    Q_OBJECT

public:
    explicit SystemTwo(QWidget *parent = nullptr);
    ~SystemTwo();
    void Wread();
    int min=0;
    static worker wor[N];
    static int existing;

    void paintEvent(QPaintEvent*);
private:
    Ui::SystemTwo *ui;
    two_new *_new=NULL;
    two_delete *_del=NULL;
    two_fix *_fix=NULL;
    password *_pw=NULL;
signals:
    void sceneback();
};

#endif // SYSTEMTWO_H
