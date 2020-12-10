#include "student_page.h"
#include "ui_student_page.h"
#include "login.h"

student_page::student_page(QJsonObject s_data, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::student_page)
{
    ui->setupUi(this);
    student_page::s_data=s_data;
    ui->label_4->setText("Welcome, "+student_page::s_data["name"].toString()+"!");
    ui->label_detail_name->setText(student_page::s_data["name"].toString());
    ui->label_detail_course->setText("Course: "+student_page::s_data["course"].toString());
    ui->label_detail_roll->setText("Roll no.: "+student_page::s_data["roll"].toString());
    ui->label_detail_year->setText("Year: "+student_page::s_data["year"].toString());
    ui->label_detail_part->setText("Part: "+student_page::s_data["part"].toString());

    ui->stackedWidget->setCurrentIndex(0);
}

student_page::~student_page()
{
    delete ui;
}

void student_page::on_pushButton_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
}

void student_page::on_pushButton_2_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);
}

void student_page::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void student_page::on_pushButton_4_clicked()
{
    hide();
    login *login_page = new login();
    login_page->show();
}
