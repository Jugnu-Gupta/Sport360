#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "LLImple.c"

void DISPLAY_Equipment_Inventory_By_Sport(Node1 *head1)
{
    char sport[50];
    printf("Enter the sports name : ");
    scanf("%s", sport);
    printf("\nsport  quantity  available  issueQuantity\n");
    while (head1 != NULL)
    {
        if (strcmp(head1->data.Sport, sport) == 0)
        {
            printf("  %d\t%d %d %d %d\n", head1->data.Sport, head1->data.Quantity, head1->data.available, head1->data.issueQuantity);
        }
        head1 = head1->next;
    }
}

void Modify_Equipment_Inventory(Node1 *head1)
{
    int Sno, cnt = 1;
    printf("\nEnter the serial number of record : ");
    scanf("%d", &Sno);
    Node1 *curr = head1;
    int quantity;
    while (curr)
    {
        if (cnt == Sno)
        {
            printf("\nEnter quantity: ");
            scanf("%d", &quantity);
            curr->data.Quantity = quantity;
            printf("\nRecord modified successfully\n");
            break;
        }
    }
}
