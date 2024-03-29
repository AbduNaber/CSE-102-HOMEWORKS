#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_WORD 300000
#define MAX_DICT 2000
#define MAX_WORD_SIZE 20
#define THRESHOLD 40.0
// function prototypes
double dissimilarity(char *w1, char *w2, char dict[][MAX_WORD_SIZE], double threshold,int *closest_word);
int occurrence(const char *w,const char words[][MAX_WORD_SIZE], int n);
int strSpliter(const char arr[],char arr2[][MAX_WORD_SIZE] );
int read_dict(const char *file_name, char dict[][MAX_WORD_SIZE]);
int read_text(const char *text_file, const char *ignore_file, char words[][MAX_WORD_SIZE]);
double dissimilarity(char *w1, char *w2, char dict[][MAX_WORD_SIZE], double threshold, int *closest_wordi);
int findVector(int i,int vector_size,int num_word,double vector[]);
int strtostr(char *dest, char *src);
int histogram(const char words[][2*MAX_WORD_SIZE],const int occurrences[], char hist[][2*MAX_WORD_SIZE+5+20]);
int strlength(const char *str);
int findDoubleStr(const char *str);
int findNotStr(const char *str);
// end of function prototypes

int main(int argc, char *argv[]){

    char dict[MAX_DICT][MAX_WORD_SIZE]; // dictionary
    char input[MAX_WORD][MAX_WORD_SIZE]; // input words

    int dict_words = read_dict("dictionary.txt",dict); // read dictionary
    int input_words = read_text("input.txt","ignore.txt",input); // read input

    // user input
    char temp[MAX_WORD_SIZE*100]; 
    printf("Enter a word: ");
    scanf ("%[^\n]%*c", temp);

    char user_input[100][MAX_WORD_SIZE]; // store user input
    int inputcounter = strSpliter(temp,user_input); // split the user input into words return how many words are there
    char closest_word[MAX_WORD_SIZE]; // store the closest word

    int occurrences[inputcounter]; // store the occurrences of each word
    int closest_wordi,j,indict; // store the index of the closest word

    char hist_word[inputcounter+1][2*MAX_WORD_SIZE]; // store the history of the words
    char hist[inputcounter+1][2*MAX_WORD_SIZE+5+20]; // store the history of the words and occurrences

    for(int i=0;user_input[i][0]!='-';i++){
        occurrences[i] = occurrence(user_input[i],input,input_words); // find the occurrences of each word
        
        j = strtostr(hist_word[i],user_input[i]); // store the word in hist_word to print out later

        if(occurrences[i] == 0){ // if the word is not in the input file go to the dictionary and find the closest word using dissimilarity

            indict = dissimilarity(user_input[i],closest_word,dict,THRESHOLD,&closest_wordi); // find the closest word
            if(indict == -1){ // if the word is not in the dictionary
                continue;
            }
            else{
                occurrences[i]= occurrence(closest_word,input,input_words); // find the occurrences of the closest word
                
                // store the closest word in hist_word to print out later
                hist_word[i][j] = '-'; 
                hist_word[i][j+1] = '>'; 
                strtostr(hist_word[i]+j+2,closest_word);
            }
        
        }
    }

    // end with sentinel control character hist_word
    hist_word[inputcounter][0] = '-'; 
    hist_word[inputcounter][1] = '\0';

    int scale;
    scale = histogram(hist_word,occurrences,hist); // print out the histogram

    printf("Good bye!\n");
    return 0;

}

// find the occurrences of given word
int occurrence(const char *w,const char words[][MAX_WORD_SIZE], int n){
    int count = 0;
    
    for(int i=0;i<n;i++){
        if(strcmp(w,words[i]) == 0){
            count++;
        }
    }

    return count;
}

// split the string into words and store in arr2 return how many words are there 
int strSpliter(const char arr[],char arr2[][MAX_WORD_SIZE] ){

    //split string " " and store in arr2
    int i=0,j=0,t=0,f=0;
    while(arr[i] != '\0'){
        if(arr[i]!=' '){
            arr2[t][j] = arr[i];
            j++;
            f=1;
        }
        else if(f){
            arr2[t][j] = '\0';
            t++;
            j=0;
            f=0;
        }
        
        i++;

    }

    // end with sentinel control character
    arr2[t+1][0] = '-';
    arr2[t+1][1] = '\0';
    return t+1;
}

