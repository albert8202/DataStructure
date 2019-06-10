#include<iostream>
#include<assert.h>
using namespace std;
//������
template<typename T>
class Queue
{
private:
	T *Array;                 //��̬�������ڴ洢����
	int Capacity;             //�����������
	int Front;                //����ͷλ��
	int Rear;                 //����βλ��
	int Sizes;                //�����ж��������
public:
	Queue(int QueueSize);    //���캯����ʼ����������
	~Queue();                //��������
	bool IsFull();           //�ж϶����Ƿ���
	bool IsEmpty();          //�ж϶����Ƿ�Ϊ��
	void EnQueue(T &data);   //���
	T DeQueue();             //����
	void print();            //�������Ԫ��
};

//���캯����ʼ����������
template<typename T>
Queue<T>::Queue(int QueueSize)      
{
    Front = 0;               
	Rear = 0;
	Sizes = 0;
	Capacity = QueueSize;
	Array = new T[QueueSize];
}
//��������
template<typename T>
Queue<T>::	~Queue()
{
	delete[] Array;
}
	

//�ж��Ƿ�Ϊ������
template<typename T>
bool Queue<T>::IsFull()
{
	return Sizes == Capacity;
}

//�ж��Ƿ�Ϊ��
template<typename T>
bool Queue<T>::IsEmpty()
{
	return Sizes == 0;
}

//��Ӻ���
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

//���Ӻ���
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

	

//��ӡ
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
	cout << "����Ϊһ�������������е�һ����N��N<=1000��Ϊ�˿��������������Nλ�˿͵ı�š����Ϊ�����Ĺ˿���Ҫ��A���ڰ���ҵ��Ϊż���Ĺ˿���ȥB���ڡ����ּ��Կո�ָ�:"<<endl;

	int N = 0, CapacityOfA = 0, CapacityOfB = 0;
	while (1)                                  //��ǿ��׳�ԣ���ֹ�û������ʹ�ó������
	{
		cin >> N;
		if (N > 0)break;
		cout << "����������������������";
	}
	
	int *temp = new int[N];                   //����temp��̬���飬������ʱ�洢��������
	for (int i = 0; i < N; i++)
	{
		while (1)                             //��ǿ��׳�ԣ���ֹ�û������ʹ�ó������
		{
			cin >> temp[i];
			if (temp[i] > 0)break;
			cout << "����������������������";
		}
		if (temp[i] % 2 == 1) { CapacityOfA++; }          //���A������
		if (temp[i] % 2 == 0) { CapacityOfB++; }          //���B������
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