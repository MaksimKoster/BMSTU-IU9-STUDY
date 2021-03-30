#include <stdio.h>
#include <stdlib.h>

struct Task {
        int low, high;
}a;

void Swap(int i, int j, int *arr){
	arr[i] = arr[i] + arr[j] - (arr[j] = arr[i]);
}

int Partition(int *arr, struct Task *a){
	int x = arr[a->high];
	int i = (a->low - 1);
	
	for (int j = a->low; j < a->high; j++) {
		if (arr[j] <= x) {
			i++;
			Swap(i,j, arr);
		}
	}
	Swap(i + 1, a->high, arr);
	return (i + 1);
}

void QuickSort(int *arr, struct Task *a, int length){
	int stack [length];
	int top = -1;
	
	stack[++top] = a->low;
	stack[++top] = a->high;
	
	while(top >= 0){
		a->high = stack[top--];
		a->low = stack[top--];
		
		int p = Partition(arr, a);
		
		if (p - 1 > a->low) {
		    stack[++top] = a->low;
		    stack[++top] = p - 1;
		}
		
		if (p + 1 < a->high) {
		    stack[++top] = p + 1;
		    stack[++top] = a->high;
		}
	}
}

int main(int argc, char **argv){
	int length;
	scanf("%d", &length);
	
	int arr[length];
	for(int i = 0; i < length; i++)
		scanf("%d", &arr[i]);
	
	a.high = length - 1;
	a.low = 0;
	
	QuickSort(arr, &a, length);
	
	for(int i = 0; i < length; i++)
		printf("%d ", arr[i]);
	
	printf("\n");
	return 0;
}
