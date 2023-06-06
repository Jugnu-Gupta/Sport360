#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <string.h>

void title()
{
    printf("  ██████╗ ██████╗    ████████    ██████╗   ██████████╗   ██████╗   ██████╗   ██████╗\n");
    printf(" ██╔════╝ ██╔══██   ██╔═════██   ██╔══██╗  ╚═══██╔═══╝   ╚════██╗ ██╔════╝  ██╔═══██╗\n");
    printf(" ██║      ██║  ██╗ ██╔╝      ██╗ ██║  ██║      ██║            ██║ ██║       ██║   ██║\n");
    printf(" ╚█████╗  ██████╔╝ ██║       ██║ ██████╔╝      ██║       ███████║ ███████╗  ██║   ██║\n");
    printf("  ╚═══██╗ ██╔═══╝  ██║       ██║ ████══╝       ██║       ╚════██║ ██╔═══██╗ ██║   ██║\n");
    printf("      ██║ ██║      ╚██      ██╔╝ ██║██══╗      ██║            ██║ ██║   ██║ ██║   ██║\n");
    printf(" ██████╔╝ ██║       ╚████████╔╝  ██║ ███║      ██║       ██████╔╝ ╚██████╔╝ ╚██████╔╝\n");
    printf(" ╚═════╝  ╚═╝        ╚═══════╝   ╚═╝ ╚══╝      ╚═╝       ╚═════╝   ╚═════╝   ╚═════╝\n");
}
// ------------------------------------------Admin password protections-----------------------------------------

// structure of Nodes in a binary tree.
typedef struct Node
{
    int user_id;
    char password[30];
    struct Node *left;
    struct Node *right;
} Admin;

// Function to Add Node in a binary tree.
Admin *insertNode(Admin *root, int userId, char pass[])
{
    if (!root)
    { // add a node.
        root = (Admin *)malloc(sizeof(Admin));
        root->left = NULL;
        root->right = NULL;
        root->user_id = userId;
        strcpy(root->password, pass);
        return root;
    }
    if (userId < root->user_id) // move towards left
        root->left = insertNode(root->left, userId, pass);
    else // move towards right
        root->right = insertNode(root->right, userId, pass);
    return root;
}

// Function to Create a binary tree.
void CreateBinaryTree(Admin **root, FILE *fp)
{
    int userId;
    char pass[30];
    fscanf(fp, "%d %s", &userId, pass);
    while (userId != -1)
    {
        *root = insertNode(*root, userId, pass);
        fscanf(fp, "%d %s", &userId, pass);
    }
}

// Function to Verify a user.
bool verify(Admin *root, int userId, char pass[])
{
    if (!root)
        return 0;

    // matches user_id and password.
    if (root->user_id == userId)
    {
        if (strcmp(root->password, pass) == 0)
        {
            return 1;
        }
        return 0;
    }
    if (userId < root->user_id) // move towards left.
        return verify(root->left, userId, pass);
    else // move towards right.
        return verify(root->right, userId, pass);
}

bool Verification()
{
    FILE *fp;
    fp = fopen("./Admin/Admin.txt", "r");
    Admin *root = NULL;
    // call the "createBinaryTree" function.
    CreateBinaryTree(&root, fp);
    fclose(fp);

    int userId;
    char pass[30];
    printf("Enter your user-id & password : ");
    scanf("%d %s", &userId, pass);
    // call the function to "verify".
    return verify(root, userId, pass);
}
// --------------------------------------------------------------------------------------------

typedef struct Equipment_Inventory
{
    int available, Quantity, issueQuantity;
    char Sport[50];
    char equipmentName[50];
} Equipment_Inventory;

typedef struct Sport_Equipment_Management
{
    int issueDate, dueDate, returnDate, NoOfDaysDelayed, fine;
    long int studentID;
    char equipmentID[20];
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
    system("cls");
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
        printf(" %d\t%s\t%s\t\t%d\t\t%d\t\t%d\n", i, sport, equipment, head->data.Quantity, head->data.available, head->data.issueQuantity);
        head = head->next;
        i++;
    }
    printf("\n \t Press any key to exit");
    getchar();
}

