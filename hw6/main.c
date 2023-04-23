#include <stdio.h>

int main(){

    /*int choice;
    printf("Welcome operator, please select an option to continue:\n\n");
    
    int status = 1;
    do{
        printf( "1- File Operations\n"
                "2- Query products\n"
                "3- Check stock status\n"
                "4- Stock control by brand\n"
                "5- Export report\n"
                "6- Help\n\n"); 
        printf("Choose one option, To exit enter 5: ");
        scanf("%d",&choice);

        switch(choice){
        case 1: status = fileOperation(); break;
        case 2: status = queryProducts(); break; 
        case 3: status = stockStatus(); break;
        case 5: status = exportReport(); break;
        case 6: status = help(); break;                    
        default: printf("invalid option, please select between [1-6]\n\n");
        }

    }while(!status);*/
    

    addStock();
}

int addProduct(){
    FILE *fp = fopen("products.txt","a");

    int pID= getProductCount()+1;
    char type;
    char name[9];
    char brand[6];
    double price;

    printf("Enter a new Type(char): ");
    scanf(" %c",&type);

    printf("Enter a new product name (MAX 8 CHAR LENGHT): ");
    scanf("%s",name);

    printf("Enter a new brand name of %s (MAX 5 CHAR LENGHT): ",name);
    scanf("%s",brand);

    printf("Enter a new price of %s (MAX 8 CHAR LENGHT): ",name);
    scanf("%lf",&price);

    fprintf(fp, "\n%d,%c,%s,%s,%lf", pID, type, name, brand, price);
    fclose(fp);
    
    return 0;

}

int updateProduct(){

    int pID;
    char feature[10];
    char value[10];
    printf("Enter the pID of the product to be updated: ");
    scanf("%d",&pID);
    printf("Enter the name of the feature to be updated: ");
    scanf("%s",feature);
    printf("Enter the new value for that feature: ");
    scanf("%s",value);

    char features[4][10];
    FILE *fp = fopen("products.txt","r+");
    fscanf(fp,"%s,%s,%s,%s,%s\n",features[0],features[1],features[2],features[3],features[4]);

    FILE *fp2 = fopen("temp.txt","w+");

    char c;
    while((c = fgetc(fp))!='\n'){
        fputc(c,fp2);
    }
    fputc('\n',fp2);

    int pID2;
    char type;
    char name[9];
    char brand[6];
    double price;
    while(fscanf(fp, "%d,%c,%[^,],%[^,],%lf", &pID2, &type, name, brand, &price) == 5){
        if(pID2 != pID){
            fprintf(fp2, "%d,%c,%s,%s,%.2lf\n", pID2, type, name, brand, price);
           
        }
        else{
            switch (strComp(feature,features)){  
            case 1: fprintf(fp2, "%d,%s,%s,%s,%.2lf\n", pID2, value, name, brand, price);break;
            case 2: fprintf(fp2, "%d,%c,%s,%s,%.2lf\n", pID2, type, value, brand, price);break;
            case 3: fprintf(fp2, "%d,%c,%s,%s,%.2lf\n", pID2, type, name, value, price);break;
            case 4: fprintf(fp2, "%d,%c,%s,%s,%s\n", pID2, type, name, brand, value);break;   
            case -1: printf("invalid feature name, please select between [pID, type, name, price]\n\n");break;
            }
        }
        
    }
    fclose(fp);
    fclose(fp2);
    remove("products.txt");
    rename("temp.txt","products.txt");
    return 0;

}

int strComp(char str1[], char str2[4][10]){

    int i;
    for(i=1;i<5;i++){
        for(int j=0;j<10;j++){
            if(str1[j] != str2[i][j]){
                break;
            }
            else if(str1[j] == '\0'&& str2[i][j] == '\0'){
                return i;
            }
            
        }
    }
    return -1;
}

int deleteProduct(){
    printf("Enter what product you want to delete: "); 
    int pID;
    scanf("%d",&pID);

    FILE *fp = fopen("products.txt","r+");
    FILE *fp2 = fopen("temp.txt","w+");

    int pID2;
    int newpID=1;
    char type;
    char name[9];
    char brand[6];
    double price;
    
    char c;
    while((c = fgetc(fp))!='\n'){
        fputc(c,fp2);
    }
    fputc('\n',fp2);

    while(fscanf(fp, "%d,%c,%[^,],%[^,],%lf", &pID2, &type, name, brand, &price) == 5){
        if(pID2 != pID){
            fprintf(fp2, "%d,%c,%s,%s,%.2lf\n", newpID, type, name, brand, price);
            newpID++;
        }
    }
    fclose(fp);
    fclose(fp2);
    remove("products.txt");
    rename("temp.txt","products.txt");
    return 0;

}

int addStock(){

    int sID;
    int pID;
    char brand[15];
    int current_stock;
    
    FILE *fp = fopen("stocks.txt","r+");

    char c;
    while((c = fgetc(fp))!='\n');

    while(fscanf(fp, "%d,%d,%[^,],%d", &sID, &pID, brand, &current_stock) == 4);
    sID++;

    do{
        printf("Enter the pID of the product to be added: ");
        scanf("%d",&pID);
        if(pID>getProductCount()){
        printf("Invalid pID, please enter a valid pID\n");
        }
        

    }
    while(pID>getProductCount());

    printf("Enter the brand of the product to be added: ");
    scanf("%s",brand);
    printf("Enter the current stock of the product to be added: ");
    scanf("%d",&current_stock);

    fprintf(fp, "\n%d,%d,%s,%d", sID, pID, brand, current_stock);
    fclose(fp);
    return 0;

}

int getProductCount(){
    FILE *fp = fopen("products.txt","r+");
    int pID;
    char type;
    char name[9];
    char brand[6];
    double price;
    int count=0;

    int c;
    while((c = fgetc(fp))!='\n');

    while(fscanf(fp, "%d,%c,%[^,],%[^,],%lf", &pID, &type, name, brand, &price) == 5){
        count++;
    }
    fclose(fp);
    return count;
}
/*
int fileOperation(){

    int choice;
    int status;
    do{
        printf("-----FILE OPERATION-----\n");
        printf( "1) Add a new product\n"
                "2) Delete a product\n"
                "3) Update a product\n"
                "4) Add feature to products\n"
                "5) Add  a  new  stock  entry\n"
                "6)Delete a stock entry\n"
                "7)Update a stock entry\n"
                "8)Back to Menu\n");

        printf("What do you want?: ");
        scanf("%d",choice);
                      
        switch (choice) {
            case 1:status = addProduct();break;
            case 2:status = deleteProduct();break;
            case 3:status = updateProduct();break;
            case 4:status = newFeature();break;
            case 5:status = addStock();break;
            case 6:status = deleteStock();break;
            case 7:status = updateStock();break;
            case 8:status =0;break;
            default:printf("invalid option, Select between [1-8]\n\n ");
        }
        }while(status);

    printf("You terminated file operation, going to menu....\n\n") ;
    return 0;

}



int newFeature(){

}



int deleteStock(){

}

int updateStock(){

}




int queryProducts(){

}

int stockStatus(){

}

int exportReport(){

}*/