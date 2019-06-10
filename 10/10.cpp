#include <iostream>
#include<time.h>
using namespace std;


//交换的次数
long long swapCount = 0;
//检查是否排序成功
void check(int* numbers, int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		if (numbers[i] <= numbers[i + 1])
			continue;
		else
		{
			cout << "排序错误" << endl;
			cout << i << endl;
			for (int j = 0; j < 100; j++)
				cout << numbers[j] << endl;
			return;;
		}
	}

	cout << "排序成功" << endl;
}
//获取随机的未经排序的数
int* getRandomNum(int n)
{
	auto nums = new int[n];
	srand(time(NULL));

	for (int i = 0; i < n; i++)
		nums[i] = rand() % n;

	return nums;
}
//冒泡排序
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
//选择排序
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
//希尔排序
void shellSort(int* numbers, int n)
{

	int j, gap;

	for (gap = n / 2; gap > 0; gap /= 2)
		for (j = gap; j < n; j++)//从数组第gap个元素开始
			if (numbers[j] < numbers[j - gap])//每个元素与自己组内的数据进行直接插入排序
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
//插入排序
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
//用于交换两个数
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

//快速排序
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


//归并排序
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


//堆排序的核心是建堆,传入参数为数组，根节点位置，数组长度
void Heap_build(int a[], int root, int length)
{
	int lchild = root * 2 + 1;//根节点的左子结点下标
	if (lchild < length)//左子结点下标不能超出数组的长度
	{
		int flag = lchild;//flag保存左右节点中最大值的下标
		int rchild = lchild + 1;//根节点的右子结点下标
		if (rchild < length)//右子结点下标不能超出数组的长度(如果有的话)
		{
			if (a[rchild] > a[flag])//找出左右子结点中的最大值
			{
				flag = rchild;
			}
		}
		if (a[root] < a[flag])
		{
			//交换父结点和比父结点大的最大子节点
			Swap(&a[root], &a[flag]);
			swapCount++;
			//从此次最大子节点的那个位置开始递归建堆
			Heap_build(a, flag, length);
		}
	}
}

void heapSort(int a[], int len)
{
	for (int i = len / 2; i >= 0; --i)//从最后一个非叶子节点的父结点开始建堆
	{
		Heap_build(a, i, len);
	}

	for (int j = len - 1; j > 0; --j)//j表示数组此时的长度，因为len长度已经建过了，从len-1开始
	{
		Swap(&a[0], &a[j]);//交换首尾元素,将最大值交换到数组的最后位置保存
		swapCount++;
		Heap_build(a, 0, j);//去除最后位置的元素重新建堆，此处j表示数组的长度，最后一个位置下标变为len-2
	}

}



//得到各个数的位上的值
int getNumPos(int num, int pos)
{
	int division = 1;
	for (int i = 0; i < pos - 1; i++)
		division *= 10;

	return (num / division) % 10;
}

//基数排序
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
		//分配在各个桶里面
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
	//释放空间
	for (int i = 0; i < 10; i++)
		delete(radixArrays[i]);
	delete(radixArrays);
	

}
//主要的运行逻辑
void run(int* numbers, int n)
{
	int command = 1;

	while (command != 9)
	{
		cout << "请选择排序算法:    ";
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
			cout << "冒泡排序所用时间:   " << float(finish - begin) / CLOCKS_PER_SEC << "秒" << endl;
			cout << "冒泡排序交换次数:   " << swapCount << endl;
		}
		break;
		case 2:
		{
			auto begin = clock();

			selectSort(numbers, n);

			auto finish = clock();
			check(numbers, n);
			cout << "选择排序所用时间:   " << float(finish - begin) / CLOCKS_PER_SEC << "秒" << endl;
			cout << "选择排序交换次数:   " << swapCount << endl;
		}
		break;
		case 3:
		{
			auto begin = clock();

			insertSort(numbers, n);

			auto finish = clock();
			check(numbers, n);
			cout << "直接插入排序所用时间:   " << float(finish - begin) / CLOCKS_PER_SEC << "秒" << endl;
			cout << "直接插入排序交换次数:   " << swapCount << endl;
		}
		break;
		case 4:
		{
			auto begin = clock();

			shellSort(numbers, n);

			auto finish = clock();
			check(numbers, n);
			cout << "希尔排序排序所用时间:   " << float(finish - begin) / CLOCKS_PER_SEC << "秒" << endl;
			cout << "希尔排序交换次数:   " << swapCount << endl;
		}
		break;
		case 5:
		{
			auto begin = clock();

			quickSort(numbers, 0, n - 1);

			auto finish = clock();
			check(numbers, n);
			cout << "快速排序所用时间:   " << float(finish - begin) / CLOCKS_PER_SEC << "秒" << endl;
			cout << "快速排序交换次数:   " << swapCount << endl;
		}
		break;
		case 6:
		{
			auto begin = clock();

			heapSort(numbers, n);

			auto finish = clock();

			check(numbers, n);
			cout << "堆排序所用时间:   " << float(finish - begin) / CLOCKS_PER_SEC << "秒" << endl;
			cout << "堆排序交换次数:   " << swapCount << endl;
		}
		break;
		case 7:
		{
			auto begin = clock();

			mergeSort(numbers, numbers+n);
			check(numbers, n);
			auto finish = clock();

			cout << "归并排序所用时间:   " << float(finish - begin) / CLOCKS_PER_SEC << "秒" << endl;
			cout << "归并排序交换次数:   " << swapCount << endl;
		}
		break;
		case 8:
		{
			auto begin = clock();
			radixSort(numbers, n);
			check(numbers, n);
			auto finish = clock();

			cout << "基数排序所用时间:   " << float(finish - begin) / CLOCKS_PER_SEC << "秒" << endl;
			cout << "基数排序交换次数:   " << swapCount << endl;
		}
		break;
		case 9:
			cout << "已经成功退出！" << endl;
			break;
		default:
			cout << "输入错误,请重新输入" << endl;
			break;

		}
	}
	delete numbers;
}
//主函数
int main()
{

	
	cout << "**\t\t\t  排序算法比较\t\t\t\t**\n";
	cout << "==================================================================\n";
	cout << "**\t\t\t1 --- 冒泡排序\t\t\t\t**\n";
	cout << "**\t\t\t2 --- 选择排序\t\t\t\t**\n";
	cout << "**\t\t\t3 --- 直接插入排序\t\t\t**\n";
	cout << "**\t\t\t4 --- 希尔排序\t\t\t\t**\n";
	cout << "**\t\t\t5 --- 快速排序\t\t\t\t**\n";
	cout << "**\t\t\t6 --- 堆排序\t\t\t\t**\n";
	cout << "**\t\t\t7 --- 归并排序\t\t\t\t**\n";
	cout << "**\t\t\t8 --- 基数排序\t\t\t\t**\n";
	cout << "**\t\t\t9 --- 退出程序\t\t\t\t**\n";
	cout << "==================================================================\n";
	
	cout << "请选择要产生的随机数的个数:" << endl;
	int n;
	cin >> n;
	auto numbers = getRandomNum(n);
	run(numbers, n);
	return 0;
}


