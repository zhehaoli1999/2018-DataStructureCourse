// Kruskal.cpp: 定义控制台应用程序的入口点。
//
#include<cstdlib>
#include<cstdio>
typedef struct edge {
	int w;
	int a, b;   //顶点a与b
}edge;

//Find函数用于对并查集进行路径压缩并返回标志
int Find(int* uset,int x){        
	if (uset[x] != x) uset[x]= Find(uset, uset[x]);
	return uset[x];
}

//Union函数用于合并并查集
void Union(int* uset, int x, int y){  //对并查集进行合并
	if (Find(uset,x)!= Find(uset,y)) uset[uset[y]]= uset[x];
}

//compare函数用于快排
int compare(const void* x,const void* y) {
	edge* e1 = (edge*)x;
	edge* e2 = (edge*)y;
	if (e1->w > e2->w)return 1;
	else if (e1->w < e2->w)return -1;
	else return 0;
}

int Kruskal(edge* Edge,int* uset,int edgenum,int vexnum) {
	int result=0;   //最后得到的生成树的长度
	
	qsort(Edge, edgenum, sizeof(edge), compare);
	///调试用：输出快排结果：for (int i = 0; i < edgenum; i++) printf("%d ",Edge[i].w);
	
	result += Edge[0].w;
	Union(uset,Edge[0].a, Edge[0].b);
	int count = 1;

	for (int i = 1; i < edgenum&&count<vexnum-1; i++) {
		if (Find(uset,Edge[i].a) == Find(uset,Edge[i].b))continue;
		else {
			Union(uset, Edge[i].a, Edge[i].b); 
			result += Edge[i].w;
			count++;
		}
	}
	return result;
}

int main()
{   
	int vexnum, edgenum;
	scanf("%d%d",&vexnum,&edgenum);
	edge* Edge = (edge*)malloc(sizeof(edge)*edgenum);
	int* uset = (int *)malloc(sizeof(int)*(vexnum+1));   //并查集，判断圈要用顶

	for (int i = 0; i < edgenum; ++i) {
		scanf("%d%d%d",&Edge[i].a,&Edge[i].b,&Edge[i].w);
	}
	for (int i = 1; i <= vexnum; i++) {   //注意顶从1--vexnum
		uset[i] = i;     //初始时，并查集中的每个结点的父节点都指向自身
	}
	printf("%d",Kruskal(Edge,uset,edgenum,vexnum));
	return 0;
}


