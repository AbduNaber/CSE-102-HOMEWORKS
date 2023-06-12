#include "util.h"

int main(){
    
        Book_t *head_book = NULL; // head of the book list
        Student_t *head_student = NULL; // head of the student list
       
        read_library("library.txt",&head_book); // read the library.txt file and create the book list
        read_student("students.txt",&head_student,&head_book); // read the students.txt file and create the student list

        // define variables
        char ISBN[14];
        char title[100];
        char author[100];
        char publication_year[5];
        char filter[100];
        char feature[100];
        char value[100];
        int filter_choice,sort_choice,method,id;
        int choice;

        
        do{
            printf(" Welcome to the Library Management System\n");
            printf("1. Display the list of borrowed books by student\n");
            printf("2. Add a new book\n");
            printf("3. Remove a book\n");
            printf("4. Update a book\n");
            printf("5. Filter and Sort books\n");
            printf("6. Reverse Books\n");
            printf("7. Borrow a book\n");
            printf("8. Return a book\n");
            printf("9. Exit\n");
            printf("Enter your choice: ");
            scanf("%d",&choice);
            switch(choice){
                case 1:
                    printf("Enter student id: ");
                    scanf("%d",&id);
                    display_borrowedBooks(id,head_student);
                    printf("\n");
                    break;
                case 2:
                    printf("Enter ISBN: ");
                    scanf("%s",ISBN);
                    scanf("%*c");
                    printf("Enter title: ");
                    scanf("%[^\n]", title);
                    scanf("%*c");
                    printf("Enter author: ");
                    scanf("%[^\n]", author);
                    scanf("%*c");
                    printf("Enter publication year: ");
                    scanf("%s",publication_year);
                    printf("Enter 1 to FIFO, 2 to LIFO: ");
                    scanf("%d",&method);
                    addBook(&head_book,ISBN,title,author,publication_year,method);
                    printf("Book added successfully\n");
                    break;
                case 3:
                    printf("Enter ISBN: ");
                    scanf("%s",ISBN);
                    deleteBook(&head_book,ISBN);
                    break;
                case 4:
                    printf("Enter ISBN: ");
                    scanf("%s",ISBN);
                    printf("Enter Featue to update: ");
                    scanf("%s",feature);
                    printf("Enter new value: ");
                    scanf("%s",value);
                    updateBook(&head_book,ISBN,feature,value);

                    break;
                case 5:
                    printf("0 for filtering by author, 1 for filtering by publication year\n");
                    printf("Enter your choice: ");
                    scanf("%d",&filter_choice);
                    scanf("%*c");
                    printf("Enter filter value: ");
                    scanf("%[^\n]",filter);
                    printf("0 for sorting by title, 1 for sorting by author, 2 for sorting by publication year\n");
                    printf("Enter your choice: ");
                    scanf("%d",&sort_choice);
                    filterAndSortBooks(&head_book,filter_choice,filter,sort_choice);
                    printf("Books filtered and sorted successfully\n");
                    break;
                case 6:
                    reverseBookList(&head_book);
                    printf("Books reversed successfully\n");
                    break;
                case 7:
                    printf("Enter ISBN: ");
                    scanf("%s",ISBN);
                    borrowBook(head_book,head_student,ISBN);
                    break;
                case 8:
                    printf("Enter ISBN: ");
                    scanf("%s",ISBN);
                    returnBook(head_book,head_student,ISBN);
                    break;
                case 9:
                    printf("Exiting...\n");
                    break;
                default:
                    printf("Invalid choice\n");
            }
        updateFiles(head_book,head_student);
        scanf("%*c");
        } while(choice != 9);

        return 0;
}