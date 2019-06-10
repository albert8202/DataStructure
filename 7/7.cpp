#include<iostream>
#include<vector>
using namespace std;
int huffmanForm(vector<int> &huffmanArr)
{
	long long int total = 0;               //总花费
	while (huffmanArr.size() > 1)
	{
		int min1 = huffmanArr[0];//权值最小的两个值
		int pos1 = 0, pos2 = 0;  //当前最小结点的下标
		int tmp = 0;             //保存当前两个最小结点的权值之和
		for (int i = 1; i < huffmanArr.size(); i++)
		{
			if (huffmanArr[i] < min1)
			{
				min1 = huffmanArr[i];
				pos1 = i;
			}
		}
		tmp += min1;
		//从huffmanArr中删除找出的最小权值的
		huffmanArr.erase(huffmanArr.begin() + pos1);

		int min2 = huffmanArr[0];//删除一个数之后的第一个元素
		for (int i = 1; i < huffmanArr.size(); i++)
		{
			if (huffmanArr[i] < min2)
			{
				min2 = huffmanArr[i];
				pos2 = i;
			}
		}
		tmp += min2;
		//从huffmanArr中删除找出的最小权值的
		huffmanArr.erase(huffmanArr.begin() + pos2);
		total += tmp;
		//将两最小权值之和重新加入
		huffmanArr.push_back(tmp);
	}
	return total;
}

int main()
{
	int N;
	//cost用来计算最小花费
	int cost;
	//arr用来存储当前Huffman树各结点的权值
	vector<int> arr;
	while (1)
	{
		cin >> N;
		if (N > 0) break;
		else cout << "输入不合法，请输入正整数！" << endl;
	}
	
	for (int i = 0; i < N; i++)
	{
		cin >> cost;
		arr.push_back(cost);
	}
	int result = huffmanForm(arr);
	cout << result<<endl;
	system("pause");
	return 0;
}
	