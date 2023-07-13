#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Define a struct named Node that contains a void pointer named data and a Node pointer named next. 
typedef struct Node { 
    void* data; 
    struct Node* next; 
} Node;

typedef struct{
    char type[20];
} Asset;

// Asset1, Asset2, Asset3, and Asset4 are four different types of assets.
typedef struct { 
    char type[20]; 
    int ivals[1]; 
    double svals[1]; 
} Asset1;


typedef struct { 
    char type[20]; 
    double svals[2]; 
    int ivals[2]; 
}Asset2;

typedef struct { 
    char type[20]; 
    char string1[50]; 
    char string2[50]; 
}Asset3;

typedef struct { 
    char type[20]; 
    double value1; 
    float value2; 
    double value3; 
}Asset4;

void fillLinkedList(struct  Node**  head); // this function fills linkedlist romdomly
void serializeLinkedList(struct Node* head); // This function serializes the linked list and writes it to a binary file named output.bin.
void deserializeLinkedList(struct Node** head); // This function deserializes the linked list from the binary file named output.bin and prints the data to the screen.

int main(){

     // Create a head nodes for the linked list
    Node *serializehead = malloc(sizeof(Node));
    Node *deserializehead = malloc(sizeof(Node));
    
    fillLinkedList(&serializehead); // fill the linked list with random number of assets (between 10 and 20)
    serializeLinkedList(serializehead); // serialize the linked list 
    free(serializehead); // free the memory allocated for the linked list
    deserializeLinkedList(&deserializehead); // deserialize the linked list
    free(deserializehead); // free the memory allocated for the linked list
    
    return 0;
}

void  fillLinkedList(struct  Node**  head){


    printf("Filling the linked list\n");
    srand(time(NULL));
    int assetnum = rand() % 11 + 10; // Generate a random number between 10 and 20 for the number of assets.

    // Create a linked list with random number of assets.
    int whichasset;
    int i,j;
    Node *cp = *head;
    Asset1 *asset1;
    Asset2 *asset2;
    Asset3 *asset3;
    Asset4 *asset4;
    for(i=0;i<assetnum;i++){

        whichasset =rand()%4+1;// Generate a random number between 1 and 4 to determine which asset to create.
        
        /* 
         * Create an asset according to the random number generated.
         * Assign the asset to the data field of the current node.
         * Create a new node and assign it to the next field of the current node.
         * Write the asset to the file.
         * Print the asset to the screen.
         * Repeat the process until the number of assets is reached.
        */
        switch(whichasset){
            case 1:
                asset1 = malloc(sizeof(Asset1)); 
                strcpy (asset1->type,"Asset1");
                asset1->ivals[0] = rand(); 
                asset1->svals[0] =(double)rand()/(double)(RAND_MAX);
                cp->data = asset1; 
                cp->next = malloc(sizeof(Node)); 
                cp = cp->next;

                break;

            case 2:
                asset2 = malloc(sizeof(Asset2));
                strcpy (asset2->type,"Asset2"); 
                asset2->ivals[0] = rand();
                asset2->ivals[1] = rand();
                asset2->svals[0] = (double)rand()/(double)(RAND_MAX);
                asset2->svals[1] = (double)rand()/(double)(RAND_MAX);
                cp->data = asset2;
                cp->next = malloc(sizeof(Node));
                cp = cp->next;


                break;
            case 3:
                asset3 = malloc(sizeof(Asset3));
                strcpy (asset3->type,"Asset3");
                strcpy(asset3->string1,"nothingMatters");
                strcpy(asset3->string2,"nothingReallyMatters");
                cp->data = asset3;
                cp->next = malloc(sizeof(Node));
                cp = cp->next;

            case 4:
                asset4 = malloc(sizeof(Asset4));
                strcpy (asset4->type,"Asset4");
                asset4->value1 = (double)rand()/(double)(RAND_MAX);
                asset4->value2 = (float)rand()/(float)(RAND_MAX);
                asset4->value3 =(double)rand()/(double)(RAND_MAX);
                cp->data = asset4;
                cp->next = malloc(sizeof(Node));
                cp = cp->next;

                break;
        }
        
    }
    cp->data = NULL; // Assign NULL to the data field of the last node.
    cp->next = NULL; // Assign NULL to the next field of the last node.
    printf("Filling is done\n");
    printf("--------------------\n");

}


/*
 * Function: serializeLinkedList
 * ----------------------------
 * This function serializes the linked list and writes it to a binary file named output.bin.
 */
