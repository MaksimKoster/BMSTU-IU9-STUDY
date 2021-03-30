#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void Swap(const void *a, const void *b, size_t width){
	
	char *mass_a =(char*)a;
	char *mass_b =(char*)b;
	char change;
	
	for (int i = 0; i < width; i++){
		change = mass_a[i];
		mass_a[i] = mass_b[i];
		mass_b[i] = change;
	}
}

int compare(const void *a, const void *b){
	
	char *mass_a =(char*)a;
	char *mass_b =(char*)b;
	int i = 0, count_a = 0, count_b = 0, flag_a = 0, flag_b = 0;
	
	while ((flag_a == 0) || (flag_b == 0)){
		if (flag_a == 0){
			if (mass_a[i] == '\0')
				flag_a = 1;
			else{
				if (mass_a[i] == 'a')
					count_a++;
			}
		}
		if (flag_b == 0){
			if (mass_b[i] == '\0')
				flag_b = 1;
			else{
				if (mass_b[i] == 'a')
					count_b++;
			}
		}
		i++;
	}
	
	if (count_a == count_b)
		return 0;
	
	return count_a < count_b ? 1 : -1;
}


void Heapify(void *base, size_t i, size_t n, size_t width)
{
	while(1){
		long l = 2*i + 1,
		r = l + 1,
		j = i;
		
		if ((l < n) && (compare(base + i*width,base + l*width) == 1))
			i = l;
		if ((r < n) && (compare(base + i*width,base + r*width) == 1))
			i = r;
		if (i == j)
			break;
		Swap(base + i*width, base + j*width, width);
	}
}

void Build_Heap(void *base, size_t n, size_t width){
	
	long i = floor(n/2) - 1;
	while (i >= 0) {
		Heapify(base, i, n, width);
		i--;
	}
}

void Heap_Sort(void *base, size_t nel, size_t width,
        int (*compare)(const void *a, const void *b)){
	
	Build_Heap(base, nel, width);
	long i = nel - 1;
	while (i > 0) {
		Swap(base, base + i*width, width);
		Heapify(base, 0, i , width);
		i--;
	}
}

int main(int argc, const char * argv[]) {
	
	long length;
	scanf("%ld", &length);
	char arr[length][200];
	
	for(int i = 0; i < length; i++)
		scanf("%s", arr[i]);
	
	Heap_Sort(arr, length, 200, compare);
	
	for(int i = 0; i < length; i++)
	printf("%s\n", arr[i]);
	
    return 0;
}
