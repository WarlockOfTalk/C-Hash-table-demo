#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "helpers.h"




int hash(char* name)
{
    int sum = 0;
    for (int i = 0; name[i] != '\0'; i++)
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
    printf("\n-----\nList of items\n-----\n");
    for (int j = 0; j < HASH_MAX; j++)
    {
        if(hash_table[j] != NULL)
        {
            print_list(hash_table[j]);
        }
    }
    return;
}

void print_hash_limited(int num_items)
{
    int count = 0;

    printf("\n-----\nList of items\n-----\n");
    for (int j = 0; j < HASH_MAX; j++)
    {
        if(hash_table[j] != NULL)
        {
            count += print_list_limited(hash_table[j], num_items, count);
            if( count >= num_items)
            {
                printf("---------------\n");
                printf("Printed first %d items", num_items);
                return;
            }
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

int print_list_limited(node* current, int num_items, int count)
{
    while(current != NULL)
    {
        printf("%s\n", current->name);
        count++;
        
        if(count >= num_items)
        {
            return count;
        }

        current = current->next;
    }

    return count;
}


bool find(char* name)
{
    // printf("\nLooking for %s...\n", name);
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
        // printf("Found it!\n");
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

bool delete_from_hash(char* string_input)
{
    int hash_code = hash(string_input);
    return delete_node(&hash_table[hash_code], string_input);
}

bool delete_node(node** Pcurrent, char* string_input)
{
    node* current = *Pcurrent;

    if(current == NULL) //empty list error
    {
        return false;
    }

    else if (strcmp(current->name, string_input) == 0) //first item in list
    {
        if (current->next == NULL) //one length list 
        {
            free(current);
            *Pcurrent = NULL;
            return true;
        }

        node* toDelete = current->next;
        current->name = current->next->name;
        current->next = current->next->next;
        free(toDelete);
        return true;
    }

    node* prev = current;
    node* next = NULL;

    while(current != NULL)
    {
        if(strcmp(current->name, string_input) == 0)
        {
            prev->next = current->next;
            free(current);
            current = NULL;
            return true;
        }

        prev = current;
        current = current->next;
    }

    return false;
}

int validate_int()
{
    fflush(stdin); //flush any left over values

    int num_items = 0; 
    char buf[BUFFER_SIZE];

    do
    {
        printf("How many items to print?\n");
        if (!fgets(buf, 1024, stdin))
        {
            // reading input failed
            printf("ERROR: Invalid Input");
            continue; 1;
        }
        
        num_items = atoi(buf);

        //validate user input
        if(num_items == 0)
        {
            printf("ERROR: Invalid input\n");
        }

        if(num_items < 0)
        {
            printf("ERROR: Input must be more than 0\n");
            num_items = 0;
            continue;
        }

    } while (num_items == 0);

    return num_items;
}

void print_menu()
{
    printf("MENU\n"
            "\t1: Print all items in hash table\n"
            "\t2: Print a defined number of items\n"
            "\t3: Search hash table for string\n"
            "\t4: Add string to hash table\n"
            "\t5: Delete string from hash table\n"
            "\t6: Import text file to hash table\n"
            "\t7: Exit\n"
            "\t8: Benchmark lookups using file\n\n"
            "Select an option: "
        );
}