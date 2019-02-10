// 括号匹配.cpp: 定义控制台应用程序的入口点。
//
#include<cstdlib>
#include<iostream>
#define STACK_INIT_SIZE 100 
#define	STACK_INCREMENT_SIZE 10

using namespace std;

class Stack {
	char* top, *base;
	int stack_size;
	
public:
	int length;

	Stack() {
		char*  temp = (char*)malloc(STACK_INIT_SIZE * sizeof(char));
		if (!temp) return;

		base = temp;
		top = base;
		length = 0;
		stack_size = STACK_INIT_SIZE;
	}

	~Stack() {
	}

	void ClearStack() {    //栈清空;
		top = base;
		length = 0;
	}
	void Push(char p) {
		if (top - base >= stack_size) {  //栈满
			base = (char*)realloc(base, (stack_size + STACK_INCREMENT_SIZE) * sizeof(char));
			top = base + stack_size;   //先修改top指针
			stack_size += STACK_INCREMENT_SIZE;
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
	Stack stack;
	int num;  //表达式的个数
	cin >> num;
	char temp;
	bool is_right = 1;   
	while (num) {
		cin >> temp;
		while (temp != '@') {
			if (temp == '(' || temp == '[' || temp == '{') stack.Push(temp);
			if (temp == ')') {
				char bracket = stack.Pop();
				if (bracket == '(') {
					cin >> temp;
					continue;
				}
				else {
					cout << "NO" << endl;
					is_right= 0;
					while (temp != '@') cin >> temp;   //吃完这一行的表达式，才能判断下一个表达式
					break;
				}
			}
			if (temp == ']') {
				char bracket = stack.Pop();
				if (bracket == '[') {
					cin >> temp;
					continue;
				}
				else {
					cout << "NO" << endl;
					is_right = 0;
					while (temp != '@') cin >> temp;   //吃完这一行的表达式，才能判断下一个表达式
					break;
				}
			}
			if (temp == '}') {
				char bracket = stack.Pop();
				if (bracket == '{') {
					cin >> temp;
					continue;
				}
				else {
					cout << "NO" << endl;
					is_right = 0;
					while (temp != '@') cin >> temp; //吃完这一行的表达式，才能判断下一个表达式
					break;
				}
			}
			cin >> temp;
		}
		if (is_right&&stack.length == 0)cout << "YES" << endl;
		stack.ClearStack();
		is_right = 1;
		num--;
	}
    return 0;
}