void Display_Sport_Equipment_Management(Node2 *head)
{
    system("cls");
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
        addSpaces(Incharge);
        addSpaces(sport);
        addSpaces(equipment);
        printf(" %d\t%s\t%ld\t\t%s\t%s\t%s\t\t%d-%d-%d\t%d-%d-%d\t%d-%d-%d\t\t%d\t\t%d\n", i, Incharge,
               head->data.studentID, sport, equipment, head->data.equipmentID, Iday, Imonth, Iyear,
               Dday, Dmonth, Dyear, Rday, Rmonth, Ryear, head->data.NoOfDaysDelayed, head->data.fine);
        head = head->next;
        i++;
    }
    printf("\n \t Press any key to exit");
    getchar();
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
    system("cls");
    printf("\n\t\t\t\t\t\t\t\t=======Student History Record=======\n");
    int flag = 0;

    int i = 1;
    Node2 *curr = head;
    while (curr != NULL)
    {
        if (curr->data.studentID == studID && curr->data.returnDate == 0)
        {
            if (flag == 0)
            {
                printf("\n Issued equipment");
                printf("\nSNo\tIncharge\tStudent ID\tSport\t\tEquipment Name\tEquipment ID\tIssue date\tDue date\tReturn date\tNo of days delayed\tFine\n");
                printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
            }
            // Calculate Date.
            int Iday = curr->data.issueDate / pow(10, 6);
            int Imonth = (curr->data.issueDate / 10000) % 100;
            int Iyear = curr->data.issueDate % 10000;
            int Dday = curr->data.dueDate / pow(10, 6);
            int Dmonth = (curr->data.dueDate / 10000) % 100;
            int Dyear = curr->data.dueDate % 10000;
            int Rday = curr->data.returnDate / pow(10, 6);
            int Rmonth = (curr->data.returnDate / 10000) % 100;
            int Ryear = curr->data.returnDate % 10000;

            char sport[50];
            char equipment[50];
            char Incharge[50];
            strcpy(Incharge, curr->data.incharge);
            strcpy(sport, curr->data.Sport);
            strcpy(equipment, curr->data.equipmentName);
            addSpaces(Incharge);
            addSpaces(sport);
            addSpaces(equipment);
            printf(" %d\t%s\t%ld\t\t%s\t%s\t%s\t\t%d-%d-%d\t%d-%d-%d\t%d-%d-%d\t\t%d\t\t%d\n", i, Incharge,
                   curr->data.studentID, sport, equipment, curr->data.equipmentID, Iday, Imonth, Iyear,
                   Dday, Dmonth, Dyear, Rday, Rmonth, Ryear, curr->data.NoOfDaysDelayed, curr->data.fine);
            i++;
            flag++;
        }
        curr = curr->next;
    }
    if (flag == 0)
    {
        printf("\n No Equipment to Return\n");
    }

    flag = 0;
    i = 0;
    curr = head;
    while (curr != NULL)
    {
        if (curr->data.studentID == studID && curr->data.returnDate != 0)
        {
            if (flag == 0)
            {
                printf("\n Returned equipment");
                printf("\nSNo\tIncharge\tStudent ID\tSport\t\tEquipment Name\tEquipment ID\tIssue date\tDue date\tReturn date\tNo of days delayed\tFine\n");
                printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
            }
            // Calculate Date.
            int Iday = curr->data.issueDate / pow(10, 6);
            int Imonth = (curr->data.issueDate / 10000) % 100;
            int Iyear = curr->data.issueDate % 10000;
            int Dday = curr->data.dueDate / pow(10, 6);
            int Dmonth = (curr->data.dueDate / 10000) % 100;
            int Dyear = curr->data.dueDate % 10000;
            int Rday = curr->data.returnDate / pow(10, 6);
            int Rmonth = (curr->data.returnDate / 10000) % 100;
            int Ryear = curr->data.returnDate % 10000;

            char sport[50];
            char equipment[50];
            char Incharge[50];
            strcpy(Incharge, curr->data.incharge);
            strcpy(sport, curr->data.Sport);
            strcpy(equipment, curr->data.equipmentName);
            addSpaces(Incharge);
            addSpaces(sport);
            addSpaces(equipment);
            printf(" %d\t%s\t%ld\t\t%s\t%s\t%s\t\t%d-%d-%d\t%d-%d-%d\t%d-%d-%d\t\t%d\t\t%d\n", i, Incharge,
                   curr->data.studentID, sport, equipment, curr->data.equipmentID, Iday, Imonth, Iyear,
                   Dday, Dmonth, Dyear, Rday, Rmonth, Ryear, curr->data.NoOfDaysDelayed, curr->data.fine);
            i++;
            flag++;
        }
        curr = curr->next;
    }
    if (flag == 0)
    {
        printf("\n No Equipment Issued Yet");
    }
    printf("\n \t Press any key to exit");
    getchar();
}

int isLeapYear(int year)
{
    return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}

