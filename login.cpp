#include<iostream>
#include "login.h"
#include "json_parsing.h"
#include "ui_login.h"


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
    QString entered_username = ui->lineEdit_id->text();
    QString entered_password = ui->lineEdit_password->text();
    parsedata loginasd;
    loginasd.parse_student_data();
}
