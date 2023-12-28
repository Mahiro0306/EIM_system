#include "systemthree.h"
#include "ui_systemthree.h"
#include<QFile>
#include<QPushButton>
#include<QMessageBox>
#include<QPainter>
int SystemThree::existing=0;
wage SystemThree::wag[N]={};

SystemThree::SystemThree(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SystemThree)
{
    //初始化
    ui->setupUi(this);
    setWindowTitle("职工工资管理子系统");
    setFixedSize(410,550);
    setWindowIcon(QIcon(":/incon.png"));

    //读取既有信息
    Gread();

    //工具栏
    ui->toolBar->setFixedHeight(50);
    ui->toolBar->setMovable(false);
    ui->toolBar->setFloatable(false);
    setContextMenuPolicy(Qt::NoContextMenu);//不可移除工具栏
    //功能按钮

    QPushButton *newpb=new QPushButton("新建",this);
    newpb->setFixedSize(100,40);
    ui->toolBar->addWidget(newpb);

    QPushButton *fixpb=new QPushButton("修订",this);
    fixpb->setFixedSize(100,40);
    ui->toolBar->addWidget(fixpb);

    QPushButton *deletepb=new QPushButton("删除",this);
    deletepb->setFixedSize(100,40);
    ui->toolBar->addWidget(deletepb);


    ui->toolBar->addSeparator();
    //返回按钮
    QPushButton *backpb=new QPushButton("返回",this);
    backpb->setFixedSize(60,30);
    ui->toolBar->addWidget(backpb);
    connect(backpb,&QPushButton::clicked,[=](){
        existing=0;//静态变量清零
        emit sceneback();
    });

    //统计
    //计算
    connect(ui->calculate,&QPushButton::clicked,[=](){

        if(ui->sum->isChecked())
        {
            int sum=0;
            for(int i=0;i<existing;i++)
            {
                sum+=wag[i]._wage;
            }
            ui->showarea->setText(QString("总工资：%1").arg(sum));
        }
        else if(ui->average->isChecked())
        {
            if(existing==0)
            {
                QMessageBox::warning(this,"警告","尚未录入任何信息！");
            }
            else{
                int sum=0;
                for(int i=0;i<existing;i++)
                {
                    sum+=wag[i]._wage;
                }
                ui->showarea->setText(QString("平均工资：%1").arg(sum/existing));
            }

        }
        else
        {
            QMessageBox::warning(this,"警告","未选择计算内容！");
        }
    });
    //排序
    connect(ui->sort,&QPushButton::clicked,[=](){
        bool flag=true;
        if(ui->high->isChecked())
        {
            for(int i=0;i<existing-1;i++)
            {
                min=i;
                for(int j=i+1;j<existing;j++)
                {
                    if(wag[j]._wage<wag[min]._wage)
                    {
                        min=j;
                    }
                }
                if(min!=i)
                {
                    wage temp;
                    temp=wag[i];
                    wag[i]=wag[min];
                    wag[min]=temp;
                }
            }
        }

        else if(ui->low->isChecked())
        {
            for(int i=0;i<existing-1;i++)
            {
                max=i;
                for(int j=i+1;j<existing;j++)
                {
                    if(wag[j]._wage>wag[max]._wage)
                    {
                        max=j;
                    }
                }
                if(max!=i)
                {
                    wage temp;
                    temp=wag[i];
                    wag[i]=wag[max];
                    wag[max]=temp;
                }
            }
        }
        else
        {
            flag=false;
            QMessageBox::warning(this,"警告","未选择排序方式！");
        }
        if(flag)
        {
            QString str="";
            for(int i=0;i<existing;i++)
            {
                str+="姓名："+wag[i]._name+"     "+"性别："+wag[i]._gender+"     "+"年龄："+QString::number(wag[i]._age)+"\n"
                       +"出生年月："+QString::number(wag[i]._year)+"年"+QString::number(wag[i]._month)+"月"+"     "+"婚姻状况："+wag[i]._marry+"\n"
                       +"家庭住址："+wag[i]._address+"     "+"职称："+wag[i]._title+"\n"
                       +"工资："+QString::number(wag[i]._wage)+"     "+"工资级别："+wag[i]._level+"\n";
                           str+="\n";
            }
            ui->showarea->setText(str);
        }
    });

    //查找
        connect(ui->find,&QPushButton::clicked,[=](){

            int find[N]={};
            int count=0;
            for(int i=0;i<existing;i++)
            {
                if(wag[i]._level==ui->level->text())
                {
                    find[count]=i;
                    count++;
                }
            }
            if(count==0)
            {
                ui->showarea->setText("未找到相关信息！");
            }
            else{
                QString str="";
                for(int i=0;i<count;i++)
                {
                    str+="姓名："+wag[find[i]]._name+"     "+"性别："+wag[find[i]]._gender+"     "+"年龄："+QString::number(wag[find[i]]._age)+"\n"
                           +"出生年月："+QString::number(wag[find[i]]._year)+"年"+QString::number(wag[find[i]]._month)+"月"+"     "+"婚姻状况："+wag[find[i]]._marry+"\n"
                           +"家庭住址："+wag[find[i]]._address+"     "+"职称："+wag[find[i]]._title+"\n"
                           +"工资："+QString::number(wag[find[i]]._wage)+"     "+"工资级别："+wag[find[i]]._level+"\n";
                               str+="\n";
                }
                ui->showarea->setText(str);
            }
        });

    //新建
    connect(newpb,&QPushButton::clicked,[=](){
        _new=new three_new;
        _new->setGeometry(this->geometry());

        _new->show();
        this->hide();
        connect(_new,&three_new::sceneback,[=](){
            this->setGeometry(_new->geometry());
            this->show();
            _new->hide();
            delete _new;
            _new=NULL;
        });
    });
    //删除

    connect(deletepb,&QPushButton::clicked,[=](){

        _del=new three_delete;
        _del->setGeometry(this->geometry());

        _del->show();
        this->hide();
        connect(_del,&three_delete::sceneback,[=](){
            this->setGeometry(_del->geometry());
            this->show();
            _del->hide();
            delete _del;
            _del=NULL;
        });
    });

    //修订
    connect(fixpb,&QPushButton::clicked,[=](){

        _fix=new three_fix;
        _fix->setGeometry(this->geometry());

        _fix->show();
        this->hide();
        connect(_fix,&three_fix::sceneback,[=](){
            this->setGeometry(_fix->geometry());
            this->show();
            _fix->hide();
            delete _fix;
            _fix=NULL;
        });
    });





}

