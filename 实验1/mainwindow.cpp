#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <cmath>
#include "define.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //initial
    for(int i=0;i<LEN;i++){
        polyn_set[i]=NULL;
    }
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::myLayout(){

    QWidget *centerWindow = new QWidget;   //作用？？
    this->setCentralWidget(centerWindow);

    input_expn = new QLineEdit("");   //重要，输入用！！ -->需要两个，一个用来输次数，一个用来输系数！
    input_coef =new QLineEdit("");
    input_num1 =new QLineEdit("");
    input_num2 =new QLineEdit("");
    input_x=new QLineEdit("");
    status =new QLineEdit("");

    polyn1=new QLineEdit("");
    polyn2=new QLineEdit("");
    polyn3=new QLineEdit("");

    //label
    labelInputCoef=new QLabel("         #Input Coef#->");
    labelInputExpn=new QLabel("         #Input Expn#->");
    label_num1=new QLabel("Main_operand Array Pos:");
    label_num2=new QLabel(" Sub_oprand Array Pos:");
    label_input_x=new QLabel("    Input x/Storage Pos=");
    label_status=new QLabel("         Current Status:");
    label_polyn1=new QLabel("                Polyn1=");
    label_polyn2=new QLabel("                Polyn2=");
    label_polyn3=new QLabel("         Result Polyn3=");


    //button ：要添加的：
    //1.输入多项式 2.多项式相加、相减 3.打印多项式 4.修改多项式  5.清空 6.销毁 7.计算多项式
    button_create_list = new QPushButton("Create/Insert List");

    button_subtract = new QPushButton("Substract");

    button_add = new QPushButton("Add");

    button_print = new QPushButton("Print");

    button_revise = new QPushButton("Revise");

    button_clear = new QPushButton("Clear");

    button_destroy = new QPushButton("Destroy");

    button_calculate_x = new QPushButton("Calculate x");

    button_position_in_array=new QPushButton("Position In Array");

    button_differential=new QPushButton("Differential");

    button_multiply=new QPushButton("Multiply");

    button_power=new QPushButton("Power");


    //到时需要label！表示这是输入处
    input_expn->setFixedHeight(50);    //输入框的高度
    input_coef->setFixedHeight(50);    //输入框的高度
    polyn1->setFixedHeight(40);
    polyn2->setFixedHeight(40);
    polyn3->setFixedHeight(40);
    status->setFixedHeight(40);

    button_create_list->setMinimumHeight(30);  //button的高度

    button_subtract->setMinimumHeight(30);
    button_add->setMinimumHeight(30);

    button_print->setMinimumHeight(30);

    button_revise->setMinimumHeight(30);

    button_clear->setMinimumHeight(30);

    button_destroy->setMinimumHeight(30);

    button_calculate_x->setMinimumHeight(30);

    button_position_in_array->setMinimumHeight(30);

    button_differential->setMinimumHeight(30);

    button_multiply->setMinimumHeight(30);

    button_power->setMinimumHeight(30);

    //连接信号

    connect(button_create_list,SIGNAL(clicked(bool)),this,SLOT(button_create_list_clicked()));   //重要!!!

    connect(button_subtract,SIGNAL(clicked(bool)),this,SLOT(button_substract_clicked()));

    connect(button_add,SIGNAL(clicked(bool)),this,SLOT(button_add_clicked()));

    connect(button_print,SIGNAL(clicked(bool)),this,SLOT(button_print_clicked()));

    connect(button_revise,SIGNAL(clicked(bool)),this,SLOT(button_revise_clicked()));

    connect(button_clear,SIGNAL(clicked(bool)),this,SLOT(button_clear_clicked()));

    connect(button_destroy,SIGNAL(clicked(bool)),this,SLOT(button_destroy_clicked()));

    connect(button_calculate_x,SIGNAL(clicked(bool)),this,SLOT(button_calculate_x_clicked()));

    connect(button_differential,SIGNAL(clicked(bool)),this,SLOT(button_differential_clicked()));

    connect(button_position_in_array,SIGNAL(clicked(bool)),this,SLOT(button_position_in_array_clicked()));

    connect(button_multiply,SIGNAL(clicked(bool)),this,SLOT(button_multiply_clicked()));

    connect(button_power,SIGNAL(clicked(bool)),this,SLOT(button_power_clicked()));


    QGridLayout * layout = new QGridLayout;
    //第一行
    layout->addWidget(input_num1,1,2,1,1,Qt::Alignment());
    layout->addWidget(label_num1,1,1,1,1,Qt::Alignment());

    layout->addWidget(input_num2,1,4,1,1,Qt::Alignment());
    layout->addWidget(label_num2,1,3,1,1,Qt::Alignment());


    //第二行：输入
    layout->addWidget(input_expn,2,4,1,1,Qt::Alignment());   //输入框的位置
    layout->addWidget(labelInputExpn,2,3,1,1,Qt::Alignment());

    layout->addWidget(input_coef,2,2,1,1,Qt::Alignment());   //输入框的位置
    layout->addWidget(labelInputCoef,2,1,1,1,Qt::Alignment());
    //第三行：status，input_x
    layout->addWidget(label_status,3,1,1,1,Qt::Alignment());
    layout->addWidget(status,3,2,1,2,Qt::Alignment());


    layout->addWidget(input_x,3,5,1,1,Qt::Alignment());
    layout->addWidget(label_input_x,3,4,1,1,Qt::Alignment());

    //第4行：polyn1
    layout->addWidget(label_polyn1,4,1,1,1,Qt::Alignment());
    layout->addWidget(polyn1,4,2,1,4,Qt::Alignment());


    //第5行：polyn2
    layout->addWidget(label_polyn2,5,1,1,1,Qt::Alignment());
    layout->addWidget(polyn2,5,2,1,4,Qt::Alignment());
    //第6行：polyn3
    layout->addWidget(label_polyn3,6,1,1,1,Qt::Alignment());
    layout->addWidget(polyn3,6,2,1,4,Qt::Alignment());

    //第7行：从左到右：create， print，clear，revise,destroy
    layout->addWidget(button_create_list,7,1,Qt::Alignment());

    layout->addWidget(button_print,7,2,Qt::Alignment());

    layout->addWidget(button_clear,7,3,Qt::Alignment());

    layout->addWidget(button_revise,7,4,Qt::Alignment());

     layout->addWidget(button_destroy,7,5,Qt::Alignment());

    //第8行：add,subtract,calculate,differential,position
    layout->addWidget(button_subtract,8,1,Qt::Alignment());

    layout->addWidget(button_add,8,2,Qt::Alignment());

    layout->addWidget(button_calculate_x,8,3,Qt::Alignment());

    layout->addWidget(button_differential,8,4,Qt::Alignment());

    layout->addWidget(button_multiply,8,5,Qt::Alignment());

    //第9行
    layout->addWidget(button_power,9,1,Qt::Alignment());

    layout->setMargin(12);

    centerWindow->setLayout(layout);

}


