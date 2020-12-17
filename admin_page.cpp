#include <QDebug>

#include "admin_page.h"
#include "ui_admin_page.h"
#include "login.h"
#include "admin.h"
#include "student.h"
#include "book.h"
#include "json_parsing.h"
#include "date.h"



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


/*------------------------------------------------------------------------------------------------------------
 * ----                                                                                                 ------
 * ----                             Checked in page                                                     ------
 * ----                                                                                                 ------
 * ----------------------------------------------------------------------------------------------------------*/

void admin_page::on_pushButton_checkin_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    //clean that sht
    ui->label_issue_BookName->setText("");
    ui->label_issue_BookAuthor->setText("");
    ui->label_issue_BookStatus->setText("");
}
QString issue_stu_ID;
bool can_issue=false;
QString issue_book_ID;
void admin_page::on_pushButton_issue_stID_search_clicked()
{
    parsedata *json = new parsedata;
    QJsonArray stu_json = json->student_data();
    QString input_st=ui->lineEdit_issue_stID_search->text();
    //clean that sht part 2
    ui->label_issue_stuName->setText("");
    ui->label_issue_stuYear->setText("");
    ui->label_issue_stuCourse->setText("");
    ui->label_issue_stuIssued->setText("");
    bool is_data=false;
    for(int i=0;i<=json->student_no();i++){
        if(stu_json.at(i).toObject()["id"].toString().toLower()==input_st.toLower()){
            is_data=true;
            ui->label_issue_stuName->setText(stu_json.at(i).toObject()["name"].toString());
            ui->label_issue_stuYear->setText(stu_json.at(i).toObject()["year"].toString()+"/"+stu_json.at(i).toObject()["part"].toString());
            ui->label_issue_stuCourse->setText(stu_json.at(i).toObject()["course"].toString());
            ui->label_issue_stuIssued->setText(QString::number(stu_json.at(i).toObject()["book_issued"].toArray().count()));
            if(stu_json.at(i).toObject()["book_issued"].toArray().count()>=7)
                QMessageBox::critical(this,"Error","Book limit reached");
            else{
                issue_stu_ID=input_st;
                can_issue=true;
            }
            break;
        }
    }
    if(is_data==false)
        QMessageBox::critical(this,"Error","Student ID doesnt exists");
}

void admin_page::on_pushButton_issue_bID_search_clicked()
{
    parsedata *json = new parsedata;
    QJsonArray book_json = json->book_data();
    QString input_book=ui->lineEdit_issue_bID_search->text();
    //clean that sht part 3
    ui->label_issue_BookName->setText("");
    ui->label_issue_BookAuthor->setText("");
    ui->label_issue_BookStatus->setText("");
    bool is_data=false;
    for(int i=0;i<=json->book_no();i++){
        if(book_json.at(i).toObject()["id"].toString().toLower()==input_book.toLower()){
            is_data=true;
            ui->label_issue_BookName->setText(book_json.at(i).toObject()["name"].toString());
            ui->label_issue_BookAuthor->setText(book_json.at(i).toObject()["author"].toString());

            if(book_json.at(i).toObject()["issued_by"].toString()=="NULL"){
                ui->label_issue_BookStatus->setText("Not Issued");
                issue_book_ID=input_book;
                can_issue=true;
            }
            else{
                ui->label_issue_BookStatus->setText("Already Issued");
                QMessageBox::critical(this,"Error","Book ALready issued");
            }
            break;
        }
    }
    if(is_data==false)
        QMessageBox::critical(this,"Error","Book ID doesnt exists");
}

