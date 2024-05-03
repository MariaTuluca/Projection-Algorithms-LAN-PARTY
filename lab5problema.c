#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include "stive.h" // Fișierul header pentru operațiile cu stiva

int* aleatoriu(int n) {
    int* vector = (int*)malloc(n * sizeof(int));
    int elem, ok;

    for (int i = 0; i < n; i++) {
        do {
            elem = (rand() % n) + 1;
            ok = 1;
            for (int j = 0; j < i; j++)
                if (vector[j] == elem) {
                    ok = 0;
                    break;
                }
        } while (ok == 0);

        vector[i] = elem;
    }

    return vector;
}

Node* rearrangeStack(Node* in, int* permutation, int n) {
    Node* out = NULL;
    Node* spur = NULL;

    int index = 0;
    int expected_value = permutation[index];

    while (!isEmpty(in)) {
        int current_value = top(in);
        if (current_value == expected_value) {
            pop(&in);
            push(&out, current_value);
            index++;
            if (index < n)
                expected_value = permutation[index];
        } else {
            if (!isEmpty(spur) && top(spur) == expected_value) {
                pop(&spur);
                push(&out, expected_value);
                index++;
                if (index < n)
                    expected_value = permutation[index];
            } else {
                if (isEmpty(spur)) {
                    printf("Permutarea nu poate fi realizata.\n");
                    deleteStack(&out); // Eliberăm memoria alocată pentru stiva out
                    return NULL;
                } else {
                    printf("Permutarea nu poate fi realizata.\n");
                    deleteStack(&out); // Eliberăm memoria alocată pentru stiva out
                    deleteStack(&spur); // Eliberăm memoria alocată pentru stiva spur
                    return NULL;
                }
            }
        }
    }

    deleteStack(&in); // Eliberăm memoria alocată pentru stiva in
    deleteStack(&spur); // Eliberăm memoria alocată pentru stiva spur
    return out;
}

int main() {
    srand(time(NULL)); // Inițializăm generatorul de numere aleatoare

    Node* in = NULL;
    Node* out = NULL;

    // Inițializăm stiva in cu numere de la 1 la 4
    for (int i = 1; i <= 4; ++i) {
        push(&in, i);
    }

    printf("\nVagoanele initiale:");
    printStack(in);

    int n = 4; // Numărul de vagoane
    int* permutation = aleatoriu(n); // Generăm permutarea aleatoare
    printf("\nPermutarea aleatoare generata: ");
    for (int i = 0; i < n; i++)
        printf("%d ", permutation[i]);

    // Rearanjam stiva in conform permutarii aleatoare
    out = rearrangeStack(in, permutation, n);

    if (out != NULL) {
        printf("\nVagoanele in ordinea dorita:");
        printStack(out);
    }

    return 0;
}

