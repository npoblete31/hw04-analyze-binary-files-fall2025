// The vector in this header is not to be confused with the variable-length
// vector found in the C++ standard library.
struct vector {
    int x;
    int y;
    int z;
};

int count_vectors_in_file(char * filename, int * vector_count);
struct vector * read_vectors_from_file(char * filename, int vector_count);
int compare_vectors(const void* a, const void* b);
void call_qsort(struct vector * vector_list, int vector_count);
int write_vectors_to_file(char * filename, struct vector * vector_list, int vector_count);