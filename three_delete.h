#ifndef THREE_DELETE_H
#define THREE_DELETE_H

#include <QMainWindow>

namespace Ui {
class three_delete;
}

class three_delete : public QMainWindow
{
    Q_OBJECT

public:
    explicit three_delete(QWidget *parent = nullptr);
    ~three_delete();
    void paintEvent(QPaintEvent*);
private:
    Ui::three_delete *ui;
signals:
    void sceneback();
};

#endif // THREE_DELETE_H
