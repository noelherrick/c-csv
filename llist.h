#include <stdlib.h>

struct strllist_node
{
	char* text;
	struct strllist_node* next;
};

struct strllist
{
	struct strllist_node* head;
	struct strllist_node* tail;
};

struct strarrllist_node
{
	char** arr;
	struct strarrllist_node* next;
};

struct strarrllist
{
	struct strarrllist_node* head;
	struct strarrllist_node* tail;
};

struct strllist* strllist_create(void);
struct strllist_node* strllist_nalloc(void);
int strllist_count(struct strllist* list);
void strllist_print(struct strllist* list);
void strllist_add(struct strllist* list, char* text);
char** strllist_to_array(struct strllist* list, int size);
void strllist_del(struct strllist* list);

struct strarrllist* strarrllist_create(void);
struct strarrllist_node* strarrllist_nalloc(void);
int strarrllist_count(struct strarrllist* list);
//void strarrllist_print(struct strarrllist* list);
void strarrllist_add(struct strarrllist* list, char** arr);
char*** strarrllist_to_array (struct strarrllist* list, int size);
void strarrllist_del(struct strarrllist* list);
char** strarrllist_pop(struct strarrllist* list);