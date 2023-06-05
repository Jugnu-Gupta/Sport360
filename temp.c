#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Equipment_Inventory
{
    int available, Quantity, issueQuantity;
    char Sport[50];
    char equipmentName[50];
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

void bubbleSort(Node2 *head2)
{
    while (head2 != NULL && head2->next != NULL)
    {
        Node2 *curr = head2;
        while (curr != NULL && curr->next != NULL)
        {
            if ((curr->data.dueDate) % 10000 < (curr->next->data.dueDate) % 10000) // compared year wise.
            {
                swap2(curr, curr->next); // swap the node's value in LL.
            }
            else if ((curr->data.dueDate) % 10000 <= (curr->next->data.dueDate) % 10000 &&
                     ((curr->data.dueDate) % 1000000) / 10000 < ((curr->next->data.dueDate) % 1000000) / 10000) // compared month wise.
            {
                swap2(curr, curr->next); // swap the node's value in LL.
            }
            if ((curr->data.dueDate) % 10000 <= (curr->next->data.dueDate) % 10000 &&
                ((curr->data.dueDate) % 1000000) / 10000 <= ((curr->next->data.dueDate) % 1000000) / 10000 &&
                (curr->data.dueDate) / 1000000 < (curr->next->data.dueDate) / 1000000) // compared day wise.
            {
                swap2(curr, curr->next); // swap the node's value in LL.
            }
            curr = curr->next;
        }
        head2 = head2->next;
    }
}
void Student_History(Node2 *head, long int studID)
{
    bubbleSort(head);
    printf("Not returned");
    printf("\nincharge  studentID  sport  equipmentName  equipmentID  issueDate  dueDate  returnDate NoOfDaysDelayed fine\n");
    Node2 *curr = head;
    while (curr != NULL)
    {
        if (curr->data.studentID == studID && curr->data.returnDate == -1)
        {
            printf("  %s %ld %s %s %d %d %d %d %d %d\n", head->data.incharge, head->data.studentID, head->data.Sport,
                   head->data.equipmentName, head->data.equipmentID, head->data.issueDate, head->data.dueDate,
                   head->data.returnDate, head->data.NoOfDaysDelayed, head->data.fine);
        }
        curr = curr->next;
    }

    printf("Returned");
    printf("\nincharge  studentID  sport  equipmentName  equipmentID  issueDate  dueDate  returnDate NoOfDaysDelayed fine\n");
    curr = head;
    while (curr != NULL)
    {
        if (curr->data.studentID == studID && curr->data.returnDate != -1)
        {
            printf("  %s %ld %s %s %d %d %d %d %d %d\n", head->data.incharge, head->data.studentID, head->data.Sport,
                   head->data.equipmentName, head->data.equipmentID, head->data.issueDate, head->data.dueDate,
                   head->data.returnDate, head->data.NoOfDaysDelayed, head->data.fine);
        }
        curr = curr->next;
    }
}
int main()
{
    Node1 *head1 = NULL;
    Node2 *head2 = NULL;

    FILE *fp1, *fp2;
    fp1 = fopen("Equipment_Inventory_DataBase.txt", "r");
    fp2 = fopen("Sport_Equipment_Management_DataBase.txt", "r");
    Equipment_Inventory equipInvent;
    Sport_Equipment_Management equipManage;
    int n;
    fscanf(fp1, "%d", &n);
    while (n--)
    {
        fscanf(fp1, "%d %d %d %[^\n] %[^\n]", &equipInvent.available, &equipInvent.Quantity, &equipInvent.issueQuantity, equipInvent.Sport, equipInvent.equipmentName);
        Insert_Equipment_Inventory(&head1, equipInvent);
    }
    fscanf(fp2, "%d", &n);
    while (n--)
    {
        fscanf(fp2, "%d %d %d %d %d %d %ld %[^\n] %[^\n] %[^\n]", &equipManage.equipmentID, &equipManage.issueDate, &equipManage.dueDate, &equipManage.returnDate,
               &equipManage.NoOfDaysDelayed, &equipManage.fine, &equipManage.studentID, equipManage.equipmentName, equipManage.incharge, equipManage.Sport);
        Insert_Sport_Equipment_Management(&head2, equipManage);
    }
    fclose(fp1);
    fclose(fp2);
    Display_Equipment_Inventory(head1);
    Display_Sport_Equipment_Management(head2);
    bubbleSort(head2);
    Display_Sport_Equipment_Management(head2);
    Student_History(head2, 1210055);
    return 0;
}