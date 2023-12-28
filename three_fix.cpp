#include "three_fix.h"
#include "ui_three_fix.h"
#include"systemthree.h"
#include<QMessageBox>
#include<QPainter>
int three_fix::find=0;

three_fix::three_fix(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::three_fix)
{
    ui->setupUi(this);
    setWindowTitle("修改信息");
    setFixedSize(350,150);
    setWindowIcon(QIcon(":/incon.png"));


    connect(ui->ok,&QPushButton::clicked,[=](){
        bool found=false;
        for(int i=0;i<SystemThree::existing;i++)
        {
            if(SystemThree::wag[i]._name==ui->fix->text())
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
                _new=new three_fix_new;
                _new->setGeometry(this->geometry());

                _new->show();
                this->hide();
                connect(_new,&three_fix_new::sceneback,[=](){
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

void three_fix::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/delbg.jpg");
    pix=pix.scaled(this->width(),this->height());
    painter.drawPixmap(0,0,pix);
}

three_fix::~three_fix()
{
    delete ui;
}
