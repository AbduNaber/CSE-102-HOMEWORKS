#include "util.h"


int main(){
    family_t *family1;
    family_t *family2;
    int choice;
    int num;
    
    do{
        printf("**********************************\n");
        printf("1. Add family tree\n");
        printf("2. Remove family tree\n");
        printf("3. load family tree\n");
        printf("4. exit\n");
        printf(">");
        scanf("%d", &choice);
        if(choice < 1 || choice > 4){
            printf("Invalid choice\n");
            continue;
        }
    }while(choice < 1 || choice > 4);
    switch (choice){
        case 1:
            addfa(family1);
    }

}