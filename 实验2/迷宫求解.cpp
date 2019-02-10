#include<cstdlib>
#include<iostream>
using namespace std;

//*****思路***** 找最短路径：用队列进行广度优先搜索：某结点出队后将其周围可以走的位置入队，
//                           再队头出队，直到队头位置为终点位置，能确保是最短 
 
//定义位置结点：
typedef struct pos_node {
	struct pos_node * prior = NULL;    //设置前驱的目的：输出的时候找迷宫矩阵中当前位置的前驱
	int cur[2] = { 0 };    //current   当前位置，[0]为x,[1]为y
	struct pos_node * next = NULL;    //为链式队列
}pos, *ptr_pos;

//采用链式队列
typedef struct {
	ptr_pos rear;
	ptr_pos front;
}queue;

//定义
int InitQueue(queue & que) {    //队列初始化
	ptr_pos temp = (ptr_pos)malloc(sizeof(pos));  //头结点
	if (!temp)return 1;
	temp->next = NULL;
	temp->prior = NULL;

	que.front = que.rear = temp;
	return 0;
}

int Enter(queue & que, ptr_pos pos) {  //入队
	if (!pos) {
		return 1;  //如果pos 为NULL，非法，退出
	}
	que.rear->next = pos;
	que.rear = que.rear->next;
	que.rear->next = NULL;
	return 0;
}

ptr_pos Out(queue & que) {   //出队
	ptr_pos temp = que.front->next;//队头
	//若为空队列返回NULL；
	if (!temp) return NULL;
	//若队列中只有一个元素，要修改rear
	if (que.rear == temp)que.rear = que.front;

	que.front->next = temp->next;
	//出队的元素未删除！因为输出时可能用
	return temp;
}
void print(ptr_pos p) {   //打印
	if (p->prior!=NULL) print(p->prior);
	cout << "(" << p->cur[0]+1<<',' << p->cur[1]+1 << ")" << "->";
}
bool is_first = true;
void output(ptr_pos p,int* final)//可以通过调用本函数输出结果 
{
	if(p->prior!=NULL) output(p->prior,final);
	cout<<"("<<p->cur[0]+1<<","<<p->cur[1]+1<<")";
	if((p->cur[0]+1)!=(final[0]+1)||(p->cur[1]+1)!=(final[1]+1))
		cout<<"->";
}


void Moveable(ptr_pos pos, bool&up, bool&down, bool& left, bool& right, int** maze, int row, int column) {
	//这是判断当前位置的上下左右方位能不能走的函数
	up = down = left = right = 0;//不可行
	if (pos->cur[0] + 1 < row && maze[(pos->cur[0] + 1)][pos->cur[1]] == 1)down = 1;
	if (pos->cur[0] - 1 >= 0 && maze[(pos->cur[0] - 1)][pos->cur[1]] == 1)up = 1;
	if (pos->cur[1] + 1 < column && maze[(pos->cur[0])][pos->cur[1] + 1] == 1)right = 1;
	if (pos->cur[1] - 1 >= 0 && maze[(pos->cur[0])][pos->cur[1] - 1] == 1)left = 1;
}

void Move(ptr_pos cur_pos, queue& que, int** maze, int row, int column) {
	bool left, right, up, down;
	Moveable(cur_pos, up, down, left, right, maze, row, column);
	if (up) {
		ptr_pos up_pos = (ptr_pos)malloc(sizeof(pos));
		up_pos->prior = cur_pos;
		up_pos->cur[0] = cur_pos->cur[0] - 1;
		up_pos->cur[1] = cur_pos->cur[1];
		up_pos->next = NULL;

        //下一句修改迷宫矩阵对应位置的值，是为了标识这个位置走过了，不能再走了（不用栈）
	  	maze[up_pos->cur[0]][up_pos->cur[1]] =-1;
		Enter(que, up_pos);  //入队
	}
	if (down) {
		ptr_pos down_pos = (ptr_pos)malloc(sizeof(pos));
		down_pos->prior = cur_pos;
		down_pos->cur[0] = cur_pos->cur[0] + 1;
		down_pos->cur[1] = cur_pos->cur[1];
		down_pos->next = NULL;

		maze[down_pos->cur[0]][ down_pos->cur[1]] = -1;
		Enter(que, down_pos);

	}
	if (left) {
		ptr_pos left_pos = (ptr_pos)malloc(sizeof(pos));
		left_pos->prior = cur_pos;
		left_pos->cur[0] = cur_pos->cur[0];
		left_pos->cur[1] = cur_pos->cur[1] - 1;
		left_pos->next = NULL;

		maze[left_pos->cur[0]][left_pos->cur[1]] = -1;
		Enter(que, left_pos);
		;
	}
	if (right) {
		ptr_pos right_pos = (ptr_pos)malloc(sizeof(pos));
		right_pos->prior = cur_pos;
		right_pos->cur[0] = cur_pos->cur[0];
		right_pos->cur[1] = cur_pos->cur[1] + 1;
		right_pos->next = NULL;

		maze[right_pos->cur[0] ][ right_pos->cur[1]] =-1;

		Enter(que, right_pos);

	}

}

int main()
{
	//读取迷宫的行数和列数
	int m, n;//m 行 n 列
	cin >> m >> n;

	//储存输入的迷宫
	int** maze = (int**)malloc(m* sizeof(int*));
	for(int i=0;i<m;i++){
		maze[i]=(int*)malloc(n* sizeof(int));
	}
	
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			int temp;
			cin>>temp;
			maze[i][j] = temp; 
		}
	}

	//读取起点和终点
	ptr_pos start_pos = (ptr_pos)malloc(sizeof(pos));  //起点
	int final[2]; //终点
		
	start_pos->prior= NULL;
	start_pos->next = NULL;

	cin>>start_pos->cur[0]>>start_pos->cur[1];
	start_pos->cur[0] -=1;  
	start_pos->cur[1] -=1;

	cin>>final[0]>>final[1];
	final[0] -=1; 
	final[1] -=1;

	//开始正式的操作
	maze[start_pos->cur[0]][start_pos->cur[1]] = -1;  

	queue que;
	InitQueue(que);   //不要忘！！！

	Move(start_pos,que,maze,m,n);  //start_pos周围的pos入队
	if (que.rear == que.front) {
		cout << "-1" << endl;
		return 0;
	}
	ptr_pos temp = Out(que);   

	while ((temp->cur[0] != final[0]) || (temp->cur[1] != final[1])){
		Move(temp, que, maze, m, n);
		//队列空时，全部完毕
		if (que.rear == que.front) break;
		temp = Out(que);
	}

	if ((temp->cur[0] == final[0]) && (temp->cur[1] == final[1])) {   //走到了终点 ，递归打印
		output(temp,final);
		//cout << "\b"<<" ";
		//cout << "\b\b" << " ";
	}
	else cout << "-1" << endl;
		

    return 0;
}


