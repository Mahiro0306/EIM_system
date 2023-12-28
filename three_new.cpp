#include "three_new.h"
#include "ui_three_new.h"
#include"systemthree.h"
#include<QMessageBox>
#include<QFile>
#include<QPainter>
three_new::three_new(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::three_new)
{
    //初始化
    ui->setupUi(this);
    setWindowTitle("新建信息");
    setFixedSize(520,350);
    setWindowIcon(QIcon(":/incon.png"));


    //返回
    connect(ui->back,&QPushButton::clicked,[=](){
        emit sceneback();
    });

    //信息读取
    connect(ui->ok,&QPushButton::clicked,[=](){
        if(ui->name->text().isEmpty()||ui->year->text().isEmpty()||ui->month->text().isEmpty()||ui->age->text().isEmpty()
            ||ui->title->text().isEmpty()||ui->level->text().isEmpty()||ui->add->text().isEmpty()||ui->wage->text().isEmpty()
            ||!(ui->man->isChecked()||ui->woman->isChecked())||!(ui->marryed->isChecked()||ui->unmarryed->isChecked()))
        {QMessageBox::warning(this,"警告","信息不完全，请继续输入！");}
        else{
            SystemThree::wag[SystemThree::existing]._name=ui->name->text();
            SystemThree::wag[SystemThree::existing]._year=ui->year->text().toInt();
            SystemThree::wag[SystemThree::existing]._month=ui->month->text().toInt();
            SystemThree::wag[SystemThree::existing]._age=ui->age->text().toInt();
            SystemThree::wag[SystemThree::existing]._wage=ui->wage->text().toInt();
            SystemThree::wag[SystemThree::existing]._address=ui->add->text();
            SystemThree::wag[SystemThree::existing]._title=ui->title->text();
            SystemThree::wag[SystemThree::existing]._level=ui->level->text();

            if(ui->man->isChecked())
                SystemThree::wag[SystemThree::existing]._gender="男";
            else SystemThree::wag[SystemThree::existing]._gender="女";

            if(ui->marryed->isChecked())
                SystemThree::wag[SystemThree::existing]._marry="已婚";
            else SystemThree::wag[SystemThree::existing]._marry="未婚";


            QFile f("D:\\wag.dat");
            f.open(QIODevice::WriteOnly|QIODevice::Append);
            if(!f.isOpen())
            {
                qDebug()<<"!!!";
            }
            else{

                QString arr;
                arr=ui->name->text()+"\n"+SystemThree::wag[SystemThree::existing]._gender+"\n"
                      +ui->year->text()+"\n"+ui->month->text()+"\n"+ui->age->text()+"\n"
                      +SystemThree::wag[SystemThree::existing]._marry+ui->add->text()+"\n"+"\n"+ui->title->text()+"\n"
                      +ui->wage->text()+"\n"+ui->level->text()+"\n";

                f.write(arr.toUtf8());
                f.close();

                SystemThree::existing++;
                QMessageBox::information(this,"提示信息","新建成功!");
                emit sceneback();

            }
        }

    });
}

void three_new::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/newbg.jpg");
    pix=pix.scaled(this->width(),this->height());
    painter.drawPixmap(0,0,pix);
}


three_new::~three_new()
{
    delete ui;
}
