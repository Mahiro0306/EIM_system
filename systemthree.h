#ifndef SYSTEMTHREE_H
#define SYSTEMTHREE_H

#include"three_delete.h"
#include"three_fix.h"
#include"three_new.h"


#include <QMainWindow>
#define N 50//最大人数
class wage
{
public:
    QString _name;
    QString _gender;
    int _year;
    int _month;
    int _age;
    int _wage;
    QString _marry;
    QString _address;
    QString _title;
    QString _level;
};



namespace Ui {
class SystemThree;
}

class SystemThree : public QMainWindow
{
    Q_OBJECT

public:
    explicit SystemThree(QWidget *parent = nullptr);
    ~SystemThree();
    void Gread();

    static wage wag[N];
    static int existing;
    int min=0;
    int max=0;

    void paintEvent(QPaintEvent*);
private:
    Ui::SystemThree *ui;
    three_new *_new=NULL;
    three_delete *_del=NULL;
    three_fix *_fix=NULL;
signals:
    void sceneback();
};

#endif // SYSTEMTHREE_H
