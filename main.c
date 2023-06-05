#include "LLImple.c"
#include "user.c"
#include "admin.c"
// struct Equipment_Inventory typedef Equipment_Inventory;
int main()
{
    Node1 *head1 = NULL;
    Node2 *head2 = NULL;

    FILE *fp1, *fp2;
    fp1 = fopen("Equipment_Inventory_DataBase.txt", "r+");
    fp2 = fopen("Sport_Equipment_Management_DataBase.txt", "r+");
    int n;
    fscanf(fp1, "%d", &n);
    while (n--)
    {
        Equipment_Inventory equipInvent;
        fscanf(fp1, "%d %d %d %s %s", &equipInvent.available, &equipInvent.Quantity, &equipInvent.issueQuantity, equipInvent.Sport, equipInvent.equipmentName);
        Insert_Equipment_Inventory(&head1, equipInvent);
    }
    Sport_Equipment_Management equipManage;
    fscanf(fp2, "%d", &n);
    while (n--)
    {
        fscanf(fp2, "%d %d %d %d %d %d %ld %s %s %s", &equipManage.equipmentID, &equipManage.issueDate, &equipManage.dueDate, &equipManage.returnDate,
               &equipManage.NoOfDaysDelayed, &equipManage.fine, &equipManage.studentID, equipManage.equipmentName, equipManage.incharge, equipManage.Sport);
        Insert_Sport_Equipment_Management(&head2, equipManage);
    }
    fclose(fp1);
    fclose(fp2);
    int who;
    do
    {
        printf("Choose your identity : \n");
        printf("--->1. user\n--->2. admin \n");
        scanf("%d", &who);
    } while (who != 1 && who != 2);
    switch (who)
    {
    case 1:
        int user_choose;
        printf("Welcome!! You have logged into the student account.\n\n\n");

        printf("Choose your work\n");
        printf("1:issue \n2: return \n3: display the content\n\n");
        scanf("%d", &user_choose);
        switch (user_choose)
        {
        case 1:
            // user_issue(head1, head2);
            break;
        case 2:
            // user_return(head1, head2);
        case 3:
            // User_Display(head1, head2);
        default:
            break;
        }
        break;
    case 2:
        printf("Choose your work\n");
        printf("Welcome!! You have logged into the admin account.\n\n");
        int admin_choose;
        // printf("Choose your work\n");
        printf("1: Display equipments inventory \n2: Display equipments inventory by  sports name \n3: Modify equipment record \n4: Insert record of equipment\n\n");
        scanf("%d", &admin_choose);
        switch (admin_choose)
        {
        case 1:
            // LDISPLAY1(head1);
            break;
        case 2:
            // DISPLAY_Equipment_Inventory(head1);
            break;
        case 3:
            // Modify_Equipment_Inventory(head1);
        case 4:
            // LINSERT1(head1);
        default:
            break;
        }
        break;
    }
    return 0;
}