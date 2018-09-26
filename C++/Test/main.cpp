// C program to search and replace
// all occurrences of a word with
// other word.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to replace a string with another
// string
char *replaceChar(char *s, char oldChar, char newChar){
    int i, j = 0, cnt = 0;

    for(i = 0; i < strlen(s); i++) {
        if(s[i] == oldChar) {
            cnt++;
        }
    }

    char * result = (char *) malloc(strlen(s) - cnt);

    for(i = 0; i < strlen(s); i++) {
        if(s[i] != oldChar) {
            result[j] = s[i];
            j++;
        }
    }
    return result;
}

// Driver Program
int main(){
    char * originalStr = "A_B_C_D_E_F_G_H_I_J_K_L_M_N_O_P_Q_R_S_T_U_V_W_X_Y_Z";
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