bool MakeNode(PNode &p,int in_expn,double in_coef) {
    PNode q = (PNode)malloc(sizeof(Node));
    if (!q) return false;
    else {
        q->coef=in_coef;
        q->expn=in_expn;
        q->next = NULL;    		//!!!!
        p = q;
        return true;
    }
}

bool LocateElem(int temp_expn, PNode p,PNode &position) {
    PNode q = p->next;      //需要每次从头开始比对
    //元素按次数升序排列：
    while (q&&q->expn<temp_expn) {  //q不为NULL & 待插入元素次数更大
        p = q;        //p被使用了
        q = q->next;
    }
    //如果q已经为NULL 或者发现没有相等的次数，则可以插入
    if (!q ||q->expn>temp_expn) {
        position = p;
        return true;  //true表示在p的后面可以插入
    }
    else return false;
}

void InsertNode(PNode &p, PNode &Inserted_Node) {
    //将Inserted_Node所指向结点插入p所指结点的下一位
    Inserted_Node->next = p->next;
    p->next = Inserted_Node;
}

bool CreatePolyn(PNode &L,PNode &p) {
     //输入数据
    double temp_coef=p->coef;
    int temp_expn=p->expn;

    PNode position;

    if(fabs(temp_coef-0)>=EPS||fabs(temp_expn-0)>=EPS){
        bool flag=LocateElem(temp_expn, L, position);
        if(flag) InsertNode(position, p);
        else return false;
        PNode q;
        for (q=L->next;q!=NULL;q = q->next) {
        }
        q= NULL;
        L->expn++;
    }
   //长度储存在头结点
    return true;
}

