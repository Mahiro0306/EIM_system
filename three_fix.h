#ifndef THREE_FIX_H
#define THREE_FIX_H

#include <QMainWindow>
#include"three_fix_new.h"
namespace Ui {
class three_fix;
}

class three_fix : public QMainWindow
{
    Q_OBJECT

public:
    explicit three_fix(QWidget *parent = nullptr);
    ~three_fix();
    static int find;
    void paintEvent(QPaintEvent*);
private:
    Ui::three_fix *ui;
    three_fix_new *_new=NULL;
signals:
    void sceneback();
};

#endif // THREE_FIX_H
