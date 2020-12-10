#include<QDebug>

#include "admin_page.h"
#include "ui_admin_page.h"
#include "login.h"
#include "admin.h"
#include "student.h"
#include "book.h"
#include  "json_parsing.h"

QJsonObject stu_to_qjsonobj(student temp){
    QJsonObject Jtemp;
    QJsonArray bookiss;
    for(int i=0;i<7;i++)
        bookiss.append("NULL");
    Jtemp.insert("id",temp.id());
    Jtemp.insert("name",temp.name());
    Jtemp.insert("password",temp.password());
    Jtemp.insert("year",temp.year());
    Jtemp.insert("part",temp.part());
    Jtemp.insert("course",temp.course());
    Jtemp.insert("roll",temp.roll());
    Jtemp.insert("book_issued",bookiss);
    Jtemp.insert("access_level","student");
    return Jtemp;
}

QJsonObject book_to_qjsonobj(book temp){
    QJsonObject Jtemp;
    Jtemp.insert("id",temp.id());
    Jtemp.insert("name",temp.name());
    Jtemp.insert("author",temp.author());
    Jtemp.insert("pub_year",temp.pub_year());
    Jtemp.insert("issued_by",temp.issued_by());
    Jtemp.insert("issued_date",temp.issued_date());
    return Jtemp;
}

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

void admin_page::on_pushButton_add_2_clicked()
{
    foreach(QLineEdit* le, findChildren<QLineEdit*>()) {
    le->clear();
    }
    if(ui->radioButton_addstud->isChecked())
        ui->stackedWidget->setCurrentIndex(5);
    else if(ui->radioButton_addbook->isChecked())
        ui->stackedWidget->setCurrentIndex(6);
}

void admin_page::on_pushButton_addConfirm_clicked()
{
    parsedata *json = new parsedata;
    QJsonArray s_json= json->student_data();
    //checks for pre-existing data
    bool data_already_exists = false;
    for(int i=0;i<=json->student_no();i++){
        if(ui->lineEdit_addID->text()==s_json.at(i).toObject()["id"].toString()){
            QMessageBox::critical(nullptr,"error","ID already exists");
            data_already_exists=true;
        }
    }
    if(data_already_exists==false){
        student new_stu;
        new_stu.new_id(ui->lineEdit_addID->text());
    //    qDebug()<<new_stu.id();
        new_stu.new_name(ui->lineEdit_addName->text());
        new_stu.new_password(ui->lineEdit_addPass->text());
        new_stu.new_course(ui->lineEdit_addCourse->text());
        new_stu.new_year(ui->lineEdit_addYear->text());
        new_stu.new_part(ui->lineEdit_addPart->text());
        new_stu.new_roll(ui->lineEdit_addID->text());
        QJsonObject new_stu_obj = stu_to_qjsonobj(new_stu);


        s_json.append(new_stu_obj);
    //    qDebug()<<s_json;
        QFile s_file("../LibraryMS/JSON/student_data.json");
        if (!s_file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::critical(nullptr,"Error", "Error in parsing student data");
        }
        QJsonDocument doc(s_json);
        if(!s_file.write(doc.toJson()))
            QMessageBox::critical(nullptr,"Error", "Data could not be added");
        else{
            QMessageBox::about(nullptr,"Success","Data added successfully");
            ui->stackedWidget->setCurrentIndex(3);
        }
        s_file.close();
    }
}

void admin_page::on_pushButton_addnewbook_clicked()
{
    parsedata *json = new parsedata;
    QJsonArray b_json= json->book_data();
    //checks for pre-existing data
    bool data_already_exists = false;
    for(int i=0;i<=json->book_no();i++){
        if(ui->lineEdit_addBookID->text()==b_json.at(i).toObject()["id"].toString()){
            QMessageBox::critical(nullptr,"error","ID already exists");
            data_already_exists=true;
        }
    }
    if(data_already_exists==false){
        book new_book;
        new_book.new_id(ui->lineEdit_addBookID->text());
        new_book.new_name(ui->lineEdit_addBookName->text());
        new_book.new_author(ui->lineEdit_addBookAuthor->text());
        new_book.new_pub_year(ui->lineEdit_addBookYear->text());

        QJsonObject new_book_obj = book_to_qjsonobj(new_book);


        b_json.append(new_book_obj);
    //    qDebug()<<s_json;
        QFile b_file("../LibraryMS/JSON/book_data.json");
        if (!b_file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::critical(nullptr,"Error", "Error in parsing book data");
        }
        QJsonDocument doc(b_json);
        if(!b_file.write(doc.toJson()))
            QMessageBox::critical(nullptr,"Error", "Data could not be added");
        else{
            QMessageBox::about(nullptr,"Success","Data added successfully");
            b_file.close();
            ui->stackedWidget->setCurrentIndex(3);
        }

    }
}