void MainWindow::print(PNode &L,QLineEdit* p){
    if(L==NULL){
        status->setText("The polynomial has already been destoryed..");
        return;  //如果L被dertroy了
    }
    PNode q=L->next;  //应为L1->next
    QString S_polyn="";

    while(q!=NULL){
        QString S_temp=(S_polyn.number(q->coef,'g')+"x^"+S_polyn.number(q->expn)+"+");
        S_polyn+=S_temp;
        q=q->next;

    }
    QString S_temp=S_polyn.left(S_polyn.length() - 1);
    //S_polyn =S_polyn.left(S_polyn.length() - 1);
    QString S_length=NULL;
    S_length=S_length.setNum(L->expn);
    S_temp+=(" (length:"+S_length+")");
    p->setText(S_temp);
    //状态
    status->setText("The result is printed.");

}

void MainWindow::button_create_list_clicked(){
    //读取指针数组序号
    QString S_num =input_num1->text();
    int temp_num =S_num.toInt();
    //读取coef
    QString S_coef = input_coef->text();
    double temp_coef =S_coef.toDouble();
    if(fabs(temp_coef-0)<=EPS) return;  //输入系数为1的情况
    //读取expn
    QString S_expn = input_expn->text();
    double temp_expn2=S_expn.toDouble();//用来判断用户是不是输入正确格式的expn
    if((temp_expn2-floor(temp_expn2))>EPS){
        status->setText("Wrong! The expn shoule be an int!");
        return;
    }
    int temp_expn=S_expn.toInt();
    //创建链表
    PNode p;
    MakeNode(p,temp_expn,temp_coef);

    if(polyn_set[temp_num]==NULL) MakeNode(polyn_set[temp_num],0,0);

    if(!CreatePolyn(polyn_set[temp_num],p)){
        status->setText("Wrong! You have entered a previous expn!");
        return;    //否则后一个setText会覆盖这一个！！！
    }

    //打印
    print(polyn_set[temp_num],polyn1);
    //状态
    status->setText("Polyn["+S_num+"] is created!");
}

void MainWindow::button_add_clicked(){
    QString S_num1 =input_num1->text();
    int num1=S_num1.toInt();

    QString S_num2 =input_num2->text();
    int num2=S_num2.toInt();

    QString S_num3=input_x->text();
    int num3=S_num3.toInt();

    PNode temp_result_L=NULL;
    Add(polyn_set[num1],polyn_set[num2],temp_result_L);

    //打印运算结果
    print(temp_result_L,polyn3);
    //状态
    QString S_status="Polyn["+S_num1+"] substracted polyn["+S_num2+"].The result is shown.";
    status->setText(S_status);

    if (num3) polyn_set[num3-1] = temp_result_L;   //当input_x 输入！=0时，储存结果
    //要记得销毁temp_result_L!!!
    else{
        PNode p;
        p=temp_result_L->next;
        while(p){
            temp_result_L->next=p->next;
            free(p);
            p=temp_result_L->next;
        }
        free(temp_result_L);
    }

}

