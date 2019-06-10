#include<iostream>
using namespace std;
//链表结点
struct linkedNode
{
	int value;            //存储数据
	linkedNode* next;     //指向下一结点
};
//链表类
class linkedList
{
public:
	linkedList();         //构造函数
	linkedNode* first;    //指向首元结点
	linkedNode* last;     //指向尾节点
	int size;             //链表大小
	void print()const;    //打印链表
	void insertData(int pos,int &numToInsert);  //插入函数：pos为插入位置，numToInsert为插入的数据
	void deleteData(int &numToDelete);          //删除函数：numToDelete为删除的数据     
	bool find(int num)const;                    //查找函数：所查找的数据为num
};
linkedList::linkedList()
{
	first = nullptr;
	size=0;
	cout << "请输入集合中的的元素（非降序的正整数），每个元素之间用空格隔开，以-1结尾： ";
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
//在链表pos位后插入numToInsert的数据
void linkedList::insertData(int pos, int &numToInsert)
{
	auto newNode = new linkedNode;
	newNode->value = numToInsert;
	auto p = first;
	for (int i = 0; i < pos - 1; i++)
	{
	    //先找到所要插入的位置
		if (p->next != nullptr)
		{
			p = p->next;
		}
	}
	if (p->next == nullptr)
	{
		//已是链表尾部，则开辟新结点，并接上原链表
		p->next = newNode;
		this->last = newNode;
	}
	else
	{
		newNode->next = p->next;
		p->next = newNode;
	}
}
//删除值为numToDelete的结点
void linkedList::deleteData(int &numToDelete)
{
	//首元结点为所要删除的
	if (this->first->value == numToDelete)
	{
		auto temp = first;
		first = first->next;
		delete temp;
		this->size--;
		return;
	}
	//非首元结点
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
	//遍历完没找到所要删除的结点
	if (p->next == nullptr)
	{
		cout << "找不到元素：" << numToDelete << endl;
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
	{//如果A,B链都为空
		cout << "A和B的交集为： NULL";
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
			{//在B链中没招到该元素，则在A链中删除该元素所在结点
				A.deleteData(numToSearch);
			}
			p = temp;
		}
		//输出结果
		cout << "A和B的交集为：";
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




