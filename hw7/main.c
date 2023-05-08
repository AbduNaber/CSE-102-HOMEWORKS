#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_WORD 300000
#define MAX_DICT 2000
#define MAX_WORD_SIZE 20


double dissimilarity(char *w1, char *w2, char dict[][MAX_WORD_SIZE], double threshold, int *test);

int getVector(FILE *fp,int i,int j, double *vector1,double *vector2, int vector_size);

int main(int argc, char *argv[]){

    char dict[MAX_DICT][MAX_WORD_SIZE];
    char input[MAX_WORD][MAX_WORD_SIZE];
    int dict_words = read_dict("dictionary.txt",dict);
    int input_words = read_text("input.txt","ignore.txt",input);

    char temp[MAX_WORD_SIZE*100];
    printf("Enter a word: ");
    scanf ("%[^\n]%*c", temp);
    char user_input[100][MAX_WORD_SIZE];
    int inputc = strSpliter(temp,user_input); // split the user input into words return how many words are there
    int occur[inputc];
    for(int i=0;i<inputc;i++){
        occur[i] = occurrence(user_input[i],input,input_words);
        if(occur[i] == 0){
            
        }
    }

    
    /*



    int min_word=0;
    double temp1;
    double max_distance = dissimilarity(a,dict[0],dict,0.0,&min_word);
    for(int i=0;i<dict_words;i++){
        temp1 = doubledissimilarity(a,dict[i],dict,0.0,&min_word);
        if(temp1 < max_distance){
            max_distance = temp;
            min_word = i;
        }
  
    }



    printf("The closest word is %s\n",dict[min_word]);
    */
    return 0;

}

int occurrence(char *w, char words[][MAX_WORD_SIZE], int n){
    int count = 0;
    for(int i=0;i<n;i++){
        if(strcmp(w,words[i]) == 0){
            printf("w: %s words[i]: %s\n",w,words[i]);
            count++;
        }
    }
    return count;
}

int strSpliter(const char arr[],char arr2[][MAX_WORD_SIZE] ){
    printf("arr: %s\n",arr);
    int i=0,j=0,k=0;
    while(arr[i] != '\0'){
        if(arr[i] == ' '){
            arr2[j][k] = '\0';
            j++;
            k=0;
        }
        else{
            arr2[j][k] = arr[i];
            k++;
        }
        i++;
    }
    arr2[j][k] = '\0';

    // end with sentinel control character
    arr2[j+1][0] = '-';
    arr2[j+1][1] = '\0';
    return j+1;
}

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
                copyStr(temp,words,i); // copy the word to the words array
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

double dissimilarity(char *w1, char *w2, char dict[][MAX_WORD_SIZE], double threshold, int *test){
    // find location w1 and w2 in the dictionary
    int i=0,j=0;
    while(strcmp(w1,dict[i]) != 0){
        i++;
    }

    while(strcmp(w2,dict[j]) != 0){
        j++;
    }
    FILE *fp;
    fp = fopen("dictionary.txt","r");
    if(fp == NULL){
        printf("Error: cannot open file dictionary.txt\n");
        return -1;
    }
    int num,vector_size;
    fscanf(fp,"num_word=%d, vector_size=%d",&num,&vector_size);
    // get the vector of w1 and w2
    double vector1[vector_size];
    double vector2[vector_size];
    getVector(fp,i,j,vector1,vector2,vector_size);

    // calculate the distance
    double distance = 0;
    for(int k=0;k<vector_size;k++){

        distance += (vector1[k]-vector2[k])*(vector1[k]-vector2[k]);
    }

    distance = sqrt(distance);

    // check if the distance is smaller than the threshold */
    return distance; 


}

int getVector(FILE *fp,int l1,int l2, double *vector1,double *vector2, int vector_size){
 
    int i=0,j=0;


    char temp[MAX_WORD_SIZE];
    double temp1;
    int f1=0,f2=0;
    while(fscanf(fp,"%[^ ]",temp) == 1){
        if(f1==0 && i == l1){
            for(int k=0;k<vector_size;k++){

                fscanf(fp," %lf",&vector1[k]);

            }
            f1=1;
        }
        else if(f2 ==0 && i == l2){
            for(int k=0;k<vector_size;k++){

                fscanf(fp," %lf",&vector2[k]);

            }
            f2=1;
        }
        else if(f1 == 1 && f2 == 1){
            return 0;
        }
        else{
            for(int k=0;k<vector_size;k++){
                fscanf(fp," %lf",&temp1);
            }
        }
        fscanf(fp,"\n");
        i++;
    }
    fclose(fp);
    return 0;
}

int copyStr(char *dest, char dict[][MAX_WORD_SIZE],int position){
    int i = 0;
    while(dest[i] != '\0'){
        dict[position][i] = dest[i];
        i++;
    }
    dict[position][i] = '\0';
    return i;
}

