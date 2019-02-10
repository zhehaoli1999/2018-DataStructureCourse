#ifndef DEFINE_H
#define DEFINE_H
#define EPS 1e-6

typedef struct PolynNode {
    double coef;
    int expn;
    struct PolynNode* next;
}Node, *PNode;
//PNode = Pointer of the Node

bool MakeNode(PNode &p,int,double);//创建多项式的一个结点

bool LocateElem(int temp_expn, PNode p, PNode&position);//定位元素

void InsertNode(PNode &p, PNode &Inserted_Node);//插入结点

int cmp(int a, int b);

bool CreatePolyn(PNode &L,PNode&);//创建多项式

void ClearPolyn(PNode &L); //清空多项式

void DestroyPolyn(PNode &L);//销毁多项式

void PrintPolyn(const PNode L);//输出多项式

void PolynLength(const PNode L);//求多项式的长

void AddPolyn(int num1,int num2, PNode PolynSet[],PNode result,bool if_sub);//多项式相加&相减

void RevisePolyn(PNode& L);

void ReviseNode(PNode& L, int expn, double coef);

void InsertPolyn(PNode& L, int expn, double coef);

void DeleteNode(PNode& L, int expn);

void Multiply(PNode& a,PNode& b);

PNode Add(PNode& L1,PNode& L2,PNode& result );

#endif // DEFINE_H
