#include  <stdio.h>

int array[] = { 1, 2, 30, 45, 50, 51, 55, 60 };
const int k = 51;

unsigned long binsearch(unsigned long nel, int (*compare)(unsigned long i))
{
	unsigned long first = 0, last = nel - 1, middle;
	while (first <= last){
		middle = (first + last) / 2;
		if (compare(middle) == 1)
			last = middle - 1;
		else{
			if(compare(middle) == -1)
				first = middle + 1;
			else
				return middle;
		}
	}
	return nel;
}

int compare(unsigned long i)
{
        if (array[i] == k) return 0;
        if (array[i]  < k) return -1;
        return 1;
}

unsigned long binsearch(unsigned long, int (*)(unsigned long));

int main(int argc, char  **argv)
{
        printf("%lu\n", binsearch(8, compare));
        return 0;
}
