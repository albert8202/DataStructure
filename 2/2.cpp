#include<iostream>
using namespace std;
//������
struct linkedNode
{
	int value;            //�洢����
	linkedNode* next;     //ָ����һ���
};
//������
class linkedList
{
public:
	linkedList();         //���캯��
	linkedNode* first;    //ָ����Ԫ���
	linkedNode* last;     //ָ��β�ڵ�
	int size;             //�����С
	void print()const;    //��ӡ����
	void insertData(int pos,int &numToInsert);  //���뺯����posΪ����λ�ã�numToInsertΪ���������
	void deleteData(int &numToDelete);          //ɾ��������numToDeleteΪɾ��������     
	bool find(int num)const;                    //���Һ����������ҵ�����Ϊnum
};
linkedList::linkedList()
{
	first = nullptr;
	size=0;
	cout << "�����뼯���еĵ�Ԫ�أ��ǽ��������������ÿ��Ԫ��֮���ÿո��������-1��β�� ";
    first = new linkedNode;
	cin >> first->value;
	this->last = first;
	if (first->value != -1)
	{
		size++;
		int num = 0;

		while (num >= 0)
		{
			cin >> num;
			last->next = new linkedNode;
			last = last->next;
			last->value = num;
			size++;
		}
		last->next = nullptr;
	}
}

bool linkedList::find(int numToSearch)const
{
	auto p = first;
	while (p != nullptr)
	{
		if (p->value == numToSearch)break;
		p = p->next;
	}
	if (p == nullptr)return false;
	else return true;
}
//������posλ�����numToInsert������
void linkedList::insertData(int pos, int &numToInsert)
{
	auto newNode = new linkedNode;
	newNode->value = numToInsert;
	auto p = first;
	for (int i = 0; i < pos - 1; i++)
	{
	    //���ҵ���Ҫ�����λ��
		if (p->next != nullptr)
		{
			p = p->next;
		}
	}
	if (p->next == nullptr)
	{
		//��������β�����򿪱��½�㣬������ԭ����
		p->next = newNode;
		this->last = newNode;
	}
	else
	{
		newNode->next = p->next;
		p->next = newNode;
	}
}
//ɾ��ֵΪnumToDelete�Ľ��
void linkedList::deleteData(int &numToDelete)
{
	//��Ԫ���Ϊ��Ҫɾ����
	if (this->first->value == numToDelete)
	{
		auto temp = first;
		first = first->next;
		delete temp;
		this->size--;
		return;
	}
	//����Ԫ���
	auto p = first;
	while (p->next != nullptr)
	{
		if (p->next->value == numToDelete)
		{
			auto q = p->next;
			p->next = p->next->next;
			delete q;
			this->size--;
			return;
		}
		p = p->next;
	}
	//������û�ҵ���Ҫɾ���Ľ��
	if (p->next == nullptr)
	{
		cout << "�Ҳ���Ԫ�أ�" << numToDelete << endl;
	}
}
void linkedList::print() const
{
	auto p = first;
	while (p != last)
	{
		cout <<" "<< p->value;
		p = p->next;
	}
}

int main()
{
	linkedList A;
	linkedList B;
	if (A.size == 0 || B.size == 0)
	{//���A,B����Ϊ��
		cout << "A��B�Ľ���Ϊ�� NULL";
	}
	else
	{
		auto p = A.first;
		int numToSearch = 0;
		while (p != nullptr)
		{
			auto temp = p->next;
			numToSearch = p->value;
		
			if (B.find(numToSearch) == false)
			{//��B����û�е���Ԫ�أ�����A����ɾ����Ԫ�����ڽ��
				A.deleteData(numToSearch);
			}
			p = temp;
		}
		//������
		cout << "A��B�Ľ���Ϊ��";
		if (A.size > 1)
		{
			A.print();
		}
		else
		{
			cout << " NULL";
		}
	}
	return 0;
}




