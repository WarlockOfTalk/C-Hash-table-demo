#define HASH_MAX 1000 //hash table length
#define LIST_LEN 2000 //number of items to input in hash table
#define MAX_NAME 50 //max length of an item

typedef struct node
{
    char* name; 
    struct node* next;
}node;

extern node* hash_table[HASH_MAX];
extern FILE* hash_file;

int hash(char* name);

void add_to_hash(char* name);
node* create(node* current, char* name);
node* new_node(char* name);

bool find(char* name);
bool find_node(node* current, char* name);

void print_list(node* current);
int print_list_limited(node* current, int num_items, int count);

bool delete_node(node** Pcurrent, char* string_input);
bool delete_from_hash(char* string_input);

void free_hash(void);
void free_list(node* current);

void print_hash();
void print_hash_limited(int num_items);
