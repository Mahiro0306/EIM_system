#include "three_delete.h"
#include "ui_three_delete.h"
#include<QMessageBox>
#include<QFile>
#include"systemthree.h"
#include<QPainter>
three_delete::three_delete(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::three_delete)
{
    ui->setupUi(this);
    setWindowTitle("删除信息");
    setFixedSize(390,170);
    setWindowIcon(QIcon(":/incon.png"));

    //返回
    connect(ui->back,&QPushButton::clicked,[=](){
        emit sceneback();
    });

    //删除
    connect(ui->ok,&QPushButton::clicked,[=](){
        if(ui->del->text().isEmpty())
        {
            QMessageBox::warning(this,"警告","未输入删除对象");
        }
        else
        {
            int find[N]={};
            int count=0;
            for(int i=0;i<SystemThree::existing;i++)
            {
                if(SystemThree::wag[i]._name==ui->del->text())
                {
                    find[count]=i;
                    count++;
                }
            }

            if(count==0)
            {
                QMessageBox::warning(this,"警告","未找到相关信息！");
            }
            else{
                if(QMessageBox::Yes==QMessageBox::question(this,"删除提示",QString("找到%1条相关信息，是否全部删除？").arg(count),QMessageBox::Yes|QMessageBox::No))
                {
                    for(int i=0;i<count;i++)
                    {
                        wage temp;
                        temp=SystemThree::wag[SystemThree::existing-1-i];
                        SystemThree::wag[SystemThree::existing-1-i]=SystemThree::wag[find[i]];
                        SystemThree::wag[find[i]]=temp;
                    }
                    SystemThree::existing-=count;

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

                        QMessageBox::information(this,"删除信息","删除成功!");
                    }

                }
            }
        }
    });
}


void three_delete::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/delbg.jpg");
    pix=pix.scaled(this->width(),this->height());
    painter.drawPixmap(0,0,pix);
}


three_delete::~three_delete()
{
    delete ui;
}
