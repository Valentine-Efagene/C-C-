// C program to search and replace
// all occurrences of a word with
// other word.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *replaceChar(char *s, char charToReplace, char replacement){
    char * result = (char *) malloc(strlen(s));
    int i = 0;

    for(i = 0; i < strlen(s); i++) {
        if(s[i] == charToReplace) {
            result[i] = '_';
        }else{
            result[i] = s[i];
        }
    }
    return result;
}

int main(){
    int i;

    for(i = 33; i < 127; i++){
        printf("%c", (char)i);
    }
    return 0;
}


