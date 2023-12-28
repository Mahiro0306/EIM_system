#ifndef ONE_INSERT_H
#define ONE_INSERT_H

#include <QMainWindow>

namespace Ui {
class one_insert;
}

class one_insert : public QMainWindow
{
    Q_OBJECT

public:
    explicit one_insert(QWidget *parent = nullptr);
    ~one_insert();
    int max=0;

    void paintEvent(QPaintEvent*);
private:
    Ui::one_insert *ui;
signals:
    void sceneback();
};

#endif // ONE_INSERT_H
