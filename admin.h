#ifndef ADMIN_H
#define ADMIN_H

#include<iostream>
#include<string.h>
#include"user.h"

class admin:public user{
    std::string access_level = "admin";
};


#endif // ADMIN_H