int getMonthDays(int month, int year)
{
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeapYear(year))
        return 29;
    else
        return days[month - 1];
}

int updateDate(int date)
{
    int day = date / pow(10, 6);
    int month = (date / 10000) % 100;
    int year = date % 10000;
    int monthDays = getMonthDays(month, year);
    day += 15;
    if (day > monthDays)
    {
        day -= monthDays;
        month++;
        if (month > 12)
        {
            month = 1;
            year++;
        }
    }
    return day * pow(10, 6) + month * 10000 + year;
}

int calculateDays(int due_date, int return_date)
{
    int startDay = due_date / pow(10, 6);
    int startMonth = (due_date / 10000) % 100;
    int startYear = due_date % 10000;

    int endDay = return_date / pow(10, 6);
    int endMonth = (return_date / 10000) % 100;
    int endYear = return_date % 10000;

    int days = 0;
    while (startYear < endYear || startMonth < endMonth || startDay < endDay)
    {
        days++;
        startDay++;
        if (startDay > getMonthDays(startMonth, startYear))
        {
            startDay = 1;
            startMonth++;
        }
        if (startMonth > 12)
        {
            startMonth = 1;
            startYear++;
        }
    }
    return days;
}

int nearest_Availibility_Date(Node2 *head2)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    // system date.
    int sys_date = tm.tm_mday;
    int sys_month = tm.tm_mon + 1;
    int sys_year = tm.tm_year + 1900;
    // min date.
    int min_day = 1;
    int min_month = 1;
    int min_year = 100000;
    Node2 *curr = head2;
    while (curr != NULL)
    {
        if ((((curr->data.dueDate) % 10000 > sys_year) ||
             ((curr->data.dueDate) % 10000 == sys_year && ((curr->data.dueDate) % 1000000) / 10000 > sys_month) ||
             ((curr->data.dueDate) % 10000 == sys_year && ((curr->data.dueDate) % 1000000) / 10000 == sys_month && (curr->data.dueDate) / 1000000 >= sys_date)) &&
            (((curr->data.dueDate) % 10000 < min_year) ||
             ((curr->data.dueDate) % 10000 == min_year && ((curr->data.dueDate) % 1000000) / 10000 < min_month) ||
             ((curr->data.dueDate) % 10000 == min_year && ((curr->data.dueDate) % 1000000) / 10000 == min_month && (curr->data.dueDate) / 1000000 < min_day))) // compared year wise.
        {
            min_day = (curr->data.dueDate) / 1000000;
            min_month = ((curr->data.dueDate) % 1000000) / 10000;
            min_year = (curr->data.dueDate) % 10000;
        }
        curr = curr->next;
    }
    if (min_year != 100000 && min_month != 1 && min_day != 1)
        return min_day * 1000000 + min_month * 10000 + min_year;
    else
        return 0;
}

bool check_Quantity(Node1 *head1, char sport[], char equip[])
{
    while (head1 != NULL)
    {
        if (strcmp(head1->data.Sport, sport) == 0 && strcmp(head1->data.equipmentName, equip) == 0)
        {
            if (head1->data.available != 0)
            {
                head1->data.available--;
                head1->data.issueQuantity++;
                return 1;
            }
            else
                return 0;
        }
        head1 = head1->next;
    }
    return 0;
}

void equipment_issue(Node1 *head1, Node2 *head2, char sport[], char equip[])
{
    if (check_Quantity(head1, sport, equip) == 0)
    {
        int nearestAvailableDate = nearest_Availibility_Date(head2);
        if (nearestAvailableDate != 0)
        {
            printf(" Desired equipment is not available now!");
            printf("\n Equipment will be available by : %d-%d-%d\n", nearestAvailableDate / 1000000, (nearestAvailableDate % 1000000) / 10000, nearestAvailableDate % 10000);
        }
        else
        {
            printf(" Desired equipment is not available for Issue");
        }
    }
    else
    {
        Sport_Equipment_Management equipManage;
        strcpy(equipManage.Sport, sport);
        strcpy(equipManage.equipmentName, equip);

        printf(" Fill details\n");
        getchar();
        printf(" Incharge : ");
        scanf("%[^\n]", equipManage.incharge);
        printf(" Student ID : ");
        scanf("%ld", &equipManage.studentID);
        printf(" Equipment ID : ");
        scanf("%s", &equipManage.equipmentID);

        // date
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        equipManage.issueDate = (tm.tm_mday) * 1000000 + (tm.tm_mon + 1) * 10000 + tm.tm_year + 1900;
        equipManage.returnDate = 0;
        equipManage.dueDate = updateDate(equipManage.issueDate);

        // insert record.
        Insert_Sport_Equipment_Management(&head2, equipManage);
        // update available equipments & issueQuantity.
        while (head1)
        {
            if (strcmp(head1->data.Sport, sport) == 0 && strcmp(head1->data.equipmentName, equip) == 0)
            {
                head1->data.available--;
                head1->data.issueQuantity++;
                break;
            }
            head1 = head1->next;
        }

        // display
        printf("The due date for the item : %d-%d-%d\n", equipManage.dueDate / 1000000, (equipManage.dueDate % 1000000) / 10000, equipManage.dueDate % 10000);
        printf("Issued Successfully\n");
    }
}

