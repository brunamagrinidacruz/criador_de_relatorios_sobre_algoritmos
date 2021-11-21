#include "ordenacoes.h"

char* nome_ordenacao_por_codigo(int ordenacao) {
	switch(ordenacao) {
		case ORDENACAO1:
			return ORDENACAO1_NOME;
		case ORDENACAO2:
			return ORDENACAO2_NOME;
		case ORDENACAO3:
			return ORDENACAO3_NOME;
		case ORDENACAO4:
			return ORDENACAO4_NOME;
		case ORDENACAO5:
			return ORDENACAO5_NOME;
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

void quick_sort(int vetor[], int inicio, int fim){
	//primeira etapa: verificar caso base (vetores unitários ou nulos)
	if (fim <= inicio)
		return;

	//segunda etapa: partição em relação ao pivô
	int pivo = inicio;
	int i = inicio+1; //percorre o vetor aumentando seu valor
	int j = fim;//percorre o vetor diminuindo seu valor

	//encontrando os elementos que contradizem as regras dos elementos da lista:
	//- elementos à esquerda do pivô devem ser <= a ele ou chegar ao final do vetor
	//- elementos à direita do pivô devem ser > que ele ou chegar ao início do vetor
	int aux;
	while (i <= j){//quantas vezes forem necessárias, ou seja, até que as duas listas cruzam
		while (i <= fim && vetor[i] <= vetor[pivo]) i++; 
		while (vetor[j] > vetor[pivo]) j--; //quando j==pivo, a comparação é falsa (encontrou o inicio do vetor)

		if (j > i){
			aux = vetor[i];
			vetor[i] = vetor[j];
			vetor[j] = aux;
		}
	}

	pivo = j;
	aux = vetor[pivo]; //reposicionado o pivô
	vetor[pivo] = vetor[inicio];
	vetor[inicio] = aux;

	//terceira etapa: recursão
	quick_sort(vetor, inicio, pivo-1); //j é a nova posição do pivô
	quick_sort(vetor, pivo+1, fim);	
}

void heap_max(int vetor[], int pai, int n){
	//verificar os filhos da "posição", se ferir a condição trocar o maior filho com o pai
	int filho = pai*2;//filho da esquerda
	//filho da direita = filho+1; pai*2+1

	//garantir que o nó-filho da esquerda existe
	if (filho > n) return;

	//verificar a condição de heap em relação aos filhos
	//1 - o filho da esquerda é maior que o pai
	//2 - existe o filho da direita
	//3 - o filho da direita é maior que o pai
	//printf("Pai: %i. Esquerda %i.\n", vetor[pai], vetor[filho]);
	if (vetor[filho] > vetor[pai] || (filho+1 <= n && vetor[filho+1] > vetor[pai])){
		//1 - existe o filho da direita
		//2 - o filho da direita é maior que o filho da esquerda
		if (filho+1 <= n && vetor[filho+1] > vetor[filho])
			filho = filho+1;

		//troca o pai com o maior filho
		//***se o maior filho é o da esquerda, ele já se encontra em "filho"
		int aux = vetor[pai];
		vetor[pai] = vetor[filho];
		vetor[filho] = aux;

		//atualizar possíveis "netos" restantes
		heap_max(vetor, filho, n);
	}
}

void heap_sort(int vetor[], int n) {
	//Construção Heap
	int ultimoPai = (int)n/2.0;
	int i;
	for (i = ultimoPai; i>=1; i--) //i=1 é o nó raiz
		heap_max(vetor, i, n);
	//--- Aqui temos o vetor representado em uma estrutura de MaxHeap

	//processo ordenação
	while (n >= 2){
		//maior elemento está sempre na raiz vetor[1]
		int maior = vetor[1];
		vetor[1] = vetor[n];
		vetor[n] = maior;

		n--; // reduzimos o tamanho do Heap
		heap_max(vetor, 1, n);//verificamos a consistência do Heap para o nó-raiz!
	}
}
