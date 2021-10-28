#ifndef VETORES_H
#define VETORES_H

#include <stdio.h>
#include <stdlib.h>

#define SEED 42

/*!< Define os tipos de vetores e os nomes, mas mais importante: parte do nome do arquivo que será salvo em ./resultados/[metodo de ordenação] */
#define TIPO_DE_VETOR1 1
#define TIPO_DE_VETOR1_NOME "aleatorio"
#define TIPO_DE_VETOR2 2
#define TIPO_DE_VETOR2_NOME "ordenado"
#define TIPO_DE_VETOR3 3
#define TIPO_DE_VETOR3_NOME "ordenado_inverso"

char* nome_tipo_de_vetor_por_codigo(int tipo_de_vetor);

/*!< Retorna um vetor de tamanho quantidade_de_elementos que contém valores inteiros aleatórios no intervalo [valor_minimo, valor_maximo] */
int* gerar_vetor_aleatorio(int quantidade_de_elementos, int valor_minimo, int valor_maximo);

/*!< Retorna um vetor de tamanho quantidade_de_elementos que contém inteiros ordenados no intervalo [1, quantidade_de_elementos] */
int* gerar_vetor_ordenado(int quantidade_de_elementos);

/*!< Retorna um vetor de tamanho quantidade_de_elementos que contém inteiros ordenados de forma invertida no intervalo [quantidade_de_elementos, 1] */
int* gerar_vetor_ordenado_de_forma_invertida(int quantidade_de_elementos);

void copiar_vetor(int vetor_original[], int vetor_copia[], int quantidade_de_elementos);
void imprimir_vetor(int vetor[], int quantidade_de_elementos);

#endif