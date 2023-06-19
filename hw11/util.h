#include <stdio.h>
#include <stdlib.h>

typedef struct family{
    char  name[20];
    int age ;
    struct family *father;
    struct family *mother;
} family_t;

int delete_node(family_t *root, char *name);
int addFamily(family_t *root);
int print_node(family_t *root, char *name);
int print_tree(family_t *root);
int read_file(family_t *root, char *filename);
int write_file(family_t *root, char *filename);


