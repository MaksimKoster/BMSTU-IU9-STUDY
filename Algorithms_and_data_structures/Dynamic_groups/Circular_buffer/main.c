#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Buff{
	long *data;
	int cap;
	int count;
	int head;
	int tail;
} a;

void Buff_empty(struct Buff *a){
	if (a->count == 0)
		printf("true\n");
	else
		printf("false\n");
}
void New_buff(struct Buff *a){
	int old_len = a->cap,
	i,j;
	a->cap *= 2;
	long *New = (long*)malloc((a->cap)*sizeof(long));
	
	for(i = 0; i < (old_len - a->head); i++)
		New[i] = a->data[a->head + i];
	
	a->head = 0;
	
	for(j = 0; j < a->tail; j++)
		New[j+i] = a->data[j];
	
	a->tail = j+i;
	
	free(a->data);
	a->data = New;
	
}

void Buff_enq(long x, struct Buff *a){
	if (a->count == a->cap)
		New_buff(a);
	a->data[a->tail] = x;
	a->tail++;
	if (a->tail == a->cap)
		a->tail = 0;
	a->count++;
}

void Buff_deq(struct Buff *a){
	long x = a->data[a->head];
	a->head++;
	if (a->head == a->cap)
		a->head = 0;
	a->count--;
	printf("%ld\n", x);
}
void First_initialize(int n){
	a.data = (long*)malloc(n * sizeof(long));
	a.cap = n;
	a.count = 0;
	a.head = 0;
	a.tail = 0;
}

int main(int argc, const char * argv[]){
	
	long num_comm, x;
	char command[5];
	
	scanf("%ld", &num_comm);
	First_initialize(4);
	
	for (int i = 0; i < num_comm; i++){
		
		scanf("%s", command);
		
		if (strcmp(command, "ENQ") == 0){
			scanf("%ld", &x);
			Buff_enq(x, &a);
		}
		
		if (strcmp(command, "DEQ") == 0)
			Buff_deq(&a);
		
		if (strcmp(command, "EMPTY") == 0)
			Buff_empty(&a);
	}
	free(a.data);
	return 0;
}

