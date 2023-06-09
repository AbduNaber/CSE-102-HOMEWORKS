#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct book{
    char ISBN[14];
    char title[100];
    char author[100];
    char publication_year[5];
    int isreserved;
    struct book *next;

} Book_t;

typedef struct student{
    char name[100];
    int id;
    Book_t *borrowed_books;
    struct student *next;
}   Student_t;



void display_borrowedBooks(int id, Student_t *head){
    Student_t *current = head;
    while(current != NULL){
        if(current->id == id){

            Book_t *current_book = current->borrowed_books;
            while(current_book != NULL){
                printf("%s %s %s %s\n", current_book->ISBN, current_book->title, current_book->author, current_book->publication_year);
                current_book = current_book->next;
            }

            break;
        }
        current = current->next;
    }

    if(current == NULL){
        printf("No such student\n");
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
    Book_t *prev = head;

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
