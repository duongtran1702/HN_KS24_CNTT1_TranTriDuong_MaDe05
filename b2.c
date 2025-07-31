#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Book
{
    char title[100];
    char author[50];
    int year;
} Book;

typedef struct TreeNode
{
    Book data;
    struct TreeNode *left;
    struct TreeNode *right;
} Tree;

Tree *create(Book book)
{
    Tree *node = (Tree *)malloc(sizeof(Tree));
    node->data = book;
    node->left = node->right = NULL;
    return node;
}

Tree *insert(Tree *root, Book book)
{
    if (root == NULL)
    {
        root = create(book);
        return root;
    }
    else if (strcmp(book.title, root->data.title) < 0)
    {
        root->left = insert(root->left, book);
    }
    else if (strcmp(book.title, root->data.title) > 0)
    {
        root->right = insert(root->right, book);
    }
    else
        printf("The title existed\n");
    return root;
}

void display(Tree *root)
{
    if (root == NULL)
        return;
    display(root->left);
    printf("%s %s %d\n", root->data.title, root->data.author, root->data.year);
    display(root->right);
}

void freeTree(Tree *root)
{
    if (root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

Tree *search(Tree *root, char *title)
{
    if (root == NULL)
        return;
    search(root->left, title);
    search(root->right, title);
    if (strcmp(root->data.title, title) == 0)
        return root;
}

void menu()
{
    printf("1.Them sach\n");
    printf("2. Hien thi\n");
    printf("3. Tim kiem\n");
    printf("4. Xoa\n");
    printf("0. Thoat\n");
}
int main()
{
    Book a = {"aaa", "aaa", 3};
    Book b = {"bbb", "aaa", 3};
    Book c = {"ccc", "aaa", 3};
    Tree *root = insert(root, b);
    root = insert(root, a);
    root = insert(root, c);

    int choice;
    do
    {
        menu();
        printf("Nhap lua chon: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("Lua chon khong hop le!\n");
            while (getchar() != '\n')
                ;
            continue;
        }
        getchar();
        if (choice == 0)
        {
            printf("Thoat chuong trinh");
            freeTree(root);
        }
        else if (choice == 1)
        {
            Book book;
            printf("Nhap tieu de sach: ");
            fgets(book.title, sizeof(book.title), stdin);
            book.title[strcspn(book.title, "\n")] = '\0';

            printf("Nhap tac gia sach: ");
            fgets(book.author, sizeof(book.author), stdin);
            book.author[strcspn(book.author, "\n")] = '\0';

            printf("Nhap nam xuat ban: ");
            scanf("%d", &book.year);
            printf("%s %s %d\n", book.title, book.author, book.year);

            root = insert(root, book);
        }
        else if (choice == 2)
        {
            display(root);
        }
        else if (choice == 3)
        {
            char tmp[100];
            fgets(tmp, 100, stdin);
            tmp[strcspn(tmp, "\n")] = '\0';
            Tree *found = search(root, tmp);
            if (found)
                printf("%s %s %d\n", found->data.title, found->data.author, found->data.year);
        }
    } while (choice != 0);
}
