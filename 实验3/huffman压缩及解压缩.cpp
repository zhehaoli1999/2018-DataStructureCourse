// huffman压缩及解压缩.cpp: 定义控制台应用程序的入口点。
//
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<string>
#include<iostream>

using namespace std;

typedef struct Alpha {
	unsigned char alpha;
	unsigned long long int freq;
}Alpha;

//Part 2  生成Huffman树
typedef struct {
	unsigned long long int weight;
	int parent, lchild, rchild;
}HTNode, *HuffmanTree;

typedef char** HuffmanCode;

void Select(HuffmanTree &HT, int num, int& s1, int& s2) {   //选取HT[1--num]中最小的两个 
															//num:是待选择的结点的数目 
	int i;
	unsigned long long int min_weight = -1;
	unsigned long long int min_record = -1;
	for (i = 1; i <= num; i++) {   //HuffmanTree[0]未用
		if (HT[i].parent == 0 && min_weight<0)min_weight = min_record = HT[i].weight;//记录遇到的第一个权值
		if (HT[i].parent == 0 && (HT[i].weight <= min_weight)) {
			min_weight = HT[i].weight;
			s1 = i;
		}
	}
	HT[s1].parent = -1;   //置为负数与HT[i].parent == 0冲突

	min_weight = min_record;

	for (i = 1; i <= num; i++) {   //HuffmanTree[0]未用
		if (HT[i].parent == 0 && HT[i].weight <= min_weight) {
			min_weight = HT[i].weight;
			s2 = i;
		}
	}
};

void HuffmanCoding(HuffmanTree &HT, HuffmanCode &HC, Alpha* & Alphabet, int num_alpha) {
	if (num_alpha <= 1) return;
	int m = 2 * num_alpha - 1;    //Huffman树结点的数量
	HT = (HuffmanTree)malloc(sizeof(HTNode)*(m + 1));  //HT[0]位没有使用

	int i;
	for (i = 0; i <num_alpha; i++) {   //可以改成下标一致的！
		HT[i + 1] = { Alphabet[i].freq,0,0,0 };  //Alphabet的长度即为num_alpha
	}

	//HT中0--num_alpha位 是 Alphabet对应位 
	for (; i <m; i++)HT[i + 1] = { 0,0,0,0 };  //后num_alpha+1--m位初始化
	for (i = num_alpha + 1; i <= m; i++) {
		int s1, s2;
		Select(HT, i - 1, s1, s2);
		HT[s1].parent = HT[s2].parent = i;
		HT[i].lchild = s1; HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	//生成Huffman编码
	HC = (HuffmanCode)malloc((num_alpha + 1) * sizeof(char*));//HC[0]没用！ 
	char * code = (char*)malloc(num_alpha * sizeof(char));  //最长编码长度是num_alpha-1
	code[num_alpha - 1] = '\0';
	for (i = 1; i <= num_alpha; i++) {
		int start = num_alpha - 1;
		int c, f;
		//从叶子向根找
		for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent) {
			if (HT[f].lchild == c)code[--start] = '0';
			else code[--start] = '1';
		}
		HC[i] = (char*)malloc(num_alpha - start * sizeof(char));
		strcpy(HC[i], &code[start]);
		/*
		// 打印huffman编码，调试用
		for(int j=0;j<strlen(HC[i]);j++)cout<<HC[i][j];
		cout<<endl;
		*/
	}
}

typedef struct {
	char format[5];
	unsigned char num_alpha;
}Head;

inline void SetBit(unsigned char& value, int index) {
	value |= (1 << index);
}
inline void ClearBit(unsigned char& value, int index) {
	value &= ((1 << index) ^ 0xFF);
}
inline int GetBit(unsigned char value, int index) {
	return (value >> index) & 1;
}
void Compress(int num_alpha, HuffmanCode &HC, Alpha alphabet[], string src_file_name, string aim_file_name, unsigned long long int freq[], string format) {
	cout << "正在压缩......" << endl;
	//压缩文件的头部内容 
	Head head;
	head.num_alpha = num_alpha;
	for (int i = 0; i<format.length(); i++) head.format[i] = format[i];
	head.format[4] = '\0';

	//写入与读取 
	aim_file_name += ".huff";
	FILE* fpin = fopen(src_file_name.data(), "rb");
	FILE* fpout = fopen(aim_file_name.data(), "wb");
	fwrite(&head, sizeof(Head), 1, fpout);
	fwrite(freq, sizeof(unsigned long long int) * 256, 1, fpout);

	int j;
	unsigned char value = 0;
	int index = 7;
	unsigned char temp_alpha;
	fread(&temp_alpha, sizeof(unsigned char), 1, fpin);
	while (!feof(fpin)) {
		//找到字符的huff编码！ 
		int t;
		for (int i = 0; i<num_alpha; i++) {
			if (alphabet[i].alpha == temp_alpha) {
				t = i;
				break;
			}
		}
		
		//alphabet[i].alpha 对应的编码是 HC[t+1],这是缺陷之处
		for (j = 0; j< strlen(HC[t + 1]); j++) {
			if (HC[t + 1][j] == '0') ClearBit(value, index);
			else SetBit(value, index);


			index--;

			if (index < 0) {
				index = 7;
				fwrite(&value, sizeof(unsigned char), 1, fpout);
				value = 0;
			}
		}
		fread(&temp_alpha, sizeof(unsigned char), 1, fpin);
	}
	fwrite(&value, sizeof(unsigned char), 1, fpout);  //剩余未满8bit也写进去 

	cout << "压缩成功！" << endl;

}

