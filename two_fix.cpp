#include "two_fix.h"
#include "ui_two_fix.h"
#include"systemtwo.h"
#include<QMessageBox>
#include<QPainter>
int two_fix::find=0;

two_fix::two_fix(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::two_fix)
{
    ui->setupUi(this);
    setWindowTitle("修改信息");
    setFixedSize(350,150);
    setWindowIcon(QIcon(":/incon.png"));


    connect(ui->ok,&QPushButton::clicked,[=](){
        bool found=false;
        for(int i=0;i<SystemTwo::existing;i++)
        {
            if(SystemTwo::wor[i]._id==ui->fix->text())
            {
                find=i;
                found=true;
                break;
            }
        }

        if(found)
        {
            if(QMessageBox::Yes==QMessageBox::question(this,"修改提示","已找到相关信息，是否对其修改？",QMessageBox::Yes|QMessageBox::No))
            {
                _new=new two_fix_new;
                _new->setGeometry(this->geometry());

                _new->show();
                this->hide();
                connect(_new,&two_fix_new::sceneback,[=](){
                    this->setGeometry(_new->geometry());
                    ui->fix->clear();
                    this->show();
                    _new->hide();
                    delete _new;
                    _new=NULL;
                });
            }
        }
        else
        {
            QMessageBox::warning(this,"警告","未找到相关信息");
        }
    });


    //返回
    connect(ui->back,&QPushButton::clicked,[=](){
        emit sceneback();
    });


}


void two_fix::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/delbg.jpg");
    pix=pix.scaled(this->width(),this->height());
    painter.drawPixmap(0,0,pix);
}

two_fix::~two_fix()
{
    delete ui;
}
