#ifndef STUDENT_PAGE_H
#define STUDENT_PAGE_H

#include <QDialog>

namespace Ui {
class student_page;
}

class student_page : public QDialog
{
    Q_OBJECT

public:
    explicit student_page(QWidget *parent = nullptr);
    ~student_page();

private:
    Ui::student_page *ui;
};

#endif // STUDENT_PAGE_H
