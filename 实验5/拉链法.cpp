#include<iostream>
using namespace std;

typedef struct ChainNode {
	int elem;
	struct ChainNode* next;
}ChainNode,*Chain;

int H(int x,int p) {
	return (x % p);
}

void BuildChainHash(int x,int p, Chain*ChainHash ,int(*H)(int, int)) {
	int num = H(x, p);
	Chain temp = new ChainNode;
	temp->elem = x;
	temp->next = NULL;
	if (!ChainHash[num])ChainHash[num] = temp;
	else {
		Chain p,q;
		q = p = ChainHash[num];
		while ((p->elem) < x) {  //让同义词在同一线性链表中按关键字有序
			q = p;
			p = p->next;
			if (p == NULL)break;
		}
		if (p == ChainHash[num]) {
			temp->next = p;
			ChainHash[num]= temp;   //p=temp 不对！！！
		}
		else {
			temp->next = q->next;
			q->next = temp;
		}
	}
}

int SuccessSearchChainHash(int x, Chain* ChainHash, int p, int(*H)(int, int)) {
	int num = H(x, p);
	int count=1;  //记录查找了多少次
	for (Chain q = ChainHash[num]; q!=NULL&&q->elem != x; q = q->next)count++;
	return count;
}

int main()
{
	//读入关键字次数
	int num;
	cin >> num;
	//读入关键字
	int *key = new int[num];
	for (int i = 0; i < num; i++) cin >> key[i];
	//读入p
	int m,p;
	cin >> p;
	m = p ;
	Chain* ChainHash = new Chain[m];  //长度为m，范围为0--(m-1)的头指针数组  
	for (int i = 0; i < m; i++) ChainHash[i] = NULL;
	//拉链法建立哈希表
	for (int i = 0; i < num; i++) BuildChainHash(key[i],p,ChainHash,H);
	//打印哈希表
	cout << "地址 关键字"<<endl;
	for (int i = 0; i < m; i++) {
		cout << " "<<i << "   ";
		Chain q = ChainHash[i];
		if (!q) {
			cout << "-";
		}
		else {
			for (; q != NULL; q = q->next) cout << q->elem << " ";
		}
		cout << endl;
	}
	cout << endl;
	//打印成功查找次数
	float success_sum = 0;
	float fail_sum = 0;
	int success_count = 0;
	int fail_count = 1;
	for (int i = 0; i < m; i++) {
		cout << i << ":";
		Chain q = ChainHash[i];
		if (!q) {
			success_count= 0;
			cout <<"成功："<< success_count << " ";
		}
		else {
			cout << "成功：";
			for (; q != NULL; q = q->next) { 
				success_count = SuccessSearchChainHash(q->elem, ChainHash, p, H);
				success_sum += success_count;
				cout << success_count << " ";
			}
		}
		fail_count = success_count + 1;
		fail_sum += fail_count;
		cout << "失败：" << fail_count;
		cout << endl;
	}
	cout << endl;
	cout << "成功平均:"<<(success_sum/num)<<endl;
	cout << "失败平均:" << (fail_sum /m) << endl;
	
	int key_word;
    cout<<"输入要查找的关键字：";
	cin>>key_word;
	cout<<"比较次数为："<<SuccessSearchChainHash(key_word, ChainHash,p, H); 
    return 0;
}

