#include "one_find.h"
#include "ui_one_find.h"
#include"systemone.h"
#include<QMessageBox>
#include<QPainter>
one_find::one_find(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::one_find)
{
    ui->setupUi(this);
    setWindowTitle("查找信息");
    setFixedSize(460,500);
    setWindowIcon(QIcon(":/incon.png"));

    connect(ui->findpb,&QPushButton::clicked,[=](){
        int find[N]={};
        int count=0;
        bool flag=true;
        if(ui->nf->isChecked())
            for(int i=0;i<SystemOne::existingnum;i++)
            {
                if(SystemOne::tea[i]._name==ui->find->text())
                {
                    find[count]=i;
                    count++;
                }
            }
        else if(ui->cf->isChecked())
            for(int i=0;i<SystemOne::existingnum;i++)
            {
                for(int j=0;j<3;j++)
                    if(SystemOne::tea[i].course[j]._cname==ui->find->text())
                    {
                        find[count]=i;
                        count++;
                        break;
                    }
            }
        else{
            QMessageBox::warning(this,"警告","未选择查找方式！");
            flag=false;
        }
        if(flag){
            if(count==0)
                ui->showarea->setText("未找到相关信息！");
            else{
                QString str="";
                QString _str="";
                for(int i=0;i<count;i++)
                {
                    str+="职工号："+SystemOne::tea[find[i]]._id+"     "+"姓名："+SystemOne::tea[find[i]]._name+"     "+"性别："+SystemOne::tea[find[i]]._gender+"\n"
                           +"职称："+SystemOne::tea[find[i]]._title+"     "+"教学综合评分："+QString::number(SystemOne::tea[find[i]]._score)+"\n";
                               for(int j=0;j<3;j++)
                               {
                                   _str=QString("主讲课程%1：").arg(j+1);
                                   str+=_str+SystemOne::tea[find[i]].course[j]._cname+"     "+"开课学期："+SystemOne::tea[find[i]].course[j]._term+"\n"
                                      +"课程性质："+SystemOne::tea[find[i]].course[j]._property+"     "+"教学效果："+SystemOne::tea[find[i]].course[j]._score+"\n";
                               }
                               str+="\n";
                }
                ui->showarea->setText(str);
            }
        }
    });

    connect(ui->back,&QPushButton::clicked,[=](){

        emit sceneback();
    });

}

void one_find::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/fixbg.png");
    pix=pix.scaled(this->width(),this->height());
    painter.drawPixmap(0,0,pix);
}


one_find::~one_find()
{
    delete ui;
}
