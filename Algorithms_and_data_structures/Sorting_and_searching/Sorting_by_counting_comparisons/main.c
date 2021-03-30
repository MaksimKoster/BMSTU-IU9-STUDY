#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void csort(char *src, char *dest){
        
        int count_word = 0;
        long length = strlen(src);
        
        for (int i = 0; i < length; i++) {  //Подсчет слов
                if ( (src[i] != 32) && ((src[i + 1] == 32) || (src[i + 1] == '\0')) )
                        count_word++;
        }
        
        int words_length [count_word];
        int word_len = 0, index = 0;
        
        for(int i = 0; i < length; i++){ //Занесение длины слов в массив words_length
                if (src[i] != 32)
                        word_len++;
                if ( (src[i] != 32) && ((src[i + 1] == 32) || (src[i + 1] == '\0')) ){
                        words_length[index] = word_len;
                        word_len = 0;
                        index++;
                }
        }
        
        int count[count_word];
        int i , j = 0;
        for (int i = 0; i < count_word; i++)
                count[i] = 0;
        while (j < count_word - 1){
                i = j + 1;
                while (i < count_word){
                        if (words_length[i] < words_length[j])
                                count[j] += words_length[i] + 1;
                        else
                                count[i] += words_length[j] + 1;
                        i++;
                }
                j++;
        }
        //for(i = 0; i < count_word; i++)  //Проверка на индексацию
        //       printf("%d ", count[i]);
        
        for(i = 0, index = 0; i < length; i++) {
                if (src[i] != 32) {
                        for (j = 0; j < words_length[index]; j++)
                                dest[count[index] + j] = src[i+j];
                        i += words_length[index];
                        index++;
                }
        }
}

int main(int argc, char **argv){
        
        char sentence[500];
        gets(sentence);
        long count_letters = 0, count_space = 0;
        
        for(int i = 0; sentence[i] != '\0' ; i++){
                if (sentence[i] != 32) //Считаю количество всех charov
                        count_letters++;
                if ( (sentence[i] != 32) && ((sentence[i + 1] == 32) || (sentence[i + 1] == '\0')) ) //Cчитаю пробелы между словами(чтобы потом между ними был 1 пробел)
                        count_space++;
        }
        
        char dest[count_space + count_letters];
        for (int i = 0; i < count_space + count_letters; i++) //Заполнение пробелами
                dest[i] = 32;
        dest[count_space + count_letters] = '\0'; //Конец строки
       
        csort(sentence, dest);
        for (int i = 0; i < count_space + count_letters - 1; i++)
                printf("%c", dest[i]);
        printf("\n");
    return 0;
}
