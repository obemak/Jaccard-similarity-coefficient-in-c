#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myfunctions.h"



int main(int argc, char const *argv[])
{

    char* list1[] = {"hello", "hello"};
    char* list2[] = {"hello", "hello", "candy"};

    printf("hello world %.2f", calculate_similarity(list1, list2, 2, 3));
    return 0;
}
