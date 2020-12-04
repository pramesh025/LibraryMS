#ifndef BOOK_H
#define BOOK_H

#include<iostream>
#include<string.h>

class book{
    protected:
        std::string _id;
        std::string _name;
        std::string _author;
        int _pub_year;
        std::string _issued_by="NULL";
        std::string _issued_date="NULL";
    public:
        std::string id(){
            return _id;
        }
        std::string name(){
            return _name;
        }
        std::string author(){
            return _author;
        }
        int pub_year(){
            return _pub_year;
        }
        std::string issued_by(){
            return _issued_by;
        }
        std::string issued_date(){
            return _issued_date;
        }

        void new_id(std::string new_id){
            _id=new_id;
        }
        void new_name(std::string new_name){
            _name=new_name;
        }
        void new_author(std::string new_author){
            _author=new_author;
        }
        void new_pub_year(int new_pub_year){
            _pub_year=new_pub_year;
        }
        void new_issued_by(std::string new_issued_by){
            _issued_by=new_issued_by;
        }
        void new_issued_date(std::string new_issued_date){
            _issued_date=new_issued_date;
        }
};


#endif // BOOK_H
