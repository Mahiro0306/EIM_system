#include "selectscene.h"
#include "ui_selectscene.h"
#include<QMessageBox>
#include<QPainter>
SelectScene::SelectScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SelectScene)
{
    ui->setupUi(this);
    setWindowTitle("职工信息管理系统");
    setFixedSize(390,500);
    setWindowIcon(QIcon(":/incon.png"));
    //退出按钮
    connect(ui->exitpb,&QPushButton::clicked,[=](){
        if(QMessageBox::Yes==QMessageBox::question(this,"退出提示","确认退出吗？",QMessageBox::Yes|QMessageBox::No))
            close();
        else;
    });
    //返回按钮
    connect(ui->backpb,&QPushButton::clicked,[=](){
        if(QMessageBox::Yes==QMessageBox::question(this,"返回提示","返回登录界面？",QMessageBox::Yes|QMessageBox::No))
            emit sceneback();
        else;

    });
    //系统1

    connect(ui->system1,&QPushButton::clicked,[=](){
        sy_1=new SystemOne;
        sy_1->setGeometry(this->geometry());

        sy_1->show();
        this->hide();
        connect(sy_1,&SystemOne::sceneback,[=](){
            this->setGeometry(sy_1->geometry());
            this->show();
            sy_1->hide();
            delete sy_1;
            sy_1=NULL;
        });

    });
    //系统2

    connect(ui->system2,&QPushButton::clicked,[=](){
        sy_2=new SystemTwo;
        sy_2->setGeometry(this->geometry());

        sy_2->show();
        this->hide();
        connect(sy_2,&SystemTwo::sceneback,[=](){
            this->setGeometry(sy_2->geometry());
            this->show();
            sy_2->hide();
            delete sy_2;
            sy_2=NULL;
        });

    });
    //系统3

    connect(ui->system3,&QPushButton::clicked,[=](){
        sy_3=new SystemThree;
        sy_3->setGeometry(this->geometry());

        sy_3->show();
        this->hide();
        connect(sy_3,&SystemThree::sceneback,[=](){
            this->setGeometry(sy_3->geometry());
            this->show();
            sy_3->hide();
            delete sy_3;
            sy_3=NULL;
        });

    });
    //系统4

    connect(ui->system4,&QPushButton::clicked,[=](){
        sy_4=new SystemFour;
        sy_4->setGeometry(this->geometry());

        sy_4->show();
        this->hide();
        connect(sy_4,&SystemFour::sceneback,[=](){
            this->setGeometry(sy_4->geometry());
            this->show();
            sy_4->hide();
            delete sy_4;
            sy_4=NULL;
        });

    });
}

void SelectScene::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/selectbg.jpg");
    pix=pix.scaled(this->width(),this->height());
    painter.drawPixmap(0,0,pix);
}


SelectScene::~SelectScene()
{
    delete ui;
}
