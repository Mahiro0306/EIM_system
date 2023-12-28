#ifndef THREE_FIX_NEW_H
#define THREE_FIX_NEW_H

#include <QMainWindow>

namespace Ui {
class three_fix_new;
}

class three_fix_new : public QMainWindow
{
    Q_OBJECT

public:
    explicit three_fix_new(QWidget *parent = nullptr);
    ~three_fix_new();
    void paintEvent(QPaintEvent*);
private:
    Ui::three_fix_new *ui;
signals:
    void sceneback();
};

#endif // THREE_FIX_NEW_H
