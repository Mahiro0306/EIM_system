#ifndef PASSWORD_H
#define PASSWORD_H

#include <QMainWindow>

namespace Ui {
class password;
}

class password : public QMainWindow
{
    Q_OBJECT

public:
    explicit password(QWidget *parent = nullptr);
    ~password();

private:
    Ui::password *ui;
signals:
    void sceneback();
    void passed();
};

#endif // PASSWORD_H
