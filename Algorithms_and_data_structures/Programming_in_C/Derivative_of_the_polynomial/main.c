#include <stdio.h>
int main(int argc, const char * argv[]){
	long sum = 0, coeff = 1, a, x_0;
	int n,k;
	scanf("%d %d %ld", &n,&k,&x_0);
	while (n > k - 1){
		scanf("%ld", &a);
		for (int i = n; i > n - k; --i)
			coeff = coeff * i;
		sum = sum * x_0 + coeff * a;
		coeff = 1;
		n--;
	}
	printf("%ld\n", sum);
	return 0;
}