void DeCompress(string file_name) {
	cout << "正在解压缩......" << endl;
	string src_file_name = file_name + ".huff";

	FILE* fpin = fopen(src_file_name.data(), "rb");
	//分别读取头部和频率信息 
	Head head;
	unsigned long long int freq[256];
	fread(&head, sizeof(Head), 1, fpin);
	fread(freq, sizeof(unsigned long long int) * 256, 1, fpin);

	//创建 origin文件 
	string aim_file_name = file_name + "_origin" + head.format;
	FILE* fpout = fopen(aim_file_name.data(), "wb");

	//统计共计出现了多少种不同的字符：num_alpha
	int num_alpha = 0;
	for (int i = 0; i < 256; i++) {
		if (freq[i])
			num_alpha++;
	}

	//构造结构体Alpha数组，用于接下来的生成Huffman树
	Alpha* alphabet = (Alpha*)malloc(sizeof(Alpha)*num_alpha);
	int j;
	for (int i = j = 0; i < 256; i++) {
		if (freq[i]) {
			alphabet[j].alpha = i;
			alphabet[j].freq = freq[i];
			j++;
		}
	}

	HuffmanTree HT;
	HuffmanCode HC;
	HuffmanCoding(HT, HC, alphabet, num_alpha);
	/*
	//##### 打印huffman编码，调试用
	for (int i = 0; i<num_alpha; i++) {
		cout << alphabet[i].alpha;
		for (int j = 0; j<strlen(HC[i + 1]); j++)cout << " " << HC[i + 1][j];
		cout << endl;
	}
	*/

	int root;
	for (int i = 1; i <= 2 * num_alpha - 1; i++) {
		if (HT[i].parent == 0)root = i;  //找到根
	}
	int p = root;

	int index = 7;
	unsigned char temp_alpha;
	fread(&temp_alpha, sizeof(unsigned char), 1, fpin);
	int count=0;
	for (int i = 0; i < num_alpha; i++) {
		count += alphabet[i].freq;
	}
	while (!feof(fpin)) {
		while (index >= 0) {
			if (HT[p].rchild == 0 && HT[p].lchild == 0&&count>0) {
				fwrite(&alphabet[p - 1].alpha, sizeof(unsigned char), 1, fpout);
				count--;
				p = root;
			}
			if (GetBit(temp_alpha, index)) {
				if (HT[p].rchild)   //其rchild=1时向右走 
					p = HT[p].rchild;
			}
			else {
				if (HT[p].lchild)
					p = HT[p].lchild;
			}
			index--;
		}
		index = 7;
		fread(&temp_alpha, sizeof(unsigned char), 1, fpin);
	}
	cout << "解压缩成功！" << endl;
}
void start(){
	
}
int main()
{
	//用户界面
	string src_file_name;
	cout << "1.压缩  2.解压缩" << endl;
	int choice;
	cin >> choice;
	cout << "请输入文件名：";
	string file_name;
	cin >> file_name;
	if (choice == 1) {    //压缩
		cout << "待压缩文件格式为：1.txt  2.jpg  3.png  4.mp4  5.gif  6.xls  7.bmp  8.docx  9.exe---->";
		int format_num;
		cin >> format_num;
		string format;
		switch (format_num)
		{
		case 1: src_file_name = file_name + ".txt";
			format = ".txt";
			break;
		case 2: src_file_name = file_name + ".jpg";
			format = ".jpg";
			break;
		case 3: src_file_name = file_name + ".png";
			format = ".png";
			break;
		case 4: src_file_name = file_name + ".mp4";
			format = ".mp4";
			break;
		case 5:src_file_name = file_name + ".gif";
			format = ".gif";
			break;
		case 6: src_file_name = file_name + ".xls";
			format = ".xls";
			break;
		case 7: src_file_name = file_name + ".bmp";
			format = ".bmp";
			break;
		case 8: src_file_name = file_name + ".docx";
			format = ".docx";
			break;
		case 9: src_file_name = file_name + ".exe";
			format = ".exe";
			break;
		default:
			break;
		}

		FILE* fp1 = fopen(src_file_name.data(), "rb");
		unsigned long long int freq[256] = { 0 };

		//从文件中读取字符(1byte)并统计频率
		unsigned char temp;
		temp = fgetc(fp1);
		while (!feof(fp1)) {
			freq[temp]++;
			temp = fgetc(fp1);
		}
		fclose(fp1);

		//统计共计出现了多少种不同的字符：num_alpha
		int num_alpha = 0;
		for (int i = 0; i < 256; i++) {
			if (freq[i])
				num_alpha++;
		}
		//构造结构体Alpha数组，用于接下来的生成Huffman树
		//alphabet 的长度是num_alpha 
		Alpha* alphabet = (Alpha*)malloc(sizeof(Alpha)*num_alpha);
		int j;
		for (int i = j = 0; i < 256; i++) {
			if (freq[i]) {
				alphabet[j].alpha = i;
				alphabet[j].freq = freq[i];
				j++;
			}
		}
		//Part 2  生成Huffman树
		HuffmanTree HT;
		HuffmanCode HC;
		HuffmanCoding(HT, HC, alphabet, num_alpha);

		Compress(num_alpha, HC, alphabet, src_file_name, file_name, freq, format);
	}
	else {   //解压缩
		DeCompress(file_name);
	}

	return 0;
}



