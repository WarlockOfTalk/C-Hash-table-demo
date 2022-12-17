#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "helpers.h"

//Timing Tests
#include <time.h>


extern node* hash_table[HASH_MAX];
extern FILE* hash_file;

char usr_input;

int main(int argc, char* argv[])
{
    bool isPathArg = false;
    char string_input[MAX_NAME];
    char parsed_input[MAX_NAME];
    int l = 0;
    size_t size = 0;
    char* str = NULL;
    bool isLimited;

    int num_items;
    char usr_input;
    bool deleted;

    switch (argc)
    {
    case 1:
        printf("WARNING: No input file provided, hash table will be empty on start\n");
        isPathArg = false;
        break;

    case 2:
        isPathArg = true;
        printf("Opening %s..\n", argv[1]);
        break;
    
    default:
        printf("Invalid number of arguments, only one is required\n"
                "Do you want to continue using the first argument provided? y/n\n");
        
        usr_input = getchar();

        while (usr_input != 'y' && usr_input != 'n')
        {
            printf("%c\n", usr_input);
            printf("Invalid selection, please choose y/n\n");
            usr_input = fgetc(stdin);

        }

        if(usr_input == 'n')
        {
            isPathArg = false;

            printf("Exiting..\n");
            break;
        }

        isPathArg = true;
        break;
    }


    if(isPathArg)
    {
        hash_file = fopen(argv[1], "r");
        if(hash_file == NULL)
        {
            printf("ERROR: CANNOT OPEN SPECIFIED FILE\n");
            return -1;
        }
        
        printf("Processing %s..\n", argv[1]);

        while (getline(&str, &size, hash_file) != -1)
        {   
            str[strcspn(str, "\n")] = 0;
            add_to_hash(str);
            l++;
        }

        printf("Successfully added %d items to hash table..\n\n", l);

    }
    



    print_menu();

    usr_input = fgetchar();
    fflush(stdin);

    while (true) //loop until usr_input is 7
    {
        switch (usr_input)
        {
        case '1':
            print_hash(hash_table);
            break;
        case '2':
            
            num_items = validate_int();

            printf("\n\n%d\n\n", num_items);
            print_hash_limited(num_items);
            break;

        case '3':
            printf("Enter string to look up in hash table: ");
            fgets(string_input, MAX_NAME, stdin);
            fflush(stdin);
            string_input[strcspn(string_input, "\n")] = 0;

            printf("%s was %s in the hash table.\n", string_input, find(string_input) ? "found": "not found");
            break;
        
        case '4':
            printf("Enter string to add to hash table: ");
            fgets(string_input, MAX_NAME, stdin);
            fflush(stdin);
            string_input[strcspn(string_input, "\n")] = 0;
            printf("Adding %s to hash table...\n", string_input);
            add_to_hash(string_input);
            break;
        case '5':
            printf("Enter string to delete from hash table: ");
            fgets(string_input, MAX_NAME, stdin);
            fflush(stdin);
            string_input[strcspn(string_input, "\n")] = 0;
            
            // printf("Searching for %s..\n", string_input);
            
            if( !find(string_input))
            {
                printf("%s was not found!", string_input);
            }

            else
            {
                deleted = delete_from_hash(string_input);

                if(deleted)
                {
                    printf("Successfully deleted %s from hash table", string_input);
                }
                else
                {   
                    printf("ERROR: Could not delete item from hash table");
                }
            }

            deleted = false;

            break;

        case '6':
            printf("Enter path of file to add to hash table: ");
            fgets(string_input, MAX_PATH, stdin);
            fflush(stdin);
            string_input[strcspn(string_input, "\n")] = 0;
            printf("Adding %s to hash table...\n", string_input);

            hash_file = fopen(string_input, "r");
            if(hash_file == NULL)
            {
                printf("ERROR: CANNOT OPEN SPECIFIED FILE\n");
                return -1;
            }
            
            printf("Processing %s..\n", string_input);
            

            while (getline(&str, &size, hash_file) != -1)
            {   
                str[strcspn(str, "\n")] = 0;
                add_to_hash(str);
                l++;
            }

            printf("Successfully added %d items to hash table..\n\n", l);
            
            break;
        
        case '7':
            printf("Exiting..\n");
            return 0;

        case '8':

            printf("\nThis benchmark test clocks the time taken to find items from one file in the hash table. Provide a file name and then the number of items you want to lookup in that file. A stopwatch will calculate the time taken to look up those items\n");
            printf("Note: This was used mostly as a tool to optimise the bucket size of the hash table\n\n");

            printf("Enter path of file to add to hash table: ");
            fgets(string_input, MAX_PATH, stdin);
            fflush(stdin);
            string_input[strcspn(string_input, "\n")] = 0;

            hash_file = fopen(string_input, "r");

            printf("Opening %s\n", string_input);
            if(hash_file == NULL)
            {
                printf("ERROR: CANNOT OPEN SPECIFIED FILE\n");
                return -1;
            }

            num_items = validate_int();
            
            printf("Searching %d names in %s...\n", num_items, string_input);

            clock_t begin = clock();
            
            l = 0;
            while (getline(&str, &size, hash_file) != -1 && l < num_items)
            {   
                str[strcspn(str, "\n")] = 0;
                find(str);
                l++;
            }

            clock_t end = clock();
            double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

            printf("Successfully looked-up %d items in the hash table..in %lf seconds\n\n", l, time_spent);
            

            break;
        
        default:
            print_menu();
            break;
        }

        printf("\n\n Select option from menu (7 to quit).\n");

        fflush(stdin);
        usr_input = fgetchar();
        fflush(stdin);

    }
    

    fclose(hash_file);
    hash_file = NULL;

    free_hash();
    return 0;
}

