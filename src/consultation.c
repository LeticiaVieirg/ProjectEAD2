#include "../include/consultation.h"
List table[SIZE];

Heap *createHeap(int capacity) {
    Heap *heap = (Heap*) malloc(sizeof(Heap));
    if (!heap) {
        printf("Memory allocation failed for heap.\n");
        return NULL;
    }
    heap->Patient = (Patient*) malloc(capacity * sizeof(Patient));
    if (!heap->Patient) {
        printf("Memory allocation failed for patient array.\n");
        free(heap);
        return NULL;
    }
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(Patient *patientOne, Patient *patientTwo) {
    Patient temp = *patientOne;
    *patientOne = *patientTwo;
    *patientTwo = temp;
}

void heapUp(Heap *heap, int index) {
    if (index == 0) return;

    int parent = (index - 1) / 2;
    if (heap->Patient[index].age > heap->Patient[parent].age) {
        swap(&heap->Patient[index], &heap->Patient[parent]);
        heapUp(heap, parent);
    }
}

void insertIntoHeap(Heap *heap, NodePatient **root, List table[]) {
    if (heap->size == heap->capacity) {
        printf("Full heap!\n");
        return;
    }

    Patient newPatient;
    char CPF[11];

    printf("Enter the patient's CPF: ");
    scanf("%s", CPF);

    NodePatient *foundPatient = returnSearchPatientByCPF(*root, CPF);
    if (foundPatient == NULL) {
        printf("Patient not found.\n");
    } else {
        printf("Patient found:\n");
        printf("Name: %s, Age: %d, CPF: %s\n", foundPatient->name, foundPatient->age, foundPatient->cpf);

        
        newPatient.age = foundPatient->age; 
        newPatient.dataPataient = *foundPatient;  
        strcpy(newPatient.description, "");  

        printf("Inform the procedure to be carried out: \n");
        getchar(); 
        fgets(newPatient.description, sizeof(newPatient.description), stdin);
        newPatient.description[strcspn(newPatient.description, "\n")] = '\0';

        printf("Provide the necessary inputs for the procedure:\n");
        int totalDecremented = 0;
        DecrementResult* results = decrement(table, &totalDecremented);
        strcpy(newPatient.dataInputs.productName, results->name);
        newPatient.dataInputs.amount = results->quantity;

    
        heap->Patient[heap->size] = newPatient;
        heapUp(heap, heap->size); 
        heap->size++;
    }
}

void heapBelow(Heap *heap, int index) {
    int bigger = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size && heap->Patient[left].age > heap->Patient[bigger].age) {
        bigger = left;
    }

    if (right < heap->size && heap->Patient[right].age > heap->Patient[bigger].age) {
        bigger = right;
    }

    if (bigger != index) {
        swap(&heap->Patient[index], &heap->Patient[bigger]);
        heapBelow(heap, bigger);  
    }
}

void searchByCPF(Heap *heap, const char *CPF) {
    int found = 0;  
    
    for (int i = 0; i < heap->size; i++) {
        if (strcmp(heap->Patient[i].dataPataient.cpf, CPF) == 0) {
            printf("Patient found at position %d:\n", i + 1);
            printf("Patient: %s\n", heap->Patient[i].dataPataient.name);
            printf("CPF: %s, Age: %d\n", heap->Patient[i].dataPataient.cpf, heap->Patient[i].age);
            printf("Description: %s\n", heap->Patient[i].description);
            printf("Input: %s, Amount: %d\n", heap->Patient[i].dataInputs.productName, heap->Patient[i].dataInputs.amount);
            found = 1;
            break;  
        }
    }

    if (!found) {
        printf("Patient with CPF %s not found.\n", CPF);
    }
}

Patient removeHeap(Heap *heap) {
    if (heap->size == 0) {
        printf("Heap Null!\n");
        exit(1);
    }

    
    Patient patientRemoved = heap->Patient[0];
    heap->Patient[0] = heap->Patient[heap->size - 1];
    heap->size--;

    heapBelow(heap, 0);  

    return patientRemoved;
}

void freeHeap(Heap *heap) {
    free(heap->Patient);
    free(heap);
}

