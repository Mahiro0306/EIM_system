#ifndef ONE_SORT_H
#define ONE_SORT_H

#include <QMainWindow>

namespace Ui {
class one_sort;
}

class one_sort : public QMainWindow
{
    Q_OBJECT

public:
    explicit one_sort(QWidget *parent = nullptr);
    ~one_sort();
    int min=0;
    int max=0;

    void paintEvent(QPaintEvent*);
private:
    Ui::one_sort *ui;
signals:
    void sceneback();
};

#endif // ONE_SORT_H
