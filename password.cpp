#include "password.h"
#include "ui_password.h"
#include<QMessageBox>
password::password(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::password)
{
    ui->setupUi(this);
    setWindowTitle("安全密码");
    setFixedSize(340,150);
    setWindowIcon(QIcon(":/incon.png"));

    QString PASSWORD="123";
    connect(ui->ok,&QPushButton::clicked,[=](){
        if(ui->Pass->text()==PASSWORD)
        {
            emit passed();
        }
        else
        {
            QMessageBox::warning(this,"密码错误","密码错误，请重新输入！");
            ui->Pass->clear();
        }
    });

    //返回
    connect(ui->back,&QPushButton::clicked,[=](){
        emit sceneback();
    });

}

password::~password()
{
    delete ui;
}
