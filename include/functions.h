#ifndef FUNCOES_H
#define FUNCOES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/stock.h"
#include "../include/patient.h"
#include "../include/consultation.h"
#include "../include/clear.h"

// Function to display the stock menu and handle stock-related operations
void menuStock(List table[]);

// Function to display the patient menu and handle patient-related operations
void menuPatient();

// Function to display the consultation menu and handle consultation-related operations
void menuConsultation(List table[]);

// Function to clear the input buffer
void clear_buffer();

#endif /* FUNCOES_H */
