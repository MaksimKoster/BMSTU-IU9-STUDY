#include  <stdio.h>
#include  <string.h>
int strdiff(char *a, char *b){
	int
	len_1 = strlen(a),
	len_2 = strlen(b);
	
	for (unsigned long i = len_1; i < 1000; i++)
		a[i] = '\0';
	
	for (unsigned long i = len_2; i < 1000; i++)
		b[i] = '\0';
	
	for (int i = 0; i < len_1 || i < len_2; i++){
		if (a[i] != b[i]){
			for (int j = 0; j < 8; j++){
				int
				bit_a = a[i] & (1<<j),
				bit_b = b[i] & (1<<j);
				
				if (bit_a != bit_b)
					return i * 8 + j;
			}
		}
	}
	return -1;
}

int strdiff(char *a, char *b);

int main(int argc, char **argv)
{
        char s1[1000], s2[1000];
        gets(s1);
        gets(s2);
        printf("%d\n", strdiff(s1, s2));

        return 0;
}

