// Create structure, fill with data, save to a file
// Structure as a pointer
    // string name, int age
// Prompt user to input both members
// Write to file saved.dat

#include <stdlib.h>
#include <stdio.h>
#include "../../allocerr.h"

#define OUTPUTFILE "saved.dat"

typedef struct Person 
{
    char name[32];
    int age;
} Person;


int main()
{
    Person *p;
    FILE *fp;

    // Allocate memory for Person Struct
    p = (Person *)malloc( sizeof (Person) * 1 );
    if (p == NULL)
    {
        fail_alloc(FAIL_ARGS);
    }

    // Get input values  
    printf("Please enter your name: ");
    scanf("%s", p->name);
    printf("Please enter your age: ");
    scanf("%d", &(p->age));

    // Open output file
    fp = fopen(OUTPUTFILE, "w");
    if ( fp == NULL )
    {
        fprintf(stderr, "Could not open file\n");
        return EXIT_FAILURE;
    }

    // Write to output file
    fwrite(p, sizeof(Person), 1, fp);

    // Free allocated memory, and close open files
    free(p);
    fclose(fp);

    printf("Information saved to %s\n", OUTPUTFILE);

    return 0;
}