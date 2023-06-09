#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct book{
    
    char ISBN[14];
    char title[100];
    char author[100];
    char publication_year[5];
    int isreserved ;
    struct book *next;

} Book_t;

typedef struct borrowed {
    Book_t *borrowed_book;
    struct borrowed *next;
} Borrowed_t;

typedef struct student {
    char name[100];
    int id;
    struct borrowed *borrowed_books;
    struct student *next;
} Student_t;



void filterAndSortBooks(Book_t **head,int filterChoice, char* filter, int sortChoice);
int read_library(char *filename, Book_t **head_book);
int read_student(char *filename,Student_t **head_student, Book_t **head_book);
Book_t* findBook(char *isbn, Book_t *head);
void addStudent(Student_t **head, Student_t *new_student);
void display_borrowedBooks(int id, Student_t *head);
void addBook(Book_t **head, char * isbn, char* title, char* author, char* publicationYear, int method );
void deleteBook(Book_t **head,char* isbn);
void updateBook(Book_t **head, char* isbn, char* feature, char* value);




int read_library(char *filename, Book_t **head_book){
        
    FILE *fp = fopen(filename,"r");
    if(fp == NULL){
        printf("File could not be opened\n");
        return -1;
    }
    
    char ISBN[14];
    char title[100];
    char author[100];
    char publication_year[5];
    int isreserved =0;
    while(fscanf(fp,"%[^,],%[^,],%[^,],%[^,],%d\n",ISBN,title,author,publication_year,&isreserved) != EOF){
        addBook(head_book,ISBN,title,author,publication_year,1);
    }
    return 0;

}
int read_student(char *filename,Student_t **head_student, Book_t **head_book){
        
        FILE *fp = fopen(filename,"r");
        if(fp == NULL){
            printf("File could not be opened\n");
            return -1;
        }
        
        char name[100];
        int id;
        char ISBN[13];
        char title[100];
        char author[100];
        char publication_year[5];
        int isreserved =1;
        while(!feof(fp)){
            fscanf(fp,"%[^,],%d",name,&id);
            printf("%s %d\n",name,id);
            Student_t *new_student = (Student_t *)malloc(sizeof(Student_t));
            strcpy(new_student->name,name);
            new_student->id = id;
            new_student->borrowed_books = NULL;
            new_student->next = NULL;
            while(fscanf(fp,",%[^\n,]",ISBN) ==1){

                if(strlen(ISBN) != 13){
                    ISBN[strlen(ISBN)-1] = '\0';
                }

                Book_t *book = findBook(ISBN,*head_book);
                book->isreserved = 1;
                if(book != NULL){
                    Borrowed_t *new_borrowed = (Borrowed_t *)malloc(sizeof(Borrowed_t));
                    new_borrowed->borrowed_book = book;
                    new_borrowed->next = NULL;
                    if(new_student->borrowed_books == NULL){
                        new_student->borrowed_books = new_borrowed;
                    }
                    else{
                        Borrowed_t *current = new_student->borrowed_books;
                        while(current->next != NULL){
                            current = current->next;
                        }
                        current->next = new_borrowed;
                    }
                }

            } 
            fscanf(fp, "%*c");
            addStudent(head_student,new_student);
        }
}

void addStudent(Student_t **head, Student_t *new_student){
    
    Student_t *current = *head;
    if(*head == NULL){
        *head = new_student;
    }
    else{
        while(current->next != NULL){
            current = current->next;
        }
        current->next = new_student;
    }
}

Book_t* findBook(char *isbn, Book_t *head){

    Book_t *current = head;
    
    while(current != NULL){

        if(strcmp(current->ISBN,isbn) == 0){
            return current;
        }
        current = current->next;
    }
    return NULL;
}



void display_borrowedBooks(int id, Student_t *head){
    
    Student_t *current = head;
    while(current != NULL){
        if(current->id == id){
            Borrowed_t *current_borrowed = current->borrowed_books;
            while(current_borrowed != NULL){
                printf("%s %s %s %s %d\n",current_borrowed->borrowed_book->ISBN,current_borrowed->borrowed_book->title,current_borrowed->borrowed_book->author,current_borrowed->borrowed_book->publication_year,current_borrowed->borrowed_book->isreserved);
                current_borrowed = current_borrowed->next;
            }
        }
        current = current->next;
    }

}

