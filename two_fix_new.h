#ifndef TWO_FIX_NEW_H
#define TWO_FIX_NEW_H

#include <QMainWindow>

namespace Ui {
class two_fix_new;
}

class two_fix_new : public QMainWindow
{
    Q_OBJECT

public:
    explicit two_fix_new(QWidget *parent = nullptr);
    ~two_fix_new();
    void paintEvent(QPaintEvent*);
private:
    Ui::two_fix_new *ui;
signals:
    void sceneback();
};

#endif // TWO_FIX_NEW_H
