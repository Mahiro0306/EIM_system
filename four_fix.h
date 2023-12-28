#ifndef FOUR_FIX_H
#define FOUR_FIX_H

#include"four_fix_new.h"
#include <QMainWindow>

namespace Ui {
class four_fix;
}

class four_fix : public QMainWindow
{
    Q_OBJECT

public:
    explicit four_fix(QWidget *parent = nullptr);
    ~four_fix();
    bool _flag=0;
    static int find;
    void paintEvent(QPaintEvent*);
private:
    Ui::four_fix *ui;
    four_fix_new *_new=NULL;
signals:
    void sceneback();
};

#endif // FOUR_FIX_H
