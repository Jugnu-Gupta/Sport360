#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
// #include "LLImple.c"

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
    if (min_year != 100000 && min_month != 1 && min_day != -1)
        return min_day * 1000000 + min_month * 10000 + min_year;
    else
        return -1;
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
        printf("desired equipment is not available.");
        int nearestAvailableDate = nearest_Availibility_Date(head2);
        if (nearestAvailableDate == -1)
        {
            printf("equipment is not  available");
        }
        else
        {
            printf("\nEquipment will be available by : %d-%d-%d\n", nearestAvailableDate / 1000000, (nearestAvailableDate % 1000000) / 10000, nearestAvailableDate % 10000);
        }
    }
    else
    {
        Sport_Equipment_Management equipManage;
        strcpy(equipManage.Sport, sport);
        strcpy(equipManage.equipmentName, equip);
        printf("Incharge  StudentID  equipmentID  issueDate");
        scanf("%s %s %s %d", equipManage.incharge, equipManage.studentID, equipManage.equipmentID, equipManage.issueDate);
        equipManage.returnDate = -1;
        equipManage.dueDate = updateDate(equipManage.issueDate);
        printf("The due date for the item : %d-%d-%d\n", equipManage.dueDate / 1000000, (equipManage.dueDate % 1000000) / 10000, equipManage.dueDate % 10000);
        LINSERT2(&head2, equipManage);
        printf("Issued Successfully\n");
    }
}

void user_issue(Node1 *head1, Node2 *head2)
{
    printf("enter your desired sport \n");
    int choice;
    char equip_No;
    char sport[50];
    char equip[50];
    printf("1) table tennis  \n 2) cricket \n 3) badminton \n 4) basketball \n 5) football \n 6) lawn tennis \n 7) chess \n 8) carrom \n 9) hockey \n 10) volleyball \n");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        strcpy(sport, "Table Tennis");
        printf("Choose the equipment:\n");
        printf("a) racquet\n b) ball\n c) net\n");
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
        printf("Choose the equipment:\n");
        printf("a) bat\n b) leather ball\n c) tennis ball\n d) kit \n e) stumps\n");
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
        printf("Choose the equipment:\n");
        printf("a) racquet\n b) shuttelcock\n");
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
        printf("Choose the equipment:\n");
        printf("a) basketball\n");
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
        printf("Choose the equipment:\n");
        printf("a) football\n b) gloves\n c) kit\n");
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
        printf("Choose the equipment:\n");
        printf("a) racquet\n b) ball\n");
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
        printf("Choose the equipment:\n");
        printf("a) chess set\n");
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
        printf("Choose the equipment:\n");
        printf("a) board\n b) carrom coins\n c) powder\n");
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
        printf("Choose the equipment:\n");
        printf("a) hockey stick\n b) hockey ball\n c) kit\n");
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
        printf("Choose the equipment:\n");
        printf("a) volleyball\n");
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
                head1->data.available--;
                head1->data.issueQuantity++;
                printf("\nEquipment is Available\n");
                return;
            }
            else
            {
                printf("\nEquipment is not Available\n");
                return;
            }
        }
        head1 = head1->next;
    }
}

void User_Display(Node1 *head1, Node2 *head2)
{
    printf("enter your desired sport \n");
    int choice;
    char equip_No;
    char sport[50];
    char equip[50];
    printf("1) table tennis  \n 2) cricket \n 3) badminton \n 4) basketball \n 5) football \n 6) lawn tennis \n 7) chess \n 8) carrom \n 9) hockey \n 10) volleyball \n");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        strcpy(sport, "table tennis");
        printf("Choose the equipment:\n");
        printf("a)racquet\n b)ball\n c)net\n");
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
        printf("Choose the equipment:\n");
        printf("a) bat\n b) leather ball\n c) tennis ball\n d) kit\n e) stumps\n");
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
        default:
            printf("\nInvalid Input!!");
            break;
        case 'e':
            strcpy(equip, "Stumps");
            user_display_Quantity(head1, sport, equip);
            break;
        default:
            printf("\nInvalid Input!!");
            break;
        }
        break;
    case 3:
        strcpy(sport, "Badminton");
        printf("Choose the equipment:\n");
        printf("a) racquet\n b) shuttelcock\n");
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
        printf("Choose the equipment:\n");
        printf("a)basketball\n");
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
        printf("Choose the equipment:\n");
        printf("a) football\n b) gloves\n c) kit\n");
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
        printf("Choose the equipment:\n");
        printf("a) racquet\n b) ball\n");
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
        printf("Choose the equipment:\n");
        printf("a) chess set\n");
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
        printf("Choose the equipment:\n");
        printf("a) board\n b) carrom coins\n c) powder\n");
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
        printf("Choose the equipment:\n");
        printf("a) hockey stick\n b) hockey ball\n c) kit\n");
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
        printf("Choose the equipment:\n");
        printf("a) volleyball\n");
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
    // fgets(sport, 50, stdin);
}

void user_return(Node1 *head1, Node2 *head2)
{
    long int studId;
    int equipID;
    printf("Enter StudentID & EquipmentID");
    scanf("%ld %d", &studId, &equipID);
    while (head2 != NULL)
    {
        if (head2->data.studentID == studId && head2->data.equipmentID == equipID)
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
            // calculate fine.
            // printf fine.
            head2->data.NoOfDaysDelayed = calculateDays(head2->data.dueDate, head2->data.returnDate);
            head2->data.fine = (head2->data.NoOfDaysDelayed) * 10;
            if (head2->data.fine != 0)
            {
                printf("\nFine = %d Rs\n", head2->data.fine);
            }
            printf("\nSports equipment successfully\n");
        }
        head2 = head2->next;
    }
    printf("\nYou havn't issue any sports equipment\n");
}

// bool isempty_studID(Node2 *head2, long int studID)
// {
//     while (head2 != NULL)
//     {
//         if (head2->data.studentID == studID)
//             if (head2->data.returnDate == -1)
//                 return 1;
//             else
//                 return 0;

//         head2 = head2->next;
//     }
//     return 0;
// }

// Assumption here is that "latest date" has highest value when compared year, month or date wise.
// Function to sort records based on dueDate(i.e latest date first).
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
    printf("\nNot returned");
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

    printf("\nReturned");
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