#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int Peak(int i, int* array, int length){
        
        if (length == 1)
                return 1;
        if (i == 0 && array[i] >= array[i + 1])
                return 1;
        if (i == length - 1 && array[i] >= array[i - 1])
                return 1;
        if (i > 0 && i < length - 1 && array[i] >= array[i - 1] && array[i] >= array[i + 1])
                return 1;
        
        return 0;
}

void Build(int* array,int length, int i, int a, int b, int* tree){
        
        if (a == b)
                tree[i] = Peak(a, array, length);
        else {
                int m = floor((a+b)/2);
        Build(array, length, i * 2 + 1, a, m, tree);
                Build(array, length,i * 2 + 2, m + 1, b, tree);
                tree[i] = tree[i * 2 + 1] + tree[i * 2 + 2];
        }
}

int Query(int* tree, int i, int l, int r, int a, int b){
        
        if (l == a && r == b)
                return tree[i];
        
        int m = floor((a+b)/2);
        
        if (r <= m)
                return Query(tree, i * 2 + 1, l, r, a, m);
        if (l > m)
                return Query(tree, i * 2 + 2, l, r, m + 1, b);
        
        return Query(tree, i * 2 + 1, l, m, a, m) + Query(tree, i * 2 + 2, m + 1, r, m + 1, b);
}

void Update(int* tree, int* array, int length, int j, int i, int a, int b){
        
        if (a == b)
                tree[i] = Peak(j, array, length);
        else {
                int m = floor((a+b)/2);
                
                if (j <= m)
                        Update(tree, array, length, j, i * 2 + 1, a, m);
                else
                        Update(tree, array, length, j, i * 2 + 2, m + 1, b);
                
                tree[i] = tree[i * 2 + 2] + tree[i * 2 + 1];
        }
}



void SegmentTree_Update(int* tree, int* array, int length, int i){
        Update(tree, array, length, i, 1, 0, length - 1);
}

int SegmentTree_Query(int *tree,int l,int r,int length){
        return Query(tree, 1, l, r, 0, length);
}

void SeqmentTree_Build(int* array, int length, int* tree){
          Build(array, length, 1, 0, length - 1, tree);
}

int main(int argc, const char * argv[]){
        
        int length,
        count_commands,
        count = 0;
        
        scanf("%d", &length);
        int* array = (int*)malloc(length * sizeof(int));
        int* tree = (int*)malloc(6 * length * sizeof(int));
        
        for (int i = 0; i < length; i++)
                scanf("%d", &array[i]);
        
        SeqmentTree_Build (array, length, tree);
        
        scanf("%d", &count_commands);
        int* answer = (int*)malloc(count_commands * sizeof(int));
        
        char Command[5];
        
        for (int i = 0; i < count_commands; i++){
               
                for (int k = 3; k < 5; k++)
                        Command[k] = '\0';
                
                scanf("%s", Command);
                
                if (strcmp(Command, "PEAK") == 0){
                        int l, r;
                        scanf("%d %d", &l, &r);
                        answer[count] = SegmentTree_Query(tree, l, r, length - 1);
                        count++;
                }
                
                if (strcmp(Command, "UPD") == 0){
                        int i, value;
                        scanf("%d %d", &i, &value);
                        array[i] = value;
                        SegmentTree_Update(tree, array, length, i);
            
            if (i > 0)
                SegmentTree_Update(tree, array, length, i - 1);
            if (i < length - 1)
                SegmentTree_Update(tree, array, length, i + 1);
        }
    }

        for (int i = 0; i < count; i++)
                printf("%d\n", answer[i]);
        
        free(array);
        free(tree);
        free(answer);
        return 0;
}