PNode Add(PNode& L1,PNode& L2,PNode& result){

    PNode temp_result_L,temp_result1,temp_result2;

    int if_zero=0;  //用来指示相加的结果是否为0；if_zero为1表示结果为0，否则为1
    int temp_count = 0; //用来计数temp_result的长度，然后存储在temp_result头结点
    //临时的结果链表的头结点，这里的空间是在堆上。注意如果加的结果不需要，要释放空间
    MakeNode(temp_result_L,0,0);

    temp_result1 = temp_result_L;

    PNode p1 = L1->next;
    PNode p2 = L2->next;

    while (p1&&p2) {   //循环条件是p1和p2都不为NULL！
       MakeNode(temp_result2,0,0);
            if (p1->expn < p2->expn) {
                temp_result2->coef = p1->coef;
                temp_result2->expn = p1->expn;
                p1=p1->next;
            }
            else if (p1->expn > p2->expn) {
                temp_result2->coef = p2->coef;
                temp_result2->expn = p2->expn;
                p2 = p2->next;
            }
            else { //次数相等了
                temp_result2->expn = p1->expn;
                temp_result2->coef = p1->coef + p2->coef;

                if (fabs(temp_result2->coef- 0.0)<=EPS) {
                    if_zero = 1;
                    free(temp_result2);
                    temp_count -= 1;
                    temp_result2 = NULL;
                }
                else { if_zero = 0; }

                p1 = p1->next;
                p2 = p2->next;
            }
            if (if_zero == 0) {   //=0表示结果不为0！！！
                temp_count++;
                temp_result1->next = temp_result2;
                temp_result1=temp_result1->next;
            } //如果相加结果不为0，temp_result1后移

        }
    if(!p1&&p2){
        while(p2!=NULL){
             MakeNode(temp_result2,0,0);
             temp_result2->coef = p2->coef;
             temp_result2->expn = p2->expn;
             p2 = p2->next;
             temp_count++;
             temp_result1->next = temp_result2;
             temp_result1=temp_result1->next;
        }
    }
    if(p1&&!p2){
        while(p1!=NULL){
             MakeNode(temp_result2,0,0);
             temp_result2->coef = p1->coef;
             temp_result2->expn = p1->expn;
             p1 = p1->next;
             temp_count++;
             temp_result1->next = temp_result2;
             temp_result1=temp_result1->next;
        }
    }

        temp_result1->next = NULL;
        temp_result_L->expn = temp_count;   //长度存储在头结点

        result =temp_result_L;
        return result;
}

