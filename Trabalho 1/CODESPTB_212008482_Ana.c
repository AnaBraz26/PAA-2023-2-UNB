#include <stdio.h>
#include <stdlib.h>

void insertion_sort(int n, int v[])
{
    int trocas = 0;
	
    int i, chave, j;
    for(i = 1; i < n; i++)
    {
        chave = v[i];
        j = i - 1;

        while(j >= 0 && v[j] > chave)
        {
            v[j+1] = v[j];
            j--;
            trocas++;
        }
        v[j+1] = chave;
    }
   printf("%d\n", trocas);
}

int main(){

    int testes; 
    int casos;
    int vetor[100000];

    scanf("%d", &testes);
       
    for(int i = 0; i < testes; i++){
        scanf("%d", &casos);   
        for(int j = 0; j < casos; j++){
            scanf("%d", &vetor[j]);
        }
        
        insertion_sort(casos, vetor);      
    }
    return 0;
}