#include "util.h"
#include <stdio.h> // for printing
#include <string.h> // for strings
#include <stdlib.h>


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

void strings_test() {
    
    char s1[] = "ABCD"; // this will have a null terminator at the end of it \0
    char s2[20]; // an empty string ready to hold data, the null terminator has the lowest value

    // copies a string, dest <- source
    strcpy(s2, s1);
    printf("s2 is now %s\n", s2);

    strcat(s2, " 123"); // adds to a string
    printf("s2 is now %s\n", s2);

    if (strcmp(s2, s2)) { // comapres two strings
        printf("They are equal\n");
    }

    // strlen prints the length except for the null terminator
    printf("The length of s2 is %lu\n", strlen(s2)); 
    char* s_ptr = "abcd";
    printf("The length of s_ptr is %lu\n", strlen(s_ptr));  // it also works on ptr_array

    if ('a' < 'b') { // to compare chars, the one with lower value comes first
        printf("a comes before b\n");
    }

    // it does not support a substring function
}

void user_input_test() {

    int num;
    printf("Enter an interger\n");
    scanf("%d", &num);
    printf("Integer given is %d\n", num);

    char txt[200];
    printf("Enter a text\n");
    scanf("%s", txt);
    printf("Text entered is %s\n", txt); // does not take spaces
}

void user_input_test_2() {

    char txt2[200];
    printf("Enter another text\n");
    // fgets supports spaces in the string
    if (fgets(txt2, sizeof(txt2), stdin) != NULL) {
        txt2[strcspn(txt2, "\n")] = '\0'; // gets the location
        printf("The text we got is %s\n", txt2);
    }
}

char* get_str() {

    // char txt[] = "got result"; // this returns a null, since it is on the stack

    // this is a string literal    
    // stored in read only section and lasts until the end
    char* txt = "got result"; 
    
    printf("inside the function %s\n", txt);

    return txt;
}

void dynamic_allocation_test() {

    // use malloc to allocated the memory dynamically
    // it allocated 20 * size of int (4 bytes) on the heap
    // you have to use pointer casting when using malloc
    int* data = (int*)malloc(20 * sizeof(int));
    free(data);// this frees up the data

    // use calloc to do the same thing, but it sets up the memory to zero
    char* content = (char*)calloc(30,  sizeof(char));
    free(content);

    // using realloc will resize the memory
    int* nums = (int*) calloc(20, sizeof(int));
    nums = (int*)realloc(nums, 50);
    free(nums);
}

void sizeof_test() {
    int a;
    double b;
    int arr[10];

    // it returns the size of the datatype in bytes
    printf("Size of int: %zu bytes\n", sizeof(int));
    printf("Size of double: %zu bytes\n", sizeof(double));
    printf("Size of variable a: %zu bytes\n", sizeof(a));
    printf("Size of variable b: %zu bytes\n", sizeof(b));
    printf("Size of array arr: %zu bytes\n", sizeof(arr));
    printf("Size of pointer to int: %zu bytes\n", sizeof(int *));
}

void sizeof_test_2() {

    //you can use sizeof to get how many items are held in an array
    int data[5];
    // total array size / size of a single item = num of items
    int size = sizeof(data) / sizeof(data[0]);

    // using it on a pointer would be useless
}

char* string_reversal(char* data) {

    int length = strlen(data);

    char result [length+1];
    memset(result, 0, length+1);

    char buffer[length];
    memset(buffer,0,length);

    int end_index = length-1;

    for (int i=0; i<length; i++) {

        if (data[i] == ' ' || i == length -1) {

            if (i == length -1) {
                strncat(buffer, &data[i], 1);
            }

            int x = end_index;
            for (int j=0; j < strlen(buffer); j++) {
                result[x - strlen(buffer)+1] = buffer[j];
                x++;
            }
            
            end_index -= strlen(buffer);
            result[end_index] = ' ';
            end_index --;
            memset(buffer,0,length);

        } else {
            strncat(buffer, &data[i], 1);
        }
    }
    result[length]= '\0';

    char* res = (char*) malloc((length+1) * sizeof(char));
    strcpy(res, result);
    return res;
}