void user_issue(Node1 *head1, Node2 *head2)
{
    system("cls");
    printf("\t\t=======Issue Sports Equipment=======\n");
    int choice;
    char equip_No;
    char sport[50];
    char equip[50];
    printf(" 1) table tennis  \n 2) cricket \n 3) badminton \n 4) basketball \n 5) football \n 6) lawn tennis \n 7) chess \n 8) carrom \n 9) hockey \n 10) volleyball \n");
    printf("Enter your desired sport : ");
    scanf("%d", &choice);
    getchar();
    switch (choice)
    {
    case 1:
        strcpy(sport, "table tennis");
        printf(" a) racquet\n b) ball\n c) net\n");
        printf("Choose the equipment : ");
        scanf("%c", &equip_No);
        switch (equip_No)
        {
        case 'a':
            strcpy(equip, "racquet");
            equipment_issue(head1, head2, sport, equip);
            break;
        case 'b':
            strcpy(equip, "ball");
            equipment_issue(head1, head2, sport, equip);
            break;
        case 'c':
            strcpy(equip, "net");
            equipment_issue(head1, head2, sport, equip);
            break;
        default:
            printf("\nInvalid Input!!");
            break;
        }
        break;
    case 2:
        strcpy(sport, "cricket");
        printf(" a) bat\n b) leather ball\n c) tennis ball\n d) kit \n e) stumps\n");
        printf("Choose the equipment : ");
        scanf("%c", &equip_No);
        switch (equip_No)
        {
        case 'a':
            strcpy(equip, "bat");
            equipment_issue(head1, head2, sport, equip);
            break;
        case 'b':
            strcpy(equip, "leather ball");
            equipment_issue(head1, head2, sport, equip);
            break;
        case 'c':
            strcpy(equip, "tennis ball");
            equipment_issue(head1, head2, sport, equip);
            break;
        case 'd':
            strcpy(equip, "kit");
            equipment_issue(head1, head2, sport, equip);
            break;
        case 'e':
            strcpy(equip, "stumps");
            equipment_issue(head1, head2, sport, equip);
            break;
        default:
            printf("\nInvalid Input!!");
            break;
        }
        break;
    case 3:
        strcpy(sport, "badminton");
        printf(" a) racquet\n b) shuttelcock\n");
        printf("Choose the equipment : ");
        scanf("%c", &equip_No);

        switch (equip_No)
        {
        case 'a':
            strcpy(equip, "racquet");
            equipment_issue(head1, head2, sport, equip);
            break;
        case 'b':
            strcpy(equip, "shuttelcock");
            equipment_issue(head1, head2, sport, equip);
            break;
        default:
            printf("\nInvalid Input!!");
            break;
        }

        break;
    case 4:
        strcpy(sport, "basketball");
        printf(" a) basketball\n");
        printf("Choose the equipment : ");
        scanf("%c", &equip_No);

        switch (equip_No)
        {
        case 'a':
            strcpy(equip, "basketball");
            equipment_issue(head1, head2, sport, equip);
            break;
        default:
            printf("\nInvalid Input!!");
            break;
        }

        break;
    case 5:
        strcpy(sport, "football");
        printf(" a) football\n b) gloves\n c) kit\n");
        printf("Choose the equipment : ");
        scanf("%c", &equip_No);

        switch (equip_No)
        {
        case 'a':
            strcpy(equip, "football");
            equipment_issue(head1, head2, sport, equip);
            break;
        case 'b':
            strcpy(equip, "gloves");
            equipment_issue(head1, head2, sport, equip);
            break;
        case 'c':
            strcpy(equip, "kit");
            equipment_issue(head1, head2, sport, equip);
            break;
        default:
            printf("\nInvalid Input!!");
            break;
        }

        break;
    case 6:
        strcpy(sport, "lawn tennis");
        printf(" a) racquet\n b) ball\n");
        printf("Choose the equipment : ");
        scanf("%c", &equip_No);

        switch (equip_No)
        {
        case 'a':
            strcpy(equip, "racquet");
            equipment_issue(head1, head2, sport, equip);
            break;
        case 'b':
            strcpy(equip, "ball");
            equipment_issue(head1, head2, sport, equip);
            break;
        default:
            printf("\nInvalid Input!!");
            break;
        }

        break;
    case 7:
        strcpy(sport, "chess");
        printf(" a) chess set\n");
        printf("Choose the equipment : ");
        scanf("%c", &equip_No);

        switch (equip_No)
        {
        case 'a':
            strcpy(equip, "chess set");
            equipment_issue(head1, head2, sport, equip);
            break;
        default:
            printf("\nInvalid Input!!");
            break;
        }

        break;
    case 8:
        strcpy(sport, "carrom");
        printf(" a) board\n b) carrom coins\n c) powder\n");
        printf("Choose the equipment : ");
        scanf("%c", &equip_No);

        switch (equip_No)
        {
        case 'a':
            strcpy(equip, "board");
            equipment_issue(head1, head2, sport, equip);
            break;
        case 'b':
            strcpy(equip, "carrom coins");
            equipment_issue(head1, head2, sport, equip);
            break;
        case 'c':
            strcpy(equip, "powder");
            equipment_issue(head1, head2, sport, equip);
            break;
        default:
            printf("\nInvalid Input!!");
            break;
        }

        break;
    case 9:
        strcpy(sport, "hockey");
        printf(" a) hockey stick\n b) hockey ball\n c) kit\n");
        printf("Choose the equipment : ");
        scanf("%c", &equip_No);

        switch (equip_No)
        {
        case 'a':
            strcpy(sport, "hockey stick");
            equipment_issue(head1, head2, sport, equip);
            break;
        case 'b':
            strcpy(equip, "hockey ball");
            equipment_issue(head1, head2, sport, equip);
            break;
        case 'c':
            strcpy(equip, "kit");
            equipment_issue(head1, head2, sport, equip);
            break;
        default:
            printf("\nInvalid Input!!");
            break;
        }

        break;
    case 10:
        strcpy(sport, "volleyball");
        printf(" a) volleyball\n");
        printf("Choose the equipment : \n");
        scanf("%c", &equip_No);

        switch (equip_No)
        {
        case 'a':
            strcpy(equip, "volleyball");
            equipment_issue(head1, head2, sport, equip);
            break;
        default:
            printf("\nInvalid Input!!");
            break;
        }
        break;
    default:
        printf("\nInvalid Input!!");
        break;
    }
    printf("\n \t Press any key to exit");
    getchar();
    // fgets(sport, 50, stdin);
}

