#ifndef JSON_PARSING_H
#define JSON_PARSING_H

#include <QFile>
#include <QByteArray>
#include <QJsonDocument>
#include<QJsonArray>
#include <QJsonObject>
#include<QMessageBox>


class parsedata{
    QJsonArray s_data;
    int s_num;
    public:
        parsedata(){
            //parsing json data
            QFile file("../LibraryMS/JSON/student_data.json");
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QMessageBox::critical(nullptr,"Error", "Error in parsing student data");
            }
            QByteArray rawData = file.readAll();
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
        }
        QJsonArray student_data(){
            return s_data;
        }
        int student_no(){
            return s_num;
        }

};
#endif // JSON_PARSING_H
