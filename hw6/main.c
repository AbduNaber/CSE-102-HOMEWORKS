#include <stdio.h>

#define MAX 100
#define FEATURE_LENGTH 15

int addProduct();
int deleteProduct();
int addStock();
int updateProduct();
int exportReport(double arr[][3],int size);
int outOfStock();
int listStock();
int queryStock();
int printFilteredpID(int arr);
int cmpStr(char arr[],char arr2[]);
int featureFinder(FILE *fp,char arr[MAX][FEATURE_LENGTH]);
int listProducts();
int strCompFeature(char str1[], char str2[][15], int size);
int getProductCount();
int filterProducts();
int fileOperation();
int stockStatus();
int help();
int deleteStock();
int updateProduct();
int updateProduct();
int updateStock();
int newFeature();
int brandStock(double filteredProduct[][3],int *num);
int searchProducts();

int main(){
    
    double filteredProduct[100][3]= {0};// 0->pID 1->price 2->stock 
    
    int num=0;
    int choice;
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
        case 2: status = searchProducts(); break; 
        case 3: status = stockStatus(); break;
        case 4: status = brandStock(filteredProduct,&num);
        case 5: status = exportReport(filteredProduct,num); break;
        case 6: status = help(); break;                    
        default: printf("invalid option, please select between [1-6]\n\n");
        }
    }while(!status);
    printf("You terminated the program, Goodbye!\n");
    return 0;
}

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
        scanf("%d",&choice);
                      
        switch (choice) {
            case 1:status = addProduct();break;
            case 2:status = deleteProduct();break;
            case 3:status = updateProduct();break;
            case 4:status = newFeature();break;
            case 5:status = addStock();break;
            case 6:status = deleteStock();break;
            case 7:status = updateStock();break;
            case 8:status =1;break;
            default:printf("invalid option, Select between [1-8]\n\n ");
        }
        }while(!status);

    printf("You terminated file operation, going to menu....\n\n") ;
    return 0;

}

int help(){}

int addProduct(){

    int pID= getProductCount()+1;

    FILE *fp = fopen("products.txt","r+");
    if(fp == NULL){
        printf("File could not be opened\n");
        return -1;
    }

    char features [MAX][FEATURE_LENGTH];

    int numFeatures=0; 
    fscanf(fp, "%[^,]", features[numFeatures]);
    while (fscanf(fp, ",%[^,\n]", features[numFeatures + 1]) == 1) {
        numFeatures++;
    }
    numFeatures++;

    // go to end of file using while loop
    char c;
    while((c=fgetc(fp))!=EOF);
    fprintf(fp,"\n");

    char type;
    char name[9];
    char brand[6];
    double price;

    for(int i=1;i<numFeatures;i++){
        printf("Enter the %s of the product: ",features[i]);
        scanf("%s",features[i]);
        
    }
    
    fprintf(fp,"%d,",pID);
    for(int i=1;i<numFeatures-1;i++){
        fprintf(fp,"%s,",features[i]);
    }
    fprintf(fp,"%s",features[numFeatures-1]);   

    fclose(fp);
    printf("Product added successfully\n\n");
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

    FILE *fp = fopen("products.txt","r+");
    if(fp == NULL){
        printf("File could not be opened\n");
        return -1;
    }

    FILE *fp2 = fopen("temp.txt","w+");
    if(fp2 == NULL){
        printf("File could not be opened\n");
        return -1;
    }

    char features [MAX][FEATURE_LENGTH];

    int numFeatures=0; 
    fscanf(fp, "%[^,]", features[numFeatures]);
    fprintf(fp2,"%s",features[numFeatures]);
    while (fscanf(fp, ",%[^,\n]", features[numFeatures + 1]) == 1) {
        fprintf(fp2,",%s",features[numFeatures + 1]);
        numFeatures++;
    }
    numFeatures++;

    fprintf(fp2,"\n");

    int pID2;
    char temp[15];
    char c;
    while(fscanf(fp,"%d",&pID2)==1){
        if(pID2 != pID){
            fprintf(fp2,"%d",pID2);
            for(int i=1;i<numFeatures;i++){
                fscanf(fp,",%[^,\n]",temp);
                fprintf(fp2,",%s",temp);
            }
        }
        else{
            fprintf(fp2,"%d",pID2);
            for(int i=1;i<numFeatures;i++){
                fscanf(fp,",%[^,\n]",temp);
                if(strCompFeature(feature,features,numFeatures)!=i){
                    fprintf(fp2,",%s",temp);
                }
                else{
                    fprintf(fp2,",%s",value);
                }   
            }
        }
        fprintf(fp2,"\n");
    }
    
    fclose(fp);
    fclose(fp2);
    remove("products.txt");
    rename("temp.txt","products.txt");
    return 0;

}