void MainWindow::button_substract_clicked(){
        QString S_num1 =input_num1->text();
        int num1=S_num1.toInt();

        QString S_num2 =input_num2->text();
        int num2=S_num2.toInt();

        QString S_num3=input_x->text();
        int num3=S_num3.toInt();

        PNode L1 = polyn_set[num1];
        PNode L2 = polyn_set[num2];
        //为L1+ or -L2

        PNode temp_result_L,temp_result1,temp_result2;
        MakeNode(temp_result_L,0,0);

        if(num1!=num2){
            int if_zero=0;  //用来指示相加的结果是否为0；if_zero为1表示结果为0，否则为1
            int temp_count = 0; //用来计数temp_result的长度，然后存储在temp_result头结点
            //临时的结果链表的头结点，这里的空间是在堆上。注意如果加的结果不需要，要释放空间

            temp_result1 = temp_result_L;

            PNode p1 = L1->next;
            PNode p2 = L2->next;

            while (p1&&p2) {   //循环条件是p1和p2都不为NULL！
               MakeNode(temp_result2,0,0);
                    if (p1->expn < p2->expn) {
                        temp_result2->coef = p1->coef;
                        temp_result2->expn = p1->expn;
                        p1=p1->next;
                    }
                    else if (p1->expn > p2->expn) {
                        temp_result2->coef = -p2->coef;
                        temp_result2->expn = p2->expn;
                        p2 = p2->next;
                    }
                    else { //次数相等了
                        temp_result2->expn = p1->expn;
                        temp_result2->coef = p1->coef - p2->coef;

                        if (fabs(temp_result2->coef- 0.0)<=EPS) {
                            if_zero = 1;
                            free(temp_result2);
                            temp_count -= 1;
                            temp_result2 = NULL;
                        }
                        else { if_zero = 0; }

                        p1 = p1->next;
                        p2 = p2->next;
                    }
                    if (if_zero == 0) {   //=0表示结果不为0！！！
                        temp_count++;
                        temp_result1->next = temp_result2;
                        temp_result1=temp_result1->next;
                    } //如果相加结果不为0，temp_result1后移

                }
            if(!p1&&p2){
                while(p2!=NULL){
                     MakeNode(temp_result2,0,0);
                     temp_result2->coef = -p2->coef;
                     temp_result2->expn = p2->expn;
                     p2 = p2->next;
                     temp_count++;
                     temp_result1->next = temp_result2;
                     temp_result1=temp_result1->next;
                }
            }
            if(p1&&!p2){
                while(p1!=NULL){
                     MakeNode(temp_result2,0,0);
                     temp_result2->coef = p1->coef;
                     temp_result2->expn = p1->expn;
                     p1 = p1->next;
                     temp_count++;
                     temp_result1->next = temp_result2;
                     temp_result1=temp_result1->next;
                }
            }

                temp_result1->next = NULL;
                temp_result_L->expn = temp_count;   //长度存储在头结点
       }
            //打印运算结果
        print(temp_result_L,polyn3);
            //状态
        QString S_status="Polyn["+S_num1+"] substracted polyn["+S_num2+"].The result is shown.";
        status->setText(S_status);

        if (num3) polyn_set[num3-1] = temp_result_L;   //当input_x 输入！=0时，储存结果
        else{
            PNode p;
            p=temp_result_L->next;
            while(p){
                temp_result_L->next=p->next;
                free(p);
                p=temp_result_L->next;
            }
            free(temp_result_L);
            }
    }

void MainWindow::button_print_clicked(){
    //读取指针数组序号
    QString S_num =input_num1->text();
    int temp_num=S_num.toInt();
    //打印
    print(polyn_set[temp_num],polyn2);
}

void MainWindow::button_revise_clicked(){
    //读入
    QString S_num =input_num1->text();
    int num=S_num.toInt();

    QString S_revise_expn =input_expn->text();
    int revise_expn=S_revise_expn.toInt();

    QString S_revise_coef =input_coef->text();
    double revise_coef=S_revise_coef.toDouble();

    QString S_expn=input_x->text();     //修改后的次数
    int expn=S_expn.toInt();

    //处理
    PNode p = polyn_set[num]->next;
    PNode q= polyn_set[num];
    while (p) {
       if (p->expn==revise_expn) {
                if (fabs(revise_coef-0.0)<=EPS) {
                    q->next = p->next;
                    free(p);
                    polyn_set[num]->expn--;
                    print(polyn_set[num],polyn3);
                    status->setText("Polynomial["+S_num+"] is revised.");
                    return;
                }
                else {
                    p->coef = revise_coef;
                    //次数修改后要重新排序！
                    if(expn!=0){
                        p->expn=expn;
                        q->next=p->next;
                        PNode pos;
                        bool flag=LocateElem(expn,polyn_set[num],pos);
                        if(!flag){
                            status->setText("Wrong! You have entered a previous expn!");
                            return;
                        }
                        else InsertNode(pos,p);

                    }

                    print(polyn_set[num],polyn3);
                    status->setText("Polynomial["+S_num+"] is revised.");
                    return;
                }
            }
            else {
                q = p;
                p = p->next;
            }
            if (p == NULL)status->setText("Sorry, can't find the aim node!");
        }

}

