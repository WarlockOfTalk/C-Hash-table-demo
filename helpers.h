
#ifndef HELPERS_H_
#define HELPERS_H_

#define HASH_MAX 1 //hash table length
#define LIST_LEN 2000 //number of names to input in hash table
#define MAX_NAME 50 //max length of a name

typedef struct node
{
    char* name; 
    struct node* next;
}node;

node* hash_table[HASH_MAX];
FILE* hash_file;

int hash(char* name);
node* create(node* current, char* name);
node* new_node(char* name);
void add_to_hash(char* name);
void print_list(node* current);
int print_list_limited(node* current, int num_items, int count);

void print_hash();
void print_hash_limited(int num_items);
bool find_node(node* current, char* name);
bool find(char* name);
void free_list(node* current);
void free_hash(void);

bool delete_node(node** Pcurrent, char* string_input);
bool delete_from_hash(char* string_input);


#endif /* HELPERS_H_ */