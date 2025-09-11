# Overview

In this assignment, you will learn to:
* Read data from binary files using `fread`
* Write data to binary files using `fwrite`
* Use C's built-in `qsort` function to sort things
* Use the `struct` construct in C
* Edit a Makefile

# Background
## Binary files
Functions like `fscanf` and `fprintf` are useful 
for working with text files - files consisting of 
printable characters, usually one corresponding to each byte, 
such as `.txt` text files, program code like `.c`, `.h`, and 
`.py` files, markup files like `.md`, and `.html` files, and 
text-based data files like `.csv`, `.json`, and `.xml` files.
However, most file types are not text-based, such as images,
audio files, PDFs, and program-specific or proprietary types
like `.blend` and `.solidprt`.  These other files are known as 
binary files (even though all files consist of 1s and 0s), and 
the bytes in these files correspond not to characters but to pixels,
bits of audio, integers in a header providing parameters for the 
interpretation of the file, etc., according to the schema of the 
file type.

In this lab, you will be reading and writing files of the generic
`.bin` type, which do not have any elaborate schema.  These files 
contain the integer values that compose a series of three-dimensional
vectors:

v_0 = (x_0, y_0, z_0)

v_1 = (x_1, y_1, z_1)

v_2 = (x_2, y_2, z_2)

v_3 = (x_3, y_3, z_3)
...

The files contain only the integer values, each one represented by 
four consecutive bytes, in the order x_0, y_0, z_0, x_1, y_1 ...,
with no file header or delimiter between vectors.

In C, one can copy bytes from a file to a buffer using the `fread`
function, as described in [this reference](https://en.cppreference.com/w/c/io/fread).
In a file with a header, the header might mention the size of the file 
so that some number of bytes can be allocated for use, or in a file without,
the function can be called repeatedly until the file pointer returns end-of-file,
and the size of the file determined that way.

Binary files can be written to using the `fwrite` function.

## The `struct` keyword in C
The C programming language does not have classes (with which you may
be familiar from Python or other langauges); this is the primary
feature that distinguishes it from C++ (which its developer,
Bjarne Stroustrup, considered naming "C with classes").  This means
that C does not have objects which can perform methods.  However, C 
does have `struct` objects, sometimes called "records" or
"passive data structures".

A `struct` is simple.  It is like a variable composed of multiple 
types in order.  For example, the struct below consists of two integers
and a character:
```
struct point {
    int x;
    int y;
    color c;
}
```
The attributes of the struct can be accessed directly using the `.` operator,
or indirectly using the `->` operator:
```
#include "point.h"

int main() {
    point A;
    A.x = 2;
    A.y = 6;
    point B = { .x = 4, .y = -5, .c = 'r' }
    point * C = malloc(sizeof(point));
    if (C) {
        C->x = 5;
        C->y = 10;
    }
}
```
Since structs take up more memory than single variables, they are 
often passed by address instead of copied:
```
#include "sqrt.h"

float sqrt(int n);

float distance(point * P, point * Q) {
    int a = P->x - Q->x;
    int b = P->y - Q->y;
    int c_squared = a * a + b * b;
    return sqrt(c);
}
```
In this program, you will use a `struct` consisting of three integers.
It is defined in "hw04.h"; you can **read its attribute names there**.

## The qsort function 
In CS 159, you were made familiar with a number of inefficient sorting 
algorithms.  In 368, you may be made familiar with a number of efficient ones.
In industry and in projects, you will not write sorting algorithms[^*], because
those have already been written and are free to use.

The `qsort` function in C, as described in 
[this reference](https://en.cppreference.com/w/c/algorithm/qsort),
sorts an array in-place (that is, calling it with an array as the first argument
causes the array to be sorted; it does not return another array).  All 
the sorting logic (including the choice of algorithm) is done by the compiler,
except for the function to compare two items and determine which belongs
later in the list.  See the reference for an example of how to use `qsort` to 
sort an array of integers.

# What to do
The program you write in this assignment reads in a binary file representing a list 
of vectors, puts them in an array, sorts the array, and writes the result to a 
binary file in the same format.  You will need to write functions:

* First, a function to count and return the number of vectors in a given file.
* Second, a function to read a file and assign the values appropriately to vectors.
* Third, a function to compare two vectors for sorting, to be used by qsort.
* Fourth, the call to qsort.
* Fifth, a function to write the sorted array to a binary file.

In this program, you will be responsible for memory allocation and error handling.
The functions you write may need to return errors to be sent to main.

The sorting of the vectors should be based not on magnitude but on the coordinates in order,
with a vector being greater if its x-coordinate is greater, less if its x-coordinate is less,
or, if the x-coordinates are equal, greater if its y-coordinate is greater, less if its y-coordinate 
is less, or, if its x- and y-coordinates are equal, then to be based on its z-coordinate.

## Makefile

If you look at the Makefile for this homework assignment, you may notice two things:

Firstly, there are new targets, `show1` and `show2`, which convert binary files to hex-based text files.  This makes it easier to compare the resulting values in the shorter lists, 
although the resulting hexdumps are little-endian, which means that the first few (lower-address)
bytes are the significant digits in the integer.

Secondly, there are fewer test targets than input and expected outputs given.  Writing more
test targets and adding them to `testall`'s dependency list is good practice for when you
write your own Makefiles.
The expected results 3, 4, 5, 6, 7, and 8 correspond to the binaries
sort_function_tester, medium_list, medium_list_high_vals, long_list, long_list_high_vals, and
very_long_list_very_high_vals, respectively.

## Submission instructions
Please submit only your `hw04.c` file to Gradescope.  Do not modify `main.c`, `hw04.h`, or other files;
these will not be graded.

[^*] Unless you are a genius developing a new and more efficient general sorting algorithm,
or are exploring whether a new sorting algorithm may be more efficient in some particular application.
