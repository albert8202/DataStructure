#include<iostream>
#include<string>
#include<vector>
using namespace std;


//����ѧ�����
struct student
{
	int number;    //����
	string name;   //����
	string gender; //�Ա�
	int age;       //����
	string type;  //�������
	student* next; //���ָ����
};

//����������Ϣ����
class StudentInformation
{
private:
	student* first;  //��ͷ
	student* last;   //��β
public:
	StudentInformation();  //���캯��
	void print() const;    //�����ʾָ��
	void insertData();     //��������
	void deleteData();     //ɾ������
	void setData();        //�޸�����
	void getData();        //�������
};

//��ʼ�����Ա���ϵͳ
StudentInformation::StudentInformation()
{
	first = nullptr;
	cout << "���Ƚ�������ϵͳ" << endl << "�����뿼��������";
    int studentNum;   //��������
	cin >> studentNum;
	while (studentNum < 0) //����������С��1�򱨴�����ʾ��������
	{
		cout << "���������������ڵ���1����! " << endl;
		cin >> studentNum;
	}
	cout << "���������뿼�����ţ��������Ա����估�������" << endl;
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

//��ӡѧ����Ϣ
void StudentInformation::print() const
{
	cout << "����" << "\t";
	cout << "����" << "\t";
	cout << "�Ա�" << "\t";
	cout << "����" << "\t";
	cout << "�������" << endl;
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

//��������
void StudentInformation::insertData()
{
	cout << "����������Ҫ����Ŀ���λ�ã�" << endl;
	int position;
	cin >> position;
	while (position < 1)    //����������С��1�򱨴�����ʾ�û���������
	{
		cout << "���������������ڵ���1������" << endl;
		cin >> position;
	}
	cout << "����������Ҫ����Ŀ����Ŀ��ţ��������Ա����估�������" << endl;
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
//ɾ������
void StudentInformation::deleteData()
{
	cout << "������Ҫɾ���Ŀ����Ŀ��ţ�" << endl;
	int num;
	cin >> num;
	//ͷ�ڵ㼴Ϊ��Ҫɾ�����
	if (this->first->number == num)
	{
		auto temp = first;
		first = first->next;
		delete temp;
		return;
	}
	//ɾ������ͷ�ڵ�����
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
	//�����������δ�ҵ�Ҫɾ����ѧ��������
	if (p->next == nullptr)
	{
		cout << "�Ҳ���ѧ������Ϣ" << endl;
	}
}

//�޸���Ϣ
void StudentInformation::setData()
{
	cout << "������Ҫ�޸ĵ�ѧ���Ŀ��ţ�" << endl;
	int number;
	cin >> number;
	auto p = first;
	while (p != nullptr)
	{
		if (p->number == number)
		{
			cout << "���Դ�����Ҫ�޸ĵĿ����Ŀ��ţ��������Ա����估���������" << endl;
			cin >> p->number >> p->name >> p->gender >> p->age >> p->type;
			cout << "�޸ĳɹ���" << endl;
			cout << "����" << "\t";
			cout << "����" << "\t";
			cout << "�Ա�" << "\t";
			cout << "����" << "\t";
			cout << "�������" << endl;
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
		cout << "�Ҳ���ѧ����Ϣ����������������˳���" << endl;
	}
}

//���Ҹ�����Ϣ
void StudentInformation::getData()
{
	cout << "������Ҫ���ҵĿ���:" << endl;
	int number;
	cin >> number;
	auto p = first;

	while (p != nullptr)
	{
		if (p->number == number)
		{
			cout << "����" << "\t";
			cout << "����" << "\t";
			cout << "�Ա�" << "\t";
			cout << "����" << "\t";
			cout << "�������" << endl;
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
		cout << "�Ҳ���ѧ����Ϣ������������" << endl;
	}
}


int main()
{
	StudentInformation data;
	while (1)
	{
		int command;
		cout << "��ѡ����Ҫ���еĲ�����1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ��������" << endl;
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
			cout << "\n�����Ѿ��ɹ��˳�!\n " << endl;
	   
		}
	}
	return 0;
}


