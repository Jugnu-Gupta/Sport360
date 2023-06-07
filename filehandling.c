#include <stdio.h>
#include <string.h>

#define RESET "\033[0m"
#define RED "\033[31m"     /* Red */
#define GREEN "\033[32m"   /* Green */
#define YELLOW "\033[33m"  /* Yellow */
#define BLUE "\033[34m"    /* Blue */
#define MAGENTA "\033[35m" /* Magenta */
#define CYAN "\033[36m"    /* Cyan */
#define WHITE "\033[37m"   /* White */

void addSpace(char word[])
{
    int len1 = strlen(word);
    if (len1 < 7)
    {
        for (int i = len1; i < 7; i++)
        {
            word[i] = ' ';
        }
        word[7] = '\0';
    }
}

int main()
{
    // char sport[50] = "kiT";
    // char equip[50] = "kit";
    char sport[50] = "kit bat";
    char equip[50] = "kit bat";
    // addSpace(sport);
    // addSpace(equip);
    if (strcmp(sport, equip) == 0)
        printf(GREEN "%s %s %s %.2d", sport, equip, "hi", 2, RESET);
    return 0;
}