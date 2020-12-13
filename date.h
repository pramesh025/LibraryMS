#ifndef DATE_H
#define DATE_H

#include<QString>
#include<QDate>

class date{
    QString _today;
    public:
        date(){
            QDate temp = QDate::currentDate();
            _today=QString::number((temp.year()*100+temp.month())*100+temp.day());
        }
        QString today(){
            return _today;
        }
};

#endif // DATE_H
