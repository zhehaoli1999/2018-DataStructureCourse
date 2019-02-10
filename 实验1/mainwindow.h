#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPushButton>
#include <QLineEdit>
#include<QLabel>
#include"define.h"
#define LEN 31
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
protected:
    PNode polyn_set[LEN];

    QLineEdit *input_expn;
    QLineEdit *input_coef;
    QLineEdit *input_num1;
    QLineEdit *input_num2;
    QLineEdit *input_x;
    QLineEdit *polyn1;
    QLineEdit *polyn2;
    QLineEdit *polyn3;
    QLineEdit *status;

    QLabel  *labelInputCoef;
    QLabel  *labelInputExpn;
    QLabel  *label_num1;
    QLabel  *label_num2;
    QLabel  *label_input_x;   //选择指针数组中的序号
    QLabel *label_polyn1;
    QLabel *label_polyn2;
    QLabel *label_polyn3;
    QLabel *label_status;

    QPushButton *button_create_list;
    QPushButton *button_add;
    QPushButton *button_subtract;
    QPushButton *button_print;
    QPushButton *button_revise;
    QPushButton *button_clear;
    QPushButton *button_destroy;
    QPushButton *button_calculate_x;
    QPushButton *button_differential;  //微分
    QPushButton *button_position_in_array;   //输出指针数组中已经创建的多项式的序号
    QPushButton *button_multiply;
    QPushButton *button_power;

public:

    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();



public:
    void print(PNode &L,QLineEdit *);
    void myLayout();

private slots:

    void button_create_list_clicked();

    void button_substract_clicked();

    void button_print_clicked();

    void button_revise_clicked();

    void button_clear_clicked();

    void button_destroy_clicked();

    void button_calculate_x_clicked();

    void button_add_clicked();

    void button_position_in_array_clicked();

    void button_differential_clicked();

    void button_multiply_clicked();

    void button_power_clicked();

private:
    Ui::MainWindow *ui;

};



#endif // MAINWINDOW_H