void MainWindow::button_clear_clicked(){
    QString S_num=input_num1->text();
    int num=S_num.toInt();
    PNode p=polyn_set[num]->next;
    while(p!=NULL){
        polyn_set[num]->next=p->next;
        free(p);
        p=polyn_set[num]->next;
    }
    polyn_set[num]->expn=0;
    status->setText("Polynomial["+S_num+"] is Cleared.");

}

void MainWindow::button_destroy_clicked(){
    QString S_num=input_num1->text();
    int num=S_num.toInt();
    PNode p=polyn_set[num]->next;
    while(p!=NULL){
        polyn_set[num]->next=p->next;
        free(p);
        p=polyn_set[num]->next;
    }
    free(polyn_set[num]);
    polyn_set[num]=NULL;//方便print函数操作
    status->setText("Polynomial["+S_num+"] is Destroyed.");


}

void MainWindow::button_calculate_x_clicked(){
    QString S_num=input_num1->text();
    int num=S_num.toInt();
    QString S_x=input_x->text();
    double x=S_x.toDouble();
    PNode p=polyn_set[num]->next;

    double result=0.0;
    while(p!=NULL){
        if(p->expn<0&&fabs(x-0.0)<EPS){
            status->setText("Wrong! x can't be zero!");
            return;
        }
        result+=(p->coef*pow(x,(double)p->expn));
        p=p->next;
    }
    QString S_result=0;
    S_result=S_result.setNum(result);
    polyn3->setText("result="+S_result);


}

void MainWindow::button_position_in_array_clicked(){
    QString S_position=0;
    QString S_temp=0;
    int count=0;
    for(int i=0;i<LEN ;i++) {
        if(polyn_set[i]){
            S_position+=(S_temp.setNum(i)+",");
            count++;
        }

    QString S_pos=S_position.left(S_position.length() -1);
    //为什么S_position=S_position.left(S_position.length() -1);不对？？？

    polyn3->setText("There are "+S_temp.setNum(count)+\
                    " polynomials in array,their positions are:"+S_pos);
    }
}

void MainWindow::button_differential_clicked(){
    QString S_num=input_num1->text();
    int num=S_num.toInt();

    QString S_order=input_num2->text();  //n阶导
    int order=S_order.toInt();

    QString S_if_store=input_x->text();
    int if_store=S_if_store.toInt();

    if(!polyn_set[num]){
        status->setText("Wrong! This polynomial doesn't exist!");
        return;
    }

    PNode p=polyn_set[num]->next; //p用来遍历polyn_set[num]

    PNode temp_L,temp1,temp2;  //temp用来创建新链表
    MakeNode(temp_L,0,0);
    temp1=temp_L;
    temp_L->expn=polyn_set[num]->expn;
    while(p){
        MakeNode(temp2,p->expn,p->coef);
        temp1->next=temp2;
        temp1=temp1->next;
        p=p->next;
    }

    //处理临时链表
    p=temp_L->next;
    PNode q=temp_L;


    for(int i=0; i<order; i++){
        while(p){
            if(p->expn==0){
                q->next=p->next;
                free(p);
                temp_L->expn--;
                p=q->next;

            }
            else{
                p->coef*=p->expn;
                p->expn--;
                q=q->next;
                p=p->next;
            }
        }//while结束！
        p=temp_L->next;
        q=temp_L;
    }

    print(temp_L,polyn3);
    status->setText("Differential is done.");
    if(if_store)polyn_set[if_store]=temp_L;
    else{
        p=temp_L->next;
        while(p){
            temp_L->next=p->next;
            free(p);
            p=temp_L->next;
        }
        free(temp_L);
    }
}

