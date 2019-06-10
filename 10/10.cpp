#include <iostream>
#include<time.h>
using namespace std;


//�����Ĵ���
long long swapCount = 0;
//����Ƿ�����ɹ�
void check(int* numbers, int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		if (numbers[i] <= numbers[i + 1])
			continue;
		else
		{
			cout << "�������" << endl;
			cout << i << endl;
			for (int j = 0; j < 100; j++)
				cout << numbers[j] << endl;
			return;;
		}
	}

	cout << "����ɹ�" << endl;
}
//��ȡ�����δ���������
int* getRandomNum(int n)
{
	auto nums = new int[n];
	srand(time(NULL));

	for (int i = 0; i < n; i++)
		nums[i] = rand() % n;

	return nums;
}
//ð������
void bubbleSort(int* numbers, int n)
{
	int temp;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n - i - 1; j++)
		{
			if (numbers[j] > numbers[j + 1])
			{
				swapCount++;
				temp = numbers[j];
				numbers[j] = numbers[j + 1];
				numbers[j + 1] = temp;
			}
		}

}
//ѡ������
void selectSort(int* numbers, int n)
{

	int temp;
	for (int i = 0; i < n - 1; i++)
		for (int j = i; j < n; j++)
		{
			if (numbers[i] > numbers[j])
			{
				swapCount++;
				temp = numbers[i];
				numbers[i] = numbers[j];
				numbers[j] = temp;
			}
		}
}
//ϣ������
void shellSort(int* numbers, int n)
{

	int j, gap;

	for (gap = n / 2; gap > 0; gap /= 2)
		for (j = gap; j < n; j++)//�������gap��Ԫ�ؿ�ʼ
			if (numbers[j] < numbers[j - gap])//ÿ��Ԫ�����Լ����ڵ����ݽ���ֱ�Ӳ�������
			{
				int temp = numbers[j];
				int k = j - gap;
				while (k >= 0 && numbers[k] > temp)
				{
					numbers[k + gap] = numbers[k];
					k -= gap;
					swapCount++;
				}
				numbers[k + gap] = temp;
			}

}
//��������
void insertSort(int* numbers, int n)
{
	for (int i = 1; i < n; i++)
	{
		auto temp = numbers[i];
		if (numbers[i] < numbers[i - 1])
		{
			int j = 0;
			for (j = i - 1; j >= 0 && temp < numbers[j]; j--)
			{
				numbers[j + 1] = numbers[j];
			}
			numbers[j + 1] = temp;
		}

	}
}
//���ڽ���������
void Swap(int *p, int *q)
{
	auto temp = *p;
	*p = *q;
	*q = temp;
}
int Median3(int* numbers, int left, int right)
{
	int mid = (left + right) / 2;

	if (numbers[left] > numbers[mid])
		Swap(&numbers[left], &numbers[mid]);

	if (numbers[left] > numbers[right])
		Swap(&numbers[left], &numbers[right]);

	if (numbers[mid] > numbers[right])
		Swap(&numbers[mid], &numbers[right]);

	Swap(&numbers[mid], &numbers[right - 1]);

	return numbers[right - 1];
}

//��������
void quickSort(int* numbers, int left, int right)
{
	int pivot, i, j;


	if (right - left >= 50)
	{
		if (left >= right)
			return;
		pivot = Median3(numbers, left, right);
		i = left;
		j = right - 1;
		while (1)
		{
			while (numbers[++i] < pivot);
			while (numbers[--j] > pivot);

			if (i < j)
			{
				Swap(&numbers[i], &numbers[j]);
				swapCount++;
			}
			else
				break;
		}
		Swap(&numbers[i], &numbers[right - 1]);
		swapCount++;
		quickSort(numbers, left, i - 1);
		quickSort(numbers, i + 1, right);
	}
	else
	{
		insertSort(numbers + left, right - left + 1);
	}

}


