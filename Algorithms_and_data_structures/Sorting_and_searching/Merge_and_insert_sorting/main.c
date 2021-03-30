#include <stdio.h>
#include <math.h>
#include <stdlib.h>
 
void Insert_Sort(long begin,long end, long *arr){
        long i = begin + 1;
              while (i <= end){
                      long loc = i - 1;
                      while ( (loc >= begin) && (labs(arr[loc+1]) < labs(arr[loc])) ){
                              long change = arr[loc+1];
                              arr[loc+1] = arr[loc];
                              arr[loc] = change;
                              loc--;
                      }
              i++;
              }
}

void Merge(long k, long l, long m, long *arr){
        long help_arr[m - k + 1];
        long i = k;
        long j = l + 1;
        long h = 0;
        while (h < m - k + 1) {
                if ( (j <= m) && ((i == l + 1) || (labs(arr[j]) < labs(arr[i]))) ){
                        help_arr[h] = arr[j];
                        j++;
                }
                else{
                        help_arr[h] = arr[i];
                        i++;
                }
                h++;
        }
        for (long i = k; i<= m; i++)
                arr[i] = help_arr[i - k];
}

void Merge_Sort_Rec(long low, long high, long *arr){
	long med = floor((high - low) / 2);
	if (med < 5){
		Insert_Sort(low, med, arr);
		Insert_Sort(med + 1, high, arr);
	}
	else{
		Merge_Sort_Rec(low, med, arr);
		Merge_Sort_Rec(med + 1, high, arr);
	}
	Merge(low, med, high, arr);
}

void Merge_Sort(long n, long *arr){
	Merge_Sort_Rec(0, n - 1, arr);
}

int main(int argc, const char * argv[]) {
        long length;
        scanf("%ld", &length);
        long arr[length];
        for (int i = 0; i < length; i++)
                scanf("%ld", &arr[i]);
        Merge_Sort(length, arr);
        for (int i = 0; i < length; i++)
                printf("%ld ", arr[i]);
        printf("\n");
    return 0;
}
