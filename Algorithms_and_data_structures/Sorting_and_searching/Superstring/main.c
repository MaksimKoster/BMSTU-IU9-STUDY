#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int Mass_Equal(char *string_1,char *string_2){
	long len1 = strlen(string_1),
	len2 = strlen(string_2);
	
	for(int i = 0; (i < len1) && (i < len2); i++)
		if (string_1[i] != string_2[i])
			return 0;
	return 1;
}


void Substring(char *str,char *arr, long beginIndex, long endIndex){
        int position = 0;
        for(long i = beginIndex; i < endIndex; i++){
                str[position] = arr[i];
                position++;
        }
}

void Merge_Strings(char **arr, int i, int j, int between){
	long len_top = strlen(arr[i]);
	long len_down = strlen(arr[j]);
	
	for(int p = 0; p < len_down - between; p++)
		arr[i][len_top + p] = arr[j][between + p];
	
	for (int k = 0; k < len_down; k++)
		arr[j][k] = '\0';
}

int Overlap(char **arr, int i_i, int j_j){
	long s1_last = strlen(arr[i_i]) - 1,
	s1_length = strlen(arr[i_i]),
	s2_length = strlen(arr[j_j]),
	overlap = 0;
	
	char *string_suff=(char*)malloc(100*sizeof(char));
	char *string_preff=(char*)malloc(100*sizeof(char));
	
	for(int j = 0; j < 100; j++){
		string_suff[j] = '\0';
		string_preff[j] = '\0';
	}
	
	for (long i = s1_last, j = 1; i > 0 && j < s2_length; i--, j++){
		Substring(string_suff, arr[i_i], i, s1_length);
		Substring(string_preff, arr[j_j], 0, j);
		if(Mass_Equal(string_preff, string_suff) == 1)
			overlap = j;
	}
        free(string_preff);
        free(string_suff);
                return (int)overlap;
}

void Call_Overlap (char **arr, int length, int count){
	if (count > 1){
		int max_overlap = 0,
		current_overlap,
		poisition_i = 0,
		poisition_j = 0;
		
		for (int i = 0; i < length; i++){
			for (int j = 0; j < length; j++){
				if (i != j){
					current_overlap = Overlap(arr, i, j);
					if(current_overlap > max_overlap){
						max_overlap = current_overlap;
						poisition_i = i;
						poisition_j = j;
					}
				}
			}
		}
		if ((poisition_i == 0) && (poisition_j == 0))
			Call_Overlap(arr, length, 0);
		else{
			Merge_Strings(arr,poisition_i, poisition_j, max_overlap);
			Call_Overlap(arr, length, count - 1);
		}
	}
}

void Super_string(char **arr, int length){
	Call_Overlap(arr, length, length);
}

int main(int argc, const char * argv[]){
	int length;
	int answer = 0;
	scanf("%d", &length);
	
	char **arr = (char**)malloc(length * sizeof(char*));
	for (int i = 0; i < length; i++){
		arr[i] = (char*)malloc(100 * sizeof(char));
		for(int j = 0; j < 100; j++){
			arr[i][j] = '\0';
		}
	}
	
	for (int i = 0; i < length; i++)
		scanf("%s", arr[i]);
	
	Super_string(arr, length);
	
	for (int i = 0; i < length; i++){
		printf("%s", arr[i]); //Суперстрока(Ура!)
		answer += strlen(arr[i]);
	}
	//printf("\n");
	//printf("%d\n", answer);
	
	for (int i = 0; i < length; i++)
		free(arr[i]);
	free(arr);
	return 0;
}
