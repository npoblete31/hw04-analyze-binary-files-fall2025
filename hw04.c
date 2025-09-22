#include <stdlib.h>
#include <stdio.h>
#include "hw04.h"

/* The first function you write counts the numbers of vectors
(that is, the number of triads of 32-bit integers) found in the
file with name 'filename'.  It assigns this value to the location
pointed to by 'vector_count'.  If it is unable to open the file,
OR if the file cannot be interpreted as a binary file of vectors
(that is, it does not contain a multiple of three integers' worth of data), it returns
EXIT_FAILURE.  Else, it returns EXIT_SUCCESS.  */
int count_vectors_in_file(char * filename, int * vector_count) {
    // Open the file in "rb" (read binary) mode
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return -1; // Indicate an error occurred
    }
    // Set up a buffer of three integers to read to,
    // a count of how many integers are read in on the last pass,
    // and a count of how many times three integers have been read in
    int buffer[3];
    int last_pass_count = 0;
    int full_pass_count = 0;
    int nRead = 0;
    // While not encountering the end of the file or receiving an error,
    // call f_read with the buffer to retrieve three integers.  Update
    // the counts.
    while ((nRead = fread(buffer, sizeof(int), 3, file)) > 0) {
        if (nRead == 3) {
            full_pass_count++;
        }
        else {
            last_pass_count = nRead;
            break;
        }
    }
    if (ferror(file)){
        perror("Error reading file");
        fclose(file);
        return -1;
    }

    fclose(file);
    *vector_count = full_pass_count;
    // If the last pass reached the end of the file and retrieved no integers
    // (rather than a stray one or two) and didn't throw an error, return EXIT_SUCCESS
    // Else, return EXIT_FAILURE
    if (last_pass_count == 0) {
        return EXIT_SUCCESS; 
    }
    else {
        return EXIT_FAILURE;
    }
}

/* The second function you write allocates space for the vectors
counted before - there are vector_count vectors stored in the file at
filename.  It reads in those vector_count vectors from the file 'filename'
to the space it allocates and returns a pointer to that space.

That space will need to be freed - though, of course, not before
the program is done using it.  Free it in an appropriate place (hint: not in this function.)

In the event of a file read failure or memory allocation failure (both
are unlikely), you can return NULL.*/
struct vector * read_vectors_from_file(char * filename, int vector_count) {
    // Open the file in "rb" (read binary) mode
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }
    // Allocate sufficient space for all of the vector structs
    struct vector *vector_list = malloc(vector_count * sizeof(struct vector));
    if (vector_list == NULL) {
        perror("Error allocating memory");
        fclose(file);
        return NULL;
    }
    // Read in all the integers from the file.  Place each
    // set into the x-, y-, and z-coordinates of a vector in the list
    size_t nRead = fread(vector_list, sizeof(struct vector), vector_count, file);

    // Return the list of vectors
    if (nRead == vector_count) {
        fclose(file);
        return vector_list;
    }
    else {
        perror("Error reading file");
        fclose(file);
        return NULL;
    }
    return NULL;
}

/* The third function you write takes in two pointers of type
const void*, casts them to access the attributes of the 
structs to which they point, and returns a positive value if the
first is greater, a negative value if the second is greater,
and 0 if they are equal.  Being greater is determined by the 
x-coordinate's being greater, or, those being equal, by the
y-coordinate's being greater, or, those also being equal, by 
the z-coordinate's being greater.

This function is meant to be sent to qsort - see 
https://en.cppreference.com/w/c/algorithm/qsort for an example
of using qsort and a warning about comparison functions.*/
int compare_vectors(const void* a, const void* b) {
    const struct vector *vecA = (const struct vector *)a;
    const struct vector *vecB = (const struct vector *)b;
    if (vecA->x != vecB->x) {
        return vecA->x - vecB->x;
    }
    if (vecA->y != vecB->y) {
        return vecA->y - vecB->y;
    }
    if (vecA->z != vecB->z) {
        return vecA->z - vecB->z;
    }
    return 0;
}

/* The fourth function calls qsort with the appropriate
parameters, including the function above. */
void call_qsort(struct vector * vector_list, int vector_count) {
    qsort(vector_list, vector_count, sizeof(struct vector), compare_vectors);
}

/* The fifth function writes the vectors in 'vector_list' (which
has length 'vector_count') to a binary file at 'filename'.  If the
file cannot be opened, it returns EXIT_FAILURE. */
int write_vectors_to_file(char * filename, struct vector * vector_list, int vector_count) {
    // Open the file in "wb" (write binary) mode
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    // Write the coordinates of each vector to the binary file
    fwrite(vector_list, sizeof(struct vector), vector_count, file);
    if (ferror(file)){
        perror("Error writing to file");
        fclose(file);
        return EXIT_FAILURE;
    }
    fclose(file);
    free(vector_list);
    return EXIT_SUCCESS;
}
