#ifndef JSON_PARSING_H
#define JSON_PARSING_H

#include <QFile>
#include <QByteArray>
#include <QJsonDocument>
#include<QJsonArray>
#include <QJsonObject>
#include<QMessageBox>


class parsedata{
    public:
        void parse_student_data(){
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
            int a=json.count()-1;
            qDebug()<<a << json.at(a).toObject()["id"];
        }
};
#endif // JSON_PARSING_H
