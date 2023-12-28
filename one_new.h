#ifndef ONE_NEW_H
#define ONE_NEW_H

#include <QMainWindow>


namespace Ui {
class one_new;
}

class one_new : public QMainWindow
{
    Q_OBJECT

public:
    explicit one_new(QWidget *parent = nullptr);
    ~one_new();
    void paintEvent(QPaintEvent*);

private:
    Ui::one_new *ui;
signals:
    void sceneback();
};

#endif // ONE_NEW_H
