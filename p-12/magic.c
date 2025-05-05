# include <stdio.h>
# include <string.h>
# include <ctype.h>
# include <stdlib.h>


# define N 3
# define N_SQR N*N
# define MAX_LINE_LEN 1024
# define SPACES "\n\r\t \f\v"
# define TRUE 1
# define FALSE 0


int getInput(int inputsLen, int inputsArr[]);
int orderValuesIntoCube(int cubeLen, int cube[][N], int inputsLen, int inputsArr[]);
int convertTokenToInt(char* token, int* input);
int checkMagicRow(int line[], int cubeLen, int expectedSum);
int checkMagicCols(int cubeLen, int cube[][N], int expectedSum);
int checkMagicDiags(int cubeLen, int cube[][N], int expectedSum);
void printResult(int cubeLen, int cube[][N], int isMagic);
int checkRepeatVals(int inputsLen, int inputsArr[]);
int computeSum(int n);

int main() {
    int values[N_SQR];
    int cube[N][N];
    int isError = FALSE;
    int isMagic = FALSE;
    isError = getInput(N_SQR, values);
    if (!isError){
        isMagic = orderValuesIntoCube(N, cube, N_SQR, values);
        printResult(N, cube, isMagic);
    }
    return isError;
}

int getInput(int inputsLen, int inputsArr[]) {
    int argCount = 0, isError = FALSE;
    char line[MAX_LINE_LEN];
    int input;
    printf("please enter %d integer values separated by white spaces\n", inputsLen);
    printf("the values shoule be lower then then %d\n", inputsLen + 1);
    while (fgets(line, MAX_LINE_LEN, stdin) && !isError) {
        char *token = strtok(line, SPACES);
        while (token != NULL && !isError) {
            if (argCount >= inputsLen) {
                fprintf(stderr, "ERROR: to many values in the input\n");
                isError = TRUE;
            }
            if (!isError) {
            isError = convertTokenToInt(token, &input);
            inputsArr[argCount++] = input;
            token = strtok(NULL, SPACES);
            }
        }
    }
    if (!isError && argCount < inputsLen) {
        fprintf(stderr, "ERROR: not enough values in input\n");
        isError = TRUE;
    }
    return isError;
}

int convertTokenToInt(char *token, int *input)
{
    int isError = FALSE;
    char *endptr;
    *input = (int)strtol(token, &endptr, 10);
    if (*input == 0 && token == endptr) {
        isError = TRUE;
    }
    else if (!(*token != '\0' && *endptr == '\0')) {
        isError = TRUE;
    }
    if (isError) {
        fprintf(stderr, "ERROR invalid input '%s'.\n", token);
    }
    return isError;
}

int orderValuesIntoCube(int cubeLen, int cube[][N], int inputsLen, int inputsArr[]) {
    int expectedSum = computeSum(N);
    int isMagic = TRUE;
    int i, j;
    for (i = 0; i < cubeLen; i++) {
        for (j = 0; j < cubeLen; j++) {
            cube[i][j] = inputsArr[cubeLen * i + j];
        }
        isMagic = (!isMagic) ? isMagic : checkMagicRow(cube[i], cubeLen, expectedSum);
    }
    isMagic = (!isMagic) ? isMagic : checkMagicCols(cubeLen, cube, expectedSum);
    isMagic = (!isMagic) ? isMagic : checkMagicDiags(cubeLen, cube, expectedSum);
    isMagic = (!isMagic) ? isMagic : checkRepeatVals(inputsLen, inputsArr);
    return isMagic;
}

int checkMagicRow(int line[], int cubeLen, int expectedSum) {
    int sum = 0, i; 
    for (i = 0; i < cubeLen; i++) {
        sum += line[i];
    }
    return expectedSum == sum;
}

int computeSum(int n) {
    return (N * (N_SQR + 1)) / 2;
}

int checkMagicCols(int cubeLen, int cube[][N], int expectedSum) {
    int isMagic = TRUE;
    int i, j, sum = 0;
    for (i = 0; i < cubeLen; i++) {
        for (j = 0 ; j < cubeLen; j++) {
            sum += cube[j][i];
        }
        isMagic = (!isMagic) ? isMagic : (expectedSum == sum);
        sum = 0;
    }
    return isMagic;
}

int checkMagicDiags(int cubeLen, int cube[][N], int expectedSum) {
    int i, sum = 0, aSum = 0;
    int diag = FALSE, aDiag = FALSE;
    for (i = 0; i < cubeLen; i++) {
        sum += cube[i][i];
        aSum += cube[i][cubeLen - 1 - i];
    }
    diag = (expectedSum == sum);
    aDiag = (expectedSum == aSum);
    return diag && aDiag;
}

void printResult(int cubeLen, int cube[][N], int isMagic) {
    int i, j;
    fprintf(stderr, "\n");
    for (i = 0; i < cubeLen; i++) {
        for (j = 0; j < cubeLen; j++) {
            fprintf(stdout, "%3d", cube[i][j]);
        }
        fprintf(stdout, "\n");
    }
    fprintf(stdout, "\n%s\n", ((isMagic) ? "This Square is a Magic Square" : "This Square is Not a Magic Square"));
} 

int checkRepeatVals(int inputsLen, int inputsArr[]) {
    int foundVals[(N_SQR + 1)] = {FALSE};
    int i, tmp, isMagic = TRUE;
    for (i = 0; i < inputsLen; i++) {
        tmp = inputsArr[i];
        if (tmp > inputsLen || foundVals[tmp]) {
            isMagic = FALSE;
        }
        foundVals[tmp] = TRUE;
    }
    return isMagic;
}