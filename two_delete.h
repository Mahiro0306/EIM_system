#ifndef TWO_DELETE_H
#define TWO_DELETE_H

#include <QMainWindow>

namespace Ui {
class two_delete;
}

class two_delete : public QMainWindow
{
    Q_OBJECT

public:
    explicit two_delete(QWidget *parent = nullptr);
    ~two_delete();
    void paintEvent(QPaintEvent*);
private:
    Ui::two_delete *ui;
signals:
    void sceneback();
};

#endif // TWO_DELETE_H
