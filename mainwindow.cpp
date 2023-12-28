#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPainter>
#include<QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//界面基本配置
    setWindowTitle("职工信息管理系统");
    setFixedSize(390,500);
    setWindowIcon(QIcon(":/incon.png"));

    QPalette pal;
    pal.setColor(QPalette::WindowText,Qt::white);
    ui->label->setPalette(pal);
    ui->label_2->setPalette(pal);
//退出按钮
    connect(ui->exitpb,&QPushButton::clicked,[=](){
        if(QMessageBox::Yes==QMessageBox::question(this,"退出提示","确认退出吗？",QMessageBox::Yes|QMessageBox::No))
            close();
        else;
    });
//登录按钮
    //QString _USERNAME="xxx";
    QString _SIGNINPASSWORD="123";

    selsc=new SelectScene;
    connect(ui->signinpb,&QPushButton::clicked,[=](){

        if(ui->signinpassword->text()==_SIGNINPASSWORD)
        {
            selsc->setGeometry(this->geometry());
            selsc->show();
            this->hide();
            ui->signinpassword->clear();
        }
        else
        {
            QMessageBox::warning(this,"密码错误","密码错误，请重新输入！");
            ui->signinpassword->clear();
        }
    });
//选择界面返回登录界面
    connect(selsc,&SelectScene::sceneback,[=](){
        this->setGeometry(selsc->geometry());
        this->show();
        selsc->hide();
    });



}

void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/mainbg.jpg");
    pix=pix.scaled(this->width(),this->height());
    painter.drawPixmap(0,0,pix);
}



MainWindow::~MainWindow()
{
    delete ui;
}

