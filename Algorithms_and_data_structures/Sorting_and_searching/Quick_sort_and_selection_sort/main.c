#include <stdio.h>

void Select_Sort(long low, long high ,long *arr){
	long j = high - 1;
	while (j > low){
		long k = j;
		long i = j - 1;
		while (i >= 0){
			if (arr[k] < arr[i])
				k = i;
			i--;
		}
		long change = arr[j];
		arr[j] = arr[k];
		arr[k] = change;
		j--;
	}
}

long Partition(long low, long high,long *arr){
	long i = low;
	long j = low;
	while (j < high) {
		if (arr[j] < arr[high]){
			long change = arr[i];
			arr[i] = arr[j];
			arr[j] = change;
			i++;
		}
		j++;
	}
	long change_1 = arr[i];
	arr[i] = arr[high];
	arr[high] = change_1;
	return i;
}
		

void Quick_Sort_Rec(long low, long high,long m, long *arr){
	while(low < high){
		if ((high - low) <= m){
			Select_Sort(low, high, arr);
		}
		long q = Partition(low, high, arr);
		if ((q-low) < (high-q)){
                        Quick_Sort_Rec(low, q-1, m, arr);
                        low = q+1;
		}
                else{
                        Quick_Sort_Rec(q+1, high, m, arr);
                        high = q-1;
		}
	}
}

void Quick_Sort(long n,long m, long *arr){
	Quick_Sort_Rec(0, n - 1, m, arr);
}

int main(int argc, const char * argv[]) {
	long length, m;
	scanf("%ld", &length);
	long arr[length];
	scanf("%ld", &m);
	for (int i = 0; i < length; i++)
		scanf("%ld", &arr[i]);
	Quick_Sort(length, m, arr);
	for (int i = 0; i < length; i++)
		printf("%ld ", arr[i]);
	printf("\n");
	return 0;
    }
