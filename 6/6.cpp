#include <iostream>
#include <string>
#include <cctype>

using namespace std;
/*----��Ա�ṹ��----*/
struct familyMember
{
	string m_name;                //��Ա����
	familyMember * father;        //��ָ��
	familyMember * child;         //��ָ��
	familyMember * brotherPre;    //�ֵ�ָ��
	familyMember * brotherNext;   //�ֵ�ָ��
	int sonNum;                   //ֱϵ�������
};
/*----��������----*/
class familyTree
{
private:
	familyMember * ancestor;      //����  
public:
	familyTree();                 //���캯�� 
	~familyTree();                //��������

	void addFamilyMember();       //��Ӽ�ͥ��Ա
	void completeFamilyMember();  //���Ƽ�ͥ
	void deleteFamilyMember();    //����ֲ���ͥ
	void changeName();            //���ļ�ͥ��Ա����
	void get();                   //�鿴��Ա��Ϣ

	familyMember * findFamilyMember(string name, familyMember * key);  //���Ҽ�ͥ��Ա
	void showSons(familyMember * p);                                   //��ʾ�Ӵ�
	void destroy(familyMember * p);                                    //�ݹ�ɾ��
	familyMember * familyMemberCreate();                               //��Ա���ɺ���
	void ancestorCreate();                                             //���ڵ����ɺ���
};

familyTree::familyTree()
{
	ancestor = new familyMember;
	ancestor->m_name = "";
	ancestor->sonNum = 0;
	ancestor->father = NULL;
	ancestor->child = NULL;
	ancestor->brotherPre = NULL;
	ancestor->brotherNext = NULL;
}

familyTree::~familyTree()
{
	destroy(ancestor);
}

/*----���ӳ�Ա----*/
void familyTree::addFamilyMember()
{
	string name;
	cout << "������Ҫ��Ӷ��ӣ���Ů�������˵�������";
	cin >> name;
	familyMember *p = findFamilyMember(name, ancestor);
	if (p == NULL)
	{
		cout << "���޴���" << endl;
		return;
	}
	cout << "������" << p->m_name << "����ӵĶ��ӣ���Ů������������";
	familyMember * newChild = familyMemberCreate();
	newChild->father = p; 
	p->sonNum++;
	cin >> newChild->m_name;
	if (!p->child)
	{
		p->child = newChild;
		showSons(p);
		return;
	}
	familyMember * temp = p;
	temp = temp->child;
	while (temp->brotherNext)
	{
		temp = temp->brotherNext;
	}
	temp->brotherNext = newChild;
	showSons(p);
}

/*----���Ƽ�ͥ��Ա----*/
void familyTree::completeFamilyMember()
{
	string name;
	cout << "������Ҫ������ͥ���˵�����:";
	cin >> name;
	familyMember * p = findFamilyMember(name, ancestor);
	if (p == NULL)
	{
		cout << "δ�ҵ�����" << endl;
		return;
	}
	if (p->child)
	{
		cout << p->m_name << "�Ѿ���������ͥ" << endl;
		return;
	}
	cout << "������" << p->m_name << "�Ķ�Ů������";
	cin >> p->sonNum;
	if (p->sonNum == 0)
		return;
	cout << "����������" << p->m_name << "�Ķ�Ů��������";
	p->child = familyMemberCreate();
	familyMember *temp = p->child;
	cin >> temp->m_name;
	temp->father = p;
	//�������sonNum����Ů
	for (int i = 1; i < p->sonNum; i++)
	{
		familyMember *brother = familyMemberCreate();
		cin >> brother->m_name;
		brother->father = p;
		brother->brotherPre = temp;
		temp->brotherNext = brother;
		temp = temp->brotherNext;
	}
	showSons(p);
}

/*----ɾ����ͥ��Ա----*/
void familyTree::deleteFamilyMember()
{
	string name;
	familyMember *p = NULL;
	cout << "������Ҫ��ɢ��ͥ���˵�������";
	cin >> name;
	p = findFamilyMember(name, ancestor);
	if (p == NULL)
	{
		cout << "���޴���" << endl;
		return;
	}
	showSons(p);
	if (p->brotherPre && p->brotherNext)
	{
		p->brotherPre->brotherNext = p->brotherNext;
		p->brotherNext->brotherPre = p->brotherPre;
		p->father->sonNum--;
	}
	if (p->brotherPre && !p->brotherNext)
	{
		p->brotherPre->brotherNext = NULL;
		p->father->sonNum--;
	}
	if (!p->brotherPre && p->brotherNext)
	{
		p->father->child = p->brotherNext;
		p->brotherNext->brotherPre = NULL;
		p->father->sonNum--;
	}
	if (!p->brotherPre && !p->brotherNext)
	{
		p->father->child = NULL;
		p->father->sonNum--;
	}
	if (p->child)
		destroy(p->child);
	delete p;
}

