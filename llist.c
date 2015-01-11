#include "llist.h"

struct strllist* strllist_create(void)
{
	struct strllist* newlist = (struct strllist *) malloc(sizeof(struct strllist));
	
	newlist->head = NULL;
	newlist->tail = NULL;

	return newlist;
}

void strllist_add(struct strllist* list, char* text)
{
	struct strllist_node* newtail = strllist_nalloc();
	newtail->text = text;

	if (list->head == NULL)
	{
		list->head = newtail;
		list->tail = newtail;
	}
	else
	{
		list->tail->next = newtail;
		list->tail = newtail;
	}	
}

int strllist_count(struct strllist* list)
{
	if (list->head == NULL)
	{
		return 0;
	}

	struct strllist_node* currnode = list->head;

	int count = 0;

	while (currnode != NULL)
	{
		count++;
		currnode = currnode->next;
	}

	return count;
}

void strllist_print(struct strllist* list)
{
	if (list->head == NULL)
	{
		return;
	}

	struct strllist_node* currnode = list->head;

	while (currnode != NULL)
	{
		currnode = currnode->next;
	}
}

void strllist_del(struct strllist* list)
{
	if (list->head == NULL)
	{
		return;
	}

	struct strllist_node* currnode = list->head;
	struct strllist_node* prevnode;

	while (currnode != NULL)
	{
		prevnode = currnode;
		currnode = currnode->next;
		free(prevnode->text);
		free(prevnode);
	}
}

char** strllist_to_array(struct strllist* list, int size)
{
	char** collist = malloc(sizeof(char*) * size);

	struct strllist_node* currnode = list->head;

	for (int i = 0; i < size; i++)
	{
		collist[i] = currnode->text;
		currnode = currnode->next;
	}

	return collist;
}

struct strllist_node* strllist_nalloc(void)
{
	struct strllist_node* newnode = (struct strllist_node *) malloc(sizeof(struct strllist_node));
	newnode->next = NULL;
	return newnode;
}

struct strarrllist* strarrllist_create(void)
{
	struct strarrllist* newlist = (struct strarrllist *) malloc(sizeof(struct strarrllist));
	
	newlist->head = NULL;
	newlist->tail = NULL;

	return newlist;
}

void strarrllist_add(struct strarrllist* list, char** arr)
{
	struct strarrllist_node* newtail = strarrllist_nalloc();
	newtail->arr = arr;

	if (list->head == NULL)
	{
		list->head = newtail;
		list->tail = newtail;
	}
	else
	{
		list->tail->next = newtail;
		list->tail = newtail;
	}	
}

int strarrllist_count(struct strarrllist* list)
{
	if (list->head == NULL)
	{
		return 0;
	}

	struct strarrllist_node* currnode = list->head;

	int count = 0;

	while (currnode != NULL)
	{
		count++;
		currnode = currnode->next;
	}

	return count;
}

void strarrllist_del(struct strarrllist* list)
{
	if (list->head == NULL)
	{
		return;
	}

	struct strarrllist_node* currnode = list->head;
	struct strarrllist_node* prevnode;

	while (currnode != NULL)
	{
		prevnode = currnode;
		currnode = currnode->next;
		free(prevnode->arr);
		free(prevnode);
	}
}

/*
void strarrllist_print(struct strarrllist* list)
{
	if (list->head == NULL)
	{
		return;
	}

	struct strarrllist_node* currnode = list->head;

	while (currnode != NULL)
	{
		currnode = currnode->next;
	}
}
*/


struct strarrllist_node* strarrllist_nalloc(void)
{
	struct strarrllist_node* newnode = (struct strarrllist_node *) malloc(sizeof(struct strarrllist_node));
	newnode->next = NULL;
	return newnode;
}

char*** strarrllist_to_array (struct strarrllist* list, int size)
{
	char*** twodarr = (char***)malloc(sizeof(char***) * size);

	struct strarrllist_node* currnode = list->head;

	for (int i = 0; i < size; i++)
	{
		twodarr[i] = currnode->arr;
		currnode = currnode->next;
	}

	return twodarr;
}

// This function gets the head and replaces head in the list with the next node
char** strarrllist_pop (struct strarrllist* list)
{
	struct strarrllist_node* currhead = list->head;

	if (currhead->next == NULL)
	{
		list->tail = NULL;
	}

	list->head = currhead->next;

	return currhead->arr;
}