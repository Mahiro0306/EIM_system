#ifndef SYSTEMONE_H
#define SYSTEMONE_H

#include <QMainWindow>
#include"one_new.h"
#include"one_find.h"
#include"one_sort.h"
#include"one_insert.h"
//#include<QString>

#define N 50	//教师个数

using namespace std;
class Course
{
public:
    QString _cname;
    QString _term;
    QString _property;
    QString _score;
};
class Teacher
{
public:
    QString _id;
    QString _name;
    QString _title;
    QString _gender;
    Course course[3] = {};
    int _score;
};



namespace Ui {
class SystemOne;
}

class SystemOne : public QMainWindow
{
    Q_OBJECT

public:
    explicit SystemOne(QWidget *parent = nullptr);
    ~SystemOne();
    void Iread();

    static int existingnum;
    static Teacher tea[N];

    void paintEvent(QPaintEvent*);
private:
    Ui::SystemOne *ui;
    one_new *_new=NULL;
    one_find *_find=NULL;
    one_sort *_sort=NULL;
    one_insert *_insert=NULL;
signals:
    void sceneback();
};
#endif // SYSTEMONE_H

