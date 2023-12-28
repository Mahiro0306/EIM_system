#include "four_fix_new.h"
#include "ui_four_fix_new.h"
#include<QMessageBox>
#include<QFile>
#include"systemfour.h"
#include<QPainter>
four_fix_new::four_fix_new(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::four_fix_new)
{
    ui->setupUi(this);
    setWindowTitle("修改信息");
    setFixedSize(450,270);
    setWindowIcon(QIcon(":/incon.png"));

    //返回
    connect(ui->back,&QPushButton::clicked,[=](){
        emit sceneback();
    });

    //信息读取
    connect(ui->ok,&QPushButton::clicked,[=](){
        if(ui->name->text().isEmpty()||ui->phone->text().isEmpty()
            ||ui->add->text().isEmpty()||ui->detail->text().isEmpty())
        {QMessageBox::warning(this,"警告","信息不完全，请继续输入！");}
        else{

            SystemFour::per[four_fix::find]._name=ui->name->text();
            SystemFour::per[four_fix::find]._phone=ui->phone->text();
            SystemFour::per[four_fix::find]._address=ui->add->text();
            SystemFour::per[four_fix::find]._detail=ui->detail->text();
            QFile f("D:\\per.dat");
            f.open(QIODevice::WriteOnly|QIODevice::Truncate);
            if(!f.isOpen())
            {
                qDebug()<<"!!!";
            }
            else{

                QString arr="";
                for(int i=0;i<SystemFour::existing;i++)
                {
                    arr+=SystemFour::per[i]._name+"\n"+SystemFour::per[i]._phone+"\n"
                           +SystemFour::per[i]._address+"\n"+SystemFour::per[i]._detail+"\n";
                }

                f.write(arr.toUtf8());
                f.close();

                QMessageBox::information(this,"提示信息","修改成功!");

                emit sceneback();
            }
        }

    });
}

void four_fix_new::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/newbg.jpg");
    pix=pix.scaled(this->width(),this->height());
    painter.drawPixmap(0,0,pix);
}


four_fix_new::~four_fix_new()
{
    delete ui;
}
