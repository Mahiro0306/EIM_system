#include "three_fix_new.h"
#include "ui_three_fix_new.h"
#include<QMessageBox>
#include<QFile>
#include"systemthree.h"
#include<QPainter>
three_fix_new::three_fix_new(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::three_fix_new)
{
    ui->setupUi(this);
    setWindowTitle("修改信息");
    setFixedSize(500,340);
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
            SystemThree::wag[three_fix::find]._name=ui->name->text();
            SystemThree::wag[three_fix::find]._year=ui->year->text().toInt();
            SystemThree::wag[three_fix::find]._month=ui->month->text().toInt();
            SystemThree::wag[three_fix::find]._age=ui->age->text().toInt();
            SystemThree::wag[three_fix::find]._address=ui->add->text();
            SystemThree::wag[three_fix::find]._title=ui->title->text();
            SystemThree::wag[three_fix::find]._wage=ui->wage->text().toInt();
            SystemThree::wag[three_fix::find]._level=ui->level->text();
            if(ui->man->isChecked())
                SystemThree::wag[three_fix::find]._gender="男";
            else SystemThree::wag[three_fix::find]._gender="女";
            if(ui->marryed->isChecked())
                SystemThree::wag[three_fix::find]._marry="已婚";
            else SystemThree::wag[three_fix::find]._marry="未婚";

            QFile f("D:\\wag.dat");
            f.open(QIODevice::WriteOnly|QIODevice::Truncate);
            if(!f.isOpen())
            {
                qDebug()<<"!!!";
            }
            else{

                QString arr="";
                for(int i=0;i<SystemThree::existing;i++)
                {
                    arr=SystemThree::wag[i]._name+"\n"+SystemThree::wag[i]._gender+"\n"
                          +QString::number(SystemThree::wag[i]._year)+"\n"+QString::number(SystemThree::wag[i]._month)+"\n"+QString::number(SystemThree::wag[i]._age)+"\n"
                          +SystemThree::wag[i]._marry+"\n"+SystemThree::wag[i]._address+"\n"+SystemThree::wag[i]._title+"\n"
                          +QString::number(SystemThree::wag[i]._wage)+"\n"+SystemThree::wag[i]._level+"\n";
                }

                f.write(arr.toUtf8());
                f.close();

                QMessageBox::information(this,"提示信息","修改成功!");
                emit sceneback();
            }
        }

    });
}


void three_fix_new::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/newbg.jpg");
    pix=pix.scaled(this->width(),this->height());
    painter.drawPixmap(0,0,pix);
}


three_fix_new::~three_fix_new()
{
    delete ui;
}
