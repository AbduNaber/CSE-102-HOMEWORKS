#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct person {
    char name[20];
    int age;
    struct family *father;
    struct family *mother;
    struct family *child;
} Person;
void addnode(char name[], int age, char father[], char mother[]);
void savefamily(Person *p1);
void removefamily(char name[]);
void printnuclear(char name[]);
void removenode(char name[]);
void searchrelatives(char name[]);
void loadfamily(int menu);
int main(){

    Person *p1 = (Person *)malloc(sizeof(Person));
    Person *p2 = (Person *)malloc(sizeof(Person));
    char name[20];
    int age;
    char father[20];
    char mother[20];
    char child[20];
    int menu;
    do{
        printf("Family Tree System Menu:\n");
    printf("1. Add Family Tree\n");
    printf("2. Remove Family tree\n");
    printf("3. Load Family Tree\n");
    printf("4. EXIT\n");
    printf("> ");
    scanf("%d", &menu);
    switch (menu){
        case 1:
            printf("1. Add node \n");
            printf("2. Save family tree \n");
            printf("3. EXIT \n");
            printf("> ");
            scanf("%d", &menu);
            if(menu == 1){
                printf("Enter name: ");
                scanf("%s", name);
                printf("Enter age: ");
                scanf("%d", &age);
                printf("Enter father's name: ");
                scanf("%s", father);
                printf("Enter mother's name: ");
                scanf("%s", mother);
                addnode(name, age, father, mother);
                printf("%s has been added successfully... \n", name);
            }
            else if(menu == 2){
                printf("Saved family tree \n");
                savefamily(p1);
            }
            else if(menu == 3){
                printf("EXIT \n");

            }
            break;
        case 2:
            printf("enter the name of the txt file of family tree: ");
            scanf("%s", name);
            removefamily(name);
            printf("familyl.txt has been removed successfully... \n");
            break;
        case 3:
            printf("listing family tree \n");
            printf("1.family1.txt \n");
            printf("2.family2.txt \n");
            printf("> ");
            scanf("%d", &menu);
            printf("family%d.txt has been selected... \n", menu);
            loadfamily(menu);
            printf("select an option \n");
            printf("1. Add new person \n");
            printf("2. Remove person \n");
            printf("3. print a person's nuclear family \n");
            printf("4. search Relatives of Given Person \n");
            printf("5. EXIT \n");
            printf("> ");
            scanf("%d", &menu);
            if(menu ==1 ){
                printf("Enter name: ");
                scanf("%s", name);
                printf("Enter age: ");
                scanf("%d", &age);
                printf("Enter father's name: ");
                scanf("%s", father);
                printf("Enter mother's name: ");
                scanf("%s", mother);
                addnode(name, age, father, mother);
                printf("%s has been added successfully... \n", name);
            }
            else if(menu == 2){
                printf("Enter name: ");
                scanf("%s", name);
                removenode(name);
                printf("%s has been removed successfully... \n", name);
            }
            else if(menu == 3){
                printf("Enter name: ");
                scanf("%s", name);
                printnuclear(name);
            }
            else if(menu == 4){
                printf("Enter name: ");
                scanf("%s", name);
                searchrelatives(name);
            }
            else if(menu == 5){
                printf("EXIT \n");
                exit(0);
            }
            break;
        case 4:
            printf("EXIT \n");
            exit(0);
            break;
        }
        menu = 5;
    }while(menu != 4);
    

}

void addnode(char name[], int age, char father[], char mother[]){
   
}

void savefamily(Person *p1){
    
}

void removefamily(char name[]){
    
}
void printnuclear(char name[]){
    printf("name: %s \n", name);
    printf("age: 20 \n");
    printf("father: John \n");
    printf("mother: Terreisa \n");
    printf("children: Emily \n");

}

void removenode(char name[]){
    
}

void searchrelatives(char name[]){
    int menu;
    printf("select type of revatives \n");
    printf("1. parents \n");
    printf("2. children \n");
    printf("3. spouse \n");
    printf("4. grandparents \n");
    printf("5. cousin \n");
    printf("6. EXIT \n");
    printf("> ");
    scanf("%d", &menu);
    if(menu == 1){
        printf("parents are Terreisa and John \n");
    }
    else if(menu == 2){
        printf("children is emily\n");
    }
    else if(menu == 3){
        printf("spouse are not found \n");
    }
    else if(menu == 4){
        printf("grandparents are not found \n");
    }
    else if(menu == 5){
        printf("cousin  are not found\n");
    }
    else if(menu == 6){
        printf("EXIT \n");
    }
}

void loadfamily(int menu){
    
}