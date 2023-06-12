#ifndef UTIL_H
#define UTIL_H

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
void updateFiles(Book_t *head_book, Student_t *head_student);
void returnBook(Book_t *head, Student_t *student, char *isbn);
void borrowBook(Book_t *head, Student_t *head_Student, char *isbn);
void reverseBookList(Book_t **head);
void searchBooks(Book_t **head,int searchChoice, char* searchValue);

#endif