//�鲢����
template<class Iterator>
void mergeSort(Iterator begin, Iterator end)
{
	if (begin == end)
	{
		return;
	}
	int len = end - begin;
	if (len == 1)
	{
		return;
	}
	Iterator mid = begin + len / 2;
	mergeSort(begin, mid);
	mergeSort(mid, end);
	auto type = *begin;
	decltype(type)* temp = new decltype(type)[len];
	Iterator i = begin;
	Iterator j = mid;
	for (int c = 0; c < len; ++c)
	{
		if ((i != mid) && (j == end || (*i) < (*j)))
		{
			temp[c] = *i;
			++i;
			swapCount++;
		}
		else
		{
			temp[c] = *j;
			++j;
			swapCount++;
		}
	}
	for (int c = 0; c < len; ++c)
	{
		*(begin + c) = temp[c];
	}
	delete[] temp;
}


//������ĺ����ǽ���,�������Ϊ���飬���ڵ�λ�ã����鳤��
void Heap_build(int a[], int root, int length)
{
	int lchild = root * 2 + 1;//���ڵ�����ӽ���±�
	if (lchild < length)//���ӽ���±겻�ܳ�������ĳ���
	{
		int flag = lchild;//flag�������ҽڵ������ֵ���±�
		int rchild = lchild + 1;//���ڵ�����ӽ���±�
		if (rchild < length)//���ӽ���±겻�ܳ�������ĳ���(����еĻ�)
		{
			if (a[rchild] > a[flag])//�ҳ������ӽ���е����ֵ
			{
				flag = rchild;
			}
		}
		if (a[root] < a[flag])
		{
			//���������ͱȸ����������ӽڵ�
			Swap(&a[root], &a[flag]);
			swapCount++;
			//�Ӵ˴�����ӽڵ���Ǹ�λ�ÿ�ʼ�ݹ齨��
			Heap_build(a, flag, length);
		}
	}
}

void heapSort(int a[], int len)
{
	for (int i = len / 2; i >= 0; --i)//�����һ����Ҷ�ӽڵ�ĸ���㿪ʼ����
	{
		Heap_build(a, i, len);
	}

	for (int j = len - 1; j > 0; --j)//j��ʾ�����ʱ�ĳ��ȣ���Ϊlen�����Ѿ������ˣ���len-1��ʼ
	{
		Swap(&a[0], &a[j]);//������βԪ��,�����ֵ��������������λ�ñ���
		swapCount++;
		Heap_build(a, 0, j);//ȥ�����λ�õ�Ԫ�����½��ѣ��˴�j��ʾ����ĳ��ȣ����һ��λ���±��Ϊlen-2
	}

}



//�õ���������λ�ϵ�ֵ
int getNumPos(int num, int pos)
{
	int division = 1;
	for (int i = 0; i < pos - 1; i++)
		division *= 10;

	return (num / division) % 10;
}

