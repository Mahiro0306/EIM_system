#ifndef ONE_FIND_H
#define ONE_FIND_H

#include <QMainWindow>

namespace Ui {
class one_find;
}

class one_find : public QMainWindow
{
    Q_OBJECT

public:
    explicit one_find(QWidget *parent = nullptr);
    ~one_find();


    void paintEvent(QPaintEvent*);
private:
    Ui::one_find *ui;
signals:
    void sceneback();
};

#endif // ONE_FIND_H
