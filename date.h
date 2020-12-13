#ifndef DATE_H
#define DATE_H

#include<QString>
#include<QDate>

class date{
    QString _today;
    QString _deadline;
    public:
        date(){
            QDate temp = QDate::currentDate();
            _today=QString::number((temp.year()*100+temp.month())*100+temp.day());
            QDate temp2=temp.addDays(7);
            _deadline=QString::number((temp2.year()*100+temp2.month())*100+temp2.day());
        }
        QString today(){
            return _today;
        }

        QString deadline(){
            return _deadline;
        }
};

#endif // DATE_H