void displayHeap(Heap *heap) {
    printf("Query List: \n");
    for (int i = 0; i < heap->size; i++) {
        printf("Position %d\n", i + 1);
        printf("Patient: %s\n", heap->Patient[i].dataPataient.name);
        printf("CPF: %s, Age: %d\n", heap->Patient[i].dataPataient.cpf, heap->Patient[i].age);
        printf("Description: %s\n", heap->Patient[i].description);
        printf("Input: %s, Amount: %d\n", heap->Patient[i].dataInputs.productName, heap->Patient[i].dataInputs.amount);
    }
}

void writeToFile(Heap *heap) {
    FILE *file = fopen("consultationBakn.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    
    for (int i = 0; i < heap->size; i++) {
        fprintf(file, "%s\n", heap->Patient[i].dataPataient.name);               
        fprintf(file, "%s\n", heap->Patient[i].dataPataient.cpf);   
        fprintf(file, "%d\n", heap->Patient[i].age);               
        fprintf(file, "%s\n", heap->Patient[i].description);                     
        fprintf(file, "%s\n", heap->Patient[i].dataInputs.productName);
        fprintf(file, "%d\n", heap->Patient[i].dataInputs.amount);        
    }

    fclose(file);
    printf("Data successfully written to file.\n");
}

Heap* loadFromFileHeap(Heap *heap) {
   
    FILE *file = fopen("consultationBakn.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading!\n");
        return NULL; 
    }

   
    Patient tempPatient;
    heap->size = 0;

   
    while (fgets(tempPatient.dataPataient.name, sizeof(tempPatient.dataPataient.name), file) != NULL) {
        
        tempPatient.dataPataient.name[strcspn(tempPatient.dataPataient.name, "\n")] = '\0';

        
        if (fscanf(file, "%s %d\n", tempPatient.dataPataient.cpf, &tempPatient.age) != 2) {
            printf("Error reading CPF and age.\n");
            fclose(file);
            return NULL;  
        }

       
        fgets(tempPatient.description, sizeof(tempPatient.description), file);
        tempPatient.description[strcspn(tempPatient.description, "\n")] = '\0';

        
        fscanf(file, "%s %d\n", tempPatient.dataInputs.productName, &tempPatient.dataInputs.amount);

        
        heap->Patient[heap->size] = tempPatient;
        heapUp(heap, heap->size);
        heap->size++;
    }

    fclose(file);  
    printf("Data successfully loaded from file.\n");
    return heap;
}

void editConsultationByCPF(Heap *heap, const char *CPF, List table[]) {
    int found = 0;

    for (int i = 0; i < heap->size; i++) {
        if (strcmp(heap->Patient[i].dataPataient.cpf, CPF) == 0) {
            printf("Patient found:\n");
            printf("Name: %s, CPF: %s, Age: %d\n", heap->Patient[i].dataPataient.name, heap->Patient[i].dataPataient.cpf, heap->Patient[i].age);
            printf("Current Description: %s\n", heap->Patient[i].description);
            printf("Current Input: %s, Amount: %d\n", heap->Patient[i].dataInputs.productName, heap->Patient[i].dataInputs.amount);

            
            printf("Enter new description (leave empty to keep current): ");
            getchar();
            char newDescription[100];
            fgets(newDescription, sizeof(newDescription), stdin);
            newDescription[strcspn(newDescription, "\n")] = '\0';

           
            if (strlen(newDescription) > 0) {
                strcpy(heap->Patient[i].description, newDescription);
            }

           
            printf("Inform the new equipment needed for the procedure:\n");
            int totalDecremented = 0;
            DecrementResult* results = decrement(table, &totalDecremented);

            
            if (results != NULL) {
                strcpy(heap->Patient[i].dataInputs.productName, results->name);
                heap->Patient[i].dataInputs.amount = results->quantity;
            } else {
                printf("Error while fetching equipment details. Keeping the previous values.\n");
            }

            printf("Consultation updated successfully!\n");
            found = 1;
            break; 
        }
    }

    if (!found) {
        printf("Patient with CPF %s not found.\n", CPF);
    }
}

