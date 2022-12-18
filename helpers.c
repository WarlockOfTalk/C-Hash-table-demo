#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>

#include "helpers.h"

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

void get_path(char* string_input)
{
    //TODO: DON'T OPEN FILE POINTER HERE, JUST VALIDATE STRING AND THEN RETURN PATH TO OPEN IN MAIN
    
    printf("Enter path of file to add to hash table or \"quit\" to return to menu: ");

    fgets(string_input, PATH_MAX, stdin);
    fflush(stdin);
    string_input[strcspn(string_input, "\n")] = 0; //remove \n from end of string
   
    return;
}