//��������
void radixSort(int* numbers, int n)
{
	auto radixArrays = new int*[10];
	for (int i = 0; i < 10; i++)
	{
		radixArrays[i] = new int[n + 1];
		radixArrays[i][0] = 0;
	}

	int count = 0;
	int maxNum = n;
	while (maxNum /= 10)
		count++;
	count++;

	int num = 0, position = 0;


	for (int i = 1; i < count + 1; i++)
	{
		//�����ڸ���Ͱ����
		for (int j = 0; j < n; j++)
		{
			num = getNumPos(numbers[j], i);
			position = ++radixArrays[num][0];
			radixArrays[num][position] = numbers[j];
		}

		int index = 0;
		for (int j = 0; j < 10; j++)
		{
			for (int k = 1; k < radixArrays[j][0] + 1; k++, index++)
			{
				numbers[index] = radixArrays[j][k];
				swapCount++;
			}
			radixArrays[j][0] = 0;
		}
	}
	//�ͷſռ�
	for (int i = 0; i < 10; i++)
		delete(radixArrays[i]);
	delete(radixArrays);
	

}
//��Ҫ�������߼�
void run(int* numbers, int n)
{
	int command = 1;

	while (command != 9)
	{
		cout << "��ѡ�������㷨:    ";
		cin >> command;
		swapCount = 0;
		delete numbers;

		numbers = getRandomNum(n);

		switch (command)
		{
		case 1:
		{
			auto begin = clock();

			bubbleSort(numbers, n);

			auto finish = clock();
			check(numbers, n);
			cout << "ð����������ʱ��:   " << float(finish - begin) / CLOCKS_PER_SEC << "��" << endl;
			cout << "ð�����򽻻�����:   " << swapCount << endl;
		}
		break;
		case 2:
		{
			auto begin = clock();

			selectSort(numbers, n);

			auto finish = clock();
			check(numbers, n);
			cout << "ѡ����������ʱ��:   " << float(finish - begin) / CLOCKS_PER_SEC << "��" << endl;
			cout << "ѡ�����򽻻�����:   " << swapCount << endl;
		}
		break;
		case 3:
		{
			auto begin = clock();

			insertSort(numbers, n);

			auto finish = clock();
			check(numbers, n);
			cout << "ֱ�Ӳ�����������ʱ��:   " << float(finish - begin) / CLOCKS_PER_SEC << "��" << endl;
			cout << "ֱ�Ӳ������򽻻�����:   " << swapCount << endl;
		}
		break;
		case 4:
		{
			auto begin = clock();

			shellSort(numbers, n);

			auto finish = clock();
			check(numbers, n);
			cout << "ϣ��������������ʱ��:   " << float(finish - begin) / CLOCKS_PER_SEC << "��" << endl;
			cout << "ϣ�����򽻻�����:   " << swapCount << endl;
		}
		break;
		case 5:
		{
			auto begin = clock();

			quickSort(numbers, 0, n - 1);

			auto finish = clock();
			check(numbers, n);
			cout << "������������ʱ��:   " << float(finish - begin) / CLOCKS_PER_SEC << "��" << endl;
			cout << "�������򽻻�����:   " << swapCount << endl;
		}
		break;
		case 6:
		{
			auto begin = clock();

			heapSort(numbers, n);

			auto finish = clock();

			check(numbers, n);
			cout << "����������ʱ��:   " << float(finish - begin) / CLOCKS_PER_SEC << "��" << endl;
			cout << "�����򽻻�����:   " << swapCount << endl;
		}
		break;
		case 7:
		{
			auto begin = clock();

			mergeSort(numbers, numbers+n);
			check(numbers, n);
			auto finish = clock();

			cout << "�鲢��������ʱ��:   " << float(finish - begin) / CLOCKS_PER_SEC << "��" << endl;
			cout << "�鲢���򽻻�����:   " << swapCount << endl;
		}
		break;
		case 8:
		{
			auto begin = clock();
			radixSort(numbers, n);
			check(numbers, n);
			auto finish = clock();

			cout << "������������ʱ��:   " << float(finish - begin) / CLOCKS_PER_SEC << "��" << endl;
			cout << "�������򽻻�����:   " << swapCount << endl;
		}
		break;
		case 9:
			cout << "�Ѿ��ɹ��˳���" << endl;
			break;
		default:
			cout << "�������,����������" << endl;
			break;

		}
	}
	delete numbers;
}
//������
int main()
{

	
	cout << "**\t\t\t  �����㷨�Ƚ�\t\t\t\t**\n";
	cout << "==================================================================\n";
	cout << "**\t\t\t1 --- ð������\t\t\t\t**\n";
	cout << "**\t\t\t2 --- ѡ������\t\t\t\t**\n";
	cout << "**\t\t\t3 --- ֱ�Ӳ�������\t\t\t**\n";
	cout << "**\t\t\t4 --- ϣ������\t\t\t\t**\n";
	cout << "**\t\t\t5 --- ��������\t\t\t\t**\n";
	cout << "**\t\t\t6 --- ������\t\t\t\t**\n";
	cout << "**\t\t\t7 --- �鲢����\t\t\t\t**\n";
	cout << "**\t\t\t8 --- ��������\t\t\t\t**\n";
	cout << "**\t\t\t9 --- �˳�����\t\t\t\t**\n";
	cout << "==================================================================\n";
	
	cout << "��ѡ��Ҫ������������ĸ���:" << endl;
	int n;
	cin >> n;
	auto numbers = getRandomNum(n);
	run(numbers, n);
	return 0;
}


