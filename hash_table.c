#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define HASH_MAX 100 //hash table length
#define LIST_LEN 2000 //number of names to input in hash table
#define MAX_NAME 50 //max length of a name

typedef struct node
{
    char* name; 
    struct node* next;
}node;

int hash(char* name);
node* create(node* current, char* name);
node* new_node(char* name);
void add_to_hash(char* name);
void print_list(node* current);
void print_hash();
bool find_node(node* current, char* name);
bool find(char* name);
void free_list(node* current);
void free_hash(void);

node* hash_table[HASH_MAX];

int main(void)
{
    FILE* namefile = fopen("names.txt", "r");
    if(namefile == NULL)
    {
        printf("ERROR: CANNOT OPEN SPECIFIED FILE\n");
        return -1;
    }
    
    int l = 0;
    size_t size = 0;
    char* str = NULL;

    while (getline(&str, &size, namefile) != -1)
	{   
        str[strcspn(str, "\n")] = 0;
        add_to_hash(str);
        l++;
    }

    printf("Successfully added %d names to list..");

    fclose(namefile);
    namefile = NULL;

    // print_hash();

    char* lookfor = "Steve";
    printf("%s %s.\n", lookfor, find(lookfor) ? "was found": "was not found");


    free_hash();

    return 0;
}

int hash(char* name)
{
    int sum = 0;
    for (int i = 0; i < name[i] != '\0'; i++)
    {
        sum+= name[i];
    }

    return sum % HASH_MAX;
}

void add_to_hash(char* name)
{
    int hash_code = hash(name);
    
    node* new_head = create(hash_table[hash_code], name);

    
    hash_table[hash_code] = new_head;

    return;
}

node* create(node* current, char* name)
{
    node* new_head = new_node(name);

    if(current != NULL)
    {
        new_head->next = current;
    }

    return new_head;

}

node* new_node(char* name)
{
    node* new_head = malloc(sizeof(node));

    char* node_name = malloc(MAX_NAME);
    strcpy(node_name, name);
    new_head->name = node_name;
    new_head->next = NULL;
    return new_head;
}

void print_hash()
{
    printf("\n-----\nList of names\n-----\n");
    for (int j = 0; j < HASH_MAX; j++)
    {
        if(hash_table[j] != NULL)
        {
            print_list(hash_table[j]);
        }
    }
    return;
}

void print_list(node* current)
{
    while(current != NULL)
    {
        printf("%s\n", current->name);
        current = current->next;
    }

    return;
}

bool find(char* name)
{
    printf("\nLooking for %s...\n", name);
    int hash_code = hash(name);
    return find_node(hash_table[hash_code], name);
}

bool find_node(node* current, char* name)
{
    if(current == NULL)
    {
        return false;
    }

    else if (strcmp(current->name, name) == 0)
    {
        printf("Found it!\n");
        return true;
    }

    find_node(current->next, name);
}

void free_hash(void)
{
    for (int i = 0; i < HASH_MAX; i++)
    {
        free_list(hash_table[i]);
    }
}

void free_list(node* current)
{
    struct node* tmp;
    
    while (current != NULL)
    {
       tmp = current;
       tmp->name = NULL;
       current = current->next;
       free(tmp);
    }
}

void freeList(struct node* head)
{


}