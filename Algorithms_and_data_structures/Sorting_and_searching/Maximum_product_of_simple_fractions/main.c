#include <stdio.h>
#include <math.h>

void Jay_Kadane_Algorithm(float *arr, long n){
	long l = 0, r = 0, start = 0, i = 0;
	float maxsum = arr[0], sum = 0;
	while (i < n){
		sum = sum + arr[i]; //log(x1/x2) + log(y1/y2) = log((x1*y1) / (x2*y2))
		if (sum > maxsum){
			maxsum = sum;
			l = start;
			r = i;
		}
		i++;
		if (sum < 0){
			sum = 0;
			start = i;
		}
	}
	printf("%ld %ld", l, r);
}

int main(int argc, const char * argv[]) {
	long length;
	scanf("%ld", &length);
	float arr[length];
	float x1, x2;
	for (int i = 0; i < length; i++){
		scanf("%f/%f", &x1, &x2);
		arr[i] = logf(x1) - logf(x2); //log (x) - log(y) = log(x/y);
	}
	Jay_Kadane_Algorithm(arr, length);
	printf("\n");
	return 0;
}
