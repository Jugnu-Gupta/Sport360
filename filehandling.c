#include <stdio.h>

int main()
{
    FILE *fp;
    fp = fopen("temp.txt", "w");
    fprintf(fp, "%s \n%s ", "Jugnu Gupta", "Jugnu Gupta");
    return 0;
}