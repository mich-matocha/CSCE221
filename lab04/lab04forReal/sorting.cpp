#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

long int swaps;
long int comparisons;

bool compare(int one, int two)
{
	comparisons++;
	if(one < two)
		return true;
	else
		return false;
}

//selection sort
void selectionSort(int *items, int size)
{
	int max;

	for(int i = size - 1; i > 0; --i)
	{
		int holder;
		max = i;
		for(int j = 0; j < i; ++j)
		{
			if(!compare(items[j], items[max]))
			{
				max = j;
			}
		}
		if(max != i)
		{
			holder = items[max];
			items[max] = items[i];
			items[i] = holder;
			swaps += 3;
		}
	}
}

//insertion sort
void insertionSort(int *items, int size)
{
	for(int i = 0; i < size -  1; ++i)
	{
		int j = i - 1;
		int holder = items[i];
		while(j >= 0 and compare(holder, items[j]))
		{
			items[j + 1] = items[j];
			swaps++;
			j = j - 1;
		}
		items [j + 1] = holder;
		swaps++;
	}
}

//bubble sort
void bubbleSort(int *items, int size) //doesn't work...
{
	int holder;
	for(int i = 0; i < size - 1; ++i)
	{
		for(int j = size - i; j > 0; --j)
		{
			if(compare(items[j], items[j - 1]))
			{
				holder = items[j];
				items[j] = items[j - 1];
				items[j - 1] = holder;
				swaps += 3;
			}
		}
	}
}

//merge sort helper
void merge(int *items, int size, int left, int middle, int end) //getting a seg fault
{
	//setting where each sub array starts and ends
	int lIndex = left;
	int rIndex = middle + 1;
	int leftEnd = middle;
	int rightEnd = end;

	int temps[size];

	//copy items into temps
	for(int i = 0; i < size; ++i)
	{
		temps[i] = items[i];
	}

	int k = lIndex;

	while(lIndex <= leftEnd && rIndex <= rightEnd)
	{
		if(compare(items[lIndex], items[rIndex]))
		{
			items[k] = temps[lIndex];
			lIndex++;
			swaps++;
		}
		else
		{
			items[k] = temps[rIndex];
			rIndex++;
			swaps++;
		}
		k++;
	}

	while(lIndex <= leftEnd)
	{
		items[k] = temps[lIndex];
		k++;
		swaps++;
		lIndex++;
	}

	while(rIndex <= rightEnd)
	{
		items[k] = temps[rIndex];
		k++;
		swaps++;
		rIndex++;
	}
}

//merge sort
void mergeSort(int *items, int size, int left, int right)
{
	int mid;
	if(right - left >= 1)
	{
		mid = (left + right) / 2;
		mergeSort(items, size, left, mid);
		mergeSort(items, size, mid + 1, right);
		merge(items, size, left, mid, right);
	}

}

int partition(int *items, int lowest, int highest)
{
	int pivot = items[highest];

	int i = lowest - 1;
	int holder;

	for (int j = lowest; j <= highest - 1; j++)
	{
		if(items[j] <= pivot)
		{
			i++;
			holder = items[i];
			items[i] = items[j];
			items[j] = holder;
			swaps += 3;
		}
	}

	holder = items[i + 1];
	items[i + 1] = items[highest];
	items[highest] = holder;
	swaps += 3;

	return i + 1;
}

//quick sort
void quickSort(int * items, int lowest, int highest)
{
	int partIndex;
	if(compare(lowest, highest))
	{
		partIndex = partition(items, lowest, highest);

		quickSort(items, lowest, partIndex - 1);
		quickSort(items, partIndex + 1, highest);
	}
}

int main()
{
	//starting timer
	clock_t timer;
	timer = clock();

	//read in what sort to be done, the length of the array, and the data points
	ifstream file;
	file.open("numbers.txt");
	int sortValue;
	int length;

	//reading parameters for sort from the file
	file >> sortValue >> length;

	int values[length];

	for(int i = 0; i < length; ++i)
	{
		file >> values[i];
	}

	file.close();

	switch(sortValue)
	{
		case 1:
			cout << "selection" << endl;
			selectionSort(values, length);
			break;
		case 2:
			cout << "insertion" << endl;
			insertionSort(values, length);
			break;
		case 3:
			cout << "bubble" << endl;
			bubbleSort(values, length);
			break;
		case 4:
			cout << "merge" << endl;
			mergeSort(values, length, 0, length - 1);
			break;
		case 5:
			cout << "quick" << endl;
			quickSort(values, 0, length - 1);
			break;
	}

	cout << "Number of swaps: " << swaps << endl;
	cout << "Number of comparisons: " << comparisons << endl;

	//outputting sorted array to a .txt file
	ofstream out;
	out.open("sortedNums.txt");

	for(int i = 0; i < length; ++i)
	{
		out << values[i] << endl;
	}
	out.close();

	//stopping timer
	long double time;
	time = (clock() - timer) / (double) CLOCKS_PER_SEC;
	cout << "Time elapsed: " << time << endl;

	return 0;
}
