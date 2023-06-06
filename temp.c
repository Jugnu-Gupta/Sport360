#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

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

void addSpaces(char word[])
{
    int len1 = strlen(word);
    if (len1 < 8)
    {
        for (int i = len1; i < 8; i++)
        {
            word[i] = ' ';
        }
        word[8] = '\0';
    }
}

void Display_Equipment_Inventory(Node1 *head)
{
    // system("cls");
    printf("\n\t\t\t=======Equipment Inventory Record=======\n");
    int i = 1;
    printf("\nSNo\tSport \t\tEquipment Name\t\tQuantity \tAvailable \tIssueQuantity\n");
    printf("---------------------------------------------------------------------------------------------\n");
    while (head != NULL)
    {
        char sport[50];
        char equipment[50];
        strcpy(sport, head->data.Sport);
        strcpy(equipment, head->data.equipmentName);
        addSpaces(sport);
        addSpaces(equipment);
        printf("%d\t%s\t%s\t\t%d\t\t%d\t\t%d\n", i, sport, equipment, head->data.Quantity, head->data.available, head->data.issueQuantity);
        head = head->next;
        i++;
    }
    // printf(" \t Press any key to exit");
    // getchar();
}

void Display_Sport_Equipment_Management(Node2 *head)
{
    // system("cls");
    printf("\n\t\t\t\t\t\t\t=======Sport Equipment Management Record=======\n");
    int i = 1;
    printf("\nSNo\tIncharge\tStudent ID\tSport\t\tEquipment Name\tEquipment ID\tIssue date\tDue date\tReturn date\tNo of days delayed\tFine\n");
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    while (head != NULL)
    {
        // Calculate Date.
        int Iday = head->data.issueDate / pow(10, 6);
        int Imonth = (head->data.issueDate / 10000) % 100;
        int Iyear = head->data.issueDate % 10000;
        int Dday = head->data.dueDate / pow(10, 6);
        int Dmonth = (head->data.dueDate / 10000) % 100;
        int Dyear = head->data.dueDate % 10000;
        int Rday = head->data.returnDate / pow(10, 6);
        int Rmonth = (head->data.returnDate / 10000) % 100;
        int Ryear = head->data.returnDate % 10000;

        char sport[50];
        char equipment[50];
        char Incharge[50];
        strcpy(Incharge, head->data.incharge);
        strcpy(sport, head->data.Sport);
        strcpy(equipment, head->data.equipmentName);
        // addSpaces(Incharge);
        addSpaces(sport);
        addSpaces(equipment);
        printf("%d\t%s\t\t%ld\t\t%s\t%s\t%s\t\t%d-%d-%d\t%d-%d-%d\t%d-%d-%d\t\t%d\t\t%d\n", i, Incharge,
               head->data.studentID, sport, equipment, head->data.equipmentID, Iday, Imonth, Iyear,
               Dday, Dmonth, Dyear, Rday, Rmonth, Ryear, head->data.NoOfDaysDelayed, head->data.fine);
        head = head->next;
        i++;
    }
    printf(" \t Press any key to exit");
    getchar();
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
    // Display_Equipment_Inventory(head1);
    Display_Sport_Equipment_Management(head2);
    // bubbleSort(head2);
    // Display_Sport_Equipment_Management(head2);
    // Student_History(head2, 1210055);
    return 0;
}