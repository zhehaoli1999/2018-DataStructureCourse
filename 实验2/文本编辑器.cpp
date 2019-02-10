// 文本编辑器.cpp: 定义控制台应用程序的入口点。
//
#include<cstdlib>
#include<iostream>
#define STACK_INIT_SIZE 100 
#define	STACK_INCREMENT_SIZE 10

using namespace std;


class Stack {
	
	int stack_size;

public:
	char* top, * base;
	int length;
	int k;//光标，光标的范围是0（第一个元素前面）至length（最后一个元素）

	Stack() {
		char*  temp = (char*)malloc(STACK_INIT_SIZE * sizeof(char));
		if (!temp) return;

		base = temp;
		top = base;
		k = 0;	//光标先置为0
		length = 0;
		stack_size = STACK_INIT_SIZE;
	}

	~Stack() {
		/*
		while (top != base) {
			char* temp = --top;
			free(temp);
		}
		free(base);
		*/
	}

	void PrintStack() {   //打印栈中的所有元素
		for (char* p = base; p != top; p++) {       //栈底为字符串头！
			cout << *p;
		}
		cout << endl;
	}

	void Push(char p) {
		if (top - base >= stack_size) {  //栈满
			base = (char* )realloc(base, (stack_size + STACK_INCREMENT_SIZE) * sizeof(char));
			top = base + stack_size;   //先修改top指针
			stack_size+= STACK_INCREMENT_SIZE;
		}
		length++;
		*top = p;
		top++;
	}
	char Pop() {
		if (base == top)return NULL;
		length--;
		return (*(--top));    //top指在下一位，故 -- 在前
	}

};

int main()
{
	//读取输入的指令
	int num;
	cin >> num;  //读取指令数目
	char temp;
	Stack stack;
	//freopen("in.txt", "r", stdin);
	freopen("myout.txt", "w", stdout);

	while (num) {
		cin >> temp;
		//cout << "temp=" << temp << endl;
		switch (temp)
		{
		case 'M':   //Move k
			cin >> temp >> temp >> temp;	//用这个吃掉指令中剩余字母 M ove
			int k;
			cin >> k;
			stack.k = k;
			break;

		case 'G':   //Get
			cin >> temp >> temp;
			//stack.PrintStack();
		for (char* p = stack.base; p != stack.top; p++) {     //栈底为字符串头！
			cout << *p;
		}
		cout << endl;
			break;

		case 'I':   //Insert
		{

			cin >> temp >> temp >> temp >> temp >> temp;
			int num;      //插入的字符串的长度
			cin >> num;

			int need_move = 0;   //需要移动元素则为1，否则为0
			char* char_array = NULL;
			int len = stack.length - stack.k;

			if (len) {   //stack.length == k时不需要移动元素
				char_array = (char*)malloc(sizeof(char)* len);
				//光标之后的元素都出栈并存放在这个数组中
				for (int i = 0; i <len; i++) {
					char_array[i] = stack.Pop();    //靠近栈尾的元素，装到数组中的前面
				}
				need_move = 1;
			}

			getchar();   //吃掉回车
			for (int i = 0; i <num; i++) {
				char c;
				c = getchar();
				//if(32<=c&&c<=126)
				stack.Push(c);
			}
			//stack.length += num;  Push时已经加了
			if (need_move) {
				for (int i = len - 1; i >= 0; i--) {
					stack.Push(char_array[i]);
				}
				delete[]char_array;
			}
			break;
		}

		case 'D':
		{
			cin >> temp >> temp >> temp >> temp >> temp;
			int num;      //删除的字符串的长度
			cin >> num;

			char* char_array = NULL;

			//调试cout << stack.k << " " << stack.length - stack.k;
			int len = stack.length - stack.k;
			char_array = (char*)malloc(sizeof(char)* len);
			//光标之后的元素都出栈并存放在这个数组中
			
			for (int i = 0; i < len; i++) {
				char_array[i] = stack.Pop();    //靠近栈尾的元素，装到数组中的前面
				//调试 cout << char_array[i] << " "<<i<<endl;
			}

			for (int i = len -num - 1; i >= 0; i--) {
				stack.Push(char_array[i]);
			}

			delete[]char_array;
			break;
		}

		case 'R':
		{
			cin >> temp >> temp >> temp >> temp >> temp;
			int num;      //旋转的字符串的长度
			cin >> num;

			int need_move = 0;   //需要移动元素则为1，否则为0

			char* char_array = NULL;

			int len = (stack.length - stack.k);
			char_array = (char*)malloc(sizeof(char)*len);
			//光标之后的元素都出栈并存放在这个数组中

			for (int i = 0; i <len; i++) {
				char_array[i] = stack.Pop();    //靠近栈尾的元素，装到数组中的前面
			}

			for (int i =len -num ; i < len; i++) {
				stack.Push(char_array[i]);
			}
			for (int i = len-num - 1; i >= 0; i--) {
				stack.Push(char_array[i]);
			}
			delete[]char_array;
			break;
		}

		case'P': {
			cin >> temp >> temp >> temp;
			stack.k -=1;
			break;
		}
		case'N': {
			cin >> temp >> temp >> temp;
			stack.k += 1;
			break;
		}
		default: {
			cout << "输错了指令！" << endl;
			break;
		}
		}
		num--;
	}
    return 0;
}


