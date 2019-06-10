#include <iostream>
#include <vector>
using namespace std;

//�ߵĽṹ��������㡢�յ㡢Ȩֵ
struct Edge
{
	int value;
	char begin;
	char end;
};

//��������Ĺ���
class ElecNetwork
{
private:
	Edge _network[1000];
	int _father[1000];        //���ò��鼯���Ұְ�
	int _count;               //����ĸ���
public:
	void createFather();
	void createNetwork();
	void menu();              //��ӡ���˵�
	void loop();              //��ѭ��
	void display();
	void generateMinTree();    //������С������
	char findFather(char x);  //�йز��鼯���������� ������ϲ�
	void Union(char a, char b);
	void quickSort(Edge network[], int left, int right);  //���ߵ�Ȩֵ��������

};

void ElecNetwork::display()
{
	cout << "��С�������Ķ����Լ�����:\n\n";
	for (int i = 0; i < _count; i++)
	{
		if (_network[i].begin != '?')
			cout << _network[i].begin << "-<" << _network[i].value << "> ->" << _network[i].end << "    ";
	}
}

//�������� ��������С�����ɱ�
void ElecNetwork::quickSort(Edge *a, int left, int right)
{
	int i, j, mid;
	Edge temp;

	if (left >= right)
		return;

	i = left;
	j = right;
	mid = (i + j) >> 1;
	do
	{
		while (a[mid].value > a[i].value) i++;
		while (a[mid].value < a[j].value) j--;
		//����ҵ��������Ļ�  ���н���
		if (i <= j)
		{
			temp = a[i];
			a[i] = a[j];
			a[j] = temp;

			i++;
			j--;
		}
	} while (i <= j);

	quickSort(a, left, j);
	quickSort(a, i, right);

}

//�ҵ��Լ��İְ�
char ElecNetwork::findFather(char x)
{
	if (_father[x] < 0)
		return x;
	else
		return _father[x] = findFather(_father[x]);
}


void ElecNetwork::generateMinTree()
{
	char begining;
	cout << "��ѡ����ʼ����:";
	
	cin >> begining;
		
	
	cout << "��С�������Ѿ����ɣ�" << endl;
	for (int i = 0; i < _count; i++)
	{
		//���û����ͨ�Ļ�
		if (findFather(_network[i].begin) != findFather(_network[i].end))
			Union(_network[i].begin, _network[i].end);
		else
		{
			_network[i].begin = '?';
		}
	}

}


//�ҵ��Լ�������(��ͨ or ����ͨ)
void ElecNetwork::Union(char a, char b)
{
	char father1, father2;
	father1 = findFather(a);
	father2 = findFather(b);
	_father[father2] = father1;

}

void ElecNetwork::menu()
{

	cout << "**\t\t\t  �������ģ��ϵͳ\t\t\t\t**\n";
	cout << "==========================================================================\n";
	cout << "**\t\t\tA --- ������������\t\t\t\t**\n";
	cout << "**\t\t\tB --- ��ӵ����ı�\t\t\t\t**\n";
	cout << "**\t\t\tC --- ������С������\t\t\t\t**\n";
	cout << "**\t\t\tD --- ��ʾ��С������\t\t\t\t**\n";
	cout << "**\t\t\tE --- �˳�����\t\t\t\t\t**\n";
	cout << "==========================================================================\n";

}

void ElecNetwork::createFather()
{
	cout << "�����붥��ĸ���:";
	while (1)
	{
		cin >> _count;
		if (_count > 1) break;
		else cout << "���������1����������"<<endl<<"�����붥��ĸ�����";
	}
	cout << "�������������������:" << endl;
	char temVertex;
	for (int i = 0; i < _count; i++)
	{
		cin >> temVertex;
		_father[temVertex] = -1;
	}
}
void ElecNetwork::createNetwork()
{
	Edge tempEdge;
	int i = 0;
	while (1)
	{
		cout << "���������������Լ���:";
		cin >> tempEdge.begin;
		cin >> tempEdge.end;
		cin >> tempEdge.value;

		if (tempEdge.begin == '?')
			break;
		_network[i++] = tempEdge;
	}

	quickSort(_network, 0, i - 1); //��Ȩֵ��������

}
//ѭ������
void ElecNetwork::loop()
{

	char command = 'A';
	while (command != 'E')
	{
		cout << "\n��ѡ�����:";
		cin >> command;
		switch (command)
		{
		case 'A':
			createFather();
			break;
		case 'B':
			createNetwork();
			break;
		case 'C':
			generateMinTree();
			break;
		case 'D':
			display();
			break;
		case 'E':
			cout << "��л��ʹ�ñ�ϵͳ��ף�㸣�綫�����ٱ���ɽ!" << endl;
			break;
		default:
			cout << "���������������Ч�Ĳ�����!" << endl;
			break;
		}
	}

}

int main()
{
	ElecNetwork network;
	network.menu();
	network.loop();
	return 0;
}