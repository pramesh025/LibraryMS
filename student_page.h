#ifndef STUDENT_PAGE_H
#define STUDENT_PAGE_H

#include <QDialog>
#include <QJsonObject>

namespace Ui {
class student_page;
}

class student_page : public QDialog
{
    QJsonObject s_data;
    Q_OBJECT

public:
    explicit student_page(QJsonObject,QWidget *parent = nullptr);
    ~student_page();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();


    void on_pushButton_4_clicked();

private:
    Ui::student_page *ui;
};

#endif // STUDENT_PAGE_H