// read the dictionary and store in dict return how many words are there
int read_dict(const char *file_name, char dict[][MAX_WORD_SIZE]){

    FILE *fp; // file pointer
    fp = fopen(file_name, "r"); // open file for reading
    if(fp == NULL){
        printf("Error: cannot open file %s\n", file_name); // print error message
        return -1;
    }
    char c;
    int i=0,j=0;
    while((c = fgetc(fp)) != '\n'); // skip the first line
    
    while((c=fgetc(fp)) != EOF){
        if(c == ' '){
            dict[i][j] = '\0';
            i++;
            j=0;
        while((c = fgetc(fp)) != '\n'&& c != EOF);    
        }
        else{
            dict[i][j] = c;
            j++;
        }
    }
    dict[i][j] = '-'; dict[i][j+1] = '\0'; // mark the end of the dictionary
    fclose(fp);
    return i;
}

// read the input and store in words return how many words are there
int  read_text(const char *text_file, const char *ignore_file, char words[][MAX_WORD_SIZE]){

    char ingoreWords[100][12];

    FILE *fp; // input file pointer
    fp = fopen(text_file, "r"); // open file for reading
    if(fp == NULL){
        printf("Error: cannot open file %s\n", text_file); // print error message
        return -1;
    }

    FILE *fp2; // ignore file pointer
    fp2 = fopen(ignore_file, "r"); // open file for reading
    if(fp2 == NULL){
        printf("Error: cannot open file %s\n", ignore_file); // print error message
        return -1;
    }

    int e=0;
    while(fscanf(fp2,"%[^\n]\n",ingoreWords[e]) == 1){
        e++;
    }
    fclose(fp2);

    char c;
    char temp[MAX_WORD_SIZE];
    int i=0,j=0,l=0;
    int ingoreFlag = 0;
    while((c = fgetc(fp)) != EOF){

        if((c>='0' && '9'>=c) || (c>='a' && 'z'>=c) || (c>='A' && 'Z'>=c)){
            temp[j] = c;
            j++;
            l=1; // set the flag to I am reading a word
        }

        else if(l==1){ // if I am read a word
            temp[j] = '\0';
            for(int k=0;k<e;k++){ // check if the word is in the ignore list
                if(strcmp(temp,ingoreWords[k]) == 0){ // if the word is in the ignore list
                    ingoreFlag = 1; // set the flag
                    k=e; // break the loop
                }
            }
            if(ingoreFlag == 0){ // if the word is not in the ignore list
                strtostr(words[i],temp);

                i++; // increase the number of words
            }
            j=0; // reset j
            l=0; // reset k
            ingoreFlag = 0; // reset the flag
        }

    }

    fclose(fp);
    return i;
}

/*
    * find the closest word to the given word in the dictionary using dissimilarity formula
    * input: word, dictinary and threshold
    * outputs : distance between word and its closest word ,the index of the closest word and the closest word     
*/ 
double dissimilarity(char *w1, char *w2, char dict[][MAX_WORD_SIZE], double threshold, int *closest_wordi){
    FILE *fp; // file pointer
    fp = fopen("dictionary.txt", "r"); // open file for reading
    if(fp == NULL){
        printf("Error: cannot open file %s\n", "dictionary.txt"); // print error message
        return -1;
    }
    
    int num_word, vector_size;
    fscanf(fp,"num_word=%d, vector_size=%d\n",&num_word,&vector_size); // read the first line

    // find index of word in dictionary array
    int index1 = -1,t=0;
    for(int i=0;i<num_word;i++){
        if(strcmp(w1,dict[i]) == 0){
            index1 = i;
            break;
        }
    }

    if(index1 == -1){ // if the word is not in the dictionary
        return -1; 
    }
    
    double vector1[vector_size]; // user input vector
    double temp[vector_size]; // word vector for temp
    findVector(index1,vector_size,num_word,vector1); // find the vector of the word
    double distance = threshold,temp_distance = 0; // set the distance to a large number

    char tempstr[MAX_WORD_SIZE]; // temp string to read the word

    // read each word and its vector and calculate the distance and find the closest word
    while((fscanf(fp,"%[^ ]",tempstr))==1){ 
        for(int k=0;k<vector_size;k++){
            fscanf(fp," %lf",&temp[k]);
            temp_distance += pow((vector1[k]-temp[k]),2);
            
        }

        if(temp_distance < distance && temp_distance !=0){
            distance = temp_distance;
            *closest_wordi = t;
        }
        fscanf(fp,"\n");
        t++;
        temp_distance = 0;
    }

    strtostr(w2,dict[*closest_wordi]); // copy the closest word to w2

    fclose(fp); // close the file
    
    return distance; 

}

