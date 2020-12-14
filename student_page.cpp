#include<QDebug>
#include<QDate>
#include<string>
#include<QPixmap>

#include "student_page.h"
#include "ui_student_page.h"
#include "login.h"
#include "json_parsing.h"
#include "date.h"
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
    QPixmap pic("../LibraryMS/img/default_profile.jpg");
    int height=ui->label_profile->height();
    ui->label_profile->setPixmap(pic.scaled(height,height,Qt::KeepAspectRatio));
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




/*------------------------------------------------------------------------------------------------------------
 * ----                                                                                                 ------
 * ----                             Issue-detail_page                                                   ------
 * ----                                                                                                 ------
 * ----------------------------------------------------------------------------------------------------------*/
void student_page::on_pushButton_2_clicked()
{
     ui->stackedWidget->setCurrentIndex(1);
     parsedata *json = new parsedata;
     QJsonArray book_json = json->book_data();
     QJsonObject s_json= student_page::s_data;
     int fine=0;
//     qDebug()<<"so were did it crash?";
     ui->tableWidget_issuedBooks->setRowCount(1);
     for(int j=0;j<=s_json["book_issued"].toArray().count();j++){
         for(int i=0;i<=json->book_no();i++){
             if(s_json["book_issued"].toArray().at(j).toString().toLower()==book_json.at(i).toObject()["id"].toString().toLower()){
                 QTableWidgetItem *temp_id = new QTableWidgetItem;
                 temp_id->setText(book_json.at(i).toObject()["id"].toString());
                 ui->tableWidget_issuedBooks->setItem(j, 0, temp_id);

                 QTableWidgetItem *temp_name = new QTableWidgetItem;
                 temp_name->setText(book_json.at(i).toObject()["name"].toString());
                 ui->tableWidget_issuedBooks->setItem(j, 1, temp_name);


                 date date;
                 QDate Today=date.today_Qdate();
                 QDate iss_Date=QDate::fromString(book_json.at(i).toObject()["issued_date"].toString(), "yyyyMMdd");
                 QDate return_date=date.add_deadline(iss_Date);
                 int day= return_date.daysTo(Today);



                 QTableWidgetItem *temp_issued = new QTableWidgetItem;
                 temp_issued->setText(iss_Date.toString("yyyy/MM/dd"));
                 ui->tableWidget_issuedBooks->setItem(j, 2, temp_issued);

                 QTableWidgetItem *temp_return = new QTableWidgetItem;
                 temp_return->setText(return_date.toString("yyyy/MM/dd"));
                 ui->tableWidget_issuedBooks->setItem(j, 3, temp_return);

                 QTableWidgetItem *temp_fine = new QTableWidgetItem;
                 if(day>0){
                    temp_fine->setText(QString::number(day*date.price()));
                    fine+=day*date.price();
                 }
                 else{
                     temp_fine->setText("0");
                 }
                 ui->tableWidget_issuedBooks->setItem(j,4,temp_fine);

//                 qDebug()<<"so it had crashed here!!!!!!!!!!!";
                 ui->tableWidget_issuedBooks->insertRow(ui->tableWidget_issuedBooks->rowCount());
                 break;
             }
         }
     }
     QTableWidgetItem *temp_fine_ = new QTableWidgetItem;
     temp_fine_->setText("Total fine");
     ui->tableWidget_issuedBooks->setItem(s_json["book_issued"].toArray().count(), 3, temp_fine_);

     QTableWidgetItem *temp_fine_val = new QTableWidgetItem;
     temp_fine_val->setText(QString::number(fine));
     ui->tableWidget_issuedBooks->setItem(s_json["book_issued"].toArray().count(), 4, temp_fine_val);
     ui->tableWidget_issuedBooks->item(s_json["book_issued"].toArray().count(), 4)->setTextColor(Qt::red);
}







/*------------------------------------------------------------------------------------------------------------
 * ----                                                                                                 ------
 * ----                                book_search_page                                                 ------
 * ----                                                                                                 ------
 * ----------------------------------------------------------------------------------------------------------*/
void student_page::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void student_page::on_pushButton_search_clicked()
{
    std::string input = ui->lineEdit_search_words->text().toLower().toStdString();
    parsedata *json = new parsedata;
    QJsonArray book_json = json->book_data();

    ui->tableWidget_show_result->setRowCount(0);
    int row=0;
    for(int i=0;i<=json->book_no();i++){
        std::string temp_bname=book_json.at(i).toObject()["name"].toString().toLower().toStdString();
//        qDebug()<<ui->lineEdit_search_words->text();
//        qDebug()<<book_json.at(i).toObject()["name"].toString().toLower();
        if(temp_bname.find(input)!=std::string::npos){
//            qDebug()<<temp_bname.find(input);
            ui->tableWidget_show_result->insertRow(ui->tableWidget_show_result->rowCount());
            QTableWidgetItem *temp_B_id = new QTableWidgetItem;
            temp_B_id->setText(book_json.at(i).toObject()["id"].toString());
            ui->tableWidget_show_result->setItem(row, 0, temp_B_id);

            QTableWidgetItem *temp_B_name = new QTableWidgetItem;
            temp_B_name->setText(book_json.at(i).toObject()["name"].toString());
            ui->tableWidget_show_result->setItem(row, 1, temp_B_name);

            QTableWidgetItem *temp_B_author = new QTableWidgetItem;
            temp_B_author->setText(book_json.at(i).toObject()["author"].toString());
            ui->tableWidget_show_result->setItem(row, 2, temp_B_author);

            QTableWidgetItem *temp_B_status = new QTableWidgetItem;
            if(book_json.at(i).toObject()["issued_by"].toString()=="NULL"){
                temp_B_status->setText("Not issued");
                ui->tableWidget_show_result->setItem(row, 3, temp_B_status);
            }
            else{
                temp_B_status->setText("Issued");
                ui->tableWidget_show_result->setItem(row, 3, temp_B_status);
                ui->tableWidget_show_result->item(row,3)->setTextColor(Qt::red);
            }
            row++;
        }
    }
    ui->tableWidget_show_result->removeRow(ui->tableWidget_show_result->rowCount()+1);
}






/*------------------------------------------------------------------------------------------------------------
 * ----                                                                                                 ------
 * ----                                 logout_button                                                   ------
 * ----                                                                                                 ------
 * ----------------------------------------------------------------------------------------------------------*/

void student_page::on_pushButton_4_clicked()
{
    hide();
    login *login_page = new login();
    login_page->show();
}
