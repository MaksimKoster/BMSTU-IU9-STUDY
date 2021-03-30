#include <stdlib.h>
#include <stdio.h>

long FIB_NUMBER(unsigned long length){
	long arr[length + 1];
	arr[0] = 0;
	arr[1] = 1;
	arr[2] = 1;
	long number = 0;
	int flag = 0;
	int i = 2;
	while((i < length + 1) && (flag == 0)){
		arr[i] = arr[i-1] + arr[i-2];
		if ((arr[i] < length) && (arr[i] > number))
			number = arr[i];
		else
			flag = 1;
		i++;
	}
	return number;
}

void shellsort(unsigned long nel,
        int (*compare)(unsigned long i, unsigned long j),
        void (*swap)(unsigned long i, unsigned long j))
{
	for (long step = FIB_NUMBER(nel); step > 0; step = FIB_NUMBER(step))
		for (long i = step; i < nel; i++)
			for(long j = i - step; j>=0 && (compare(j, j + step) == 1); j-=step)
				swap(j, j + step);
}

 
int *array;
 
int compare(unsigned long i, unsigned long j)
{
        if (i <= j) {
                printf("COMPARE␣%d␣%d\n", i, j);
        } else {
                printf("COMPARE␣%d␣%d\n", j, i);
        }
 
        if (array[i] == array[j]) return 0;
        return array[i] < array[j] ? -1 : 1;
}
 
void swap(unsigned long i, unsigned long j)
{
        if (i <= j) {
                printf("SWAP␣%d␣%d\n", i, j);
        } else {
                printf("SWAP␣%d␣%d\n", j, i);
        }
 
        int t = array[i];
        array[i] = array[j];
        array[j] = t;
}
 
void shellsort(unsigned long,
        int (*)(unsigned long, unsigned long),
        void (*)(unsigned long, unsigned long));
 
int main(int argc, char **argv)
{
        int i, n;
        scanf("%d", &n);
 
        array = (int*)malloc(n * sizeof(int));
        for (i = 0; i < n; i++) scanf("%d", array+i);
 
        shellsort(n, compare, swap);
        for (i = 0; i < n; i++) printf("%d␣", array[i]);
        printf("\n");
 
        free(array);
        return 0;
}
