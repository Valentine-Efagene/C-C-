// C program to search and replace
// all occurrences of a word with
// other word.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to replace a string with another
// string
char *replaceChar(char *s, char oldChar, char newChar){
    int i;
    char * result = (char *) malloc(strlen(s));

    for(i = 0; i < strlen(s); i++) {
        if(s[i] == oldChar) {
            result[i] = newChar;
        }else{
            result[i] = s[i];
        }
    }
    return result;
}

// Driver Program
int main(){
    char * originalStr = "AASFESVDSVSD";
    char c = 'A';
    char d = '_';
    char * result;

    // oldW string
    printf("Old string: %s", originalStr);

    result = replaceChar(originalStr, c, d);
    printf("New String: %s", result);

    free(result);
    return 0;
}
