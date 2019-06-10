#include<iostream>
#include<vector>
using namespace std;
//位置结点
struct Position
{
	int x;     //x表横坐标
	int y;     //y表纵坐标
};
//定义四个方向
Position direction[4] = 
{
	{0,1},{0,-1},{-1,0},{1,0}
};
//测试地图
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
//地图
char Maze[8][8] =     
{
	"#"
};

vector<Position> Route;          //用来存储通关路径
Position ExitPostion = { 5,5 };  //出口坐标
bool Isfound = false;            //标记位
void run(int x, int y)  
{
	if (ExitPostion.x == x&&ExitPostion.y == y)
	{
		Isfound = true;
		Maze[x][y] = 'X';
		Route.push_back(ExitPostion);
		return;
    }
	
	for (int i = 0; i < 4; i++)//四个方向
	{
		//如果下一步可以走的话将当前位置放入Route，并标记地图
		if (Maze[x + direction[i].x][y + direction[i].y] == '0')
		{
			Position temp = { x,y };
			Route.push_back(temp);
			Maze[x][y] = 'X';
			run(x + direction[i].x, y + direction[i].y);
			if (Isfound) { return; }
			//如果这条路不通，则在路径中删除，并返回上一步
			Route.erase(Route.end() - 1);
			Maze[x][y] = '0';
		}
	}
}

int main()
{
	
	cout << "请输入地图（7*7）：" << endl;
	char temp;
	for (int i = 0; i < 7; i++)
	{
		cout << "请输入第"<<i<<"行：";
		for (int j = 0; j < 7; j++)
		{
			cin >> temp;
			Maze[i][j] = temp;
		}
	}
	Position pos = { 0,0 };
	cout << "请输入起点(x,y),以空格隔开：";
	cin >> pos.x >> pos.y;
	cout << "请输入终点(x,y),以空格隔开：";
	cin >> pos.x >> pos.y;
	run(1, 1);
	if (Isfound)
	{
		cout << "迷宫地图:\n\t";

		for (int i = 0; i < 7; i++)
			cout << i << "列" << "\t\t";

		cout << endl;
		for (int i = 0; i < 7; i++)
		{
			cout << i << "行" << "\t";
			for (int j = 0; j < 7; j++)
			{
				cout << Maze[i][j] << "\t\t";
			}
			cout << endl << endl;
		}

		cout << "迷宫路径：\n\t";
		for (auto iter = Route.begin(); iter != Route.end() - 1; iter++)
			cout << "<" << iter->x << "," << iter->y << "> " << "---> ";
		cout << "<" << (Route.end() - 1)->x << "," << (Route.end() - 1)->y << ">" << endl;
	}
	else cout << "Not Found!" << endl;
	system("pause");
    return 0;
}