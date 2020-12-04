#ifndef STUDENT_H
#define STUDENT_H

#include<iostream>
#include<string.h>
#include"user.h"

class student:public user{
    protected:
        int _year;
        std::string _course;
        std::string _roll;
        std::string _book_issued[7];
        std::string _access_level = "student";
    public:
        int year(){
            return _year;
        }
        std::string course(){
            return _course;
        }
        std::string roll(){
            return _roll;
        }


        void new_year(int new_year){
            _year=new_year;
        }
        void new_course(std::string new_course){
            _course=new_course;
        }
        void new_roll(std::string new_roll){
            _roll=new_roll;
        }
};

#endif // STUDENT_H
