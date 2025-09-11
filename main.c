#include <stdio.h>
#include <stdlib.h>
#include "hw04.h"

int main(int argc, char * * argv) {
    if (argc != 3) {
        fprintf(stderr, "Error:  program usage is as below:\n./binarysort inputfile outputfile\n");
        return EXIT_FAILURE;
    }

    int vector_count = 0;
    if (count_vectors_in_file(argv[1], &vector_count)) {
        fprintf(stderr, "Error, %s is not found to be a valid binary file.\n", argv[1]);
        return EXIT_FAILURE;
    }

    struct vector * vector_list = read_vectors_from_file(argv[1], vector_count);
    if (!vector_list) return EXIT_FAILURE;
    
    call_qsort(vector_list, vector_count);

    if (write_vectors_to_file(argv[2], vector_list, vector_count)) {
        fprintf(stderr, "Error, unable to write to output file.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}