void user_display_Quantity(Node1 *head1, char sport[], char equip[])
{
    while (head1 != NULL)
    {
        if (strcmp(head1->data.Sport, sport) == 0 && strcmp(head1->data.equipmentName, equip) == 0)
        {
            if (head1->data.available != 0)
            {
                printf("\n Equipment is available\n");
            }
            else
            {
                printf("\n Equipment is not available\n");
            }
            return;
        }
        head1 = head1->next;
    }
}

void User_Check_Availability(Node1 *head1, Node2 *head2)
{
    system("cls");
    printf("\t\t=======Check Availibality of Sport Equipment=======\n");
    int choice;
    char equip_No;
    char sport[50];
    char equip[50];
    printf(" 1) table tennis  \n 2) cricket \n 3) badminton \n 4) basketball \n 5) football \n 6) lawn tennis \n 7) chess \n 8) carrom \n 9) hockey \n 10) volleyball \n");
    printf("Enter your desired sport : ");
    scanf("%d", &choice);
    getchar();
    switch (choice)
    {
    case 1:
        strcpy(sport, "table tennis");
        printf(" a) racquet\n b) ball\n c) net\n");
        printf("Choose the equipment : ");
        scanf("%c", &equip_No);
        switch (equip_No)
        {
        case 'a':
            strcpy(equip, "racquet");
            user_display_Quantity(head1, sport, equip);
            break;
        case 'b':
            strcpy(equip, "ball");
            user_display_Quantity(head1, sport, equip);
            break;
        case 'c':
            strcpy(equip, "net");
            user_display_Quantity(head1, sport, equip);
            break;
        default:
            printf("\nInvalid Input!!");
            break;
        }
        break;
    case 2:
        strcpy(sport, "cricket");
        printf(" a) bat\n b) leather ball\n c) tennis ball\n d) kit\n e) stumps\n");
        printf("Choose the equipment : ");
        scanf("%c", &equip_No);
        switch (equip_No)
        {
        case 'a':
            strcpy(equip, "bat");
            user_display_Quantity(head1, sport, equip);
            break;
        case 'b':
            strcpy(equip, "leather ball");
            user_display_Quantity(head1, sport, equip);
            break;
        case 'c':
            strcpy(equip, "tennis ball");
            user_display_Quantity(head1, sport, equip);
            break;
        case 'd':
            strcpy(equip, "kit");
            user_display_Quantity(head1, sport, equip);
            break;
        case 'e':
            strcpy(equip, "stumps");
            user_display_Quantity(head1, sport, equip);
            break;
        default:
            printf("\nInvalid Input!!");
            break;
        }
        break;
    case 3:
        strcpy(sport, "badminton");
        printf(" a) racquet\n b) shuttelcock\n");
        printf("Choose the equipment : ");
        scanf("%c", &equip_No);

        switch (equip_No)
        {
        case 'a':
            strcpy(equip, "racquet");
            user_display_Quantity(head1, sport, equip);
            break;
        case 'b':
            strcpy(equip, "shuttelcock");
            user_display_Quantity(head1, sport, equip);
            break;
        default:
            printf("\nInvalid Input!!");
            break;
        }

        break;
    case 4:
        strcpy(sport, "basketball");
        printf(" a) basketball\n");
        printf("Choose the equipment : ");
        scanf("%c", &equip_No);

        switch (equip_No)
        {
        case 'a':
            strcpy(equip, "basketball");
            user_display_Quantity(head1, sport, equip);
            break;
        default:
            printf("\nInvalid Input!!");
            break;
        }

        break;
    case 5:
        strcpy(sport, "football");
        printf(" a) football\n b) gloves\n c) kit\n");
        printf("Choose the equipment : ");
        scanf("%c", &equip_No);

        switch (equip_No)
        {
        case 'a':
            strcpy(equip, "football");
            user_display_Quantity(head1, sport, equip);
            break;
        case 'b':
            strcpy(equip, "gloves");
            user_display_Quantity(head1, sport, equip);
            break;
        case 'c':
            strcpy(equip, "kit");
            user_display_Quantity(head1, sport, equip);
            break;
        default:
            printf("\nInvalid Input!!");
            break;
        }

        break;
    case 6:
        strcpy(sport, "lawn tennis");
        printf(" a) racquet\n b) ball\n");
        printf("Choose the equipment : ");
        scanf("%c", &equip_No);

        switch (equip_No)
        {
        case 'a':
            strcpy(equip, "racquet");
            user_display_Quantity(head1, sport, equip);
            break;
        case 'b':
            strcpy(equip, "ball");
            user_display_Quantity(head1, sport, equip);
            break;
        default:
            printf("\nInvalid Input!!");
            break;
        }

        break;
    case 7:
        strcpy(sport, "chess");
        printf(" a) chess set\n");
        printf("Choose the equipment : ");
        scanf("%c", &equip_No);

        switch (equip_No)
        {
        case 'a':
            strcpy(equip, "chess set");
            user_display_Quantity(head1, sport, equip);
            break;
        default:
            printf("\nInvalid Input!!");
            break;
        }

        break;
    case 8:
        strcpy(sport, "carrom");
        printf(" a) board\n b) carrom coins\n c) powder\n");
        printf("Choose the equipment : ");
        scanf("%c", &equip_No);

        switch (equip_No)
        {
        case 'a':
            strcpy(equip, "board");
            user_display_Quantity(head1, sport, equip);
            break;
        case 'b':
            strcpy(equip, "carrom coins");
            user_display_Quantity(head1, sport, equip);
            break;
        case 'c':
            strcpy(equip, "powder");
            user_display_Quantity(head1, sport, equip);
            break;
        default:
            printf("\nInvalid Input!!");
            break;
        }

        break;
    case 9:
        strcpy(sport, "hockey");
        printf(" a) hockey stick\n b) hockey ball\n c) kit\n");
        printf("Choose the equipment : ");
        scanf("%c", &equip_No);

        switch (equip_No)
        {
        case 'a':
            strcpy(equip, "hockey stick");
            user_display_Quantity(head1, sport, equip);
            break;
        case 'b':
            strcpy(equip, "hockey ball");
            user_display_Quantity(head1, sport, equip);
            break;
        case 'c':
            strcpy(equip, "kit");
            user_display_Quantity(head1, sport, equip);
            break;
        default:
            printf("\nInvalid Input!!");
            break;
        }

        break;
    case 10:
        strcpy(sport, "volleyball");
        printf(" a) volleyball\n");
        printf("Choose the equipment : ");
        scanf("%c", &equip_No);

        switch (equip_No)
        {
        case 'a':
            strcpy(equip, "volleyball");
            user_display_Quantity(head1, sport, equip);
            break;
        }
        break;
    default:
        printf("\nInvalid Input!!");
        break;
    }
    printf("\n \t Press any key to exit");
    getchar();
}

