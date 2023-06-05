#include <stdio.h>
#include <time.h>

int main()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("now: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

// time_t t = time(NULL);
// struct tm tm = *localtime(&t);
// head2->data.returnDate = (tm.tm_mday) * 1000000 + (tm.tm_mon + 1) * 10000 + tm.tm_year + 1900;

// system("clear");
// printf("\t\t=======Student History Record=======\n");
// printf(" \t Press any key to exit\n");
// getchar();