#ifndef FOUR_FIX_NEW_H
#define FOUR_FIX_NEW_H

#include <QMainWindow>

namespace Ui {
class four_fix_new;
}

class four_fix_new : public QMainWindow
{
    Q_OBJECT

public:
    explicit four_fix_new(QWidget *parent = nullptr);
    ~four_fix_new();
    void paintEvent(QPaintEvent*);
private:
    Ui::four_fix_new *ui;
signals:
    void sceneback();
};

#endif // FOUR_FIX_NEW_H
