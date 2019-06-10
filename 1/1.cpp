#include<iostream>
#include<string>
#include<vector>
using namespace std;


//定义学生结点
struct student
{
	int number;    //考号
	string name;   //姓名
	string gender; //性别
	int age;       //年龄
	string type;  //报考类别
	student* next; //结点指针域
};

//建立考生信息链表
class StudentInformation
{
private:
	student* first;  //表头
	student* last;   //表尾
public:
	StudentInformation();  //构造函数
	void print() const;    //输出提示指令
	void insertData();     //增添数据
	void deleteData();     //删除数据
	void setData();        //修改数据
	void getData();        //获得数据
};

//初始化考试报名系统
StudentInformation::StudentInformation()
{
	first = nullptr;
	cout << "首先建立考生系统" << endl << "请输入考生人数：";
    int studentNum;   //考生人数
	cin >> studentNum;
	while (studentNum < 0) //若考生人数小于1则报错，并提示重新输入
	{
		cout << "输入错误，请输入大于等于1的数! " << endl;
		cin >> studentNum;
	}
	cout << "请依次输入考生考号，姓名，性别，年龄及报考类别！" << endl;
	first = new student;
	cin >> first->number >> first->name >> first->gender >> first->age >> first->type;
	this->last = first;
	for (int i = 1; i < studentNum; i++)
	{
		last->next = new student;
		last = last->next;
		last->next = nullptr;
		cin >> last->number >> last->name >> last->gender >> last->age >> last->type;
	}
	last->next = nullptr;
	print();
}

//打印学生信息
void StudentInformation::print() const
{
	cout << "考号" << "\t";
	cout << "姓名" << "\t";
	cout << "性别" << "\t";
	cout << "年龄" << "\t";
	cout << "报考类别" << endl;
	auto p = this->first;
	while (p != nullptr)
	{
		cout << p->number << "\t";
		cout << p->name << "\t";
		cout << p->gender << "\t";
		cout << p->age << "\t";
		cout << p->type << endl;
		p = p->next;
	}
}

//插入数据
void StudentInformation::insertData()
{
	cout << "请输入您想要插入的考生位置：" << endl;
	int position;
	cin >> position;
	while (position < 1)    //如果输入的数小于1则报错，并提示用户重新输入
	{
		cout << "输入错误，请输入大于等于1的数！" << endl;
		cin >> position;
	}
	cout << "请依次输入要插入的考生的考号，姓名，性别，年龄及报考类别" << endl;
	auto newNode = new student;
	newNode->next = nullptr;
	cin >> newNode->number >> newNode->name>>newNode->gender >> newNode->age >> newNode->type;
	auto p = first;
	for (int i = 0; i < position - 1; i++)
	{
		if (p->next != nullptr)
		{
			p = p->next;
		}
	}
	if (p->next == nullptr)
	{
		p->next = newNode;
		this->last = newNode;
	}
	else
	{
		newNode->next = p->next;
		p->next = newNode;
	}
}
//删除数据
void StudentInformation::deleteData()
{
	cout << "请输入要删除的考生的考号：" << endl;
	int num;
	cin >> num;
	//头节点即为所要删除结点
	if (this->first->number == num)
	{
		auto temp = first;
		first = first->next;
		delete temp;
		return;
	}
	//删除结点非头节点的情况
	auto p = first;
	while (p->next!=nullptr)
	{
		if (p->next->number == num)
		{
			auto s = p->next;
			p->next = s->next;
			delete s;
			return;
		}
		p = p->next;
	}
	//如果遍历完仍未找到要删除的学生，报错
	if (p->next == nullptr)
	{
		cout << "找不到学生的信息" << endl;
	}
}

//修改信息
void StudentInformation::setData()
{
	cout << "请输入要修改的学生的考号：" << endl;
	int number;
	cin >> number;
	auto p = first;
	while (p != nullptr)
	{
		if (p->number == number)
		{
			cout << "请以此输入要修改的考生的考号，姓名，性别，年龄及报考的类别：" << endl;
			cin >> p->number >> p->name >> p->gender >> p->age >> p->type;
			cout << "修改成功！" << endl;
			cout << "考号" << "\t";
			cout << "姓名" << "\t";
			cout << "性别" << "\t";
			cout << "年龄" << "\t";
			cout << "报考类别" << endl;
			cout << p->number << "\t";
			cout << p->name << "\t";
			cout << p->gender << "\t";
			cout << p->age << "\t";
			cout << p->type << endl;
			break;
		}
		p = p->next;
	}
	if (p == nullptr)
	{
		cout << "找不到学生信息，请重新输入或者退出。" << endl;
	}
}

//查找个人信息
void StudentInformation::getData()
{
	cout << "请输入要查找的考号:" << endl;
	int number;
	cin >> number;
	auto p = first;

	while (p != nullptr)
	{
		if (p->number == number)
		{
			cout << "考号" << "\t";
			cout << "姓名" << "\t";
			cout << "性别" << "\t";
			cout << "年龄" << "\t";
			cout << "报考类别" << endl;
			cout << p->number << "\t";
			cout << p->name << "\t";
			cout << p->gender << "\t";
			cout << p->age << "\t";
			cout << p->type << endl;
			break;
		}
		p = p->next;
	}
	if (p == nullptr)
	{
		cout << "找不到学生信息，请重新输入" << endl;
	}
}


int main()
{
	StudentInformation data;
	while (1)
	{
		int command;
		cout << "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）" << endl;
		cin >> command;
		switch (command)
		{
		case 1:
			data.insertData();
			data.print();
			break;
		case 2:
			data.deleteData();
			data.print();
			break;
		case 3:
			data.getData();
			break;
		case 4:
			data.setData();
			break;
		case 5:
			data.print();
			break;
		case 0:
			cout << "\n程序已经成功退出!\n " << endl;
	   
		}
	}
	return 0;
}


