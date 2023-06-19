#include "util.h"

int addFamily(family_t *root){
    int choice;
    do{
        printf("1. Add node\n");
        printf("2. Save Family tree\n");
        printf("3. exit\n");
        printf(">");
        scanf("%d", &choice);
        if(choice < 1 || choice > 4){
            printf("Invalid choice\n");
            continue;
        }
    }while(choice < 1 || choice > 4);
    switch (choice){
        case 1:
            addNode(root);
            break;
        case 2:
            saveFamily(root);
            break;
        case 3:
            return 0;
    }
}

int addNode(family_t *root){
    char name[20];
    int age;
    char father[20];
    char mother[20];
    printf("Enter name: ");
    scanf("%s", name);
    printf("Enter age: ");
    scanf("%d", &age);
    printf("Enter father: ");
    scanf("%s", father);
    printf("Enter mother: ");
    scanf("%s", mother);
    family_t *newNode = (family_t *)malloc(sizeof(family_t));
    strcpy(newNode->name, name);
    newNode->age = age;

    newNode->father = NULL;
    newNode->mother = NULL;

    if(root == NULL){
        root = newNode;
    }
    else{
        family_t *temp = root;
        while(temp->father != NULL){
            temp = temp->father;
        }
        temp->father = newNode;
    }

}