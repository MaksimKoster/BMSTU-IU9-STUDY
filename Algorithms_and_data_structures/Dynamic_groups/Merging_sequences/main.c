#include <stdio.h>
#include <stdlib.h>

struct PriorityQueue {
    long *heap;
    long cap,
    count;
};

void Swap(struct PriorityQueue *a, long x ,long y){
    a->heap[x] = a->heap[x] + a->heap[y] - (a->heap[y] = a->heap[x]);
}


void Insert(struct PriorityQueue *a, long x){
	long i = a->count;
	if (i == a->cap)
		printf("Error");
	a->count = i + 1;
	a->heap[i] = x;
	while (i > 0 && (a->heap[(i - 1) / 2]) > a->heap[i]){
		Swap(a, (i - 1) / 2, i);i = (i - 1) / 2;
	}
}

void Heapify(long i, long n, struct PriorityQueue *a){
	while (1){
		long l = 2 * i + 1,
		r = l + 1,
		j = i;
		
		if (l < n && a->heap[i] > a->heap[l])
			i = l;
		if (r < n && a->heap[i] > a->heap[r])
			i = r;
		if (i == j)
			break;
		Swap(a, i, j);
	}
}

long Extract_Min(struct PriorityQueue *a){
	if (a->count == 0)
		printf("Empty");
	long x = a->heap[0];
	a->count--;
	if (a->count > 0) {
		a->heap[0] = a->heap[a->count];
		Heapify(0, a->count, a);
	}
	return x;
}

int main(int args, char **argv){
	
	long number_arrays,
	element,
	result_mass = 0;
	
	scanf("%ld", &number_arrays);

	long *size_of_arrays = (long*)malloc(number_arrays * sizeof(long));
	
	for (int i = 0; i < number_arrays; i++){
		scanf("%ld", &size_of_arrays[i]);
		result_mass += size_of_arrays[i];
	}
	
	long *answer = (long*)malloc(result_mass * sizeof(long));
	
	struct PriorityQueue a;
	a.heap = malloc(result_mass * sizeof(long));
	a.count = 0;
	a.cap = result_mass;
	
	for (int i = 0; i < number_arrays; i++){
		for (int j = 0; j < size_of_arrays[i]; j++){
			scanf("%ld", &element);
			Insert(&a, element);
		}
	}
	
	free(size_of_arrays);
	
	for(int i = 0; i < result_mass; i++)
		answer[i] = Extract_Min(&a);
	
	free(a.heap);
	
	for(int i = 0; i < result_mass; i++)
		printf("%ld ",answer[i]);
	
	free(answer);
	return 0;
}
