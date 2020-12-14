#ifndef STUDENT_H
#define STUDENT_H

#include<QString>
#include<QJsonArray>
#include<QJsonObject>

#include"user.h"

class student:public user{
    protected:
        QString _year;
        QString _course;
        QString _part;
        QString _roll;
        QJsonArray _book_issued;
        QString _access_level = "student";
    public:
        QString year(){
            return _year;
        }
        QString part(){
            return _part;
        }
        QString course(){
            return _course;
        }
        QString roll(){
            return _roll;
        }


        void new_year(QString new_year){
            _year=new_year;
        }
        void new_part(QString new_part){
            _part=new_part;
        }
        void new_course(QString new_course){
            _course=new_course;
        }
        void new_roll(QString new_roll){
            _roll=new_roll;
        }

        QJsonObject stu_to_qjsonobj(){
            QJsonObject Jtemp;
            Jtemp.insert("id",_id);
            Jtemp.insert("name",_name);
            Jtemp.insert("password",_password);
            Jtemp.insert("year",_year);
            Jtemp.insert("part",_part);
            Jtemp.insert("course",_course);
            Jtemp.insert("roll",_roll);
            Jtemp.insert("book_issued",_book_issued);
            Jtemp.insert("access_level",_access_level);
            return Jtemp;
        }

};

#endif // STUDENT_H