void admin_page::on_pushButton_issue_clicked()
{
    if(can_issue==false){
        QMessageBox::critical(this,"Error","Cannot issue");
    }
    else{
        date today;
        bool success = true;
        parsedata *json = new parsedata;
        QJsonArray book_json = json->book_data();
        QJsonArray stu_json = json->student_data();
        for(int i=0;i<=json->book_no();i++){
            if(issue_book_ID.toLower()==book_json.at(i).toObject()["id"].toString().toLower()){
                QJsonObject temp = book_json.at(i).toObject();
                book_json.removeAt(i);
                temp.remove("issued_by");
                temp.remove("issued_date");
                temp.insert("issued_by",issue_stu_ID);
                temp.insert("issued_date",today.today());
                book_json.append(temp);
                QFile book_file("./JSON/book_data.json");
                if (!book_file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                    QMessageBox::critical(nullptr,"Error", "Error in parsing book data");
                }
                QJsonDocument doc(book_json);
                if(!book_file.write(doc.toJson())){
                    QMessageBox::critical(nullptr,"Error", "Book Database couldnt be accessed");
                    success=false;
                }
                book_file.close();
//                qDebug()<<book_json;
                break;
            }
        }
        if(success){
            for(int i=0;i<=json->student_no();i++){
                if(issue_stu_ID.toLower()==stu_json.at(i).toObject()["id"].toString().toLower()){
                    QJsonObject tempOBJ =stu_json.at(i).toObject();
                    stu_json.removeAt(i);
                    QJsonArray tempAr = tempOBJ["book_issued"].toArray();
                    tempAr.append(issue_book_ID);
                    tempOBJ.remove("book_issued");
                    tempOBJ.insert("book_issued",tempAr);
                    stu_json.append(tempOBJ);
                    QFile stu_file("./JSON/student_data.json");
                    if (!stu_file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                        QMessageBox::critical(nullptr,"Error", "Error in parsing student data");
                    }
                    QJsonDocument doc(stu_json);
                    if(!stu_file.write(doc.toJson())){
                        QMessageBox::critical(nullptr,"Error", "Student Database couldnt be accessed");
                        success = false;
                    }
                    else{
                        QMessageBox::about(nullptr,"Success","Issued successfully");
                        on_pushButton_clear_clicked();
                    }
                    stu_file.close();
//                    qDebug()<<stu_json;
                    break;
                }
            }
        }
    }
}

void admin_page::on_pushButton_clear_clicked()
{
    //Jesus Christ!!!! CLEAN IT ALL!!!
    issue_stu_ID = " ";
    can_issue=false;
    issue_book_ID = " ";
    ui->label_issue_BookName->setText("");
    ui->label_issue_BookAuthor->setText("");
    ui->label_issue_BookStatus->setText("");
    ui->label_issue_stuName->setText("");
    ui->label_issue_stuYear->setText("");
    ui->label_issue_stuCourse->setText("");
    ui->label_issue_stuIssued->setText("");
    foreach(QLineEdit* le, findChildren<QLineEdit*>()) {
        le->clear();
    }
}







/*------------------------------------------------------------------------------------------------------------
 * ----                                                                                                 ------
 * ----                                    Renew page                                                   ------
 * ----                                                                                                 ------
 * ----------------------------------------------------------------------------------------------------------*/

void admin_page::on_pushButton_renew_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

QJsonObject renew_stu_data;
bool can_renew = false;
void admin_page::on_pushButton_issue_stID_search_2_clicked()
{
    parsedata *json = new parsedata;
    QJsonArray stu_json = json->student_data();
    QString input_st=ui->lineEdit_renew_stID_search_2->text();
    //clean that sht
    ui->label_renew_stuName_2->setText("");
    ui->label_renew_stuYear_2->setText("");
    ui->label_renew_stuCourse_2->setText("");
    bool is_data=false;
    for(int i=0;i<=json->student_no();i++){
        if(stu_json.at(i).toObject()["id"].toString().toLower()==input_st.toLower()){
            is_data=true;
            ui->label_renew_stuName_2->setText(stu_json.at(i).toObject()["name"].toString());
            ui->label_renew_stuYear_2->setText(stu_json.at(i).toObject()["year"].toString()+"/"+stu_json.at(i).toObject()["part"].toString());
            ui->label_renew_stuCourse_2->setText(stu_json.at(i).toObject()["course"].toString());
            renew_stu_data=stu_json.at(i).toObject();
            break;
        }
    }
    if(is_data==false)
        QMessageBox::critical(this,"Error","Student ID doesnt exists");
}

