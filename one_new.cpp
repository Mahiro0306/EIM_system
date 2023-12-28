#include "one_new.h"
#include "ui_one_new.h"
#include"systemone.h"
#include<QMessageBox>
#include<QFile>
#include<QTextStream>
#include<QPainter>
one_new::one_new(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::one_new)
{
    ui->setupUi(this);
    setWindowTitle("新增信息");
    setFixedSize(770,450);
    setWindowIcon(QIcon(":/incon.png"));

    //返回
    connect(ui->back,&QPushButton::clicked,[=](){

        emit sceneback();
    });
    //信息读取


    connect(ui->ok,&QPushButton::clicked,[=](){
        if(ui->id->text().isEmpty()||ui->name->text().isEmpty()||ui->title->text().isEmpty()
            ||ui->course1->text().isEmpty()||ui->course2->text().isEmpty()||ui->course3->text().isEmpty()
            ||ui->term1->text().isEmpty()||ui->term2->text().isEmpty()||ui->term3->text().isEmpty()
            ||ui->score1->text().isEmpty()||ui->score2->text().isEmpty()||ui->score3->text().isEmpty()
            ||ui->score->text().isEmpty()||!(ui->man->isChecked()||ui->woman->isChecked())
            ||!(ui->course1y->isChecked()||ui->course1n->isChecked())||!(ui->course2y->isChecked()||ui->course2n->isChecked())
            ||!(ui->course3y->isChecked()||ui->course3n->isChecked()))
        {QMessageBox::warning(this,"警告","信息不完全，请继续输入！");}
        else{
            SystemOne::tea[SystemOne::existingnum]._id=ui->id->text();
            SystemOne::tea[SystemOne::existingnum]._name=ui->name->text();
            SystemOne::tea[SystemOne::existingnum]._title=ui->title->text();
            SystemOne::tea[SystemOne::existingnum]._score=ui->score->text().toInt();
            if(ui->man->isChecked())
                SystemOne::tea[SystemOne::existingnum]._gender="男";
            else SystemOne::tea[SystemOne::existingnum]._gender="女";

            SystemOne::tea[SystemOne::existingnum].course[0]._cname=ui->course1->text();
            SystemOne::tea[SystemOne::existingnum].course[0]._term=ui->term1->text();
            SystemOne::tea[SystemOne::existingnum].course[0]._score=ui->score1->text();
            if(ui->course1y->isChecked())
                SystemOne::tea[SystemOne::existingnum].course[0]._property="学位";
            else SystemOne::tea[SystemOne::existingnum].course[0]._property="非学位";

            SystemOne::tea[SystemOne::existingnum].course[1]._cname=ui->course2->text();
            SystemOne::tea[SystemOne::existingnum].course[1]._term=ui->term2->text();
            SystemOne::tea[SystemOne::existingnum].course[1]._score=ui->score2->text();
            if(ui->course2y->isChecked())
                SystemOne::tea[SystemOne::existingnum].course[1]._property="学位";
            else SystemOne::tea[SystemOne::existingnum].course[1]._property="非学位";

            SystemOne::tea[SystemOne::existingnum].course[2]._cname=ui->course3->text();
            SystemOne::tea[SystemOne::existingnum].course[2]._term=ui->term3->text();
            SystemOne::tea[SystemOne::existingnum].course[2]._score=ui->score3->text();
            if(ui->course3y->isChecked())
                SystemOne::tea[SystemOne::existingnum].course[2]._property="学位";
            else SystemOne::tea[SystemOne::existingnum].course[2]._property="非学位";


            QFile f("D:\\info.dat");
            f.open(QIODevice::WriteOnly|QIODevice::Append);
            if(!f.isOpen())
            {
                qDebug()<<"!!!";
            }
            else{

                QString arr;
                arr=ui->id->text()+"\n"+ui->name->text()+"\n"+SystemOne::tea[SystemOne::existingnum]._gender+"\n"+ui->title->text()+"\n"
                      +ui->course1->text()+"\n"+ui->term1->text()+"\n"+ui->score1->text()+"\n"+SystemOne::tea[SystemOne::existingnum].course[0]._property+"\n"
                      +ui->course2->text()+"\n"+ui->term2->text()+"\n"+ui->score2->text()+"\n"+SystemOne::tea[SystemOne::existingnum].course[1]._property+"\n"
                      +ui->course3->text()+"\n"+ui->term3->text()+"\n"+ui->score3->text()+"\n"+SystemOne::tea[SystemOne::existingnum].course[2]._property+"\n"
                      +ui->score->text()+"\n";
                f.write(arr.toUtf8());
                f.close();

                SystemOne::existingnum++;
                QMessageBox::information(this,"提示信息","新增成功!");
                emit sceneback();
            }


        }

    });
}

void one_new::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/newbg.jpg");
    pix=pix.scaled(this->width(),this->height());
    painter.drawPixmap(0,0,pix);
}

one_new::~one_new()
{
    delete ui;
}
