#include "../include/consultation.h"
List table[SIZE];

Heap *createHeap(int capacity) {
    Heap *heap = (Heap*) malloc(sizeof(Heap));
    heap->Patient = (Patient*) malloc(capacity * sizeof(Patient));
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

void insertIntoHeap(Heap *heap) {
    if (heap->size == heap->capacity) {
        printf("Full heap!\n");
        return;
    }

    Patient newPatient;

    printf("Enter the patient's age: ");
    scanf("%d", &newPatient.age);

    printf("Inform the procedure to be carried out: ");
    getchar();
    fgets(newPatient.description, 50, stdin);
    newPatient.description[strcspn(newPatient.description, "\n")] = '\0'; 

    decrement(table);

    // Insere o novo paciente na heap
    heap->Patient[heap->size] = newPatient;
    heapUp(heap, heap->size);  
    heap->size++;
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

Patient removeHeap(Heap *heap) {
    if (heap->size == 0) {
        printf("Heap Null!\n");
        exit(1);
    }

    // Remove a raiz (maior valor)
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
        printf("Patient: %d\n", heap->Patient[i].age);
        printf("Description: %s\n", heap->Patient[i].description);
    }
}

// int main() {
//     // Cria uma heap com capacidade para 10 pacientes
//     Heap *heap = createHeap(10);

//     insertInputs(table);

//     char opcao;

//     do {
//         // Inserindo os pacientes diretamente via insertIntoHeap
//         printf("\nCadastrando novo paciente...\n");
//         insertIntoHeap(heap);

//         // Pergunta se o usuário quer continuar
//         printf("\nDeseja cadastrar mais um paciente? (S/N): ");
//         scanf(" %c", &opcao);  // Note o espaço antes de %c para ignorar caracteres em branco

//     } while (opcao == 'S' || opcao == 's');  // Continua enquanto o usuário digitar 'S' ou 's'

//     // Exibe a heap após as inserções
//     printf("\nHeap após inserções:\n");
//     displayHeap(heap);

//     // Remove a pessoa mais velha (a raiz da heap)
//     printf("\nRemovendo a pessoa com maior idade...\n");
//     Patient removido = removeHeap(heap);
//     printf("Paciente removido: idade = %d, descrição = %s\n", removido.age, removido.description);

//     // Exibe a heap após a remoção
//     printf("\nHeap após a remoção:\n");
//     displayHeap(heap);

//     // Liberando a memória da heap
//     freeHeap(heap);

//     return 0;
// }
