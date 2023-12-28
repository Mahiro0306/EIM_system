#include "four_fix.h"
#include"systemfour.h"
#include "ui_four_fix.h"
#include<QMessageBox>
#include<QFile>
#include<QPainter>
int four_fix::find=0;

four_fix::four_fix(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::four_fix)
{
    ui->setupUi(this);
    setWindowTitle("修改信息");
    setFixedSize(390,450);
    setWindowIcon(QIcon(":/incon.png"));

    //返回
    connect(ui->back,&QPushButton::clicked,[=](){
        _flag=false;//返回前重置
        emit sceneback();
    });

    //查找

    connect(ui->ok,&QPushButton::clicked,[=](){

        bool flag=true;
        bool found=false;
        if(ui->name->isChecked())
        {
            for(int i=0;i<SystemFour::existing;i++)
            {
                if(SystemFour::per[i]._name==ui->find->text())
                {
                    find=i;
                    found=true;
                    break;
                }
            }
        }
        else if(ui->phone->isChecked())
        {
            for(int i=0;i<SystemFour::existing;i++)
            {
                if(SystemFour::per[i]._phone==ui->find->text())
                {
                    find=i;
                    found=true;
                    break;
                }
            }
        }

        else
        {
            QMessageBox::warning(this,"警告","未选择查找方式！");
            flag=false;
        }
        if(flag)
        {
            if(!found)
            {
                QMessageBox::warning(this,"警告","未找到相关信息");
            }
            else
            {
                QString str;
                    str="姓名："+SystemFour::per[find]._name+"     "+"电话："+SystemFour::per[find]._phone+"\n"
                           +"地址："+SystemFour::per[find]._address+"\n"
                           +"备注："+SystemFour::per[find]._detail+"\n";
                ui->showarea->setText(str);
                _flag=true;

            }
        }

    });

    //删除

    connect(ui->del,&QPushButton::clicked,[=](){

        if(_flag)
        {
            if(QMessageBox::Yes==QMessageBox::question(this,"删除提示","确认删除此信息？",QMessageBox::Yes|QMessageBox::No))
                {
                    _flag=false;//手动重置
                    person temp;
                    temp=SystemFour::per[SystemFour::existing-1];
                    SystemFour::per[SystemFour::existing-1]=SystemFour::per[find];
                    SystemFour::per[find]=temp;

                    SystemFour::existing--;

                    QFile f("D:\\per.dat");
                    f.open(QIODevice::WriteOnly|QIODevice::Truncate);
                    if(!f.isOpen())
                    {
                        qDebug()<<"!!!";
                    }
                    else{
                        QString arr="";
                        for(int i=0;i<SystemFour::existing;i++)
                        {
                            arr+=SystemFour::per[i]._name+"\n"+SystemFour::per[i]._phone+"\n"
                                   +SystemFour::per[i]._address+"\n"+SystemFour::per[i]._detail+"\n";
                        }
                        f.write(arr.toUtf8());
                        f.close();

                        QMessageBox::information(this,"删除信息","删除成功!");
                        ui->showarea->clear();

                    }

                }


        }
        else
        {
            QMessageBox::warning(this,"警告","尚未查找删除对象");
        }

    });

    //修改

    connect(ui->fix,&QPushButton::clicked,[=](){

        if(_flag)
        {
            if(QMessageBox::Yes==QMessageBox::question(this,"修改提示","确认修改此信息？",QMessageBox::Yes|QMessageBox::No))
                {
                _flag=false;//手动重置
                _new=new four_fix_new;
                _new->setGeometry(this->geometry());

                _new->show();
                this->hide();
                connect(_new,&four_fix_new::sceneback,[=](){
                    this->setGeometry(_new->geometry());
                    ui->showarea->clear();
                    this->show();
                    _new->hide();
                    delete _new;
                    _new=NULL;
                });

                }

        }
        else
        {
            QMessageBox::warning(this,"警告","尚未查找修改对象");
        }

    });

}

void four_fix::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/fixbg.png");
    pix=pix.scaled(this->width(),this->height());
    painter.drawPixmap(0,0,pix);
}

four_fix::~four_fix()
{
    delete ui;
}