void addBook(Book_t **head, char * isbn, char* title, char* author, char* publicationYear, int method ){

    Book_t *current = *head;

    Book_t *new_book  = (Book_t *)malloc(sizeof(Book_t));
    strcpy(new_book->ISBN,isbn);
    strcpy(new_book->author,author);
    strcpy(new_book->title,title);
    strcpy(new_book->publication_year,publicationYear);
    new_book->isreserved = 0;
    new_book->next = NULL;

    if(method == 0){
        *head = new_book;
        new_book->next = current;
    }

    else if( method == 1) {

        if (*head == NULL) {
            *head = new_book;
        } 
        else {
            while(current->next != NULL){
            current = current->next;
            }
            current->next = new_book;
        }       
    }
}

void deleteBook(Book_t **head,char* isbn){

    Book_t *current = *head;
    Book_t *prev = *head;

    while(current->next != NULL && strcmp(current->ISBN,isbn) !=0){
        prev = current;
        current = current->next;
    }
    if(current->next == NULL){
        printf("Book is not on the library");
        return;
    }

    prev->next = current->next;
    free(current);

}

void updateBook(Book_t **head, char* isbn, char* feature, char* value){
    
    Book_t *current = *head;

    if(current == NULL){
        printf("linkedList ERROR!");
    }
    while(current->next != NULL && strcmp(current->ISBN,isbn) !=0){
        current = current->next;
    }
    if(strcmp("title",feature)==0){
        strcpy(current->title,value);
    }
    else if(strcmp("author",feature)==0){
        strcpy(current->author,value);
    }
    else if(strcmp("publication year",feature)==0){
        strcpy(current->publication_year,value);
    }
}

void filterAndSortBooks(Book_t **head,int filterChoice, char* filter, int sortChoice){
    // 0 for filtering by author, 1 for filtering by publication year.
    // get all books to arr filter 
    Book_t *current = *head;
    Book_t filterArr[100];
    int i = 0;

    while(current != NULL){
        if(filterChoice == 0){
            if(strcmp(current->author,filter) == 0){
                filterArr[i] = *current;
                i++;
            }
        }
        else if(filterChoice == 1){
            if(strcmp(current->publication_year,filter) == 0){
                filterArr[i] = *current;
                i++;
            }
        }
        current = current->next;
    }
    // sort filterArr
    if(sortChoice == 0){
        for(int j = 0; j < i; j++){
            for(int k = 0; k < i; k++){
                if(strcmp(filterArr[j].title,filterArr[k].title) < 0){
                    Book_t temp = filterArr[j];
                    filterArr[j] = filterArr[k];
                    filterArr[k] = temp;
                }
            }
        }
    }
    else if(sortChoice == 1){
        for(int j = 0; j < i; j++){
            for(int k = 0; k < i; k++){
                if(strcmp(filterArr[j].author,filterArr[k].author) < 0){
                    Book_t temp = filterArr[j];
                    filterArr[j] = filterArr[k];
                    filterArr[k] = temp;
                }
            }
        }
    }
    else if(sortChoice == 2){
        for(int j = 0; j < i; j++){
            for(int k = 0; k < i; k++){
                if(strcmp(filterArr[j].publication_year,filterArr[k].publication_year) < 0){
                    Book_t temp = filterArr[j];
                    filterArr[j] = filterArr[k];
                    filterArr[k] = temp;
                }
            }
        }
    }
    // print filterArr
    for(int j = 0; j < i; j++){
        printf("%s %s %s %s %d\n",filterArr[j].ISBN,filterArr[j].title,filterArr[j].author,filterArr[j].publication_year,filterArr[j].isreserved);
    }

}
void searchBooks(Book_t **head,int searchChoice, char* searchValue){

    Book_t *current = *head;
    while(current != NULL){
        if(searchChoice == 0){
            if(strcmp(current->title,searchValue) == 0){
                printf("%s %s %s %s %d\n",current->ISBN,current->title,current->author,current->publication_year,current->isreserved);
            }
        }
        else if(searchChoice == 1){
            if(strcmp(current->author,searchValue) == 0){
                printf("%s %s %s %s %d\n",current->ISBN,current->title,current->author,current->publication_year,current->isreserved);
            }
        }
        else if(searchChoice == 2){
            if(strcmp(current->publication_year,searchValue) == 0){
                printf("%s %s %s %s %d\n",current->ISBN,current->title,current->author,current->publication_year,current->isreserved);
            }
        }
        current = current->next;
    }
    if(current == NULL){
        printf("Book is not on the library");
    }

}


int main(){
    
        Book_t *head_book = NULL;
        Student_t *head_student = NULL;

        read_library("library.txt",&head_book);

        read_student("students.txt",&head_student,&head_book);

        //display_borrowedBooks(21010,head_student);
        filterAndSortBooks(&head_book,0,"Mary Shelley",0);

        return 0;
}