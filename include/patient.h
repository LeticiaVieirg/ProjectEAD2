#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATIENTS 100 

typedef struct {
    char name[50]; 
    char cpf[15];  
    int age;
} Patient;
