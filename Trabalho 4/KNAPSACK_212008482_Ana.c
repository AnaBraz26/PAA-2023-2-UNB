#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int knapsack_max_value(int S, int N, int tamanho[], int valores[]) {
    int matriz[N + 1][S + 1];

    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= S; j++) {
            if (i == 0 || j == 0) {
                matriz[i][j] = 0;
            } else if (tamanho[i - 1] <= j) {
                matriz[i][j] = max(matriz[i - 1][j], valores[i - 1] + matriz[i - 1][j - tamanho[i - 1]]);
            } else {
                matriz[i][j] = matriz[i - 1][j];
            }
        }
    }

    return matriz[N][S];
}

int main() {
    int S, N;
    scanf("%d %d", &S, &N);

    int tamanho[N];
    int valores[N];

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &tamanho[i], &valores[i]);
    }

    printf("%d\n", knapsack_max_value(S, N, tamanho, valores));

    return 0;
}
