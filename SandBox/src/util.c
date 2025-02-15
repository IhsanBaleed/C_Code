#include "util.h"
#include <stdio.h>

// you can add files similar to how we do it in C++
// just make usre you compile them together in the make file

void print_test() {
    // to print we include stdio.h
    printf("My print_test Func\n");

    // to print an int, use  %d, if you dont include it
    int val = 10;
    printf("the val we got is %d \n", val);

    // you can also use it to format a print statement

    char name[] = "Alfred";
    printf("%s is the name, the age is %d \n", name, val);

    // %d or %i: Integer
    // %f: Floating-point number
    // %c: Character
    // %s: String
    // %x: Hexadecimal integer
    // %p: Pointer address
}