QString renew_book_ID;
void admin_page::on_pushButton_issue_bID_search_2_clicked()
{
    parsedata *json = new parsedata;
    QJsonArray book_json = json->book_data();
    QString input_book=ui->lineEdit_renew_bID_search_2->text();
    //clean that sht part 3
    ui->label_renew_BookName_2->setText("");
    ui->label_renew_BookAuthor_2->setText("");
    ui->label_renew_BookFine->setText("");
    bool is_data=false;
    for(int i=0;i<=renew_stu_data["book_issued"].toArray().count();i++){
        if(renew_stu_data["book_issued"].toArray().at(i).toString().toLower()==input_book.toLower()){
            for(int j=0;j<=json->book_no();j++){
                if(input_book.toLower()==book_json.at(j).toObject()["id"].toString().toLower()){
                    is_data=true;
                    can_renew=true;
                    renew_book_ID = input_book;
                    date date;
                    ui->label_renew_BookName_2->setText(book_json.at(j).toObject()["name"].toString());
                    ui->label_renew_BookAuthor_2->setText(book_json.at(j).toObject()["author"].toString());
                    QDate iss_Date=QDate::fromString(book_json.at(j).toObject()["issued_date"].toString(), "yyyyMMdd").addDays(date.deadline_day());

                    QDate today(QDate::currentDate());
                    int day= iss_Date.daysTo(today);
//                    qDebug()<<iss_Date.toString("yyyy.MM.dd");
//                    qDebug()<<today.toString("yyyy.MM.dd");
                    if(day-date.deadline_day()>0)
                        ui->label_renew_BookFine->setText(QString::number(day*date.price()));
                    else
                        ui->label_renew_BookFine->setText(QString::number(0));
                    break;
                }
            }
            break;
        }
    }
    if(is_data==false)
        QMessageBox::critical(this,"Error","Book ID doesnt exists or user hasnt issued the book");
}
void admin_page::on_pushButton_Renew_clicked()
{
    if(can_renew){
        parsedata *json = new parsedata;
        date today;
        QJsonArray book_json = json->book_data();
//        qDebug()<<"WE ARE HERE";
        for(int i=0;i<=json->book_no();i++){
            if(renew_book_ID.toLower()==book_json.at(i).toObject()["id"].toString().toLower()){
                QJsonObject temp = book_json.at(i).toObject();
                book_json.removeAt(i);
                temp.remove("issued_date");
                temp.insert("issued_date",today.today());
                book_json.append(temp);
                QFile book_file("./JSON/book_data.json");
                if (!book_file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                    QMessageBox::critical(nullptr,"Error", "Error in parsing book data");
                }
                QJsonDocument doc(book_json);
                if(!book_file.write(doc.toJson())){
                    QMessageBox::critical(nullptr,"Error", "Book Database couldnt be accessed");
                }
                else{
                    QMessageBox::about(this,"Success","Book Renewed");
                    on_pushButton_clear_2_clicked();
                }
                book_file.close();
//                qDebug()<<book_json;
                break;
            }
        }
    }
    else{
        QMessageBox::critical(this,"Error","Renew error\nNo data");
    }
}

void admin_page::on_pushButton_clear_2_clicked()
{
    renew_book_ID=" ";
    renew_stu_data = {};
    can_renew = false;
    ui->label_renew_BookAuthor_2->setText("");
    ui->label_renew_BookName_2->setText("");
    ui->label_renew_BookFine->setText("");
    ui->label_renew_stuCourse_2->setText("");
    ui->label_renew_stuName_2->setText("");
    ui->label_renew_stuYear_2->setText("");
    ui->label_issue_stuIssued->setText("");
    foreach(QLineEdit* le, findChildren<QLineEdit*>()) {
        le->clear();
    }
}








/*------------------------------------------------------------------------------------------------------------
 * ----                                                                                                 ------
 * ----                             Checked out page                                                    ------
 * ----                                                                                                 ------
 * ----------------------------------------------------------------------------------------------------------*/

void admin_page::on_pushButton_checkouts_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}
QJsonObject checkout_stu_data;
bool can_checkout = false;
void admin_page::on_pushButton_out_stID_search_3_clicked()
{
    parsedata *json = new parsedata;
    QJsonArray stu_json = json->student_data();
    QString input_st=ui->lineEdit_out_stID_search_3->text();
    //clean that sht
    ui->label_out_stuName_3->setText("");
    ui->label_out_stuYear_3->setText("");
    ui->label_out_stuCourse_3->setText("");
    bool is_data=false;
    for(int i=0;i<=json->student_no();i++){
        if(stu_json.at(i).toObject()["id"].toString().toLower()==input_st.toLower()){
            is_data=true;
            ui->label_out_stuName_3->setText(stu_json.at(i).toObject()["name"].toString());
            ui->label_out_stuYear_3->setText(stu_json.at(i).toObject()["year"].toString()+"/"+stu_json.at(i).toObject()["part"].toString());
            ui->label_out_stuCourse_3->setText(stu_json.at(i).toObject()["course"].toString());
            checkout_stu_data=stu_json.at(i).toObject();
            break;
        }
    }
    if(is_data==false)
        QMessageBox::critical(this,"Error","Student ID doesnt exists");
}

