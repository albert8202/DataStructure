#include<iostream>
#include<vector>
using namespace std;
int huffmanForm(vector<int> &huffmanArr)
{
	long long int total = 0;               //�ܻ���
	while (huffmanArr.size() > 1)
	{
		int min1 = huffmanArr[0];//Ȩֵ��С������ֵ
		int pos1 = 0, pos2 = 0;  //��ǰ��С�����±�
		int tmp = 0;             //���浱ǰ������С����Ȩֵ֮��
		for (int i = 1; i < huffmanArr.size(); i++)
		{
			if (huffmanArr[i] < min1)
			{
				min1 = huffmanArr[i];
				pos1 = i;
			}
		}
		tmp += min1;
		//��huffmanArr��ɾ���ҳ�����СȨֵ��
		huffmanArr.erase(huffmanArr.begin() + pos1);

		int min2 = huffmanArr[0];//ɾ��һ����֮��ĵ�һ��Ԫ��
		for (int i = 1; i < huffmanArr.size(); i++)
		{
			if (huffmanArr[i] < min2)
			{
				min2 = huffmanArr[i];
				pos2 = i;
			}
		}
		tmp += min2;
		//��huffmanArr��ɾ���ҳ�����СȨֵ��
		huffmanArr.erase(huffmanArr.begin() + pos2);
		total += tmp;
		//������СȨֵ֮�����¼���
		huffmanArr.push_back(tmp);
	}
	return total;
}

int main()
{
	int N;
	//cost����������С����
	int cost;
	//arr�����洢��ǰHuffman��������Ȩֵ
	vector<int> arr;
	while (1)
	{
		cin >> N;
		if (N > 0) break;
		else cout << "���벻�Ϸ�����������������" << endl;
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
	