int strCompFeature(char str1[], char str2[][15], int size){

    int i;
    for(i=0;i<size;i++){
        for(int j=0;j<15;j++){
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
    if(fp == NULL){
        printf("File could not be opened\n");
        return -1;
    }

    FILE *fp2 = fopen("temp.txt","w+");
    if(fp2 == NULL){
        printf("File could not be opened\n");
        return -1;
    }

    char features [MAX][FEATURE_LENGTH];

    int numFeatures=0; 
    fscanf(fp, "%[^,]", features[numFeatures]);
    fprintf(fp2,"%s",features[numFeatures]);
    while (fscanf(fp, ",%[^,\n]", features[numFeatures + 1]) == 1) {
        fprintf(fp2,",%s",features[numFeatures + 1]);
        numFeatures++;
    }
    numFeatures++;

    fprintf(fp2,"\n");

    int pID2;
    char temp[15];
    char c;
    int temppID=1;
    while(fscanf(fp,"%d",&pID2)==1){
        if(pID2 != pID){
            fprintf(fp2,"%d",temppID);
            temppID++;
            for(int i=1;i<numFeatures;i++){
                fscanf(fp,",%[^,\n]",temp);
                fprintf(fp2,",%s",temp);
            }
        }
        else{
            for(int i=1;i<numFeatures;i++){
                fscanf(fp,",%[^,\n]",temp);
            } 
        }
        fprintf(fp2,"\n");
    }
    
    fclose(fp);
    fclose(fp2);
    remove("products.txt");
    rename("temp.txt","products.txt");
    printf("Product deleted successfully\n\n");
    return 0;

}

int addStock(){

    int sID;
    int pID;
    char brand[15];
    int current_stock;
    int productCount = getProductCount();
    int numberOfFeatures = 1;
    FILE *fp = fopen("stocks.txt","r+");

 
    while(fscanf(fp, "%d,%d,%[^,],%d", &sID, &pID, brand, &current_stock) == 4);
    sID++;

    do{
        printf("Enter the pID of the product to be added: ");
        scanf("%d",&pID);
        
        if(pID>productCount){
        printf("Invalid pID, please enter a valid pID[1-%d]\n",productCount);
        }
        

    }
    while(pID>productCount);

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
    if(fp == NULL){
        printf("Error opening file\n");
        return -1;
    }
    int c;
    while((c = fgetc(fp))!='\n');

    char temp[15];
    int pID;
    while(fscanf(fp, "%d",&pID)==1)
        while (fscanf(fp, ",%[^,\n]",temp) == 1) ;
            
    fclose(fp);
    return pID;
}

int deleteStock(){
    
    int sID; 
    printf("Enter what stock you want to delete: "); 
    scanf("%d",&sID);

    FILE *fp = fopen("stocks.txt","r+");
    FILE *fp2 = fopen("temp.txt","w+");

    int sID2;
    int newpID=1;
    int pID;
    char brand[15];
    int current_stock;
    
    char c;
    while((c = fgetc(fp))!='\n'){
        fputc(c,fp2);
    }
    fputc('\n',fp2);

    while(fscanf(fp,"%d,%d,%[^,],%d",&sID2,&pID,brand,&current_stock)==4){
        if(sID2 != sID){
            fprintf(fp2,"%d,%d,%s,%d\n",newpID,pID,brand,current_stock);
            newpID++;
        }
    }

            
    fclose(fp);
    fclose(fp2);
    remove("stocks.txt");
    rename("temp.txt","stocks.txt");
    return 0;

}

int updateStock(){

    int sID;
    

    printf("Enter the sID of the product to be updated: ");
    scanf("%d",&sID);

    char features[4][15];
    char feature[10];
    char value[10];
    FILE *fp = fopen("stocks.txt","r+");
    fscanf(fp, "%[^,],%[^,],%[^,],%[^\n]", features[0], features[1], features[2], features[3]);

    do{
        
        printf("Enter the name of the feature to be updated: ");
        scanf("%s",feature);
        if(strCompFeature(feature,features,4)==-1){
            printf("Invalid feature, please enter a valid feature\n");
        }
    }while(strCompFeature(feature,features,4)==-1); 

    printf("Enter the new value for that feature: ");
    scanf("%s",value);    
    
    FILE *fp2 = fopen("temp.txt","w+");

    int sID2;
    int pID;
    char brand[15];
    int current_stock;
    fprintf(fp2,"%s,%s,%s,%s\n",features[0],features[1],features[2],features[3]);

    fgetc(fp);
    while(fscanf(fp, "%d,%d,%[^,],%d", &sID2, &pID, brand, &current_stock) == 4){

        if(sID2 != sID){
            fprintf(fp2, "%d,%d,%s,%d\n", sID2, pID, brand, current_stock);
        }
        else{
            switch(strCompFeature(feature,features,4)){
                case 1: fprintf(fp2, "%d,%s,%s,%d\n", sID2, value, brand, current_stock);break;
                case 2: fprintf(fp2, "%d,%d,%s,%d\n", sID2, pID, value, current_stock);break;
                case 3: fprintf(fp2, "%d,%d,%s,%s\n", sID2, pID, brand, value);break;
                
                
            }
        }
    }
    fclose(fp);
    fclose(fp2);
    remove("stocks.txt");
    rename("temp.txt","stocks.txt");
    printf("Stock updated successfully\n\n");
    return 0;

}

int newFeature(){
    FILE *fp = fopen("products.txt","r+");
    if (fp == NULL) {
        printf("Error: could not open products file.\n");
        return 1;
    }
    FILE *fp2 = fopen("temp.txt","w+");
    if (fp2 == NULL) {
        printf("Error: could not open temp file.\n");
        return 1;
    }
    
    char features [MAX][FEATURE_LENGTH];
    int numFeatures=0; 
  
    fscanf(fp, "%[^,]", features[numFeatures]);
    fprintf(fp2, "%s", features[numFeatures]);
    while (fscanf(fp, ",%[^,\n]", features[numFeatures + 1]) == 1) {
        fprintf(fp2, ",%s", features[numFeatures+1]);
    numFeatures++;
    }
    printf("Enter the name of the new feature: ");
    scanf("%s",features[numFeatures+1]);
    numFeatures++;

    fprintf(fp2, ",%s", features[numFeatures]);
   char tempstr[100];
   while (fscanf(fp, "%[^,]", tempstr) == 1) {
        fprintf(fp2, "%s", tempstr);
        // read current row of data
        for (int i = 1; i < numFeatures; i++) {
            fscanf(fp, ",%[^,\n]", tempstr);
            fprintf(fp2, ",%s", tempstr);
        }

        // add "Null" value for new feature
        fprintf(fp2, ",Null");


    }
    
    fclose(fp);
    fclose(fp2);
    remove("products.txt");
    rename("temp.txt","products.txt");
    printf("New feature added successfully\n\n");
    return 0;

}

int searchProducts(){
    int choice;
    
    printf("-----SEARCH PRODUCTS-----\n"); 
    do {
        printf( "1) List all product\n"
                "2) Filter products by brand, type, price, or a user-defined feature\n"
                "3) 3.Back to main menu.\n");

        printf("What do you want?: ");
        scanf("%d",&choice);

        //switch case for the choice of the user 
        switch(choice){
            case 1: listProducts();break; //list all products
            case 2: filterProducts();break;//filter products
            case 3: printf("You terminated filtre option, going to menu....\n\n"); return 0; //back to main menu
            default: printf("Invalid choice\n\n");break;
        }
    }while(choice!=3);
}   

int listProducts(){
    FILE *fp = fopen("products.txt","r"); // read mode
    if (fp == NULL) { // if file does not exist
        printf("Error: could not open products file.\n"); // print error message
        return 1;
    }
    char c;
    while((c = fgetc(fp)) != '\n'); // skip first line
    while((c = fgetc(fp)) != EOF){ // while not end of file
        printf("%c",c); // print character
    }
    fclose(fp); // close file
    return 0;
}

int filterProducts(){

    char features [MAX][FEATURE_LENGTH];
    FILE *fp = fopen("products.txt","r");
    if (fp == NULL) {
          printf("Error: could not open products file.\n");
          return 1;
     }
    int numFeatures = featureFinder(fp,features);

    char FilterLabel[MAX];
    printf("Enter the feature you want to filter by(!Case-Sensitive! \"example == Brand,Samsung,Type,O\"): ");
    scanf("%s",FilterLabel);

    char filter[MAX][FEATURE_LENGTH];

    int i,j=0,k=0;
    for(i=0;FilterLabel[i]!='\0';i++){
        if(FilterLabel[i]==','){
            filter[j][k]='\0';
            j++;
            k=0; 
            continue;
        }
        filter[j][k]=FilterLabel[i];
        k++;

    }
    filter[j][i]='\0';
    j++;

    int fiterColumn[j+1];
    for(int a=0;a<=j;a++) fiterColumn[a]=0;
    int priceFlag=0;
    for(int a=0;a<=j;a++){
        for(int b=0;b<numFeatures;b++){
            if(cmpStr(filter[a],features[b])==0){
                if(cmpStr(filter[a],"price")!=0){
                    fiterColumn[a]=b;
                    a++;
                                   
                }
                else{
                    fiterColumn[a]=b;
                    priceFlag=1; 
                }

              
            }
        }
    }

    int ismatch[j];
    
    for(int i=0;i<j;i++) printf("%d\n",fiterColumn[i]);
    int printpID[MAX];
    for(int a=0;a<MAX;a++) printpID[a]=0;
    char tempstr[MAX];
    int tempInt;
    int pIDflag;
    int counter=0;
    if(!priceFlag){
        while(fscanf(fp,"%d",&tempInt)==1){
            for(int a=0;a<j;a++) ismatch[a]=0;

            for(int a=1;a<numFeatures;a++){
                fscanf(fp,",%[^,\n]",tempstr);
                for(int b=0;b<=j;b++){
                    if(fiterColumn[b]==a){
                        if(cmpStr(tempstr,filter[b+1])==0){
                           ismatch[b]=1; 
                        }
                    }
                }
            }
            
            pIDflag=0;
            
            for(int i=0;i<j;i=i+2){


                if( i<j && ismatch[i]==0 ){
                    printf("enter\n");
                    pIDflag=1;
                    break;
                }
                
            }

            if(!pIDflag){
               printf("girdi");  
               int a= printFilteredpID(tempInt);
            }
            
        }

    }

    fclose(fp);
 
    return 0; 

}

int printFilteredpID(int arr){

    FILE *fp = fopen("products.txt","r");
    if (fp == NULL) {
          printf("Error: could not open products file.\n");
          return 1;
     }
     
    int pID;
    int i;
    char c;
    int flag=0;

    while((c = fgetc(fp)) != '\n');

    while(fscanf(fp,"%d",&pID)==1){
        if(pID==arr){
                printf("%d",pID);
                while((c = fgetc(fp)) != '\n' && c!=EOF){
                    printf("%c",c);
                    flag =1;
                }
                printf("\n");
            }
        else{
            while((c = fgetc(fp)) != '\n' && c!=EOF);

    }
        }     
    printf("\n");
    fclose(fp);
    return 0;
}

int featureFinder(FILE *fp,char arr[MAX][FEATURE_LENGTH]){
    int numFeatures=0; 
    fscanf(fp, "%[^,]", arr[numFeatures]);
    while (fscanf(fp, ",%[^,\n]", arr[numFeatures + 1]) == 1) {
        numFeatures++;
    }
    numFeatures++;
    return numFeatures;
}

int stockStatus(){
    int choice;
    printf("-----STOCK STATUS-----\n");
    
    do{
        printf( "1) Query the stock status of a spesific product\n" 
                "2) List the stock of all products in specified branch\n"
                "3) list the out of stock products in specified branch\n"
                "4) Return to main menu\n");
        printf("What do you want?: ");
        scanf("%d",&choice);
        switch(choice){
            case 1: queryStock();break;
            case 2: listStock();break;
            case 3: outOfStock();break;
            case 4: printf("You terminated stock status option, going to menu....\n\n"); return 0; //back to main menu
            default: printf("Invalid choice\n\n");break;
        }
    }while(choice!=4);
    return 0;
    
    
}

int queryStock(){
    // Query the stock status of a spesific product using pID and branch in stocks.txt
    int filteredProduct[MAX];
    int pID;
    char branch[15];
    printf("Enter the product ID: ");
    scanf("%d",&pID);
    printf("Enter the branch: ");
    scanf("%s",branch);
    FILE *fp = fopen("stocks.txt","r");
    if (fp == NULL) {
          printf("Error: could not open stocks file.\n");
          return 1;
     }
    char c;
    while((c=fgetc(fp))!='\n');

    int sID;
    int tempID;
    char tempBranch[1][15];
    int stock;
    int num=0;
    while(fscanf(fp,"%d,%d,%[^,],%d",&sID,&tempID,tempBranch[0],&stock)==4){
        if(pID==tempID && strCompFeature(branch,tempBranch,1)==0){
            filteredProduct[num]=stock;
            num++;
        }
        }
    for(int i=0;i<num;i++){
         printf("Product %d in branch %s has %d stock\n\n",pID,branch,filteredProduct[i]);
       
    }
     return 0;
}    

int outOfStock(){
    
    // List the out of stock products in specified branch
    int filteredpID[100];
    char branch[15];
    printf("Enter the branch: ");
    scanf("%s",branch);

    FILE *fp = fopen("stocks.txt","r");
    if (fp == NULL) {
          printf("Error: could not open stocks file.\n");
          return 1;
     }

    char c;
    while((c=fgetc(fp))!='\n');

    int sID;
    int pID;
    char tempBranch[1][15];
    int stock;
    int num=0;
    while(fscanf(fp,"%d,%d,%[^,],%d",&sID,&pID,tempBranch[0],&stock)==4){
        if(stock==0 && strCompFeature(branch,tempBranch,1)==0){
            filteredpID[num]=pID;
            num++;
            
        }
    }
    for(int i=0;i<num;i++){
        printf("Product %d is out of stock in branch %s\n\n",filteredpID[i],branch);
    }
    fclose(fp);
    return 0;
}

int listStock(){

    int filteredpID[100];
    int filteredProduct[100];

    // List the stock of all products in specified branch
    char branch[15];
    printf("Enter the branch: ");
    scanf("%s",branch);

    FILE *fp = fopen("stocks.txt","r");
    if (fp == NULL) {
          printf("Error: could not open stocks file.\n");
          return 1;
     }

    char c;
    while((c=fgetc(fp))!='\n');

    int sID;
    int pID;
    char tempBranch[15];
    int stock;
    int num=0;
    while(fscanf(fp,"%d,%d,%[^,],%d",&sID,&pID,tempBranch,&stock)==4){
        if(cmpStr(branch,tempBranch)==0){
            filteredpID[num]=pID;
            filteredProduct[num]=stock;
            num++;   
        }
    }
    for(int i=0;i<num;i++){
        printf("Product %d in branch %s has %d stock\n\n",filteredpID[i],branch,filteredProduct[i]);
    }

    return 0;
}

int cmpStr(char arr[],char arr2[]){
    
    int i=0;
    while(arr[i]!='\0' && arr[i]==arr2[i]){
        i++;
    }
    if(arr[i]=='\0' && arr2[i]=='\0'){
        return 0;
    }
    return 1;

}

int brandStock(double filteredProduct[][3],int *num){
    // list all products of a given brand with their current stock. prodcuts.txt and stocks.txt

    char brand[10];

    printf("Enter the brand: ");
    scanf("%s",brand);

    FILE *fp = fopen("products.txt","r");
    if (fp == NULL) {
          printf("Error: could not open products file.\n");
          return 1;
    }

    FILE *fp2 = fopen("stocks.txt","r");
    if (fp2 == NULL) {
          printf("Error: could not open stocks file.\n");
          return 1;
    }

    char c;
    while((c=fgetc(fp))!='\n');
    while((c=fgetc(fp2))!='\n');

    int pID,sID;
    double price;
    char tempBrand[15];
    int stock;
    char temp[15];
    char line[MAX];
    *num = 0;
    while(fscanf(fp,"%d,%c,%[^,],%[^,],%lf",&pID,temp,temp,tempBrand,&price)==5){
        if(cmpStr(brand,tempBrand)==0){
            filteredProduct[*num][0]=pID;
            filteredProduct[*num][1]=price;
            (*num)++;
        }

        while ((c = fgetc(fp)) != '\n' && c != EOF);  
       
        }
    int fc2=(*num);
 
    while(fscanf(fp2,"%d,%d,%[^,],%d",&sID,&pID,temp,&stock)==4){
        
        for(int i=0;i<(*num);i++){
            if(filteredProduct[i][0]==pID){
                if(filteredProduct[i][2]==0) filteredProduct[i][2]=stock;
                else {
                    filteredProduct[fc2][0]=pID;
                    filteredProduct[fc2][1]=filteredProduct[i][1];
                    filteredProduct[fc2][2]=stock;
                    fc2++;
                }
            }
        }
    }
    *num = fc2;

    for(int i=0;i<(*num);i++){
        printf("Product %d has %d stock and %.2lf price\n",(int)filteredProduct[i][0],(int)filteredProduct[i][2],filteredProduct[i][1]);
    }

    fclose(fp);
    fclose(fp2);
    return 0;
}

int exportReport(double arr[][3],int size){


    FILE *reportFile = fopen("report.txt", "w");
    if (reportFile == NULL) {
        printf("Error: could not open report file.\n");
        return 1;
    }
    fprintf(reportFile,"pID,minStock,maxStock,medianStock\n");
    int min;
    int max;
    int printed[size];

    for(int i=0;i<size;i++) printed[i]=0;

    for(int i=0;i<size;i++){
        if (printed[i]) {
            continue; 
        }

        min=i;
        max=i;

        for(int j=0;j<size;j++){
           if((arr[i][0]==arr[j][0])&& (arr[i][2]>arr[j][2])){
                min=j;
           } 
           if((arr[i][0]==arr[j][0])&&(arr[i][2]<arr[j][2])){
                max=j;
           }
        }
        fprintf(reportFile,"%d,%d,%d,%d\n",(int)arr[i][0],(int)arr[min][2],(int)arr[max][2],(int)arr[(min+max)/2][2]);

        printed[min]=1;
        printed[max]=1;

    }
    fclose(reportFile);
    printf("Report exported to report.txt\n\n");
    return 0;
}


