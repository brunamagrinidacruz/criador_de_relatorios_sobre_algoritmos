#include "ordenacoes.h"

char* nome_ordenacao_por_codigo(int ordenacao) {
	switch(ordenacao) {
		case ORDENACAO1:
			return ORDENACAO1_NOME;
		case ORDENACAO2:
			return ORDENACAO2_NOME;
		case ORDENACAO3:
			return ORDENACAO3_NOME;
		default:
			return "Ordenação inválida";
	}
}

void bubble_sort(int vetor[], int n) { 
    int aux, troca; 
    for(int i=n-1; i > 0; i--) {
        troca = 0;
        for(int j = 0; j < i; j++) {
            if(vetor[j] > vetor[j+1]) {
                aux = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = aux;
                troca = 1;
            }
        }
        if(troca == 0) break;
    }
} 

void insertion_sort(int vetor[], int n) { 
    int chave, j; 
    for(int i=1; i < n; i++) {
        chave = vetor[i];
        j=i-1;
        while((j >= 0) && (vetor[j] > chave)) {
            vetor[j+1] = vetor[j];
            j--;
        }
        vetor[j+1] = chave;
    }
}

void intercala(int vetor[], int inicio, int centro, int fim) {
	int* vetor_auxiliar = (int*)malloc(sizeof(int) * (fim-inicio)+1);
	int i = inicio;
	int j = centro+1;
	int k = 0; 

	while(i <= centro && j <= fim) {
		if (vetor[i] <= vetor[j]) {
			vetor_auxiliar[k] = vetor[i];
			i++;
		}
		else {
			vetor_auxiliar[k] = vetor[j];
			j++; 
		}
		k++;
	}
	while(i <= centro) {
		vetor_auxiliar[k] = vetor[i];
		i++;
		k++;
	}
	while(j <= fim) {
		vetor_auxiliar[k] = vetor[j];
		j++;
		k++;
	}

	for(i = inicio, k = 0; i <= fim; i++, k++)
		vetor[i] = vetor_auxiliar[k];
	free(vetor_auxiliar);
}

void merge_sort(int vetor[], int inicio, int fim) {
	if (fim <= inicio) return;
	int centro = (int)((inicio+fim)/2.0);
	merge_sort(vetor, inicio, centro);
	merge_sort(vetor, centro+1, fim);
	intercala(vetor, inicio, centro, fim);
}