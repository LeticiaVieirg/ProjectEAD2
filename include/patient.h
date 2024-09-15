//Declaring the librarers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Defining size
#define MAX_PATIENTS 100 

//Declarate of the input type structure 
typedef struct {
    char name[50]; 
    char cpf[15];  
    int age;
} Patient;

//Functions
//Function that find patient by CPF
int find_patient_by_cpf(char *cpf);

//Function that register patient
void register_patient();
