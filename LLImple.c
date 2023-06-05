#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Equipment_Inventory
{
    int available, Quantity, issueQuantity;
    char Sport[50];
    char equipmentName[50]
} Equipment_Inventory;

typedef struct Sport_Equipment_Management
{
    int equipmentID, issueDate, dueDate, returnDate, NoOfDaysDelayed, fine;
    long int studentID;
    char equipmentName[50];
    char incharge[50];
    char Sport[50];
} Sport_Equipment_Management;

typedef struct Node1
{
    Equipment_Inventory data;
    struct Node1 *next;
} Node1;

typedef struct Node2
{
    Sport_Equipment_Management data;
    struct Node2 *next;
} Node2;

// Function prototype.
void Insert_Equipment_Inventory(Node1 **head, Equipment_Inventory record);
void Insert_Sport_Equipment_Management(Node2 **head, Sport_Equipment_Management record);

void swap1(Node1 *a, Node1 *b)
{
    Equipment_Inventory equipInvent = a->data;
    a->data = b->data;
    b->data = equipInvent;
}

void swap2(Node2 *a, Node2 *b)
{
    Sport_Equipment_Management equipManage = a->data;
    a->data = b->data;
    b->data = equipManage;
}

void Insert_Equipment_Inventory(Node1 **head, Equipment_Inventory record)
{
    Node1 *temp = (Node1 *)malloc(sizeof(Node1));
    temp->data = record;
    temp->next = *head;
    *head = temp;
}

void Insert_Sport_Equipment_Management(Node2 **head, Sport_Equipment_Management record)
{
    Node2 *temp = (Node2 *)malloc(sizeof(Node2));
    temp->data = record;
    temp->next = *head;
    *head = temp;
}

void Display_Equipment_Inventory(Node1 *head)
{
    printf("\nsport equipmentName quantity  available  issueQuantity\n");
    while (head != NULL)
    {
        printf("  %s %s %d %d %d\n", head->data.Sport, head->data.equipmentName, head->data.Quantity, head->data.available, head->data.issueQuantity);
        head = head->next;
    }
}

void Display_Sport_Equipment_Management(Node2 *head)
{
    printf("\nincharge  studentID  sport  equipmentName  equipmentID  issueDate  dueDate  returnDate NoOfDaysDelayed fine\n");
    while (head != NULL)
    {
        printf("  %s %ld %s %s %d %d %d %d %d %d\n", head->data.incharge, head->data.studentID, head->data.Sport,
               head->data.equipmentName, head->data.equipmentID, head->data.issueDate, head->data.dueDate,
               head->data.returnDate, head->data.NoOfDaysDelayed, head->data.fine);
        head = head->next;
    }
}

int countNode_Inventory(Node1 *head)
{
    int cnt = 0;
    while (head != NULL)
    {
        head = head->next;
        cnt++;
    }
    return cnt;
}

int countNode_Management(Node2 *head)
{
    int cnt = 0;
    while (head != NULL)
    {
        head = head->next;
        cnt++;
    }
    return cnt;
}

int main()
{
    // Node1 *head1 = NULL;
    // table1 t1;
    // t1.available = 5;
    // t1.issueQuantity = 3;
    // t1.quantity = 10;
    // // head1->data.sport="Kabaddi";
    // LINSERT1(&head1, t1);
    // LDISPLAY1(head1);
    // Node2 *head2 = NULL;
    // table2 t2;
    // t2.studentID = 1;
    // LINSERT2(&head2, t2);
    // LDISPLAY2(head2);
    return 0;
}