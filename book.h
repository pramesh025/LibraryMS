#ifndef BOOK_H
#define BOOK_H

#include<QString>
#include<QJsonArray>
#include<QJsonObject>

class book{
    protected:
        QString _id;
        QString _name;
        QString _author;
        QString _pub_year;
        QString _issued_by="NULL";
        QString _issued_date="NULL";
    public:
        QString id(){
            return _id;
        }
        QString name(){
            return _name;
        }
        QString author(){
            return _author;
        }
        QString pub_year(){
            return _pub_year;
        }
        QString issued_by(){
            return _issued_by;
        }
        QString issued_date(){
            return _issued_date;
        }

        void new_id(QString new_id){
            _id=new_id;
        }
        void new_name(QString new_name){
            _name=new_name;
        }
        void new_author(QString new_author){
            _author=new_author;
        }
        void new_pub_year(QString new_pub_year){
            _pub_year=new_pub_year;
        }
        void new_issued_by(QString new_issued_by){
            _issued_by=new_issued_by;
        }
        void new_issued_date(QString new_issued_date){
            _issued_date=new_issued_date;
        }

        QJsonObject book_to_qjsonobj(){
            QJsonObject Jtemp;
            Jtemp.insert("id",_id);
            Jtemp.insert("name",_name);
            Jtemp.insert("author",_author);
            Jtemp.insert("pub_year",_pub_year);
            Jtemp.insert("issued_by",_issued_by);
            Jtemp.insert("issued_date",_issued_date);
            return Jtemp;
        }

};


#endif // BOOK_H
