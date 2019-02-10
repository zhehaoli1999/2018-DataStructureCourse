#include<iostream>
using namespace std;

int H(int x, int p) {
	return (x % p);
}

int SuccessSearch(int x, int p, int m,int *HashTable, int(*H)(int, int)) {
	int success_count = 0;
	int temp_pos = H(x, p);
	int temp_new_pos = (temp_pos + 1) % m;
	if (HashTable[temp_pos] < 0)return 1;  // 直接没找到 
	if (HashTable[temp_pos] != x) {
		success_count += 1;
		while (HashTable[temp_new_pos] != x) {
			temp_new_pos = (temp_new_pos + 1) % m;
			++success_count;
			if (HashTable[temp_new_pos]<0) {
				break;
			}
		}
	}
	success_count += 1;
	return success_count;
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
	int m, p;
	cin >> p;
	m = p;
	//构造空哈希表并初始化
	int* HashTable = new int[m];
	for (int i = 0; i < m; i++)HashTable[i] = -1;

	for (int i = 0; i < num; i++) {
		int pos = H(key[i],p);
		if (HashTable[pos] < 0)HashTable[pos] = key[i];
		else {   //冲突
			int new_pos = (pos+1)%m;
			while (HashTable[new_pos] >= 0) {
				new_pos = (new_pos+1)% m;
			}
			HashTable[new_pos] = key[i];
		}
	}
	//打印哈希表
	cout << "地址 关键字" << endl;
	for (int i = 0; i <m; i++) {
		cout << " " << i;
		if(i<10)cout<< "   ";
		else cout << "  ";

		if(HashTable[i]<0)cout<<'-';
		else cout << HashTable[i];
		cout << endl;
	}
	cout << endl;
	cout << "关键字  成功查找次数" << endl;
	int success_count,fail_count;
	float success_sum=0.0, fail_sum=0.0;
	//统计成功查找次数
	for (int i = 0; i < num; i++) {
		success_count = SuccessSearch(key[i], p, m, HashTable, H);

		cout << " ";
		if (key[i] < 100)cout << key[i] << "     ";
		else cout << key[i] << "    ";
		cout<<success_count << endl;
		success_sum += success_count;
	}
	cout << "成功平均:" << (success_sum / num) << endl;
	cout << endl;
	cout << "地址" << " 失败查找次数" << endl;
	for (int i = 0; i < m; i++) {
		fail_count = 1;
		//统计失败次数和失败平均
		int j = i;
		while (HashTable[j] >= 0) {
			j+=1;
			j=j%m;
			++fail_count;
		}
		cout <<" "<<i;
		if (i<10)cout << "   ";
		else cout << "  ";
		cout<<fail_count<<endl;
		fail_sum += fail_count;
	}
	cout << endl;
	
	cout << "失败平均:" << (fail_sum / m) << endl;

	int key_word;
	cout << "输入要查找的关键字:";
	cin >> key_word;
	cout << "查找次数为:" << SuccessSearch(key_word,p,m,HashTable,H)<<endl;


    return 0;
}


