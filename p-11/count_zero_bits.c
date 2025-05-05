# include <stdio.h>
# include <string.h>
# include <ctype.h>
# include <stdlib.h>
#define MAXLEN 80
#define EOT 4
int countZeroBits(unsigned int i);
int getLine(char s[], int len);

int main() {
    char s[MAXLEN];
    unsigned long x;
    int i;
    printf("please enter a decimal number: ");
    getLine(s, MAXLEN);
    x = strtoul(s, NULL, 10);
    i = countZeroBits(x);
    printf("the number of zero bits in the number %lu is %d\n", x, i);
    return 0;
}

int getLine(char s[], int len) {
    int i = 0;
    while (i < len && (s[i] = getchar()) != EOF && s[i] != '\n' && s[i] != EOT) {
        i++;
    }
    if (i == len) {
        s[i-1] ='\0';
    }
    else {
        s[i] = '\0';
    }
    return i;
}

int countZeroBits(unsigned int num) {
    int i, count = 0;
    for (i=1; i <= sizeof(num) * 8; i++) {
        if (num % 2 == 0){
            count++;
        }
        num = num / 2;
    }
    return count;
}