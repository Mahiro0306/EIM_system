#include "systemtwo.h"
#include "ui_systemtwo.h"
#include<QFile>
#include<QMessageBox>
#include<QPainter>
int SystemTwo::existing=0;
worker SystemTwo::wor[N]={};

SystemTwo::SystemTwo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SystemTwo)
{
    //初始化
    ui->setupUi(this);
    setWindowTitle("职工档案管理子系统");
    setFixedSize(410,500);
    setWindowIcon(QIcon(":/incon.png"));

    //读取既有信息
    Wread();


    //工具栏
    ui->toolBar->setFixedHeight(50);
    ui->toolBar->setMovable(false);
    ui->toolBar->setFloatable(false);
    setContextMenuPolicy(Qt::NoContextMenu);//不可移除工具栏
    //功能按钮

    QPushButton *newpb=new QPushButton("录入",this);
    newpb->setFixedSize(100,40);
    ui->toolBar->addWidget(newpb);

    QPushButton *deletepb=new QPushButton("删除",this);
    deletepb->setFixedSize(100,40);
    ui->toolBar->addWidget(deletepb);

    QPushButton *fixpb=new QPushButton("修改",this);
    fixpb->setFixedSize(100,40);
    ui->toolBar->addWidget(fixpb);


    ui->toolBar->addSeparator();

    //返回按钮
    QPushButton *backpb=new QPushButton("返回",this);
    backpb->setFixedSize(60,30);
    ui->toolBar->addWidget(backpb);
    connect(backpb,&QPushButton::clicked,[=](){
        existing=0;//静态变量清零
        emit sceneback();
    });

    //查询
    connect(ui->findpb,&QPushButton::clicked,[=](){
        int find[N]={};
        int count=0;
        bool flag=true;
        if(ui->id->isChecked())
            for(int i=0;i<existing;i++)
            {
                if(wor[i]._id==ui->find->text())
                {
                    find[count]=i;
                    count++;
                }
            }
        else if(ui->name->isChecked())
            for(int i=0;i<existing;i++)
            {
                    if(wor[i]._name==ui->find->text())
                    {
                        find[count]=i;
                        count++;
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
                for(int i=0;i<count;i++)
                {
                    str+="职工号："+wor[find[i]]._id+"     "+"姓名："+wor[find[i]]._name+"     "+"性别："+wor[find[i]]._gender+"\n"
                           +"出生年月："+QString::number(wor[find[i]]._year)+"年"+QString::number(wor[find[i]]._month)+"月"+"     "+"年龄："+QString::number(wor[find[i]]._age)+"\n"
                           +"所在部门："+wor[find[i]]._partment+"     "+"职称："+wor[find[i]]._title+"\n"
                           +"工资级别："+wor[find[i]]._level+"     "+"电话："+wor[find[i]]._phone+"\n";
                           str+="\n";
                }
                ui->showarea->setText(str);
            }
        }
    });


    //排序
    connect(ui->sortpb,&QPushButton::clicked,[=](){
        bool flag=true;
        if(ui->id_2->isChecked())
        for(int i=0;i<existing-1;i++)
        {
            min=i;
            for(int j=i+1;j<existing;j++)
            {
                if(wor[j]._id<wor[min]._id)
                {
                    min=j;
                }
            }
            if(min!=i)
            {
                worker temp;
                temp=wor[i];
                wor[i]=wor[min];
                wor[min]=temp;
            }

        }

        else if(ui->name_2->isChecked())
            for(int i=0;i<existing-1;i++)
        {
            min=i;
            for(int j=i+1;j<existing;j++)
            {
                if(wor[j]._name<wor[min]._name)
                {
                    min=j;
                }
            }
            if(min!=i)
            {
                worker temp;
                temp=wor[i];
                wor[i]=wor[min];
                wor[min]=temp;
            }

        }
        else{
            QMessageBox::warning(this,"警告","未选择排序方式！");
            flag=false;
        }
        if(flag){
            QString str="";
            for(int i=0;i<existing;i++)
            {
            str+="职工号："+wor[i]._id+"     "+"姓名："+wor[i]._name+"     "+"性别："+wor[i]._gender+"\n"
                   +"出生年月："+QString::number(wor[i]._year)+"年"+QString::number(wor[i]._month)+"月"+"     "+"年龄："+QString::number(wor[i]._age)+"\n"
                   +"所在部门："+wor[i]._partment+"     "+"职称："+wor[i]._title+"\n"
                   +"工资级别："+wor[i]._level+"     "+"电话："+wor[i]._phone+"\n";
                   str+="\n";
            }
            ui->showarea->setText(str);
        }

    });
    //录入
    connect(newpb,&QPushButton::clicked,[=](){
        _new=new two_new;
        _new->setGeometry(this->geometry());

        _new->show();
        this->hide();
        connect(_new,&two_new::sceneback,[=](){
            this->setGeometry(_new->geometry());
            this->show();
            _new->hide();
            delete _new;
            _new=NULL;
        });
    });

    //删除
    connect(deletepb,&QPushButton::clicked,[=](){
        _pw=new password;
        _pw->setGeometry(this->geometry());

        _pw->show();
        this->hide();
        connect(_pw,&password::sceneback,[=](){

            this->setGeometry(_pw->geometry());
            this->show();
            _pw->hide();
            delete _pw;
            _pw=NULL;

        });
        connect(_pw,&password::passed,[=](){
            _del=new two_delete;
            _del->setGeometry(_pw->geometry());
            _del->show();
            _pw->hide();
            delete _pw;
            _pw=NULL;

            connect(_del,&two_delete::sceneback,[=](){
                this->setGeometry(_del->geometry());
                this->show();
                _del->hide();
                delete _del;
                _del=NULL;
            });
        });

    });

    //修改
    connect(fixpb,&QPushButton::clicked,[=](){

        _pw=new password;
        _pw->setGeometry(this->geometry());

        _pw->show();
        this->hide();
        connect(_pw,&password::sceneback,[=](){

            this->setGeometry(_pw->geometry());
            this->show();
            _pw->hide();
            delete _pw;
            _pw=NULL;

        });
        connect(_pw,&password::passed,[=](){
            _fix=new two_fix;
            _fix->setGeometry(_pw->geometry());
            _fix->show();
            _pw->hide();
            delete _pw;
            _pw=NULL;

            connect(_fix,&two_fix::sceneback,[=](){
                this->setGeometry(_fix->geometry());
                this->show();
                _fix->hide();
                delete _fix;
                _fix=NULL;
            });
        });
    });
}

