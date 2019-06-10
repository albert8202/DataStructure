#include<iostream>
#include<vector>
using namespace std;
//λ�ý��
struct Position
{
	int x;     //x�������
	int y;     //y��������
};
//�����ĸ�����
Position direction[4] = 
{
	{0,1},{0,-1},{-1,0},{1,0}
};
//���Ե�ͼ
/*
char Maze[8][8]=
{
	"#######",
	"#0#000#",
	"#0#0###",
	"#000#0#",
	"#0#000#",
	"#0#0#0#",
	"#######",

};*/
//��ͼ
char Maze[8][8] =     
{
	"#"
};

vector<Position> Route;          //�����洢ͨ��·��
Position ExitPostion = { 5,5 };  //��������
bool Isfound = false;            //���λ
void run(int x, int y)  
{
	if (ExitPostion.x == x&&ExitPostion.y == y)
	{
		Isfound = true;
		Maze[x][y] = 'X';
		Route.push_back(ExitPostion);
		return;
    }
	
	for (int i = 0; i < 4; i++)//�ĸ�����
	{
		//�����һ�������ߵĻ�����ǰλ�÷���Route������ǵ�ͼ
		if (Maze[x + direction[i].x][y + direction[i].y] == '0')
		{
			Position temp = { x,y };
			Route.push_back(temp);
			Maze[x][y] = 'X';
			run(x + direction[i].x, y + direction[i].y);
			if (Isfound) { return; }
			//�������·��ͨ������·����ɾ������������һ��
			Route.erase(Route.end() - 1);
			Maze[x][y] = '0';
		}
	}
}

int main()
{
	
	cout << "�������ͼ��7*7����" << endl;
	char temp;
	for (int i = 0; i < 7; i++)
	{
		cout << "�������"<<i<<"�У�";
		for (int j = 0; j < 7; j++)
		{
			cin >> temp;
			Maze[i][j] = temp;
		}
	}
	Position pos = { 0,0 };
	cout << "���������(x,y),�Կո������";
	cin >> pos.x >> pos.y;
	cout << "�������յ�(x,y),�Կո������";
	cin >> pos.x >> pos.y;
	run(1, 1);
	if (Isfound)
	{
		cout << "�Թ���ͼ:\n\t";

		for (int i = 0; i < 7; i++)
			cout << i << "��" << "\t\t";

		cout << endl;
		for (int i = 0; i < 7; i++)
		{
			cout << i << "��" << "\t";
			for (int j = 0; j < 7; j++)
			{
				cout << Maze[i][j] << "\t\t";
			}
			cout << endl << endl;
		}

		cout << "�Թ�·����\n\t";
		for (auto iter = Route.begin(); iter != Route.end() - 1; iter++)
			cout << "<" << iter->x << "," << iter->y << "> " << "---> ";
		cout << "<" << (Route.end() - 1)->x << "," << (Route.end() - 1)->y << ">" << endl;
	}
	else cout << "Not Found!" << endl;
	system("pause");
    return 0;
}