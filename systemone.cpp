
#include "systemone.h"
#include "ui_systemone.h"
#include<QMessageBox>
#include<QDialog>
#include<QPushButton>
#include<QFile>
#include<QPainter>
int SystemOne::existingnum=0;
Teacher SystemOne::tea[N]={};

SystemOne::SystemOne(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SystemOne)
{
    //初始化
    ui->setupUi(this);
    setWindowTitle("职工信息管理子系统");
    setFixedSize(450,500);
    setWindowIcon(QIcon(":/incon.png"));

    //读取既有信息
    Iread();
    //工具栏
    ui->toolBar->setFixedHeight(50);
    ui->toolBar->setMovable(false);
    ui->toolBar->setFloatable(false);
    setContextMenuPolicy(Qt::NoContextMenu);//不可移除工具栏
    //功能按钮
    QPushButton *showpb=new QPushButton("显示",this);
    showpb->setFixedSize(70,40);
    ui->toolBar->addWidget(showpb);

    QPushButton *newpb=new QPushButton("新增",this);
    newpb->setFixedSize(70,40);
    ui->toolBar->addWidget(newpb);

    QPushButton *findpb=new QPushButton("查找",this);
    findpb->setFixedSize(70,40);
    ui->toolBar->addWidget(findpb);

    QPushButton *sortpb=new QPushButton("排序",this);
    sortpb->setFixedSize(70,40);
    ui->toolBar->addWidget(sortpb);

    QPushButton *insertpb=new QPushButton("插入",this);
    insertpb->setFixedSize(70,40);
    ui->toolBar->addWidget(insertpb);

    ui->toolBar->addSeparator();

    //返回按钮
    QPushButton *backpb=new QPushButton("返回",this);
    backpb->setFixedSize(60,30);
    ui->toolBar->addWidget(backpb);
    connect(backpb,&QPushButton::clicked,[=](){
        existingnum=0;//静态变量归零
        emit sceneback();
    });
    //显示
    connect(showpb,&QPushButton::clicked,[=](){
        if(existingnum==0)
        {
            QMessageBox::warning(this,"警告","尚未录入任何信息！");

        }
        else
        {
            QString str="";
            QString _str="";
            for(int i=0;i<existingnum;i++)
            {
                str+="职工号："+tea[i]._id+"     "+"姓名："+tea[i]._name+"     "+"性别："+tea[i]._gender+"\n"
                    +"职称："+tea[i]._title+"     "+"教学综合评分："+QString::number(tea[i]._score)+"\n";
                for(int j=0;j<3;j++)
                {
                    _str=QString("主讲课程%1：").arg(j+1);
                    str+=_str+tea[i].course[j]._cname+"     "+"开课学期："+tea[i].course[j]._term+"\n"
                        +"课程性质："+tea[i].course[j]._property+"     "+"教学效果："+tea[i].course[j]._score+"\n";
                }
                str+="\n";
            }
            ui->showarea->setText(str);
        }
    });

    //新增

    connect(newpb,&QPushButton::clicked,[=](){
        _new=new one_new;
        _new->setGeometry(this->geometry());

        _new->show();
        this->hide();
        connect(_new,&one_new::sceneback,[=](){
            this->setGeometry(_new->geometry());
            this->show();
            _new->hide();
            delete _new;
            _new=NULL;
        });

    });

    //查找
    connect(findpb,&QPushButton::clicked,[=](){

        _find=new one_find;
        _find->setGeometry(this->geometry());

        _find->show();
        this->hide();
        connect(_find,&one_find::sceneback,[=](){
            this->setGeometry(_find->geometry());
            this->show();
            _find->hide();
            delete _find;
            _find=NULL;
        });

    });

    //排序
    connect(sortpb,&QPushButton::clicked,[=](){

        _sort=new one_sort;
        _sort->setGeometry(this->geometry());

        _sort->show();
        this->hide();
        connect(_sort,&one_sort::sceneback,[=](){
            this->setGeometry(_sort->geometry());
            this->show();
            _sort->hide();
            delete _sort;
            _sort=NULL;
        });

    });

    //插入
    connect(insertpb,&QPushButton::clicked,[=](){

        _insert=new one_insert;
        _insert->setGeometry(this->geometry());

        _insert->show();
        this->hide();
        connect(_insert,&one_insert::sceneback,[=](){
            this->setGeometry(_insert->geometry());
            this->show();
            _insert->hide();
            delete _insert;
            _insert=NULL;
        });

    });
}



void SystemOne::Iread()
{
    QFile f("D:\\info.dat");
    f.open(QIODevice::ReadOnly);
    if(!f.isOpen())
        qDebug()<<" !!!";

    else{
        QByteArray arr;
        while(!f.atEnd())
        {
            arr=f.readLine().trimmed(); tea[existingnum]._id = arr;
            arr=f.readLine().trimmed();	tea[existingnum]._name = arr;
            arr=f.readLine().trimmed();	tea[existingnum]._gender = arr;
            arr=f.readLine().trimmed();	tea[existingnum]._title = arr;
            for (int i = 0; i < 3; i++) {
                arr=f.readLine().trimmed(); tea[existingnum].course[i]._cname = arr;
                arr=f.readLine().trimmed(); tea[existingnum].course[i]._term = arr;
                arr=f.readLine().trimmed(); tea[existingnum].course[i]._property = arr;
                arr=f.readLine().trimmed(); tea[existingnum].course[i]._score = arr;
            }

            arr=f.readLine().trimmed(); tea[existingnum]._score= atoi(arr);
            existingnum++;
        }
        f.close();
    }
    return;
}


void SystemOne::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/systembg.png");
    pix=pix.scaled(this->width(),this->height());
    painter.drawPixmap(0,0,pix);
}



SystemOne::~SystemOne()
{
    delete ui;
}
