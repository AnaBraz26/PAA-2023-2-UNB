// Ana Caroline Braz - 212008482

#include <stdio.h>
#include <stdlib.h>

void buscarBinaria(int vet[], int tamanhoVetor, int chave)
{
  int i, m, f;
  int pos = -1;
  
  i = 0;
  f = tamanhoVetor - 1;
  
  while(i <= f)
  {
    m = (i+f)/2;

    if(chave == vet[m])
    {
      pos = m;
      f = m - 1;
    }
    else if(chave > vet[m])
    {
      i = m + 1;
    }
    else
    {
      f = m - 1;
    }
  }
  printf("%d\n", pos);
 
}

int main()
{
    int n; // n de elementos do array
    int q; // numeros pesquisados
    int pesquisado; // numero a ser pesquisado
    

    scanf("%d %d", &n, &q);

    int vetor[n];
    
    for(int i = 0; i < n; i++){
      scanf("%d", &vetor[i]);
    }

    for(int j = 0; j < q; j++){
      scanf("%d", &pesquisado);

      buscarBinaria(vetor, n,pesquisado);   
    }

    return 0;
}