void MainWindow::button_multiply_clicked(){
    QString S_num1 =input_num1->text();
    int num1=S_num1.toInt();

    QString S_num2 =input_num2->text();
    int num2=S_num2.toInt();

    PNode L1 = polyn_set[num1];
    PNode L2 = polyn_set[num2];
    //为L1 * L2

    //复制L2
    PNode temp_L2;
    MakeNode(temp_L2,0,0);
    PNode q=temp_L2;

    PNode temp_node;
    PNode p2=L2->next;

    while(p2){
        MakeNode(temp_node,0,0);
        temp_node->coef=p2->coef;
        temp_node->expn=p2->expn;
        q->next=temp_node;
        q=q->next;
        p2=p2->next;
    }//复制完成

    PNode temp_result;
    MakeNode(temp_result,0,0);

    PNode p1=L1->next;
    PNode temp_p2=temp_L2->next;
    p2=L2->next;
    while(p1!=NULL){
        while(p2!=NULL){
            temp_p2->coef=p2->coef*p1->coef;
            temp_p2->expn=p2->expn+p1->expn;
            p2=p2->next;
            temp_p2=temp_p2->next;
        }
        Add(temp_L2,temp_result,temp_result);
        p2=L2->next;
        temp_p2=temp_L2->next;
        p1=p1->next;
    }

    print(temp_result,polyn3);
    //print(temp_L2,polyn3);
        //状态
    QString S_status="Polyn["+S_num1+"] multiply polyn["+S_num2+"].The result is shown.";
    status->setText(S_status);

}

void MainWindow::button_power_clicked(){
    QString S_num1 =input_num1->text();
    int num1=S_num1.toInt();

    QString S_power =input_num2->text();
    int power=S_power.toInt();

    PNode L2 = polyn_set[num1];
    //为L2 **power

    //复制L2
    PNode temp_L2;
    MakeNode(temp_L2,0,0);
    PNode q=temp_L2;

    PNode temp_node;
    PNode p2=L2->next;

    while(p2){
        MakeNode(temp_node,0,0);
        temp_node->coef=p2->coef;
        temp_node->expn=p2->expn;
        q->next=temp_node;
        q=q->next;
        p2=p2->next;
    }//复制完成

    PNode temp_result;
    MakeNode(temp_result,0,0);

    PNode p1=L2->next;
    PNode temp_p2=temp_L2->next;
    p2=L2->next;

    PNode temp_result_copy2;
    for(int i=1;i<power;i++){
        while(p1!=NULL){
            while(p2!=NULL){
                temp_p2->coef=p2->coef*p1->coef;
                temp_p2->expn=p2->expn+p1->expn;
                p2=p2->next;
                temp_p2=temp_p2->next;
            }
            Add(temp_L2,temp_result,temp_result);
            p2=L2->next;
            temp_p2=temp_L2->next;
            p1=p1->next;
        }
        //复制temp_result
        PNode temp_result_copy;
        MakeNode(temp_result_copy,0,0);
        PNode copy_q=temp_result_copy;

        PNode temp_node;
        PNode copy_p2=temp_result->next;

        while(copy_p2){
            MakeNode(temp_node,0,0);
            temp_node->coef=copy_p2->coef;
            temp_node->expn=copy_p2->expn;
            copy_q->next=temp_node;
            copy_q=copy_q->next;
            copy_p2=copy_p2->next;
        }//复制完成
        temp_L2=temp_result_copy;

        //复制temp_result

        MakeNode(temp_result_copy2,0,0);
        copy_q=temp_result_copy2;

        copy_p2=temp_result->next;

        while(copy_p2){
            MakeNode(temp_node,0,0);
            temp_node->coef=copy_p2->coef;
            temp_node->expn=copy_p2->expn;
            copy_q->next=temp_node;
            copy_q=copy_q->next;
            copy_p2=copy_p2->next;
        }//复制完成
        MakeNode(temp_result,0,0);

        p2=temp_result_copy2->next;

        p1=L2->next;
        temp_p2=temp_L2->next;
    }

    print(temp_result_copy2,polyn3);
    //print(temp_L2,polyn3);
        //状态
    QString S_status="Polyn["+S_num1+"]power.The result is shown.";
    status->setText(S_status);

}
