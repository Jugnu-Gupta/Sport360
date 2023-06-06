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
    char sport[50] = "kit";
    char equip[50] = "bat";
    addSpace(sport);
    addSpace(equip);
    printf("%s %s %s", sport, equip, "hi");
    return 0;
}