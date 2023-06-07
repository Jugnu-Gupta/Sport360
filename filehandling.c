#include <stdio.h>
#include <string.h>
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
        printf("%s %s %s %.2d", sport, equip, "hi", 2);
    return 0;
}