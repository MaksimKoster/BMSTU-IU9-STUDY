#include <stdlib.h>
#include <stdio.h>

void bubblesort(unsigned long nel,int (*compare)(unsigned long i, unsigned long j),void (*swap)(unsigned long i, unsigned long j)){
	
	unsigned long last = nel - 1, first = 0;
	
	while (first < nel - 1){
		
		unsigned long bound_right = last,
		j = last,
		i = first,
		bound_left = first;
		last = 0;
		
		while (i < bound_right) {
			if (compare(i + 1, i) == -1) {
				swap(i + 1, i);
				last = i;
			}
			i++;
		}
		
		j = last;
		first = nel - 1;
		
		while (j > bound_left) {
			if (compare(j, j - 1) == -1) {
				swap(j - 1, j);
				first = j;
			}
			j--;
		}
	}
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
 
void bubblesort(unsigned long,
        int (*)(unsigned long, unsigned long),
        void (*)(unsigned long, unsigned long));
 
int main(int argc, char **argv)
{
        int i, n;
        scanf("%d", &n);
 
        array = (int*)malloc(n * sizeof(int));
        for (i = 0; i < n; i++) scanf("%d", array+i);
 
        bubblesort(n, compare, swap);
        for (i = 0; i < n; i++) printf("%d␣", array[i]);
        printf("\n");
 
        free(array);
        return 0;
}
