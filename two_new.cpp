#include "two_new.h"
#include "ui_two_new.h"
#include<QMessageBox>
#include"systemtwo.h"
#include<QFile>
#include<QPainter>
two_new::two_new(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::two_new)
{
    ui->setupUi(this);
    setWindowTitle("录入信息");
    setFixedSize(620,330);
    setWindowIcon(QIcon(":/incon.png"));



    //返回
    connect(ui->back,&QPushButton::clicked,[=](){
        emit sceneback();
    });

    //信息读取
    connect(ui->ok,&QPushButton::clicked,[=](){
        if(ui->id->text().isEmpty()||ui->name->text().isEmpty()
            ||ui->year->text().isEmpty()||ui->month->text().isEmpty()||ui->age->text().isEmpty()
            ||ui->partment->text().isEmpty()||ui->title->text().isEmpty()||ui->level->text().isEmpty()||ui->phone->text().isEmpty()
            ||!(ui->man->isChecked()||ui->woman->isChecked()))
        {QMessageBox::warning(this,"警告","信息不完全，请继续输入！");}
        else{
            SystemTwo::wor[SystemTwo::existing]._id=ui->id->text();
            SystemTwo::wor[SystemTwo::existing]._name=ui->name->text();
            SystemTwo::wor[SystemTwo::existing]._year=ui->year->text().toInt();
            SystemTwo::wor[SystemTwo::existing]._month=ui->month->text().toInt();
            SystemTwo::wor[SystemTwo::existing]._age=ui->age->text().toInt();
            SystemTwo::wor[SystemTwo::existing]._partment=ui->partment->text();
            SystemTwo::wor[SystemTwo::existing]._title=ui->title->text();
            SystemTwo::wor[SystemTwo::existing]._level=ui->level->text();
            SystemTwo::wor[SystemTwo::existing]._phone=ui->phone->text();
            if(ui->man->isChecked())
                SystemTwo::wor[SystemTwo::existing]._gender="男";
            else SystemTwo::wor[SystemTwo::existing]._gender="女";


            QFile f("D:\\wor.dat");
            f.open(QIODevice::WriteOnly|QIODevice::Append);
            if(!f.isOpen())
            {
                qDebug()<<"!!!";
            }
            else{

                QString arr;
                arr=ui->id->text()+"\n"+ui->name->text()+"\n"+SystemTwo::wor[SystemTwo::existing]._gender+"\n"
                      +ui->year->text()+"\n"+ui->month->text()+"\n"+ui->age->text()+"\n"
                      +ui->partment->text()+"\n"+ui->title->text()+"\n"+ui->level->text()+"\n"+ui->phone->text()+"\n";

                f.write(arr.toUtf8());
                f.close();

                SystemTwo::existing++;
                QMessageBox::information(this,"提示信息","录入成功!");
                emit sceneback();

            }
        }

    });

}

void two_new::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/newbg.jpg");
    pix=pix.scaled(this->width(),this->height());
    painter.drawPixmap(0,0,pix);
}


two_new::~two_new()
{
    delete ui;
}
