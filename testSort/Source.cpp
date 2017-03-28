#include <iostream>
using namespace std;
int counter = 0;

int split(int arr[], int first, int end) {
	int pivot;

	pivot = arr[first];
	int left = first, right = end;
	while (left < right) {//look for element to swap
		while (pivot < arr[right])//if > pivot then OK so skip
			right--;
		while (left < right && arr[left] <= pivot)	//if <= pivot then OK 
			left++;	//left <right to stop at cross point
		if (left < right)	//if not crossed then in wrong groups, swap
			swap(arr[left], arr[right]);
	}
	int pos = right;	//place pivot
	arr[first] = arr[pos];
	arr[pos] = pivot;
	//cout << " PIVOT  " << pivot << endl << endl;
	//for (int i = 0; i < 10; i++)
	//	cout << arr[i] << " " ;
	//cout << endl;
	return pos;
}


void quicksort(int arr[], int first, int last) {
	int pos;//know where pivot is from split

	for (int i = 0; i < 10; i++)
		cout << arr[i] << " ";
	cout << endl;
	cout << endl;
	if (first <last) {

		pos = split(arr, first, last);
		cout << "PIVOT: " << pos << endl << endl;
		
		quicksort(arr, first, pos - 1);	//split left and right groups
		quicksort(arr, pos + 1, last);

	}

}

void main() {

	int myArr[10] = { 5,3,7,6,4,1,8,2,9,0 };
	quicksort(myArr, 0, 9);

}