void serializeLinkedList(struct Node* head){

        FILE *fp;
        fp = fopen("linkedlist.bin","wb");

        if(fp == NULL){
            printf("Error opening file\n");
            return;
        }

        printf("serializing...\n");

        Node *cp = head;
        int i,j;
        Asset1 *asset1;
        Asset2 *asset2;
        Asset3 *asset3;
        Asset4 *asset4;
        while(cp->data != NULL){


            char type[20];
            strcpy(type,((Asset *)cp->data)->type); // Copy the type of the asset to the type variable.
            if(strcmp(type,"Asset1")==0){ // If the type of the asset is Asset1, write the asset to the file.
                asset1 = cp->data;
                fwrite(asset1,sizeof(Asset1),1,fp);
                printf("Asset1: %d %lf\n",asset1->ivals[0],asset1->svals[0]);
            }
            else if(strcmp(type,"Asset2")==0){ // If the type of the asset is Asset2, write the asset to the file.
                asset2 = cp->data;
                fwrite(asset2,sizeof(Asset2),1,fp);
                 printf("Asset2: %d %d %.5lf %.5lf\n",asset2->ivals[0],asset2->ivals[1],asset2->svals[0],asset2->svals[1]);

            }
            else if(strcmp(type,"Asset3")==0){ // If the type of the asset is Asset3, write the asset to the file.
                asset3 = cp->data;
                fwrite(asset3,sizeof(Asset3),1,fp);
                printf("Asset3: %s %s\n",asset3->string1,asset3->string2);
            }
            else if(strcmp(type,"Asset4")==0){ // If the type of the asset is Asset4, write the asset to the file.
                asset4 = cp->data;
                fwrite(asset4,sizeof(Asset4),1,fp);
                printf("Asset4: %.5lf %.5f %.5lf\n",asset4->value1,asset4->value2,asset4->value3);
            }
            cp = cp->next;
        }
    fclose(fp);

 }

/*
 * Function: deserializeLinkedList
 * ----------------------------
 * This function deserializes the linked list from the binary file named output.bin and prints the data to the screen.
 */
void deserializeLinkedList(struct Node** head){


    FILE *fp;
    fp = fopen("linkedlist.bin","rb");

    if(fp == NULL){
        printf("Error opening file\n");
        return;
    }

    printf("deserializing...\n");

    Node *cp = *head;
    int i,j;
    Asset1 *asset1;
    Asset2 *asset2;
    Asset3 *asset3;
    Asset4 *asset4;
    
    while(feof(fp)==0){

        int pos = ftell(fp); // Get the position of the file pointer.

        char type[20];
        int a = fread(type,sizeof(char),20,fp); // Read the type of the asset.
        if(a==0){ // If the end of the file is reached, break the loop.
            break;
        }


        /* 
         *if-else statements to determine the type of the asset.

         * If the type of the asset is Asset1, create an Asset1 struct 
         * Go to the position of the asset in the file and read the asset.
         * Print the asset to the screen.
         * Create a new node and assign it to the next field of the current node.
         * Repeat the process until the end of the file is reached.
        */
        if(strcmp(type,"Asset1")==0){
            asset1 = malloc(sizeof(Asset1));
            fseek(fp,pos,SEEK_SET);
            fread(asset1,sizeof(Asset1),1,fp);
            printf("Asset1: %d %.5lf\n",asset1->ivals[0],asset1->svals[0]);
            cp->data = asset1;
            cp->next = malloc(sizeof(Node));
            cp = cp->next;
        }

        else if(strcmp(type,"Asset2")==0){
            asset2 = malloc(sizeof(Asset2));
            fseek(fp,pos,SEEK_SET);
            fread(asset2,sizeof(Asset2),1,fp);
            printf("Asset2: %d %d %.5lf %.5lf\n",asset2->ivals[0],asset2->ivals[1],asset2->svals[0],asset2->svals[1]);
            cp->data = asset2;
            cp->next = malloc(sizeof(Node));
            cp = cp->next;
        }
        else if(strcmp(type,"Asset3")==0){
            asset3 = malloc(sizeof(Asset3));
            fseek(fp,pos,SEEK_SET);
            fread(asset3,sizeof(Asset3),1,fp);
            printf("Asset3: %s %s\n",asset3->string1,asset3->string2);
            cp->data = asset3;
            cp->next = malloc(sizeof(Node));
            cp = cp->next;
        }

        else if(strcmp(type,"Asset4")==0){
            asset4 = malloc(sizeof(Asset4));
            fseek(fp,pos,SEEK_SET);
            fread(asset4,sizeof(Asset4),1,fp);
            printf("Asset4: %.5lf %.5f %.5lf\n",asset4->value1,asset4->value2,asset4->value3);
            cp->data = asset4;
            cp->next = malloc(sizeof(Node));
            cp = cp->next;
        }

    }
    printf("done\n");
    fclose(fp);
}