void user_return(Node1 *head1, Node2 *head2)
{
    system("cls");
    printf("\t\t=======Return Sports Equipment=======\n");
    long int studId;
    char equipId[20];
    printf("Enter your StudentID & EquipmentID : ");
    scanf("%ld %s", &studId, equipId);
    while (head2 != NULL)
    {
        if (head2->data.studentID == studId && strcmp(head2->data.equipmentID, equipId) == 0)
        {
            // update available equipments & issueQuantity.
            while (head1)
            {
                if (head1->data.Sport == head2->data.Sport && head1->data.equipmentName == head2->data.equipmentName)
                {
                    head1->data.available++;
                    head1->data.issueQuantity--;
                    break;
                }
                head1 = head1->next;
            }
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            head2->data.returnDate = (tm.tm_mday) * 1000000 + (tm.tm_mon + 1) * 10000 + tm.tm_year + 1900;

            // call program to find number of days delay in return.
            head2->data.NoOfDaysDelayed = calculateDays(head2->data.dueDate, head2->data.returnDate);
            head2->data.fine = (head2->data.NoOfDaysDelayed) * 10;
            // printf fine.
            if (head2->data.fine != 0)
            {
                printf("\nFine = %d Rs\n", head2->data.fine);
            }
            printf("\nSports equipment successfully\n");
            printf(" \t Press any key to exit");
            getchar();
            return;
        }
        head2 = head2->next;
    }
    printf("\nYou havn't issue any sports equipment\n");
    printf("\n \t Press any key to exit");
    getchar();
}

