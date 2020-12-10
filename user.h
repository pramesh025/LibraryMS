#ifndef USER_H
#define USER_H

#include<QString>

class user{
    protected:
        QString _id;
        QString _name;
        QString _password;
    public:
        QString id(){
            return _id;
        }
        void new_id(QString new_id){
            _id=new_id;
        }
        QString name(){
            return _name;
        }
        void new_name(QString new_name){
            _name=new_name;
        }
        QString password(){
            return _password;
        }
        void new_password(QString new_password){
            _password=new_password;
        }
};

#endif // USER_H