void SystemThree::Gread()
{
    QFile f("D:\\wag.dat");
    f.open(QIODevice::ReadOnly);
    if(!f.isOpen())
        qDebug()<<" !!!";

    else{
        QByteArray arr;
        while(!f.atEnd())
        {

            arr=f.readLine().trimmed();	wag[existing]._name = arr;
            arr=f.readLine().trimmed();	wag[existing]._gender = arr;
            arr=f.readLine().trimmed(); wag[existing]._year= atoi(arr);
            arr=f.readLine().trimmed(); wag[existing]._month= atoi(arr);
            arr=f.readLine().trimmed(); wag[existing]._age= atoi(arr);       
            arr=f.readLine().trimmed();	wag[existing]._marry = arr;
            arr=f.readLine().trimmed();	wag[existing]._address = arr;
            arr=f.readLine().trimmed();	wag[existing]._title = arr;
            arr=f.readLine().trimmed(); wag[existing]._wage= atoi(arr);
            arr=f.readLine().trimmed();	wag[existing]._level = arr;

            existing++;
        }
        f.close();
    }
    return;
}

void SystemThree::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/systembg.png");
    pix=pix.scaled(this->width(),this->height());
    painter.drawPixmap(0,0,pix);
}



SystemThree::~SystemThree()
{
    delete ui;
}
