#ifndef JSON_PARSING_H
#define JSON_PARSING_H

#include <QFile>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include<QMessageBox>


class parsedata{
    QJsonArray s_data;
    QJsonArray ad_data;
    QJsonArray _book_data;
    int s_num;
    int ad_num;
    int book_num;
    public:
        parsedata(){
            //parsing student json data
            QFile s_file("../LibraryMS/JSON/student_data.json");
            if (!s_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QMessageBox::critical(nullptr,"Error", "Error in parsing student data");
            }
            QByteArray rawData = s_file.readAll();
            // Parse document
            QJsonDocument doc(QJsonDocument::fromJson(rawData));
            if(doc.isEmpty()){
                QMessageBox::critical(nullptr,"Error","Student data empty");
            }
            // Get JSON object
            QJsonArray json = doc.array();
            int num=json.count()-1;
            s_data = json;
            s_num = num;
            s_file.close();
            //parsing admin json data
            QFile ad_file("../LibraryMS/JSON/admin_data.json");
            if (!ad_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QMessageBox::critical(nullptr,"Error", "Error in parsing admin data");
            }
            rawData = ad_file.readAll();
            // Parse document
            QJsonDocument ad_doc(QJsonDocument::fromJson(rawData));
            if(ad_doc.isEmpty()){
                QMessageBox::critical(nullptr,"Error","Admin data empty");
            }
            // Get JSON object
            QJsonArray ad_json = ad_doc.array();
            num=ad_json.count()-1;
            ad_data = ad_json;
            ad_num = num;
            ad_file.close();

            //parsing book json data
            QFile book_file("../LibraryMS/JSON/book_data.json");
            if (!book_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QMessageBox::critical(nullptr,"Error", "Error in parsing book data");
            }
            rawData = book_file.readAll();
            // Parse document
            QJsonDocument book_doc(QJsonDocument::fromJson(rawData));
            if(book_doc.isEmpty()){
                QMessageBox::critical(nullptr,"Error","book data empty");
            }
            // Get JSON object
            QJsonArray book_json = book_doc.array();
            num=book_json.count()-1;
            _book_data = book_json;
            book_num = num;
            book_file.close();
        }
        QJsonArray student_data(){
            return s_data;
        }
        int student_no(){
            return s_num;
        }
        QJsonArray admin_data(){
            return ad_data;
        }
        int admin_no(){
            return ad_num;
        }
        QJsonArray book_data(){
            return _book_data;
        }
        int book_no(){
            return book_num;
        }

};
#endif // JSON_PARSING_H
