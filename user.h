#ifndef USER_H
#define USER_H

#include<iostream>
#include<string.h>

class user{
    protected:
        std::string _id;
        std::string _name;
        std::string _password;
    public:
        std::string id(){
            return _id;
        }
        void new_id(std::string new_id){
            _id=new_id;
        }
        std::string name(){
            return _name;
        }
        void new_name(std::string new_name){
            _name=new_name;
        }
        std::string password(){
            return _password;
        }
        void new_password(std::string new_password){
            _password=new_password;
        }
};

#endif // USER_H
