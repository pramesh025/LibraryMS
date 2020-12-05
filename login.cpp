#include<iostream>
#include<QDebug>

#include "login.h"
#include "json_parsing.h"
#include "ui_login.h"
#include "student_page.h"

login::login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}


void login::on_pushButton_login_clicked()
{
    QString entered_username = ui->lineEdit_id->text().toLower();
    QString entered_password = ui->lineEdit_password->text();
    parsedata *check_student = new parsedata;
    QJsonArray stu_data = check_student->student_data();
    int isdata=0;
    for(int i=0;i<=check_student->student_no();i++){
        if(entered_username==stu_data.at(i).toObject()["id"].toString()){
//              qDebug()<< stu_data.at(i).toObject()["id"].toString();
            isdata=1;
            if(entered_password==stu_data.at(i).toObject()["password"].toString()){
                hide();
                student_page *s_page = new student_page(stu_data.at(i).toObject(),nullptr);
                s_page->setWindowFlags(Qt::Window);
                s_page->show();
//              qDebug()<<"Password correct!!"<<Qt::endl<<"You shall enter!!!!!";
            }
            else{
                QMessageBox::about(this,"Alert","Password wrong");
            }
            break;
        }
    }
    if(!isdata){
        QMessageBox::about(this,"Alert","No such user");
    }
}
