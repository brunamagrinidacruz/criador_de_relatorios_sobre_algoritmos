#ifndef ORDENACOES_H
#define ORDENACOES_H

#include <stdlib.h>

/*!< Define o nome das ordenações para impressão e mais importante: nome da pasta em ./resultados que os arquivos correspondentes serão salvos */
#define ORDENACAO1 1
#define ORDENACAO1_NOME "bubble_sort"
#define ORDENACAO2 2
#define ORDENACAO2_NOME "insertion_sort"
#define ORDENACAO3 3
#define ORDENACAO3_NOME "merge_sort"

void bubble_sort(int vetor[], int n);
void insertion_sort(int vetor[], int n);
void merge_sort(int vetor[], int inicio, int fim);
char* nome_ordenacao_por_codigo(int ordenacao);

#endif