void DISPLAY_Equipment_Inventory_By_Sport(Node1 *head1)
{
    system("cls");
    printf("\n\t\t=======Equipment Inventory Records=======\n\n");
    int flag = 0;
    int i = 1;

    char sports[50];
    printf("Enter the sports name : ");
    scanf("%s", sports);
    while (head1 != NULL)
    {
        if (strcmp(head1->data.Sport, sports) == 0)
        {
            if (flag == 0)
            {
                printf("SNo\tSport \t\tEquipment Name\t\tQuantity \tAvailable \tIssueQuantity\n");
                printf("---------------------------------------------------------------------------------------------\n");
            }
            char sport[50];
            char equipment[50];
            strcpy(sport, head1->data.Sport);
            strcpy(equipment, head1->data.equipmentName);
            addSpaces(sport);
            addSpaces(equipment);
            printf(" %d\t%s\t%s\t\t%d\t\t%d\t\t%d\n", i, sport, equipment, head1->data.Quantity,
                   head1->data.available, head1->data.issueQuantity);
            flag++;
            i++;
        }
        head1 = head1->next;
    }
    if (flag == 0)
    {
        printf("\nNo results found?\n\n");
    }
    printf("\n \t Press any key to exit");
    getchar();
}

void Modify_Equipment_Inventory_Quantity(Node1 *head1)
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
            getchar();
            printf("\n Enter quantity: ");
            scanf("%d", &quantity);
            curr->data.Quantity = quantity;
            printf("\n Record modified successfully\n");
            break;
        }
    }
    printf("\n \t Press any key to exit");
    getchar();
}

void Import_Database(Node1 **head1, Node2 **head2)
{
    FILE *fp;
    fp = fopen("Equipment_Inventory_DataBase.txt", "r");
    Equipment_Inventory equipInvent;
    int n;
    fscanf(fp, "%d", &n);
    while (n--)
    {
        fscanf(fp, "%d %d %d %[^\n] %[^\n]", &equipInvent.available, &equipInvent.Quantity, &equipInvent.issueQuantity,
               equipInvent.Sport, equipInvent.equipmentName);
        Insert_Equipment_Inventory(head1, equipInvent);
    }
    fclose(fp);

    fp = fopen("Sport_Equipment_Management_DataBase.txt", "r");
    Sport_Equipment_Management equipManage;
    fscanf(fp, "%d", &n);
    while (n--)
    {
        fscanf(fp, "%s %d %d %d %d %d %ld %[^\n] %[^\n] %[^\n]", equipManage.equipmentID, &equipManage.issueDate,
               &equipManage.dueDate, &equipManage.returnDate, &equipManage.NoOfDaysDelayed, &equipManage.fine,
               &equipManage.studentID, equipManage.equipmentName, equipManage.incharge, equipManage.Sport);
        Insert_Sport_Equipment_Management(head2, equipManage);
    }
    fclose(fp);
    Display_Equipment_Inventory(*head1);
    Display_Sport_Equipment_Management(*head2);
}

