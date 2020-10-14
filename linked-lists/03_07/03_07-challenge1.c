#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "allocerr.h"


#define SIZE 16
#define FNAME "family.dat"
enum { FALSE, TRUE };
struct family {
	char name[SIZE];
	char relationship[SIZE];
	int age;
	struct family *next;
};

struct family *allocate();
void add_record(struct family **head);
void remove_record(struct family **head);
void print_list(struct family **node);
void save_list(struct family **head);
void open_list(struct family **head);

/* read standard input, discard newline */
char *input(void)
{
	static char buffer[SIZE];
	char *r;
	int x;

	/* initialize the buffer */
	buffer[0]='\0';

	/* gather input */
	r = fgets(buffer,SIZE,stdin);
	if( r==NULL )
	{
		fprintf(stderr,"Input error\n");
		exit(1);
	}
	
	/* remove the newline */
	for(x=0; x<SIZE; x++)
	{
		/* remove newline */
		if( buffer[x]=='\n' )
		{
			buffer[x]='\0';
			break;
		}
	}

	return(buffer);
}

int main()
{
	struct family *first;
	int done;
	char command[SIZE];

	/* initialize first record to NULL */
	first = NULL;

	/* main menu and input loop */
	done = FALSE;
	puts("Family Database");
	while(!done)
	{
		/* initialize the current pointer to
		   the start of the list */
		// current = first;
		/* output menu */
		puts("Menu:");
		puts("A - Add record");
		puts("D - Delete record");
		puts("L - List all records");
		puts("O - Open");
		puts("S - Save");
		puts("Q - Quit");
		printf("Choice: ");
		/* read input */
		strcpy(command,input() );
		/* process selection */
		switch(command[0])
		{
			/* add a record */
			case 'A':
			case 'a':
				add_record(&first);
				break;
			/* delete a record */
			case 'D':
			case 'd':
				remove_record(&first);
				break;
			/* list all records */
			case 'L':
			case 'l':
				print_list(&first);
				break;
			/* open/retrieve existing records */
			case 'O':
			case 'o':
				open_list(&first);
				break;
			/* save all records */
			case 'S':
			case 's':
				save_list(&first);
				break;
			/* quit the program */
			case 'Q':
			case 'q':
				done = TRUE;
				puts("Bye!");
				break;
			/* something weird typed */
			default:
				puts("Unrecognized command");
		}
	}

	return(0);
}

struct family *allocate()
{
	struct family *new;
	new = (struct family *)malloc(sizeof(struct family)*1);
	if  (new == NULL) {
		fail_alloc(FAIL_ARGS);
	}
	return new;
}

void add_record(struct family **head)
{
	// char name[size], char rel[size], int age, struct family next

	struct family *add; 
	struct family **seek = head;
	char *endp = NULL;
	char ageBuf[SIZE];

	add = allocate();
	puts("Please enter the name:");
	strcpy(add->name, input());

	puts("Please enter the relationship:");
	strcpy(add->relationship, input());

	puts("Please enter the age:");
	strcpy(ageBuf, input());

	add->age = strtol(ageBuf, &endp, 10);
	add->next = NULL;

	while (*seek != NULL) {
		seek = &(*seek)->next;
	}
	*seek = add;
}

void remove_record(struct family **head)
{
	struct family **indirect = head;
	struct family *temp = NULL;
	char idBuf[SIZE];
	char *endp;
	int id;
	int i = 0;

	if (*head == NULL) {
		puts("Empty list");
		return;
	}

	puts("Please type the id to delete:");
	strcpy(idBuf, input());
	id = strtol(idBuf, &endp, 10);

	while (*indirect != NULL)
	{
		if (i++ == id) {
			break;
		}
		indirect = &(*indirect)->next;
	}

	if (*indirect == NULL)
	{
		puts("ID not found.");
		return;
	}

	temp = *indirect;
	*indirect = temp->next;
	free(temp); 
}

void print_list(struct family **node)
{
	int id = 0;

	if (*node == NULL) {
		puts("List is empty.");
		return;
	}

	puts("\nPrinting:");
	while (*node != NULL) {
		printf("%d: name: %s, rel: %s, age: %d\n", 
			id,
			(*node)->name,
			(*node)->relationship,
			(*node)->age
		);
		node = &(*node)->next;
		id++;
	}
	puts("");
}

void save_list(struct family **head)
{
	FILE *fp;
	struct family **seek = head;
	int id = 0;

	if (*seek == NULL) {
		puts("Nothing to save.");
		return;
	}

	fp = fopen(FNAME, "w");
	if (fp == NULL) {
		puts("Failed to open and write to file");
		exit(0);
	}

	while (*seek != NULL) {
		printf("Writing element with id: %d\n", id);
		fwrite(*seek, sizeof(struct family), 1, fp);
		seek = &(*seek)->next;
		id++;
	}

	fclose(fp);

	puts("Data saved.");
}

void open_list(struct family **head)
{
	FILE *fp;
	struct family **seek = head;
	struct family *add;
	int id = 0;

	fp = fopen(FNAME, "r");
	if (fp == NULL) {
		puts("Failed to open file");
		exit(0);
	}

	puts("");
	while (fread(add = allocate(), sizeof(struct family), 1, fp) != 0) {
		puts("Reading element...");

		if (add == NULL) {
			free(add);
			break;
		}

		printf("%d: name: %s, rel: %s, age: %d\n", 
			id,
			add->name,
			add->relationship,
			add->age
		);

		*seek = add;
		(*seek)->next = NULL;

		seek = &(*seek)->next;
		id++;
	}

	fclose(fp);
	puts("Data loaded.\n");
}