QJsonObject checkout_book_data;
void admin_page::on_pushButton_out_bID_search_3_clicked()
{
    parsedata *json = new parsedata;
    QJsonArray book_json = json->book_data();
    QString input_book=ui->lineEdit_out_bID_search_3->text();
    //clean that sht part 3
    ui->label_out_BookName_3->setText("");
    ui->label_out_BookAuthor_3->setText("");
    ui->label_out_BookFine_2->setText("");
    bool is_data=false;
    for(int i=0;i<=checkout_stu_data["book_issued"].toArray().count();i++){
        if(checkout_stu_data["book_issued"].toArray().at(i).toString().toLower()==input_book.toLower()){
            for(int j=0;j<=json->book_no();j++){
                if(input_book.toLower()==book_json.at(j).toObject()["id"].toString().toLower()){
                    is_data=true;
                    can_checkout=true;
                    checkout_book_data = book_json.at(j).toObject();
                    date date;
                    ui->label_out_BookName_3->setText(book_json.at(j).toObject()["name"].toString());
                    ui->label_out_BookAuthor_3->setText(book_json.at(j).toObject()["author"].toString());
                    QDate iss_Date=QDate::fromString(book_json.at(j).toObject()["issued_date"].toString(), "yyyyMMdd").addDays(date.deadline_day());
                    QDate today(QDate::currentDate());
                    int day= iss_Date.daysTo(today);
//                    qDebug()<<iss_Date.toString("yyyy.MM.dd");
//                    qDebug()<<today.toString("yyyy.MM.dd");

                    if(day-date.deadline_day()>0)
                        ui->label_out_BookFine_2->setText(QString::number(day*date.price()));
                    else
                        ui->label_out_BookFine_2->setText(QString::number(0));
                    break;
                }
            }
            break;
        }
    }
    if(is_data==false)
        QMessageBox::critical(this,"Error","Book ID doesnt exists or user hasnt issued the book");
}

void admin_page::on_pushButton_out_clicked()
{
    if(can_checkout){
        parsedata *json = new parsedata;
        date today;
        bool success = false;
        QJsonArray book_json = json->book_data();
        QJsonArray stu_json = json->student_data();
//        changing student data
        QJsonObject tempObj  = checkout_stu_data;
        QJsonArray tempArr = tempObj["book_issued"].toArray();
        for(int i=0;i<=tempArr.count();i++){
            if(tempArr.at(i).toString().toLower()==checkout_book_data["id"].toString().toLower()){
                tempArr.removeAt(i);
                break;
            }
        }
        tempObj.remove("book_issued");
        tempObj.insert("book_issued",tempArr);
//        qDebug()<<tempObj;
        //remove previous data and add new from stu_json
        for(int i=0;i<=json->student_no();i++){
            if(stu_json.at(i).toObject()["id"].toString().toLower()==tempObj["id"].toString().toLower()){
                stu_json.removeAt(i);
                stu_json.append(tempObj);
                break;
            }
        }
        QFile stu_file("./JSON/student_data.json");
        if (!stu_file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::critical(nullptr,"Error", "Error in parsing student data");
        }
        QJsonDocument doc(stu_json);
        if(!stu_file.write(doc.toJson())){
            QMessageBox::critical(nullptr,"Error", "Student Database couldnt be accessed");
        }
        else{
            success = true;
        }
        stu_file.close();
        //for the book
        if(success){
            checkout_book_data.remove("issued_by");
            checkout_book_data.remove("issued_date");
            checkout_book_data.insert("issued_by","NULL");
            checkout_book_data.insert("issued_date","NULL");
           //remove previus and add new data in book_json
            for(int i=0;i<=json->book_no();i++){
                if(checkout_book_data["id"].toString().toLower()==book_json.at(i).toObject()["id"].toString().toLower()){
                    book_json.removeAt(i);
                    book_json.append(checkout_book_data);
                    break;
                }
            }
            QFile book_file("./JSON/book_data.json");
            if (!book_file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QMessageBox::critical(nullptr,"Error", "Error in parsing book data");
            }
            QJsonDocument doc(book_json);
            if(!book_file.write(doc.toJson())){
                QMessageBox::critical(nullptr,"Error", "Book Database couldnt be accessed");
            }
            else{
                QMessageBox::about(nullptr,"Success","Checkout successfully");
                on_pushButton_clear_3_clicked();
            }
            book_file.close();
        }

    }
    else{
        QMessageBox::critical(this,"Error","checkout error\nNo data");
    }
}

