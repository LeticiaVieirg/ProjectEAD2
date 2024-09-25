#ifndef FUNCOES_H
#define FUNCOES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/stock.h"
#include "../include/patient.h"
#include "../include/consultation.h"


void menuStock(List table[]);
void menuPatient();
void menuConsultation(List table[]);
void clear_buffer();
#endif /* FUNCOES_H */
