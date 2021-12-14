#ifndef ORDENACOES_H
#define ORDENACOES_H

#include <stdlib.h>
#include <stdio.h>

/*!< Define o nome das ordenações para impressão e mais importante: nome da pasta em ./resultados que os arquivos correspondentes serão salvos */
#define ORDENACAO1 1
#define ORDENACAO1_NOME "bubble_sort"
#define ORDENACAO2 2
#define ORDENACAO2_NOME "insertion_sort"
#define ORDENACAO3 3
#define ORDENACAO3_NOME "merge_sort"
#define ORDENACAO4 4
#define ORDENACAO4_NOME "quick_sort"
#define ORDENACAO5 5
#define ORDENACAO5_NOME "heap_sort"
#define ORDENACAO6 6
#define ORDENACAO6_NOME "counting_sort"
#define ORDENACAO7 7
#define ORDENACAO7_NOME "bucket_sort"

char* nome_ordenacao_por_codigo(int ordenacao);

void bubble_sort(int vetor[], int n);
void insertion_sort(int vetor[], int n);
void merge_sort(int vetor[], int inicio, int fim);
void quick_sort(int vetor[], int inicio, int fim);
void heap_sort(int vetor[], int n);
void counting_sort(int vetor[], int n);
void bucket_sort(int vetor[], int n);

#endif

