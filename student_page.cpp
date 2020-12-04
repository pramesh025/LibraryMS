#include "student_page.h"
#include "ui_student_page.h"

student_page::student_page(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::student_page)
{
    ui->setupUi(this);
}

student_page::~student_page()
{
    delete ui;
}
