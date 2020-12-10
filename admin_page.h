#ifndef ADMIN_PAGE_H
#define ADMIN_PAGE_H

#include <QWidget>
#include <QDialog>
#include <QJsonObject>

namespace Ui {
class admin_page;
}

class admin_page : public QWidget
{
    QJsonObject ad_data;
    Q_OBJECT

public:
    explicit admin_page(QJsonObject,QWidget *parent = nullptr);
    ~admin_page();

private slots:
    void on_pushButton_logout_clicked();

    void on_pushButton_checkin_clicked();

    void on_pushButton_renew_clicked();

    void on_pushButton_checkouts_clicked();

    void on_pushButton_add_clicked();

    void on_pushButton_edit_clicked();

    void on_pushButton_add_2_clicked();

    void on_pushButton_addConfirm_clicked();

    void on_pushButton_addnewbook_clicked();

private:
    Ui::admin_page *ui;
};

#endif // ADMIN_PAGE_H