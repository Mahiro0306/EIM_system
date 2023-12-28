#include "two_fix_new.h"
#include "ui_two_fix_new.h"
#include<QMessageBox>
#include<QFile>
#include"systemtwo.h"
#include"two_fix.h"
#include<QPainter>
two_fix_new::two_fix_new(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::two_fix_new)
{
    ui->setupUi(this);
    setWindowTitle("修改信息");
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
            SystemTwo::wor[two_fix::find]._id=ui->id->text();
            SystemTwo::wor[two_fix::find]._name=ui->name->text();
            SystemTwo::wor[two_fix::find]._year=ui->year->text().toInt();
            SystemTwo::wor[two_fix::find]._month=ui->month->text().toInt();
            SystemTwo::wor[two_fix::find]._age=ui->age->text().toInt();
            SystemTwo::wor[two_fix::find]._partment=ui->partment->text();
            SystemTwo::wor[two_fix::find]._title=ui->title->text();
            SystemTwo::wor[two_fix::find]._level=ui->level->text();
            SystemTwo::wor[two_fix::find]._phone=ui->phone->text();
            if(ui->man->isChecked())
                SystemTwo::wor[two_fix::find]._gender="男";
            else SystemTwo::wor[two_fix::find]._gender="女";

            QFile f("D:\\wor.dat");
            f.open(QIODevice::WriteOnly|QIODevice::Truncate);
            if(!f.isOpen())
            {
                qDebug()<<"!!!";
            }
            else{

                QString arr="";
                for(int i=0;i<SystemTwo::existing;i++)
                {
                    arr+=SystemTwo::wor[i]._id+"\n"+SystemTwo::wor[i]._name+"\n"+SystemTwo::wor[i]._gender+"\n"
                           +QString::number(SystemTwo::wor[i]._year)+"\n"+QString::number(SystemTwo::wor[i]._month)+QString::number(SystemTwo::wor[i]._age)+"\n"
                           +SystemTwo::wor[i]._partment+"\n"+SystemTwo::wor[i]._title+"\n"+SystemTwo::wor[i]._level+"\n"+SystemTwo::wor[i]._phone+"\n";
                }

                f.write(arr.toUtf8());
                f.close();

                QMessageBox::information(this,"提示信息","修改成功!");
                emit sceneback();
            }
        }

    });

}

void two_fix_new::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/newbg.jpg");
    pix=pix.scaled(this->width(),this->height());
    painter.drawPixmap(0,0,pix);
}


two_fix_new::~two_fix_new()
{
    delete ui;
}
