#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int hoare_partition(int vet[], int inicio, int fim) {
    int pivo = vet[inicio];
    int i = inicio - 1;
    int j = fim + 1;

    while (1) {
        do {
            i++;
        } while (vet[i] < pivo);

        do {
            j--;
        } while (vet[j] > pivo);

        if (i >= j) {
            return j;
        }

        swap(&vet[i], &vet[j]);
    }
}

void quickSort(int vet1[], int inicio, int fim)
{
 if(inicio < fim){
    int pivo = hoare_partition(vet1, inicio, fim);

    quickSort(vet1,inicio, pivo);
    quickSort(vet1, pivo + 1, fim);
 }

}

int main()
{
    int qtd;

    scanf("%d", &qtd);

    int vetor[qtd];

    for(int i = 0; i < qtd; i++){
        scanf("%d", &vetor[i]);
    }

    quickSort(vetor, 0, qtd-1);    

    for(int j = 0; j < qtd; j++){
        printf("%d\n", vetor[j]);
    }

    return 0;
}