// find the vector of the given word
int findVector(int i,int vector_size,int num_word,double vector[]){
    FILE *fp; // file pointer
    fp = fopen("dictionary.txt", "r"); // open file for reading
    if(fp == NULL){
        printf("Error: cannot open file %s\n", "dictionary.txt"); // print error message
        return -1;
    }
    char temp[MAX_WORD_SIZE]; 
    int j=0;

    fscanf(fp,"num_word=%*[^,], vector_size=%*[^\n]\n");     // skip the first line

    // read each word and its vector and find the vector of the given word
    while((fscanf(fp,"%[^ ]",temp))==1){ 
        if(i!=j){
            fscanf(fp,"%*[^\n]\n");
        }
        else{
            for(int k=0;k<vector_size;k++){
                
                fscanf(fp," %lf",&vector[k]);

            }
        }
        j++;
    }

    fclose(fp);
    return 0;
}

// copy src to dest
int strtostr(char *dest, char *src){
    int i=0;
    while(src[i] != '\0'){
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return i;
}

// Histogram function 
int histogram(const char words[][2*MAX_WORD_SIZE],const int occurrences[], char hist[][2*MAX_WORD_SIZE+5+20]){
    int scale, i=0;
    while(words[i][0] != '-'){
        i++;
    }

    // find max occur 
    int max = 1;
    for(int j=0;j<i;j++){
        if(occurrences[j] > max){
            max = occurrences[j];
        }
    }

    
    if ( max%20!=0) scale = max/20 +1;
    else scale = max/20;
    int lenght ;
    if(i!=1){
        if(scale > 1) printf("scale = %d\n",scale);
        for(int t=0;t<i;t++){
            printf("\"%s\"",words[t]);
            lenght = strlength(words[t]);
            if(occurrences[t]/scale !=0 ){
               if(!findDoubleStr(words[t])){
                    printf("%*c",30-lenght,'*');
                    for(int l=1;l<occurrences[t]/scale;l++){
                        printf("*");
                    }
                }
                else{
                    printf("%*c",30-lenght,'+');
                    for(int l=1;l<occurrences[t]/scale;l++){
                        printf("+");
                    }
                }     
            }
            if(occurrences[t] == 0){
                printf("%*s",39-lenght,"NO MATCHES");
            }
            printf("\n");

            
        }
    }
    else{

    
        if(!findDoubleStr(words[0])){
            if(occurrences[0]!=0) printf("\"%s\" appears in “input.txt” %d times.\n",words[0],occurrences[0]);
            else printf("\"%s\" doesn't appear in “input.txt”.\n",words[0]);
        }

        else if(findDoubleStr(words[0])){

            char first[MAX_WORD_SIZE], second[MAX_WORD_SIZE];
            int i = 0, j = 0;
            while (words[0][i] != '-') {
                first[i] = words[0][i] ;
                i++;
            }
            first[i] = '\0';
            i += 2;
            while (words[0][i]  != '\0') {
                second[j] = words[0][i];
                i++;
                j++;
            }
            second[j] = '\0';
            if(occurrences[0]!=0) 
            printf("\"%s\" appears in \"input.txt\" %d times but \"%s\" appears %d times.\n", first, occurrences[0], second, occurrences[0]);
            else 
            printf("\"%s\" doesn't appear in \"input.txt\" also \"%s\" doesn't appears \n", first, second);
        }
  
    return scale;
}}

// find str includes > sembol
int findDoubleStr(const char *str){
    int i=0;
    while(str[i] != '\0'){
        if(str[i]=='>') return 1;
        i++;
    }
    return 0;
}

// find str includes ! sembol
int findNotStr(const char *str){
    int i=0;
    while(str[i] != '\0'){
        if(str[i]=='!') return 1;
        i++;
    }
    return 0;
}

// strlength function
int strlength(const char *str){
    int i=0;
    while(str[i] != '\0'){
        i++;
    }
    return i;
}