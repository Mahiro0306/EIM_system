#ifndef SELECTSCENE_H
#define SELECTSCENE_H

#include <QMainWindow>
#include"systemone.h"
#include"systemtwo.h"
#include"systemthree.h"
#include"systemfour.h"



namespace Ui {
class SelectScene;
}

class SelectScene : public QMainWindow
{
    Q_OBJECT

public:
    explicit SelectScene(QWidget *parent = nullptr);
    ~SelectScene();
    void paintEvent(QPaintEvent*);
private:
    Ui::SelectScene *ui;
    SystemOne *sy_1=NULL;
    SystemTwo *sy_2=NULL;
    SystemThree *sy_3=NULL;
    SystemFour *sy_4=NULL;
signals:
    void sceneback();
};

#endif // SELECTSCENE_H
