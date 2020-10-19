#include  <stdio.h>

unsigned char array[] = {
	153,
	1,
	15,
	191,
	232,
	251,
	27,
	174,
	26,
	3,
	68,
	48
};

int compare(void *a, void *b)
{
	return (int)(*(unsigned char*)a) - (int)(*(unsigned char*)b);
}
int maxarray(void  *base, unsigned long nel, unsigned long width,
	     int (*compare)(void *a, void *b))
{
	void *massive = base;
	void *max = massive;
	int position = 0;
	for (int i = 1; i < nel; i++)
		if ((compare(max, massive + i * width) == -1)){
			max = massive + i * width;
			position = i;
		}
	return position;
}

int maxarray(void*, unsigned long, unsigned long,
        int (*)(void  *a, void  *b));

int main(int argc, char  **argv)
{
        printf("%d\n", maxarray(array, 5, sizeof(int), compare));
        return 0;
}
