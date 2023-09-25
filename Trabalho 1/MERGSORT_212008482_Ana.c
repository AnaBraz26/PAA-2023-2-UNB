#include <stdio.h>
#include <stdlib.h>


void mergeSortR(int v[], float vaux[], unsigned inicio, unsigned fim)
{
  unsigned  meio, i, j, k;
  if(inicio < fim)
  {
    meio = (inicio + fim)/ 2;
    mergeSortR(v,vaux,inicio,meio);
    mergeSortR(v,vaux,meio+1,fim);

    //Intercalação
    i = inicio;
    k = inicio;
    j = meio + 1;

    while((i <= meio) && (j <= fim))
    {
      if(v[i] < v[j])
      {
        vaux[k] = v[i];
        i++;
      }
      else
      {
        vaux[k] = v[j];
        j++;
      }

      k++;
    }

    while(i <= meio)
    {
      vaux[k] = v[i];
      i++;
      k++;
    }

    while(j <= fim)
    {
      vaux[k] = v[j];
      j++;
      k++;
    }

    for(k = inicio; k <= fim; k++)
    {
      v[k] = vaux[k];
    }
  }
}

void mergeSort(int v[], unsigned tamanhoVetor)
{
  float *vaux;
  vaux = (float*) malloc(tamanhoVetor*sizeof(float));
  mergeSortR(v,vaux,0,tamanhoVetor-1);
  free(vaux);
}

int main(){

  char num;
  int vetor[100000];
  int tamanho = 0;

  while ((num = getchar()) != '\n') {
      if (num != ' ') {
          vetor[tamanho] *= 10;
          vetor[tamanho] += atoi(&num);
      }else{
        tamanho++;
        vetor[tamanho] = 0;
      }
  }

  mergeSort(vetor, tamanho+1);

  for (int i = 0; i < tamanho+1; i++) {

    printf("%d", vetor[i]);
    if (i < tamanho) {
        printf(" ");
    }
} 

   return 0;
}