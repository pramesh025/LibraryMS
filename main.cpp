#include "login.h"
//#include"student_page.h"
//#include"admin_page.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("../LibraryMS/img/icon.png"));
    login w;
//    student_page w;
    w.show();
    return a.exec();
}
