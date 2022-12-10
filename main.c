#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "helpers.h"


extern node* hash_table[HASH_MAX];
extern FILE* hash_file = NULL;

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
    



    printf("MENU\n"
            "\t1: Print all items in hash table\n"
            "\t2: Print a defined number of items\n"
            "\t3: Search hash table for string\n"
            "\t4: Add string to hash table\n"
            "\t5: Delete string from hash table\n"//TODO
            "\t6: Import text file to hash table\n" //TODO
            "\t7: Exit\n"
            "Select an option: "
        );

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
            printf("How many items to print?\n");
            scanf("%d", &num_items);
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
        
        default:
            printf("Invalid option!\n");
            printf("\nMENU\n"
            "\t1: Print all items in hash table\n"
            "\t3: Search hash table for string\n"
            "\t4: Add string to hash table\n"
            "\t5: Delete string from hash table\n"
            "\t6: Something else I will add\n" //TODO
            "\t7: Exit\n"
            "Select an option: "
        );
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

