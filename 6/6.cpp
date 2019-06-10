#include <iostream>
#include <string>
#include <cctype>

using namespace std;
/*----成员结构体----*/
struct familyMember
{
	string m_name;                //成员姓名
	familyMember * father;        //父指针
	familyMember * child;         //子指针
	familyMember * brotherPre;    //兄弟指针
	familyMember * brotherNext;   //兄弟指针
	int sonNum;                   //直系后代个数
};
/*----家谱树类----*/
class familyTree
{
private:
	familyMember * ancestor;      //树根  
public:
	familyTree();                 //构造函数 
	~familyTree();                //析构函数

	void addFamilyMember();       //添加家庭成员
	void completeFamilyMember();  //完善家庭
	void deleteFamilyMember();    //解除局部家庭
	void changeName();            //更改家庭成员姓名
	void get();                   //查看成员信息

	familyMember * findFamilyMember(string name, familyMember * key);  //查找家庭成员
	void showSons(familyMember * p);                                   //显示子代
	void destroy(familyMember * p);                                    //递归删除
	familyMember * familyMemberCreate();                               //成员生成函数
	void ancestorCreate();                                             //根节点生成函数
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

/*----增加成员----*/
void familyTree::addFamilyMember()
{
	string name;
	cout << "请输入要添加儿子（或女儿）的人的姓名：";
	cin >> name;
	familyMember *p = findFamilyMember(name, ancestor);
	if (p == NULL)
	{
		cout << "查无此人" << endl;
		return;
	}
	cout << "请输入" << p->m_name << "新添加的儿子（或女儿的姓名）：";
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

/*----完善家庭成员----*/
void familyTree::completeFamilyMember()
{
	string name;
	cout << "请输入要建立家庭的人的姓名:";
	cin >> name;
	familyMember * p = findFamilyMember(name, ancestor);
	if (p == NULL)
	{
		cout << "未找到此人" << endl;
		return;
	}
	if (p->child)
	{
		cout << p->m_name << "已经建立过家庭" << endl;
		return;
	}
	cout << "请输入" << p->m_name << "的儿女人数：";
	cin >> p->sonNum;
	if (p->sonNum == 0)
		return;
	cout << "请依次输入" << p->m_name << "的儿女的姓名：";
	p->child = familyMemberCreate();
	familyMember *temp = p->child;
	cin >> temp->m_name;
	temp->father = p;
	//依次添加sonNum个子女
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

/*----删除家庭成员----*/
void familyTree::deleteFamilyMember()
{
	string name;
	familyMember *p = NULL;
	cout << "请输入要解散家庭的人的姓名：";
	cin >> name;
	p = findFamilyMember(name, ancestor);
	if (p == NULL)
	{
		cout << "查无此人" << endl;
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

/*----更新家庭成员信息----*/
void familyTree::changeName()
{
	string name;
	cout << "请输入要更改姓名的人的姓名:";
	cin >> name;
	familyMember *p = findFamilyMember(name, ancestor);
	if (p == NULL)
	{
		cout << "查无此人" << endl;
		return;
	}
	cout << "请输入更改后的姓名:";
	cin >> p->m_name;
	cout << name << "已经更名为" << p->m_name << endl;
}

/*----查找家庭成员----*/
familyMember * familyTree::findFamilyMember(string name, familyMember * key)
{
	familyMember * p = key, *ans = NULL, *temp = p;

	if (p->m_name == name)       //如果找到则返回
		return p;
	while (temp->brotherNext)    //在兄弟树中递归调用查找函数
	{
		ans = findFamilyMember(name, temp->brotherNext);
		if (ans)
			return ans;
		temp = temp->brotherNext;
	}
	temp = p;
	if (temp->child)            //在子树中递归调用查找函数
		ans = findFamilyMember(name, temp->child);
	return ans;
}

/*----第一代展示----*/
void familyTree::showSons(familyMember * p)
{
	if (p->sonNum == 0)
	{
		cout << p->m_name << "没有后代" << endl;
		return;
	}
	familyMember * temp = p->child;
	cout << p->m_name << "的第一代子孙是:";
	for (int i = 0; i < p->sonNum; i++)
	{
		cout << temp->m_name << "   ";
		if (temp->brotherNext)
			temp = temp->brotherNext;
	}
}

/*----释放空间----*/
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

/*----获取家庭成员----*/
void familyTree::get()
{
	string name;
	cout << "请输入要查看人的姓名:";
	cin >> name;
	familyMember * p = findFamilyMember(name, ancestor);  //调用查找函数，并将查找结果赋给p
	if (p == NULL)                                        //没有找到该家庭成员
	{
		cout << "查无此人" << endl;
		return;
	}
	//找到后开始打印该成员的家庭信息
	cout << "姓名：" << p->m_name << endl;
	if (p->father)
	{
		cout << "父亲：" << p->father->m_name << endl;
		if (p->father->sonNum > 0)
		{
			familyMember  *temp = p->father->child;
			cout << "兄弟：";
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

/*----创建家庭成员节点----*/
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

/*----创建根节点----*/
void familyTree::ancestorCreate()
{
	cout << "首先建立一个家谱！" << endl
		<< "请输入要建立家庭的人的姓名：";
	cin >> ancestor->m_name;
	cout << "此家谱的祖先是：" << ancestor->m_name << endl;
	cout << endl;
}

int main()
{
	familyTree Family;
	char order;

	cout << "**                         家谱管理系统                         **" << endl;
	cout << "==================================================================" << endl;
	cout << "**                     请选择要执行的操作：                     **" << endl;
	cout << "**                     A --- 完善家庭                           **" << endl;
	cout << "**                     B --- 添加家庭成员                       **" << endl;
	cout << "**                     C --- 解散局部成员                       **" << endl;
	cout << "**                     D --- 更改家庭成员姓名                   **" << endl;
	cout << "**                     E --- 查看成员信息                       **" << endl;
	cout << "**                     F --- 退出系统                           **" << endl;
	cout << "==================================================================" << endl;

	Family.ancestorCreate();

	cout << "请选择要执行的操作:";
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
			cout << "输入有误";
			break;
		}
		cout << endl << endl;
		cout << "请选择要执行的操作:";
		cin >> order;
	}
	return 0;
}