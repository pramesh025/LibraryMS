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

    void on_pushButton_edit_stuID_SEARCH_clicked();

    void on_pushButton_edit_confirm_clicked();

    void on_pushButton_delete_data_clicked();

    void on_pushButton_edit_bookID_search_clicked();

    void on_pushButton_edit_book_clicked();

    void on_pushButton_delete_book_clicked();

    void on_pushButton_issue_stID_search_clicked();

    void on_pushButton_issue_bID_search_clicked();

    void on_pushButton_issue_clicked();

private:
    Ui::admin_page *ui;
};

#endif // ADMIN_PAGE_H
