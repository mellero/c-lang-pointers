// Read the file, fill the structure, output data
// Same struct as ..write
// Read from saved.dat into structure
// Output data

#include <stdlib.h>
#include <stdio.h>
#include "../../allocerr.h"

#define INPUTFILE "saved.dat"

typedef struct Person 
{
    char name[32];
    int age;
} Person;


int main()
{
    Person *buffer;
    FILE *fp;

    // Allocate memory for the Person struct 
    buffer = (Person *)malloc( sizeof (Person) * 1 );
    if (buffer == NULL)
    {
        fail_alloc(FAIL_ARGS);
    }

    // Open the input file to read from
    fp = fopen(INPUTFILE, "r");
    if ( fp == NULL )
    {
        fprintf(stderr, "Could not open file %s\n", INPUTFILE);
        return EXIT_FAILURE;
    }

    // Read the data from the input file to the buffer struct
    fread(buffer, sizeof(Person), 1, fp);

    // Output the values from the buffer struct
    printf("Your name is: %s\n", buffer->name);
    printf("Your name is: %d\n", buffer->age);

    // Free alloc'd memory, and close open files
    free(buffer);
    fclose(fp);

    return 0;
}