#include "util.h"

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
        while(fscanf(fp,"%[^,],%d",name,&id)==2){
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
            printf("\nName: %s\n",current->name);
            Borrowed_t *current_borrowed = current->borrowed_books;
            printf("Borrowed Books:\n");
            while(current_borrowed != NULL){
                printf("%s %s %s %s %d\n",current_borrowed->borrowed_book->ISBN,current_borrowed->borrowed_book->title,current_borrowed->borrowed_book->author,current_borrowed->borrowed_book->publication_year,current_borrowed->borrowed_book->isreserved);
                current_borrowed = current_borrowed->next;
            }
            return;

        }
        current = current->next;
    }
    if(current == NULL){
        printf("Student not found\n");
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
    Book_t *prev = NULL;

    while(current != NULL && strcmp(current->ISBN,isbn) != 0){
        prev = current;
        current = current->next;
    }
    if(current == NULL){
        printf("Book not found\n");
        return;
    }
    if(prev == NULL){
        *head = current->next;
    }
    else{
        prev->next = current->next;
    }
    printf("Following Book deleted\n");
    printf("%s %s %s %s %d\n",current->ISBN,current->title,current->author,current->publication_year,current->isreserved);
    free(current);

}

void updateBook(Book_t **head, char* isbn, char* feature, char* value){
    
    Book_t *current = *head;

    if(current == NULL){
        printf("linkedList ERROR!");
    }
    while(current != NULL && strcmp(current->ISBN,isbn) !=0){
        current = current->next;
    }
    if(current == NULL){
        printf("Book not found\n");
        return;
    }

    printf("Following Book updated\n");
    printf("%s %s %s %s %d",current->ISBN,current->title,current->author,current->publication_year,current->isreserved);
    if(strcmp("title",feature)==0){
        strcpy(current->title,value);
    }
    else if(strcmp("author",feature)==0){
        strcpy(current->author,value);
    }
    else if(strcmp("publication year",feature)==0){
        strcpy(current->publication_year,value);
    }
    else{
        printf("Feature not found\n");
        return;
    }
    printf(">>%s %s %s %s %d\n",current->ISBN,current->title,current->author,current->publication_year,current->isreserved);

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

void reverseBookList(Book_t **head){

    // by ISBN
    Book_t *current = *head;
    Book_t *next = (*head)->next;
    Book_t temp;

    while(current->next != NULL){
        while(next != NULL){
            
            if(strcmp(current->ISBN,next->ISBN) > 0){
                
                //copy current to temp
                strcpy(temp.ISBN,current->ISBN);
                strcpy(temp.title,current->title);
                strcpy(temp.author,current->author);
                strcpy(temp.publication_year,current->publication_year);
                temp.isreserved = current->isreserved;

                //copy next to current
                strcpy(current->ISBN,next->ISBN);
                strcpy(current->title,next->title);
                strcpy(current->author,next->author);
                strcpy(current->publication_year,next->publication_year);
                current->isreserved = next->isreserved;

                //copy temp to next
                strcpy(next->ISBN,temp.ISBN);
                strcpy(next->title,temp.title);
                strcpy(next->author,temp.author);
                strcpy(next->publication_year,temp.publication_year);
                next->isreserved = temp.isreserved;




            }
            next = next->next;
        }
        current = current->next;
        next = current->next;
    }

    
    // reverse the linked list
    Book_t *prev = NULL;
    current = *head;
    next = (*head)->next;
    while(current != NULL){
        current->next = prev;
        prev = current;
        current = next;
        if(next != NULL){
            next = next->next;
        }
    }
    *head = prev;
    // write to file
    FILE *fp = fopen("library.txt","w");
    current = *head;
    while(current != NULL){
        fprintf(fp,"%s %s %s %s %d\n",current->ISBN,current->title,current->author,current->publication_year,current->isreserved);
        current = current->next;
    }
    fclose(fp);

} 

void borrowBook(Book_t *head, Student_t *head_Student, char *isbn){
    int id;
    printf("Enter your id: ");
    scanf("%d",&id);
    // check if student exists
    Student_t *student = head_Student;
    while(student != NULL){
        if(student->id == id){
            break;
        }
        student = student->next;
    }
    if(student == NULL){
        printf("Student does not exist\n");
        return;
    }
    
    // check if book is available to borrow
    Book_t *current = head;
    while(current != NULL){
        if(strcmp(current->ISBN,isbn) == 0){
            if(current->isreserved == 0){
                current->isreserved = 1;
                // add to student's book list
                Book_t *newBook = (Book_t*)malloc(sizeof(Book_t));
                strcpy(newBook->ISBN,current->ISBN);
                strcpy(newBook->title,current->title);
                strcpy(newBook->author,current->author);
                strcpy(newBook->publication_year,current->publication_year);
                newBook->isreserved = current->isreserved;
                newBook->next = NULL;
                if(student->borrowed_books == NULL){
                    student->borrowed_books = (Borrowed_t*)malloc(sizeof(Borrowed_t));
                    student->borrowed_books->borrowed_book = newBook;
                    student->borrowed_books->next = NULL;
                }
                else{
                    Borrowed_t *currentBook = student->borrowed_books;
                    while(currentBook->next != NULL){
                        currentBook = currentBook->next;
                    }
                    currentBook->next = (Borrowed_t*)malloc(sizeof(Borrowed_t));
                    currentBook->next->borrowed_book = newBook;
                    currentBook->next->next = NULL;
                }
                printf("Book is borrowed to %s\n",student->name);
                return;
            }
            else{
                printf("Book is not available to borrow\n");
                return;
            }
        }
        current = current->next;
    }
    
}

void returnBook(Book_t *head, Student_t *student, char *isbn){

   
    // check if book is borrowed by student
    Borrowed_t *current = student->borrowed_books;
    Borrowed_t *prev = NULL;
    while(current != NULL){
        if(strcmp(current->borrowed_book->ISBN,isbn) == 0){
            break;
        }
        prev = current;
        current = current->next;
    }
    if(current == NULL){
        printf("Book is not borrowed by student\n");
        return;
    }
    // remove book from student's borrowed list
    if(prev == NULL){
        student->borrowed_books = current->next;
    }
    else{
        prev->next = current->next;
    }
    // change book's status to available
    Book_t *book = head;
    while(book != NULL){
        if(strcmp(book->ISBN,isbn) == 0){
            book->isreserved = 0;
            break;
        }
        book = book->next;
    }
    printf("Book is returned\n");
    return;
}

   
void updateFiles(Book_t *head_book, Student_t *head_student){

    // write to library file
    FILE *fp = fopen("library.txt","w");
    Book_t *current = head_book;
    while(current != NULL){
        fprintf(fp,"%s,%s,%s,%s,%d\n",current->ISBN,current->title,current->author,current->publication_year,current->isreserved);
        current = current->next;
    }
    fclose(fp);

    // write to students file
    fp = fopen("students.txt","w");
    Student_t *student = head_student;
    while(student != NULL){
        fprintf(fp,"%s,%d",student->name,student->id);
        Borrowed_t *current = student->borrowed_books;
        while(current != NULL){
            fprintf(fp,",%s",current->borrowed_book->ISBN);
            current = current->next;
        }
        fprintf(fp,"\n");
        student = student->next;
    }
    fclose(fp);

}