void admin_page::on_pushButton_clear_3_clicked()
{
    checkout_stu_data = {};
    can_checkout=false;
    checkout_book_data = {};
    ui->label_out_BookName_3->setText("");
    ui->label_out_BookAuthor_3->setText("");
    ui->label_out_BookFine_2->setText("");
    ui->label_out_stuName_3->setText("");
    ui->label_out_stuYear_3->setText("");
    ui->label_out_stuCourse_3->setText("");
    foreach(QLineEdit* le, findChildren<QLineEdit*>()) {
        le->clear();
    }
}







/*------------------------------------------------------------------------------------------------------------
 * ----                                                                                                 ------
 * ----                                 add new page                                                    ------
 * ----                                                                                                 ------
 * ----------------------------------------------------------------------------------------------------------*/


void admin_page::on_pushButton_add_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
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
/*------------------------------------------------------------------------------------------------------------
 * ----                             add new student page                                                ------
 * ----------------------------------------------------------------------------------------------------------*/
void admin_page::on_pushButton_addConfirm_clicked()
{
    parsedata *json = new parsedata;
    QJsonArray s_json= json->student_data();
    //checks for pre-existing data
    bool data_already_exists = false;
    for(int i=0;i<=json->student_no();i++){
        if(ui->lineEdit_addID->text()==s_json.at(i).toObject()["id"].toString()){
            QMessageBox::critical(nullptr,"Error","ID already exists");
            data_already_exists=true;
        }
    }
    //          add new student
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
        QJsonObject new_stu_obj = new_stu.stu_to_qjsonobj();


        s_json.append(new_stu_obj);
    //    qDebug()<<s_json;
        QFile s_file("./JSON/student_data.json");
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
/*------------------------------------------------------------------------------------------------------------
 * ----                               add new book page                                                 ------
 * ----------------------------------------------------------------------------------------------------------*/
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

        QJsonObject new_book_obj = new_book.book_to_qjsonobj();


        b_json.append(new_book_obj);
    //    qDebug()<<s_json;
        QFile b_file("./JSON/book_data.json");
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






/*------------------------------------------------------------------------------------------------------------
 * ----                                                                                                 ------
 * ----                                 edit/delete page                                                ------
 * ----                                                                                                 ------
 * ----------------------------------------------------------------------------------------------------------*/

void admin_page::on_pushButton_edit_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

/*------------------------------------------------------------------------------------------------------------
 * ----                               edit/delete student data page                                     ------
 * ----------------------------------------------------------------------------------------------------------*/
QString edit_stud_id_temp;
void admin_page::on_pushButton_edit_stuID_SEARCH_clicked()
{
    QString input_id = ui->lineEdit_stu_id_edit->text().toLower();
//    qDebug()<<input_id;
    parsedata temp;
    QJsonArray s_temp=temp.student_data();
    bool is_data = false;
    for(int i=0;i<=temp.student_no();i++){
        if(s_temp.at(i).toObject()["id"].toString().toLower()==input_id){
//            qDebug()<<s_temp.at(i).toObject()["id"].toString();
            is_data=true;
            edit_stud_id_temp=s_temp.at(i).toObject()["id"].toString();
            ui->stackedWidget->setCurrentIndex(7);
            ui->lineEdit_edit_id->setText(s_temp.at(i).toObject()["id"].toString());
            ui->lineEdit_edit_name->setText(s_temp.at(i).toObject()["name"].toString());
            ui->lineEdit_edit_year->setText(s_temp.at(i).toObject()["year"].toString());
            ui->lineEdit_edit_part->setText(s_temp.at(i).toObject()["part"].toString());
            ui->lineEdit_edit_password->setText(s_temp.at(i).toObject()["password"].toString());
            ui->lineEdit_edit_course->setText(s_temp.at(i).toObject()["course"].toString());
        }
    }
    if(is_data==false){
            QMessageBox::critical(nullptr,"Error","Student data doesnt exist");
    }
}

void admin_page::on_pushButton_edit_confirm_clicked()
{
    parsedata *json = new parsedata;
    QJsonArray s_json= json->student_data();
    //checks for pre-existing data
    bool data_already_exists = false;
    for(int i=0;i<=json->student_no();i++){
        if(ui->lineEdit_edit_id->text().toLower()==s_json.at(i).toObject()["id"].toString() && ui->lineEdit_edit_id->text().toLower()!=edit_stud_id_temp.toLower()){
            QMessageBox::critical(nullptr,"error","ID already exists");
            data_already_exists=true;
        }
    }
    if(data_already_exists==false){
//        qDebug()<<"we are in";
        student new_stu;
        new_stu.new_id(ui->lineEdit_edit_id->text());
        new_stu.new_name(ui->lineEdit_edit_name->text());
        new_stu.new_password(ui->lineEdit_edit_password->text());
        new_stu.new_course(ui->lineEdit_edit_course->text());
        new_stu.new_year(ui->lineEdit_edit_year->text());
        new_stu.new_part(ui->lineEdit_edit_part->text());
        new_stu.new_roll(ui->lineEdit_edit_id->text());
        QJsonObject new_stu_obj = new_stu.stu_to_qjsonobj();
        for(int i=0;i<=json->student_no();i++){
            if(edit_stud_id_temp==s_json.at(i).toObject()["id"].toString()){
                s_json.removeAt(i);
                break;
            }
        }
//        qDebug()<<s_json;
        s_json.append(new_stu_obj);
//        qDebug()<<s_json;
        QFile s_file("./JSON/student_data.json");
        if (!s_file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::critical(nullptr,"Error", "Error in parsing student data");
        }
        QJsonDocument doc(s_json);
        if(!s_file.write(doc.toJson()))
            QMessageBox::critical(nullptr,"Error", "Data could not be edited");
        else{
            QMessageBox::about(nullptr,"Success","Data edited successfully");
            foreach(QLineEdit* le, findChildren<QLineEdit*>()) {
                le->clear();
            }
            ui->stackedWidget->setCurrentIndex(4);
        }
        s_file.close();
    }

}

void admin_page::on_pushButton_delete_data_clicked()
{
    parsedata *json = new parsedata;
    QJsonArray s_json= json->student_data();
    for(int i=0;i<=json->student_no();i++){
        if(edit_stud_id_temp==s_json.at(i).toObject()["id"].toString()){
            s_json.removeAt(i);
            break;
        }
    }
//  qDebug()<<s_json;

    QMessageBox::StandardButton confirm;
    confirm = QMessageBox::question(this, "Confirm", "Are you sure you want to delete?\nID: "+edit_stud_id_temp,
                                    QMessageBox::Yes|QMessageBox::No);
    if(confirm == QMessageBox::Yes){
        QFile s_file("./JSON/student_data.json");
        if (!s_file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::critical(nullptr,"Error", "Error in parsing student data");
        }
        QJsonDocument doc(s_json);
        if(!s_file.write(doc.toJson()))
            QMessageBox::critical(nullptr,"Error", "Data could not be deleted");
        else{
            QMessageBox::about(nullptr,"Success","Data deleted successfully");
            foreach(QLineEdit* le, findChildren<QLineEdit*>()) {
                le->clear();
            }
            ui->stackedWidget->setCurrentIndex(4);
        }
        s_file.close();
    }
}
/*------------------------------------------------------------------------------------------------------------
 * ----                               edit/delete book data page                                        ------
 * ----------------------------------------------------------------------------------------------------------*/
QString edit_book_id_temp;
void admin_page::on_pushButton_edit_bookID_search_clicked()
{
    QString input_id = ui->lineEdit_book_id_edit->text().toLower();
//    qDebug()<<input_id;
    parsedata temp;
    QJsonArray book_temp=temp.book_data();
    bool is_data = false;
    for(int i=0;i<=temp.book_no();i++){
        if(book_temp.at(i).toObject()["id"].toString().toLower()==input_id){
//            qDebug()<<book_temp.at(i).toObject()["id"].toString();
            is_data=true;
            edit_book_id_temp=book_temp.at(i).toObject()["id"].toString();
            ui->stackedWidget->setCurrentIndex(8);
            ui->lineEdit_edit_book_id->setText(book_temp.at(i).toObject()["id"].toString());
            ui->lineEdit_edit_book_name->setText(book_temp.at(i).toObject()["name"].toString());
            ui->lineEdit_edit_book_year->setText(book_temp.at(i).toObject()["pub_year"].toString());
            ui->lineEdit_edit_book_author->setText(book_temp.at(i).toObject()["author"].toString());
        }
    }
    if(is_data==false){
            QMessageBox::critical(nullptr,"Error","book data doesnt exist");
    }
}

void admin_page::on_pushButton_edit_book_clicked()
{
    parsedata *json = new parsedata;
    QJsonArray book_json= json->book_data();
    //checks for pre-existing data
    bool data_already_exists = false;
    for(int i=0;i<=json->book_no();i++){
        if(ui->lineEdit_edit_id->text().toLower()==book_json.at(i).toObject()["id"].toString() && ui->lineEdit_edit_id->text().toLower()!=edit_book_id_temp.toLower()){
            QMessageBox::critical(nullptr,"error","ID already exists");
            data_already_exists=true;
        }
    }
    if(data_already_exists==false){
//        qDebug()<<"we are in";
        book new_book;
        new_book.new_id(ui->lineEdit_edit_book_id->text());
        new_book.new_name(ui->lineEdit_edit_book_name->text());
        new_book.new_author(ui->lineEdit_edit_book_author->text());
        new_book.new_pub_year(ui->lineEdit_edit_book_year->text());
        QJsonObject new_book_obj = new_book.book_to_qjsonobj();
        for(int i=0;i<=json->book_no();i++){
            if(edit_book_id_temp==book_json.at(i).toObject()["id"].toString()){
                book_json.removeAt(i);
                break;
            }
        }
//        qDebug()<<book_json;
        book_json.append(new_book_obj);
//        qDebug()<<book_json;
        QFile s_file("./JSON/book_data.json");
        if (!s_file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::critical(nullptr,"Error", "Error in parsing book data");
        }
        QJsonDocument doc(book_json);
        if(!s_file.write(doc.toJson()))
            QMessageBox::critical(nullptr,"Error", "Data could not be edited");
        else{
            QMessageBox::about(nullptr,"Success","Data edited successfully");
            foreach(QLineEdit* le, findChildren<QLineEdit*>()) {
                le->clear();
            }
            ui->stackedWidget->setCurrentIndex(4);
        }
        s_file.close();
    }
}


void admin_page::on_pushButton_delete_book_clicked()
{
    parsedata *json = new parsedata;
    QJsonArray book_json= json->book_data();
    for(int i=0;i<=json->book_no();i++){
        if(edit_book_id_temp==book_json.at(i).toObject()["id"].toString()){
            book_json.removeAt(i);
            break;
        }
    }
//  qDebug()<<book_json;
    QMessageBox::StandardButton confirm;
    confirm = QMessageBox::question(this, "Confirm", "Are you sure you want to delete?\nID: "+edit_book_id_temp,
                                    QMessageBox::Yes|QMessageBox::No);
    if(confirm == QMessageBox::Yes){
        QFile book_file("./JSON/book_data.json");
        if (!book_file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::critical(nullptr,"Error", "Error in parsing book data");
        }
        QJsonDocument doc(book_json);
        if(!book_file.write(doc.toJson()))
            QMessageBox::critical(nullptr,"Error", "Data could not be deleted");
        else{
            QMessageBox::about(nullptr,"Success","Data deleted successfully");
            foreach(QLineEdit* le, findChildren<QLineEdit*>()) {
                le->clear();
            }
            ui->stackedWidget->setCurrentIndex(4);
        }
        book_file.close();
    }
}
