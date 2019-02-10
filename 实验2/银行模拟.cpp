#include<cstdlib>
#include <iostream>
using namespace std;

typedef struct {
	float money;
	int arrive_time; //到达的时间
	int wait_time; //等候时长
	bool not_dealed;  //=0表示已经办完业务，=1表示未办
}client,*ptr_client;

class Queue {
	typedef struct queue_node {
		ptr_client person;  
		struct queue_node* next;
	}qnode, *ptr_qnode;

	ptr_qnode rear;
	ptr_qnode front;
public:
	Queue() {    //队列初始化
		ptr_qnode temp = (ptr_qnode)malloc(sizeof(qnode));  //头结点
		if (!temp) return;
		temp->person = NULL;
		temp->next = NULL;

		front = rear = temp;
	}

	~Queue() {

	}
	bool EmptyQueue() {
		if (rear == front) return 1;
		else return 0;
	}

	int EnQueue(ptr_client p) {  //入队
		ptr_qnode temp = (ptr_qnode)malloc(sizeof(qnode));
		temp->person = p;
		temp->next = NULL;

		rear->next = temp;
		rear = rear->next;
		return 0;
	}
	ptr_client GetFront() {   //获取队头元素的信息
		ptr_client temp = front->next->person;
		return temp;
	}

	ptr_client DeQueue() {   //出队,返回的是ptr_client 
		ptr_qnode temp = front->next;//队头
		//若为空队列返回NULL；
		if (!temp) return NULL;
		//若队列中只有一个元素，要修改rear
		if (rear == temp)rear = front;

		front->next = temp->next;

		ptr_client p = temp->person;

		free(temp);
		return p;
	}

	int LengthQueue() {
		int count=0;
		for (ptr_qnode p = front->next; p != NULL; p = p->next) count++;
		return count;
	}

};

void CheckQue2(Queue& que2, float& total_money, int& time, int deal_time) {
	//int money_record=total_money; //记录银行刚才第一个队列中最后一个客户(第二种业务)被接待之前的数额

	if (que2.EmptyQueue()) return; //队2空，直接结束

	int len = que2.LengthQueue();
	int count = 0;
	ptr_client p = que2.DeQueue();

	while (count <= len && p != NULL) {
		if (total_money + p->money >= 0&&p->not_dealed) {   //如果银行钱够
			p->wait_time = time - p->arrive_time;
			
			total_money += p->money;
			p->not_dealed = 0;
			
			time += deal_time;
			//用户离开
		}
		else que2.EnQueue(p);   //银行钱不够，该客户未满足，再次放到que2队尾

		count++;//防止死循环

		p = que2.DeQueue();
	}
}

void CheckQue1(Queue& que1,Queue& que2,float& total_money,int& time,int deal_time){  //处理业务1的函数
	ptr_client p = que1.DeQueue();
	if (p->money < 0) {   //第一类业务
		if (total_money + p->money >= 0&&p->not_dealed) {   //如果银行钱够
			p->wait_time = time - p->arrive_time;
			
			total_money += p->money; //第一类业务，p->money为负数
			p->not_dealed = 0;
			
			time += deal_time;
			//该用户离开
		}
		else {
			que2.EnQueue(p);   //银行钱不够，该客户未满足，放到que2队尾
		}
		
	}
	else {  //第二类业务
		if (p->not_dealed) {
			p->wait_time = time - p->arrive_time;
			
			total_money += p->money; //第一类业务，p->money为负数
			p->not_dealed = 0;
			
			time += deal_time;
			
			CheckQue2(que2, total_money, time, deal_time);  //检查队2
		}
	}
}

int main()
{
	int num, close_time, deal_time;
	float total_money;
	cin >> num >> total_money >> close_time >> deal_time;
	//来银行的总人数、银行开始营业时拥有的款额（全局变量）、今天预计的营业时长、客户交易时长

	//录入客户信息
	ptr_client client_array = (ptr_client)malloc(num * sizeof(client));
	for (int i = 0; i < num; i++) {   
		cin >> client_array[i].money >> client_array[i].arrive_time;
		client_array[i].not_dealed=1;
	}

	int time=0;
	Queue que1,que2;  //队1，队2

	while(time <= close_time){
		//这里，time加多是大问题，要当心
		for (int i = 0; i < num; i++) { //每一时刻遍历客户数组，接待合适时间的客户
			if(time >=client_array[i].arrive_time && client_array[i].not_dealed){  
			//此处为>= ! 因为在上一个客户办业务的时间之中，下一个客户可能来
			
				que1.EnQueue(client_array + i);
				 
				CheckQue1(que1, que2, total_money, time, deal_time);
				//调试用cout << "ok";
			}
			
			if (time > close_time) break;
		}
		//防止死循环
		time++;
	}

	//输出
	int wait_time_sum = 0;
	for (int i = 0; i < num; i++) {
		if (client_array[i].not_dealed) {
			client_array[i].wait_time = close_time - client_array[i].arrive_time;
		}	
		wait_time_sum += client_array[i].wait_time;
		cout << client_array[i].wait_time<<endl;
	}
	cout << (wait_time_sum / num);

    return 0;
}
