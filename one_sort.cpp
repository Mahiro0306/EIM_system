#include "one_sort.h"
#include "ui_one_sort.h"
#include"systemone.h"
#include<QMessageBox>
#include<QPainter>
one_sort::one_sort(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::one_sort)
{
    ui->setupUi(this);

    setWindowTitle("排序信息");
    setFixedSize(460,500);
    setWindowIcon(QIcon(":/incon.png"));


    connect(ui->sort,&QPushButton::clicked,[=](){


        bool flag=true;
        if(ui->id->isChecked())

            for(int i=0;i<SystemOne::existingnum-1;i++)
            {
                min=i;
                for(int j=i+1;j<SystemOne::existingnum;j++)
                {
                    if(SystemOne::tea[j]._id<SystemOne::tea[min]._id)
                    {
                        min=j;
                    }
                }
                if(min!=i)
                {
                    Teacher temp;
                    temp=SystemOne::tea[i];
                    SystemOne::tea[i]=SystemOne::tea[min];
                    SystemOne::tea[min]=temp;
                }

            }


        else if(ui->score->isChecked())
            for(int i=0;i<SystemOne::existingnum-1;i++)
            {
                max=i;
                for(int j=i+1;j<SystemOne::existingnum;j++)
                {
                    if(SystemOne::tea[j]._score>SystemOne::tea[max]._score)
                    {
                        max=j;
                    }
                }
                if(max!=i)
                {
                    Teacher temp;
                    temp=SystemOne::tea[i];
                    SystemOne::tea[i]=SystemOne::tea[max];
                    SystemOne::tea[max]=temp;
                }

            }
        else{
            QMessageBox::warning(this,"警告","未选择排序方式！");
            flag=false;
        }
        if(flag){

            QString str="";
            QString _str="";
            for(int i=0;i<SystemOne::existingnum;i++)
            {
                str+="职工号："+SystemOne::tea[i]._id+"     "+"姓名："+SystemOne::tea[i]._name+"     "+"性别："+SystemOne::tea[i]._gender+"\n"
                        +"职称："+SystemOne::tea[i]._title+"     "+"教学综合评分："+QString::number(SystemOne::tea[i]._score)+"\n";
                for(int j=0;j<3;j++)
                    {
                        _str=QString("主讲课程%1：").arg(j+1);
                        str+=_str+SystemOne::tea[i].course[j]._cname+"     "+"开课学期："+SystemOne::tea[i].course[j]._term+"\n"
                                +"课程性质："+SystemOne::tea[i].course[j]._property+"     "+"教学效果："+SystemOne::tea[i].course[j]._score+"\n";
                    }
                str+="\n";
            }
            ui->showarea->setText(str);

        }
    });

    //返回
    connect(ui->back,&QPushButton::clicked,[=](){
        emit sceneback();
    });
}


void one_sort::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/fixbg.png");
    pix=pix.scaled(this->width(),this->height());
    painter.drawPixmap(0,0,pix);
}


one_sort::~one_sort()
{
    delete ui;
}
