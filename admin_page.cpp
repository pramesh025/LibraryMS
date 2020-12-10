#include "admin_page.h"
#include "ui_admin_page.h"
#include "login.h"

admin_page::admin_page(QJsonObject ad_data,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::admin_page)
{
    ui->setupUi(this);
    admin_page::ad_data=ad_data;
    ui->label_welcome->setText("Welcome, "+admin_page::ad_data["name"].toString()+"!");

    ui->stackedWidget->setCurrentIndex(0);
}

admin_page::~admin_page()
{
    delete ui;
}

void admin_page::on_pushButton_logout_clicked()
{
    hide();
    login *login_page = new login();
    login_page->show();
}

void admin_page::on_pushButton_checkin_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void admin_page::on_pushButton_renew_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void admin_page::on_pushButton_checkouts_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void admin_page::on_pushButton_add_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void admin_page::on_pushButton_edit_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}
