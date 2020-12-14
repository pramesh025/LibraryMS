#ifndef ADMIN_H
#define ADMIN_H

#include<QString>
#include"user.h"

class admin:public user{
    QString access_level = "admin";
};


#endif // ADMIN_H

