# include <stdio.h>
# include <string.h>
# include <ctype.h>
# include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAXLEN 80
#define EOT 4
int isPalindrome(char s[]);
int getLineFile(char s[], int len, FILE* f);
int getLine(char s[], int len);
void getFilePath(char path[], int len);
int getInputMethod();

int main() {
    int inputMode, index, isMirror;
    char s[MAXLEN];
    char path[MAXLEN];
    FILE * fp;
    inputMode = getInputMethod();
    switch (inputMode)
    {
    case 1: /*keyboard*/
        printf("to end program input `stop`, `ctrl+d` or `-1`.\n");
        do {
            index = getLine(s, MAXLEN);
            printf("the string received is: %s\n", s);
            isMirror = isPalindrome(s);
            printf("the string: \"%s\" is %s palindrome\n", s, (isMirror) ? "a" : "not a");
        } while (strcmp(s, "stop") && index != EOF);
        break;
    case 2: /*file*/
        getFilePath(path, MAXLEN);
        fp = fopen(path, "r");
        if (NULL != fp) {
            do {
                index = getLineFile(s, MAXLEN, fp);
                printf("the string received is: %s\n", s);
                isMirror = isPalindrome(s);
                printf("the string: \"%s\" is %s palindrome\n", s, (isMirror) ? "a" : "not a");
            } while (strcmp(s, "stop") && index != EOF);  
        }
        else {
            printf("error: file pointer of path \"%s\" is NULL\n", path);
            exit(1);
        }
        if (fp != NULL) {
            fclose(fp);
        } 
        break;
    default:
        printf("how?\n");
        exit(-1);
    }
    return 0;
}

int isPalindrome(char s[]) {
    /*checks if char s[] is a palindrome ignores white spaces*/
    int i ,j, res, check;
    res = TRUE;                             /*result to be returned. initialized TRUE, we assume that s[] is 
                                            palindrome because it's easier to check if s[] is not a palindrome*/
    i = 0;                                  /*i will point to the beginning of the s[]*/
    j = strlen(s)-1;                        /*j will point to the last char before the null terminator*/
    if (i == j || s[i] == '\0') {
        res = FALSE;
    }
    while (i < j && res) {                  /*check if i<j to brake once the mid point is reached. check res to break if we have conclusive result*/
        check = TRUE;                       /*check is initialized every round to TRUE then modified to FALSE if s[i] or s[j] is space*/
        if (isspace(s[i])) {                /*check if s[i] is a space char*/
            i++;                            /*skipping the space*/
            check = FALSE;                  /*there is no need to check because s[i] is a space character*/
        }           
        if (isspace(s[j])) {                /*check if s[j] is a space char*/
            j--;                            /*skipping the space*/
            check = FALSE;                  /*there is no need to check because s[i] is a space character*/
        }
        if (check && s[i] != s[j]) {        /*if both positions are non-whitespace chars check if they are equal*/
            res = FALSE;                    /*if they are not this string is not a palindrome*/
        }
        else if (check && s[i] == s[j]) {   /*if characters in both positions are equal we move on to next char*/
            i++;
            j--;
        }
    }
    return res;
}

int getInputMethod() { 
    /*input method menu*/
    int c = 0;
    printf("choose the desired input method:\n");
    do {
        printf("1. for keyboard.\n");
        printf("2. for file.\n");
        c = getchar();
        getchar();
    } while (c != '1' && c != '2');
    return c - '0';
}

int getLineFile(char s[], int len, FILE* f) {
    int i = 0, ret;
    while (i < len && (s[i] = fgetc(f)) != EOF && s[i] != '\n') {
        i++;
    }
    if (s[i] == EOF) {
        ret = EOF;
    }
    else {
        ret = 0;
    }
    if (i == len) {
        s[i-1] ='\0';
    }
    else {
        s[i] = '\0';
    }
    return ret;
}

void getFilePath(char path[], int len) {
    int i = 0;
    printf("enter path to file: ");
    while (i < len && (path[i] = getchar()) != EOF 
                && path[i] != EOT && path[i] != '\n') {
        i++;
    }
    if (i == len) {
        path[i-1] ='\0';
    }
    else {
        path[i] = '\0';
    }
    return; 
}

int getLine(char s[], int len) {
    int i = 0, ret;
    while (i < len && (s[i] = getchar()) != EOF && s[i] != '\n' && s[i] != EOT) {
        i++;
    }
    if (s[i] == EOF || s[i] == EOT) {
        ret = EOF;
    }
    else {
        ret = 0;
    }
    if (i == len) {
        s[i-1] ='\0';
    }
    else {
        s[i] = '\0';
    }
    return ret;
}