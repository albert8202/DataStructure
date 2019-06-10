#include<iostream>
#include<assert.h>
using namespace std;
//队列类
template<typename T>
class Queue
{
private:
	T *Array;                 //动态数组用于存储数据
	int Capacity;             //队列最大容量
	int Front;                //队列头位置
	int Rear;                 //队列尾位置
	int Sizes;                //队列中对象的数量
public:
	Queue(int QueueSize);    //构造函数初始化各个参数
	~Queue();                //析构函数
	bool IsFull();           //判断队列是否满
	bool IsEmpty();          //判断队列是否为空
	void EnQueue(T &data);   //入队
	T DeQueue();             //出队
	void print();            //输出队中元素
};

//构造函数初始化各个参数
template<typename T>
Queue<T>::Queue(int QueueSize)      
{
    Front = 0;               
	Rear = 0;
	Sizes = 0;
	Capacity = QueueSize;
	Array = new T[QueueSize];
}
//析构函数
template<typename T>
Queue<T>::	~Queue()
{
	delete[] Array;
}
	

//判断是否为满队列
template<typename T>
bool Queue<T>::IsFull()
{
	return Sizes == Capacity;
}

//判断是否为空
template<typename T>
bool Queue<T>::IsEmpty()
{
	return Sizes == 0;
}

//入队函数
template<typename T>
void Queue<T>::EnQueue(T &data)
{
	if (IsFull())
    {
	   throw("full");
	}
	Array[Rear] = data;
	Rear = (Rear+1 ) % Capacity;
	++Sizes;
}

//出队函数
template<typename T>
T Queue<T>::DeQueue()
{
	if (IsEmpty())
	{
		throw("empty");
	}
		
	--Sizes;
	return this->Array[Front++];
}

	

//打印
template<typename T>
void Queue<T>::print()
{
	while(!IsEmpty())
	{
		cout << " " << this->DeQueue();
	}
}


int main()
{
	cout << "输入为一行正整数，其中第一数字N（N<=1000）为顾客总数，后面跟着N位顾客的编号。编号为奇数的顾客需要到A窗口办理业务，为偶数的顾客则去B窗口。数字间以空格分隔:"<<endl;

	int N = 0, CapacityOfA = 0, CapacityOfB = 0;
	while (1)                                  //增强健壮性，防止用户误操作使得程序崩溃
	{
		cin >> N;
		if (N > 0)break;
		cout << "输入有误！请输入正整数：";
	}
	
	int *temp = new int[N];                   //开辟temp动态数组，用来暂时存储所有数据
	for (int i = 0; i < N; i++)
	{
		while (1)                             //增强健壮性，防止用户误操作使得程序崩溃
		{
			cin >> temp[i];
			if (temp[i] > 0)break;
			cout << "输入有误！请输入正整数：";
		}
		if (temp[i] % 2 == 1) { CapacityOfA++; }          //获得A的人数
		if (temp[i] % 2 == 0) { CapacityOfB++; }          //获得B的人数
    }
	Queue<int>A(CapacityOfA);
	Queue<int>B(CapacityOfB);
	for (int i = 0; i < N; i++)
	{
		if (temp[i] % 2 == 1) { A.EnQueue(temp[i]); }     
		if (temp[i] % 2 == 0) { B.EnQueue(temp[i]); }
	}
	int j = 1;
	while (!A.IsEmpty() && !B.IsEmpty())
	{
		if (j % 3 == 1 || j % 3 == 2) { cout<<" "<<A.DeQueue(); }
		else { cout <<" "<< B.DeQueue(); }
		j++;
	}
	if (A.IsEmpty()) { B.print(); }
	if (B.IsEmpty()) { A.print(); }
	delete[] temp;
	return 0;
}