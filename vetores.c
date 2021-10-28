#include "vetores.h"

char* nome_tipo_de_vetor_por_codigo(int tipo_de_vetor) {
	switch(tipo_de_vetor) {
		case TIPO_DE_VETOR1:
			return TIPO_DE_VETOR1_NOME;
		case TIPO_DE_VETOR2:
			return TIPO_DE_VETOR2_NOME;
		case TIPO_DE_VETOR3:
			return TIPO_DE_VETOR3_NOME;
		default:
			return "Tipo de vetor inválido";
	}
}

int* gerar_vetor_aleatorio(int quantidade_de_elementos, int valor_minimo, int valor_maximo) {
      int* vetor_aleatorio = malloc(quantidade_de_elementos * sizeof(int));

      srand(SEED);

	for (int i = 0; i < quantidade_de_elementos; i++){
		vetor_aleatorio[i] = rand() % (valor_maximo-valor_minimo+1) + valor_minimo;
		// printf("%d ", vetor_aleatorio[i]);
	}

      return vetor_aleatorio;
}

int* gerar_vetor_ordenado(int quantidade_de_elementos) {
      int* vetor_ordenado = malloc(quantidade_de_elementos * sizeof(int));

      for(int i = 0; i < quantidade_de_elementos; i++) {
            vetor_ordenado[i] = i+1;
            // printf("%d ", vetor_ordenado[i]);
      }

      return vetor_ordenado;
}

int* gerar_vetor_ordenado_de_forma_invertida(int quantidade_de_elementos) {
      int* vetor_ordenado_de_forma_invertida = malloc(quantidade_de_elementos * sizeof(int));

      for(int i = 0; i < quantidade_de_elementos; i++) {
            vetor_ordenado_de_forma_invertida[i] = quantidade_de_elementos-i;
            // printf("%d ", vetor_ordenado_de_forma_invertida[i]);
      }

      return vetor_ordenado_de_forma_invertida;
}

void copiar_vetor(int vetor_original[], int vetor_copia[], int quantidade_de_elementos) {
      for(int i = 0; i < quantidade_de_elementos; i++) {
            vetor_copia[i] = vetor_original[i];
      }
}

void imprimir_vetor(int vetor[], int quantidade_de_elementos) {
      for(int i = 0; i < quantidade_de_elementos; i++) {
            printf("%d ", vetor[i]);
      }
      printf("\n");
}