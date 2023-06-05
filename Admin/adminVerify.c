#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
            return 1;
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
    fp = fopen("Admin.txt", "r");
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

int main()
{
    if (Verification())
        printf("Valid User\n");
    else
        printf("Invalid User\n");
    getchar();
    return 0;
}