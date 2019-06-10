#include<iostream>
#include<string>
#include<stack>
#include<map>
using namespace std;


string change(string _inString);                      // 用来将中缀表达式_inString转化成相应的后缀表达式，返回值即为相应的后缀表达式
void generate_priority(map<char, int> & _prior_list); // map结构，数字或者符号为key,其value即为所对应的优先级 
bool is_num(char c);                                  //判断是否为数字
bool is_min_plus(char c);                             //判断是否是加号或者减号
bool is_multi_div(char c);                            //判断是否是乘号或者除号
string& trim(string &s);                              //调整格式



void generate_priority(map<char, int> & _prior_list)
{
	//数字优先级
	for (int i = 0; i <= 9; i++)
	{
		_prior_list['0' + i] = 1;
	}
	//加减优先级
	_prior_list['+'] = 2;
	_prior_list['-'] = 2;
	//乘除优先级
	_prior_list['*'] = 3;
	_prior_list['/'] = 3;
	//括号优先级
	_prior_list['('] = 4;
	_prior_list[')'] = 4;
}


string change(string _inString_sp)
{
	//用于存放运算符号的栈
	map<char, int> prior_list;
	generate_priority(prior_list);
	stack<char> signals;
	string _inString(_inString_sp.length(), ' ');
	int ck = 0;
	for (int i = 0; i < _inString_sp.length(); i++)
	{
		if (_inString_sp[i] == ' ')
		{
			continue;
		}
		else
		{
			_inString[ck++] = _inString_sp[i];
		}
	}
	string _outString(2 * _inString.length(), ' ');
	int index = 0;
	for (int i = 0; i < _inString.length(); i++)
	{
		if (_inString[i] == ' ')
		{
			continue;
		}
		else if (is_num(_inString[i]) || _inString[i] == '.')
		{
			_outString[index++] = _inString[i];
		}
		else if (is_min_plus(_inString[i]))
		{
			//正负号
			if (i - 1 < 0 || (!is_num(_inString[i - 1]) && _inString[i - 1] != ')'))
			{
				_outString[index++] = _inString[i];
			}
			//渐渐好
			else
			{
				while (!signals.empty()
					&& prior_list[signals.top()] >= prior_list[_inString[i]]
					&& signals.top() != '(')
				{
					_outString[index++] = ' ';
					_outString[index++] = signals.top();
					signals.pop();
				}
				_outString[index++] = ' ';
				signals.push(_inString[i]);
			}
		}
		else if (is_multi_div(_inString[i]))
		{
			while (!signals.empty()
				&& prior_list[signals.top()] >= prior_list[_inString[i]]
				&& signals.top() != '(')
			{
				_outString[index++] = ' ';
				_outString[index++] = signals.top();
				signals.pop();
			}
			_outString[index++] = ' ';
			signals.push(_inString[i]);
		}
		else if (_inString[i] == '(')
		{
			signals.push(_inString[i]);
		}
		else if (_inString[i] == ')')
		{
			while (signals.top() != '(')
			{
				_outString[index++] = ' ';
				_outString[index++] = signals.top();
				signals.pop();
			}
			signals.pop();
		}
	}
	while (!signals.empty())
	{
		_outString[index++] = ' ';
		_outString[index++] = signals.top();
		signals.pop();
	}
	_outString = trim(_outString);
	return _outString;
}

bool is_num(char c)
{
	if (c >= '0'&&c <= '9')
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool is_min_plus(char c)
{
	if (c == '-' || c == '+')
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool is_multi_div(char c)
{
	if (c == '*' || c == '/')
	{
		return true;
	}
	else
	{
		return false;
	}
}

string& trim(string &s)
{
	if (s.empty())
	{
		return s;
	}
	s.erase(0, s.find_first_not_of(" "));
	s.erase(s.find_last_not_of(" ") + 1);
	return s;
}
int main()
{
	string inInpression, outInpression;


	cout << "请输入中缀表达式：";
	getline(std::cin, inInpression);   //读取原来的中缀表达式
	outInpression = change(inInpression);
	cout << "所输入的中缀表达式转化成的后缀表达式为：";
	cout << outInpression << endl;

	system("pause");
	return 0;
}