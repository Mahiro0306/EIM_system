#include "two_delete.h"
#include "ui_two_delete.h"
#include"systemtwo.h"
#include<QMessageBox>
#include<QFile>
#include<QPainter>
two_delete::two_delete(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::two_delete)
{
    //初始化
    ui->setupUi(this);
    setWindowTitle("删除信息");
    setFixedSize(450,200);
    setWindowIcon(QIcon(":/incon.png"));


    //获取信息
    connect(ui->ok,&QPushButton::clicked,[=](){
        int find[N]={};
        int count=0;
        bool flag=true;
        if(ui->id->isChecked())
            for(int i=0;i<SystemTwo::existing;i++)
            {
                if(SystemTwo::wor[i]._id==ui->del->text())
                {
                    find[count]=i;
                    count++;
                }
            }
        else if(ui->name->isChecked())
            for(int i=0;i<SystemTwo::existing;i++)
            {
                    if(SystemTwo::wor[i]._name==ui->del->text())
                    {
                        find[count]=i;
                        count++;
                    }
            }
        else{
            QMessageBox::warning(this,"警告","未选择删除方式！");
            flag=false;
        }
        if(flag){
            if(count==0)
            {
                QMessageBox::warning(this,"警告","未找到相关信息！");
            }
            else{
                if(QMessageBox::Yes==QMessageBox::question(this,"删除提示",QString("找到%1条相关信息，是否全部删除？").arg(count),QMessageBox::Yes|QMessageBox::No))
                {
                    for(int i=0;i<count;i++)
                    {
                        worker temp;
                        temp=SystemTwo::wor[SystemTwo::existing-1-i];
                        SystemTwo::wor[SystemTwo::existing-1-i]=SystemTwo::wor[find[i]];
                        SystemTwo::wor[find[i]]=temp;
                    }
                    SystemTwo::existing-=count;

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

                        QMessageBox::information(this,"删除信息","删除成功!");
                    }

                }
            }
        }
    });


    //返回
    connect(ui->back,&QPushButton::clicked,[=](){
        emit sceneback();
    });


}


void two_delete::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/delbg.jpg");
    pix=pix.scaled(this->width(),this->height());
    painter.drawPixmap(0,0,pix);
}

two_delete::~two_delete()
{
    delete ui;
}
