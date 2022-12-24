
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#include "hash_func.h"

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

void print_hash(void)
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
            count = print_list_limited(hash_table[j], num_items, count);
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