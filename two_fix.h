#ifndef TWO_FIX_H
#define TWO_FIX_H

#include "two_fix_new.h"
#include <QMainWindow>

namespace Ui {
class two_fix;
}

class two_fix : public QMainWindow
{
    Q_OBJECT

public:
    explicit two_fix(QWidget *parent = nullptr);
    ~two_fix();
    static int find;
    void paintEvent(QPaintEvent*);
private:
    Ui::two_fix *ui;
    two_fix_new *_new=NULL;
signals:
    void sceneback();
};

#endif // TWO_FIX_H
