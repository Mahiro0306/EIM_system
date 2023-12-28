#ifndef THREE_NEW_H
#define THREE_NEW_H

#include <QMainWindow>

namespace Ui {
class three_new;
}

class three_new : public QMainWindow
{
    Q_OBJECT

public:
    explicit three_new(QWidget *parent = nullptr);
    ~three_new();
    void paintEvent(QPaintEvent*);
private:
    Ui::three_new *ui;
signals:
    void sceneback();
};

#endif // THREE_NEW_H
