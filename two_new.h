#ifndef TWO_NEW_H
#define TWO_NEW_H

#include <QMainWindow>

namespace Ui {
class two_new;
}

class two_new : public QMainWindow
{
    Q_OBJECT

public:
    explicit two_new(QWidget *parent = nullptr);
    ~two_new();
    void paintEvent(QPaintEvent*);
private:
    Ui::two_new *ui;
signals:
    void sceneback();
};

#endif // TWO_NEW_H
