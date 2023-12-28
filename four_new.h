#ifndef FOUR_NEW_H
#define FOUR_NEW_H

#include <QMainWindow>

namespace Ui {
class four_new;
}

class four_new : public QMainWindow
{
    Q_OBJECT

public:
    explicit four_new(QWidget *parent = nullptr);
    ~four_new();
    void paintEvent(QPaintEvent*);
private:
    Ui::four_new *ui;
signals:
    void sceneback();
};

#endif // FOUR_NEW_H
