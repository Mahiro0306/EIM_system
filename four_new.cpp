#include "four_new.h"
#include "ui_four_new.h"
#include<QMessageBox>
#include<QFile>
#include"systemfour.h"
#include<QPainter>
four_new::four_new(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::four_new)
{
    ui->setupUi(this);
    setWindowTitle("新增信息");
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

            SystemFour::per[SystemFour::existing]._name=ui->name->text();
            SystemFour::per[SystemFour::existing]._phone=ui->phone->text();
            SystemFour::per[SystemFour::existing]._address=ui->add->text();
            SystemFour::per[SystemFour::existing]._detail=ui->detail->text();
            QFile f("D:\\per.dat");
            f.open(QIODevice::WriteOnly|QIODevice::Append);
            if(!f.isOpen())
            {
                qDebug()<<"!!!";
            }
            else{

                QString arr;
                arr=ui->name->text()+"\n"+ui->phone->text()+"\n"+ui->add->text()+"\n"+ui->detail->text()+"\n";

                f.write(arr.toUtf8());
                f.close();

                SystemFour::existing++;
                QMessageBox::information(this,"提示信息","新增成功!");
                emit sceneback();

            }
        }

    });
}

void four_new::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/newbg.jpg");
    pix=pix.scaled(this->width(),this->height());
    painter.drawPixmap(0,0,pix);
}


four_new::~four_new()
{
    delete ui;
}
