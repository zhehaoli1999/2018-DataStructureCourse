#include<cstdlib>
#include<iostream>
using namespace std;

typedef int** MGraph;

void DFS(MGraph G, int begin_vex,int vexnum,bool* visited) {
	cout << begin_vex+ 1 << ' ';
	for (int i = 0; i < vexnum; i++) {
		if (G[begin_vex][i]&&!visited[i]) {
			visited[i] = 1;
			DFS(G, i, vexnum,visited);
		}
	}
}

//队列

class Queue {
	typedef struct qnode {
		int vex;
		struct qnode* next;
	}qnode,*ptr_qnode;

	ptr_qnode rear;
	ptr_qnode front;
public:
	Queue() {    //队列初始化
		//头结点
		ptr_qnode temp = (ptr_qnode)malloc(sizeof(qnode));  //头结点
		if (!temp) return;
		temp->vex=-1;  //头结点的vex置-1
		temp->next = NULL;

		front = rear = temp;
	}

	~Queue() {
	}

	int EnQueue(int vertex) {  //入队
		ptr_qnode temp = (ptr_qnode)malloc(sizeof(qnode));
		temp->vex = vertex;
		temp->next = NULL;

		rear->next = temp;
		rear = rear->next;
		return 0;
	}

	bool EmptyQueue() {
		if (front == rear)return 1;
		else return 0;

	}

	int DeQueue() {   //出队,返回的是vex
		ptr_qnode temp = front->next;//队头
									 //若为空队列返回NULL；
		if (!temp) return NULL;
		//若队列中只有一个元素，要修改rear
		if (rear == temp)rear = front;

		front->next = temp->next;
		int p = temp->vex;
		free(temp);
		return p;
	}
};

void BFS(MGraph G, int begin_vex, int vexnum,bool*visited,Queue& que) {
	cout << begin_vex+1<< ' ';
	for (int i = 0; i < vexnum; i++) {
		if (G[begin_vex][i] && !visited[i]) {
			cout << i + 1 << ' ';
			visited[i] = 1;
			que.EnQueue(i);
		}
	}
	while (!que.EmptyQueue()) {  //当队列不空时
		int vex = que.DeQueue();
		for (int i = 0; i < vexnum; i++) {
			if (G[vex][i] && !visited[i]) {
				cout << i + 1 << ' ';
				visited[i] = 1;
				que.EnQueue(i);
			}
		}
	}
	
}

int main()
{
	//构建图
	int vexnum, edgenum;
	MGraph G;

	cin >> vexnum >> edgenum;
	G = (MGraph)malloc(sizeof(int*)*vexnum);
	for (int i = 0; i < vexnum; i++) {
		G[i] = (int *)malloc(sizeof(int)*vexnum);
	}
	//邻接矩阵先清零
	for (int i = 0; i < vexnum; i++) {
		for (int j = 0; j < vexnum; j++) {
			G[i][j] = 0;
		}
	}
	//边的关系
	for (int i = 0; i < edgenum; i++) {
		int a, b;
		cin >> a>>b;
		G[a-1][b-1] = G[b-1][a-1] = 1;
	}
	
	int begin_vex;
	cin >> begin_vex;
	//DFS
	bool* visited=(bool*)malloc(sizeof(bool)*vexnum);
	for (int i = 0; i < vexnum; i++)visited[i] = 0;
	visited[begin_vex-1] = 1;  
	DFS(G, begin_vex-1, vexnum, visited);

	cout << endl;

	//BFS
	Queue que;
	for (int i = 0; i < vexnum; i++)visited[i] = 0;
	visited[begin_vex - 1] = 1;
	BFS(G, begin_vex - 1, vexnum, visited, que);

    return 0;
}

