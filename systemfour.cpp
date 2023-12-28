#include "systemfour.h"
#include "ui_systemfour.h"
#include<QFile>
#include<QMessageBox>
#include<QPainter>
person SystemFour::per[N]={};
int SystemFour::existing=0;

SystemFour::SystemFour(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SystemFour)
{
    //初始化
    ui->setupUi(this);
    setWindowTitle("职工通讯录管理子系统");
    setFixedSize(390,500);
    setWindowIcon(QIcon(":/incon.png"));

    //既有信息读取
    Pread();

    //工具栏
    ui->toolBar->setFixedHeight(50);
    ui->toolBar->setMovable(false);
    ui->toolBar->setFloatable(false);
    setContextMenuPolicy(Qt::NoContextMenu);//不可移除工具栏
    //功能按钮

    QPushButton *showpb=new QPushButton("显示",this);
    showpb->setFixedSize(100,40);
    ui->toolBar->addWidget(showpb);


    QPushButton *newpb=new QPushButton("新增",this);
    newpb->setFixedSize(100,40);
    ui->toolBar->addWidget(newpb);


    QPushButton *fixpb=new QPushButton("修改删除",this);
    fixpb->setFixedSize(100,40);
    ui->toolBar->addWidget(fixpb);

    ui->toolBar->addSeparator();

    //返回按钮
    QPushButton *backpb=new QPushButton("返回",this);
    backpb->setFixedSize(60,30);
    ui->toolBar->addWidget(backpb);
    connect(backpb,&QPushButton::clicked,[=](){
        existing=0;//静态变量归零
        emit sceneback();
    });

    //显示
    connect(showpb,&QPushButton::clicked,[=](){
        if(existing==0)
        {
            QMessageBox::warning(this,"警告","尚未录入任何信息！");

        }
        else
        {
            QString str="";
            for(int i=0;i<existing;i++)
            {
                str+="姓名："+per[i]._name+"     "+"电话："+per[i]._phone+"\n"
                       +"地址："+per[i]._address+"\n"
                       +"备注："+per[i]._detail+"\n";
                                        str+="\n";
            }
            ui->showarea->setText(str);
        }

    });


    //新增
    connect(newpb,&QPushButton::clicked,[=](){
        _new=new four_new;
        _new->setGeometry(this->geometry());

        _new->show();
        this->hide();
        connect(_new,&four_new::sceneback,[=](){
            this->setGeometry(_new->geometry());
            this->show();
            _new->hide();
            delete _new;
            _new=NULL;
        });
    });

    //查询
    connect(ui->ok,&QPushButton::clicked,[=](){
        bool flag=true;
        int find[N]={};
        int count=0;
        if(ui->name->isChecked())
        {
            for(int i=0;i<existing;i++)
            {
                if(per[i]._name==ui->find->text())
                {
                    find[count]=i;
                    count++;
                }
            }
        }
        else if(ui->phone->isChecked())
        {
            for(int i=0;i<existing;i++)
            {
                if(per[i]._phone==ui->find->text())
                {
                    find[count]=i;
                    count++;
                }
            }
        }

        else
        {
            QMessageBox::warning(this,"警告","未选择查询方式！");
            flag=false;
        }
        if(flag)
        {
            if(count==0)
            {
                QMessageBox::warning(this,"警告","未找到相关信息");
            }
            else
            {
                QString str="";
                for(int i=0;i<count;i++)
                {
                    str+="姓名："+per[find[i]]._name+"     "+"电话："+per[find[i]]._phone+"\n"
                           +"地址："+per[find[i]]._address+"\n"
                           +"备注："+per[find[i]]._detail+"\n";
                        str+="\n";
                }
                ui->showarea->setText(str);
            }
        }
    });

    //排序
    connect(ui->sort,&QPushButton::clicked,[=](){

        bool flag=true;
        if(ui->name_2->isChecked())
        {
            for(int i=0;i<existing-1;i++)
            {
                min=i;
                for(int j=i+1;j<existing;j++)
                {
                    if(per[j]._name<per[min]._name)
                    {
                        min=j;
                    }
                }
                if(min!=i)
                {
                    person temp;
                    temp=per[i];
                    per[i]=per[min];
                    per[min]=temp;
                }
            }
        }
        else if(ui->phone_2->isChecked())
        {
            for(int i=0;i<existing-1;i++)
            {
                min=i;
                for(int j=i+1;j<existing;j++)
                {
                    if(per[j]._phone<per[min]._phone)
                    {
                        min=j;
                    }
                }
                if(min!=i)
                {
                    person temp;
                    temp=per[i];
                    per[i]=per[min];
                    per[min]=temp;
                }
            }
        }

        else
        {
            QMessageBox::warning(this,"警告","未选择排序方式！");
            flag=false;
        }
        if(flag)
        {
            QString str="";
            for(int i=0;i<existing;i++)
            {
                str+="姓名："+per[i]._name+"     "+"电话："+per[i]._phone+"\n"
                       +"地址："+per[i]._address+"\n"
                       +"备注："+per[i]._detail+"\n";
                    str+="\n";
            }
            ui->showarea->setText(str);
        }
    });

    //修改删除

    connect(fixpb,&QPushButton::clicked,[=](){

        _fix=new four_fix;
        _fix->setGeometry(this->geometry());

        _fix->show();
        this->hide();
        connect(_fix,&four_fix::sceneback,[=](){
            this->setGeometry(_fix->geometry());
            this->show();
            _fix->hide();
            delete _fix;
            _fix=NULL;
        });
    });
}

void SystemFour::Pread()
{
    QFile f("D:\\per.dat");
    f.open(QIODevice::ReadOnly);
    if(!f.isOpen())
        qDebug()<<" !!!";

    else{
        QByteArray arr;
        while(!f.atEnd())
        {
            arr=f.readLine().trimmed();	per[existing]._name = arr;
            arr=f.readLine().trimmed();	per[existing]._phone = arr;
            arr=f.readLine().trimmed();	per[existing]._address = arr;
            arr=f.readLine().trimmed();	per[existing]._detail = arr;
            existing++;
        }
        f.close();
    }
    return;
}


void SystemFour::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/systembg.png");
    pix=pix.scaled(this->width(),this->height());
    painter.drawPixmap(0,0,pix);
}



SystemFour::~SystemFour()
{
    delete ui;
}
