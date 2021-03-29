#include  <stdio.h>

int array[] = { 1, 2, 3, 4, 5, 3, 2, -5 };

int less(unsigned long i, unsigned long j)
{
        return array[i]  < array[j];
}

unsigned long peak(unsigned long nel,int (*less)(unsigned long i, unsigned long j)){
	unsigned long first = 0, last = nel - 1, middle;
	while (first < last){
		middle = (first + last) / 2;
		if (less(middle, middle + 1)){
			first = middle + 1;
		}
		else{
			if (less(middle, middle - 1)){
				last = middle - 1;
			}
			else{
				return middle;
			}
		}
	}
     return first;
}
    
    
    
unsigned long peak(unsigned long,int (*)(unsigned long, unsigned long));

int main(int argc, char  **argv){
        unsigned long i = peak(8, less);
        if ((i == 0 || array[i]  >= array[i-1]) &&
                (i == 7 || array[i]  >= array[i+1])) {
                printf("CORRECT\n");
        } else {
                // Если функция peak работает правильно,сюда никогда не будет передано управление!
                printf("WRONG\n");
        }
        return 0;
}
