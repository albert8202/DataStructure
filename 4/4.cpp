#include<iostream>
#include<string>
#include<stack>
#include<map>
using namespace std;


string change(string _inString);                      // ��������׺���ʽ_inStringת������Ӧ�ĺ�׺���ʽ������ֵ��Ϊ��Ӧ�ĺ�׺���ʽ
void generate_priority(map<char, int> & _prior_list); // map�ṹ�����ֻ��߷���Ϊkey,��value��Ϊ����Ӧ�����ȼ� 
bool is_num(char c);                                  //�ж��Ƿ�Ϊ����
bool is_min_plus(char c);                             //�ж��Ƿ��ǼӺŻ��߼���
bool is_multi_div(char c);                            //�ж��Ƿ��ǳ˺Ż��߳���
string& trim(string &s);                              //������ʽ



void generate_priority(map<char, int> & _prior_list)
{
	//�������ȼ�
	for (int i = 0; i <= 9; i++)
	{
		_prior_list['0' + i] = 1;
	}
	//�Ӽ����ȼ�
	_prior_list['+'] = 2;
	_prior_list['-'] = 2;
	//�˳����ȼ�
	_prior_list['*'] = 3;
	_prior_list['/'] = 3;
	//�������ȼ�
	_prior_list['('] = 4;
	_prior_list[')'] = 4;
}


string change(string _inString_sp)
{
	//���ڴ��������ŵ�ջ
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
			//������
			if (i - 1 < 0 || (!is_num(_inString[i - 1]) && _inString[i - 1] != ')'))
			{
				_outString[index++] = _inString[i];
			}
			//������
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


	cout << "��������׺���ʽ��";
	getline(std::cin, inInpression);   //��ȡԭ������׺���ʽ
	outInpression = change(inInpression);
	cout << "���������׺���ʽת���ɵĺ�׺���ʽΪ��";
	cout << outInpression << endl;

	system("pause");
	return 0;
}