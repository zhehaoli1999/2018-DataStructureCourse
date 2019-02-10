
#include "mainwindow.h"

#include <QApplication>



int main(int argc, char *argv[]){

    QApplication a(argc, argv);

    MainWindow w;

    w.show();

    w.setFixedSize(1000,900);   //设置大小

    w.setWindowTitle("Polynomial Calculator");  //名字要用中文

    w.myLayout();

    return a.exec();

}