/*----���¼�ͥ��Ա��Ϣ----*/
void familyTree::changeName()
{
	string name;
	cout << "������Ҫ�����������˵�����:";
	cin >> name;
	familyMember *p = findFamilyMember(name, ancestor);
	if (p == NULL)
	{
		cout << "���޴���" << endl;
		return;
	}
	cout << "��������ĺ������:";
	cin >> p->m_name;
	cout << name << "�Ѿ�����Ϊ" << p->m_name << endl;
}

/*----���Ҽ�ͥ��Ա----*/
familyMember * familyTree::findFamilyMember(string name, familyMember * key)
{
	familyMember * p = key, *ans = NULL, *temp = p;

	if (p->m_name == name)       //����ҵ��򷵻�
		return p;
	while (temp->brotherNext)    //���ֵ����еݹ���ò��Һ���
	{
		ans = findFamilyMember(name, temp->brotherNext);
		if (ans)
			return ans;
		temp = temp->brotherNext;
	}
	temp = p;
	if (temp->child)            //�������еݹ���ò��Һ���
		ans = findFamilyMember(name, temp->child);
	return ans;
}

/*----��һ��չʾ----*/
void familyTree::showSons(familyMember * p)
{
	if (p->sonNum == 0)
	{
		cout << p->m_name << "û�к��" << endl;
		return;
	}
	familyMember * temp = p->child;
	cout << p->m_name << "�ĵ�һ��������:";
	for (int i = 0; i < p->sonNum; i++)
	{
		cout << temp->m_name << "   ";
		if (temp->brotherNext)
			temp = temp->brotherNext;
	}
}

/*----�ͷſռ�----*/
void familyTree::destroy(familyMember * p)
{
	familyMember *temp = p;
	while (temp->brotherNext)
	{
		temp = temp->brotherNext;
	}
	while (temp->brotherPre)
	{
		temp = temp->brotherPre;
		temp->brotherNext->brotherPre = NULL;
		temp->brotherNext->brotherNext = NULL;
		destroy(temp->brotherNext);
	}
	if (temp->child)
		destroy(temp->child);
	delete p;
}

/*----��ȡ��ͥ��Ա----*/
void familyTree::get()
{
	string name;
	cout << "������Ҫ�鿴�˵�����:";
	cin >> name;
	familyMember * p = findFamilyMember(name, ancestor);  //���ò��Һ������������ҽ������p
	if (p == NULL)                                        //û���ҵ��ü�ͥ��Ա
	{
		cout << "���޴���" << endl;
		return;
	}
	//�ҵ���ʼ��ӡ�ó�Ա�ļ�ͥ��Ϣ
	cout << "������" << p->m_name << endl;
	if (p->father)
	{
		cout << "���ף�" << p->father->m_name << endl;
		if (p->father->sonNum > 0)
		{
			familyMember  *temp = p->father->child;
			cout << "�ֵܣ�";
			for (int i = 1; i < p->father->sonNum;)
			{
				if (temp->m_name != name)
				{
					cout << temp->m_name << "    ";
					i++;
				}
				if (temp->brotherNext)
					temp = temp->brotherNext;
			}
			cout << endl;
		}
	}
	showSons(p);
}

/*----������ͥ��Ա�ڵ�----*/
familyMember * familyTree::familyMemberCreate()
{
	familyMember *p = new familyMember;

	p->m_name = "";
	p->sonNum = 0;
	p->father = NULL;
	p->child = NULL;
	p->brotherNext = NULL;
	p->brotherPre = NULL;

	return p;
}

/*----�������ڵ�----*/
void familyTree::ancestorCreate()
{
	cout << "���Ƚ���һ�����ף�" << endl
		<< "������Ҫ������ͥ���˵�������";
	cin >> ancestor->m_name;
	cout << "�˼��׵������ǣ�" << ancestor->m_name << endl;
	cout << endl;
}

int main()
{
	familyTree Family;
	char order;

	cout << "**                         ���׹���ϵͳ                         **" << endl;
	cout << "==================================================================" << endl;
	cout << "**                     ��ѡ��Ҫִ�еĲ�����                     **" << endl;
	cout << "**                     A --- ���Ƽ�ͥ                           **" << endl;
	cout << "**                     B --- ��Ӽ�ͥ��Ա                       **" << endl;
	cout << "**                     C --- ��ɢ�ֲ���Ա                       **" << endl;
	cout << "**                     D --- ���ļ�ͥ��Ա����                   **" << endl;
	cout << "**                     E --- �鿴��Ա��Ϣ                       **" << endl;
	cout << "**                     F --- �˳�ϵͳ                           **" << endl;
	cout << "==================================================================" << endl;

	Family.ancestorCreate();

	cout << "��ѡ��Ҫִ�еĲ���:";
	cin >> order;
	while (order != 'F')
	{
		switch (order)
		{
		case 'A':
			Family.completeFamilyMember();
			break;
		case 'B':
			Family.addFamilyMember();
			break;
		case 'C':
			Family.deleteFamilyMember();
			break;
		case 'D':
			Family.changeName();
			break;
		case 'E':
			Family.get();
			break;
		default:
			cout << "��������";
			break;
		}
		cout << endl << endl;
		cout << "��ѡ��Ҫִ�еĲ���:";
		cin >> order;
	}
	return 0;
}