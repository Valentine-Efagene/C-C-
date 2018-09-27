#ifndef KEYBOARDTESTER_H_INCLUDED
#define KEYBOARDTESTER_H_INCLUDED

#include <tchar.h>
#include <windows.h>
#include <stdio.h>

HWND textField;

char *replaceWord(const char *s, const char *oldW, const char *newW){
    char *result;
    int i, cnt = 0;
    int newWlen = strlen(newW);
    int oldWlen = strlen(oldW);

    // Counting the number of times old word
    // occur in the string
    for (i = 0; s[i] != '\0'; i++){
        if (strstr(&s[i], oldW) == &s[i]){
            cnt++;
            // Jumping to index after the old word.
            i += oldWlen - 1;
        }
    }

    // Making new string of enough length
    result = (char *)malloc(i + cnt * (newWlen - oldWlen) + 1);

    i = 0;
    while (*s){
        // compare the substring with the result
        if (strstr(s, oldW) == s){
            strcpy(&result[i], newW);
            i += newWlen;
            s += oldWlen;
        }
        else
            result[i++] = *s++;
    }

    result[i] = '\0';
    return result;
}

void display(char * str, HWND hwnd){
    textField = CreateWindow("STATIC",
                             str,
                             WS_VISIBLE|WS_CHILD|WS_BORDER,
                             20, 20, 1000, 100,
                             hwnd, NULL, NULL, NULL);
}

char *replaceChar(char *s, char charToReplace){
    int i, j = 0, cnt = 0;

    for(i = 0; i < strlen(s); i++) {
        if(s[i] == charToReplace) {
            cnt++;
        }
    }

    char * result = (char *) malloc(strlen(s) - cnt);

    for(i = 0; i < strlen(s); i++) {
        if(s[i] != charToReplace) {
            result[j] = s[i];
            j++;
        }
    }
    return result;
}

char *replaceChar(char *s, char charToReplace, char replacement){
   char * result = (char *) malloc(strlen(s));
    int i = 0;

    for(i = 0; i < strlen(s); i++) {
        if(s[i] == charToReplace) {
            result[i] = replacement;
        }else{
            result[i] = s[i];
        }
    }
    return result;
}


#endif // KEYBOARDTESTER_H_INCLUDED