void Update_Database(Node1 *head1, Node2 *head2)
{
    FILE *fp;
    fp = fopen("Temp_Equipment_Inventory_DataBase.txt", "w");
    int len = countNode_Inventory(head1);
    fprintf(fp, "%d  \n", len);
    while (head1 != NULL)
    {
        fprintf(fp, "%d  %d  %d  \n%s  \n%s  \n", head1->data.available, head1->data.Quantity,
                head1->data.issueQuantity, head1->data.Sport, head1->data.equipmentName);
        head1 = head1->next;
    }
    fclose(fp);

    fp = fopen("Temp_Sport_Equipment_Management.txt", "w");
    len = countNode_Management(head2);
    fprintf(fp, "%d  \n", len);
    while (head2 != NULL)
    {
        fprintf(fp, "%s  %d  %d  %d  %d  %d  %d  \n%s  \n%s  \n%s  \n", head2->data.equipmentID, head2->data.issueDate, head2->data.dueDate,
                head2->data.returnDate, head2->data.NoOfDaysDelayed, head2->data.fine, head2->data.studentID, head2->data.equipmentName,
                head2->data.incharge, head2->data.Sport);
        head2 = head2->next;
    }
    fclose(fp);
}

int main()
{
    Node1 *head1 = NULL;
    Node2 *head2 = NULL;
    Import_Database(&head1, &head2);
    int who;
    do
    {
        system("cls");
        title();
        printf(" 1. user\n 2. admin \n");
        printf("Enter your identity : ");
        scanf("%d", &who);
        if (who == 2)
        {
            if (Verification() == 1)
            {
                printf("\nLogged in Successfully\n");
            }
            else
            {
                printf("\nInvalid User\n");
                who = 0;
            }
            printf("\n\tPress any key to continue ");
            getchar();
            getchar();
        }
    } while (who != 1 && who != 2);
    char ch = 'y';
    do
    {
        switch (who)
        {
        case 1:
            system("cls");
            title();
            int user_choose;
            printf("\n\t\tWelcome!!\nYou have logged into the student account.\n");
            printf(" 1. Issue \n 2. Return \n 3. Check Availability of sports Equipment \n 4. History\n");
            printf(" Enter your work : ");
            scanf("%d", &user_choose);
            switch (user_choose)
            {
            case 1:
                user_issue(head1, head2);
                break;
            case 2:
                user_return(head1, head2);
                break;
            case 3:
                User_Check_Availability(head1, head2);
                break;
            case 4:
                getchar();
                int studId;
                printf(" Enter your studentId : ");
                scanf("%d", &studId);
                Student_History(head2, studId);
                break;
            default:
                break;
            }
            break;
        case 2:
            system("cls");
            title();
            int admin_choose;
            printf("\n\t\tWelcome!!\nYou have logged into the admin account\n");
            printf("1: Display equipments inventory \n2: Display equipments inventory by sports name \n3: Modify equipment quantity record \n4: Insert record of equipment\n\n");
            printf("Enter your work : ");
            scanf("%d", &admin_choose);
            switch (admin_choose)
            {
            case 1:
                Display_Equipment_Inventory(head1);
                break;
            case 2:
                DISPLAY_Equipment_Inventory_By_Sport(head1);
                break;
            case 3:
                Modify_Equipment_Inventory_Quantity(head1);
                break;
            case 4:
                Equipment_Inventory equipInvent;
                printf(" Fill details\n");
                getchar();
                printf("Quantity : ");
                scanf("%d", &equipInvent.Quantity);
                printf("Sport : ");
                scanf("%[^\n]", equipInvent.Sport);
                printf("Equipment name : ");
                scanf("%[^\n]", equipInvent.equipmentName);
                equipInvent.available = equipInvent.Quantity;
                equipInvent.issueQuantity = 0;
                Insert_Equipment_Inventory(&head1, equipInvent);
                break;
            default:
                break;
            }
            break;
        }
        getchar();
        printf("Enter you want to continue(y/n) : ");
        scanf("%c", &ch);
    } while (ch == 'y');
    // Update_Database(head1, head2);
    return 0;
}