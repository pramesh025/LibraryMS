#ifndef STUDENT_H
#define STUDENT_H

#include<QString>
#include"user.h"

class student:public user{
    protected:
        QString _year;
        QString _course;
        QString _part;
        QString _roll;
        QString _book_issued[7]={"NULL","NULL","NULL","NULL","NULL","NULL","NULL"};
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
};

#endif // STUDENT_H