void SystemTwo::Wread()
{
    QFile f("D:\\wor.dat");
    f.open(QIODevice::ReadOnly);
    if(!f.isOpen())
        qDebug()<<" !!!";

    else{
        QByteArray arr;
        while(!f.atEnd())
        {
            arr=f.readLine().trimmed(); wor[existing]._id = arr;
            arr=f.readLine().trimmed();	wor[existing]._name = arr;
            arr=f.readLine().trimmed();	wor[existing]._gender = arr;
            arr=f.readLine().trimmed(); wor[existing]._year= atoi(arr);
            arr=f.readLine().trimmed(); wor[existing]._month= atoi(arr);
            arr=f.readLine().trimmed(); wor[existing]._age= atoi(arr);
            arr=f.readLine().trimmed();	wor[existing]._partment = arr;
            arr=f.readLine().trimmed();	wor[existing]._title = arr;
            arr=f.readLine().trimmed();	wor[existing]._level = arr;
            arr=f.readLine().trimmed();	wor[existing]._phone = arr;
            existing++;
        }
        f.close();
    }
    return;
}

void SystemTwo::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/systembg.png");
    pix=pix.scaled(this->width(),this->height());
    painter.drawPixmap(0,0,pix);
}




SystemTwo::~SystemTwo()
{
    delete ui;
}
