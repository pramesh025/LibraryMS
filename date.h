#ifndef DATE_H
#define DATE_H

#include<QString>
#include<QDate>

class date{
    QString _today;
    double _price =0.5; //price for late turn in (per day)
    int _deadline_day=7; //deadline after ${deadline_day} from the issue day
    public:
        date(){
            QDate temp = QDate::currentDate();
            _today=QString::number((temp.year()*100+temp.month())*100+temp.day());
        }
        QString today(){
            return _today;
        }
        double price(){
            return _price;
        }
        int deadline_day(){
            return _deadline_day;
        }
        QDate add_deadline(QDate input){
            return input.addDays(_deadline_day);
        }
        QDate today_Qdate(){
            return QDate::currentDate();
        }

};

#endif // DATE_H
