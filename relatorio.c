#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include "ordenacoes.h" /*!< Biblioteca que contém os algoritmos de ordenação */
#include "vetores.h" /*!< Biblioteca responsável por manipulação de vetores */
#include "arquivos.h" /*!< Biblioteca responsável por geração de arquivos .dat (para o gnuplot) e .csv (para o relatório) */

#define DEBUG 0 /*!< Define se printf de debug serão impressos */

#define VALOR_MINIMO_ALEATORIO 1 /*!< Valor minimo para os elementos utilizado na geração do vetor aleatório */
#define VALOR_MAXIMO_ALEATORIO 10 /*!< Valor máximo para os elementos utilizado na geração do vetor aleatório */

#define TAMANHO_DE_VETOR_MAXIMO 10000 //100 /*!< O programa irá executar ordenação para n iniciando em 25 com acréscimo de 5 até TAMANHO_DE_VETOR_MAXIMO (ex. 25, 30, 35, ..., TAMANHO_DE_VETOR_MAXIMO) */
#define QUANTIDADE_DE_TESTES 10 /*!< Quantidade de testes a serem realizados por execução de n (o tempo final será a média das QUANTIDADE_DE_TESTES execuções) */

/*!< 
      Dado o ID da ordenação e a iteração atual (teste).
      Ordena vetor_ordenacao de tamanho quantidade_de_elementos com base na ordenação.
      Além disso, armazena em tempo_de_execucao o tempo que durou a execução para a iteração, ou seja, tempo_de_execucao[teste].
      Também adiciona o tempo_de_execução[teste] em soma.
*/
void ordenar(int ordenacao, int teste, int vetor_ordenacao[], int quantidade_de_elementos, long double tempo_de_execucao[], long double *soma) {
      if(DEBUG) printf("         Vetor %s a ser ordenado: \n", nome_ordenacao_por_codigo(ordenacao));
      if(DEBUG) imprimir_vetor(vetor_ordenacao, quantidade_de_elementos);

      clock_t inicio, fim;
      switch(ordenacao) {
            case ORDENACAO1:
                  inicio = clock();
                  bubble_sort(vetor_ordenacao, quantidade_de_elementos);
                  fim = clock();
            break;
            case ORDENACAO2:
                  inicio = clock();
                  insertion_sort(vetor_ordenacao, quantidade_de_elementos);
                  fim = clock();
            break;
            case ORDENACAO3:
                  inicio = clock();
                  merge_sort(vetor_ordenacao, 0, quantidade_de_elementos-1);
                  fim = clock();
            break;
            case ORDENACAO4:
                  inicio = clock();
                  quick_sort(vetor_ordenacao, 0, quantidade_de_elementos-1);
                  fim = clock();
            break;
            case ORDENACAO5: 
                  inicio = clock();
                  heap_sort(vetor_ordenacao, quantidade_de_elementos-1);
                  fim = clock();
            break;
            case ORDENACAO6: 
                  inicio = clock();
                  counting_sort(vetor_ordenacao, quantidade_de_elementos);
                  fim = clock();
            break;
      }
      
      if(DEBUG) printf("         Vetor %s ordenado: \n", nome_ordenacao_por_codigo(ordenacao));
      if(DEBUG) imprimir_vetor(vetor_ordenacao, quantidade_de_elementos);

      tempo_de_execucao[teste] = (fim-inicio)/(double)CLOCKS_PER_SEC;
      (*soma) += tempo_de_execucao[teste];

      if(DEBUG) printf("\n         Tempo de execução: %Lf\n", tempo_de_execucao[teste]);
      if(DEBUG) printf("         Soma parcial: %Lf\n",(*soma));
}

void executar_testes(int tipo_de_vetor) {
      /*!< Criando arquivos para análise dos resulados */
      // FILE* arquivo_dat_ordenacao1 = cria_arquivo_dat(ORDENACAO1, tipo_de_vetor);
      // FILE* arquivo_dat_ordenacao2 = cria_arquivo_dat(ORDENACAO2, tipo_de_vetor);
      // FILE* arquivo_dat_ordenacao3 = cria_arquivo_dat(ORDENACAO3, tipo_de_vetor);
      // FILE* arquivo_dat_ordenacao4 = cria_arquivo_dat(ORDENACAO4, tipo_de_vetor);
      // FILE* arquivo_dat_ordenacao5 = cria_arquivo_dat(ORDENACAO5, tipo_de_vetor);
      FILE* arquivo_dat_ordenacao6 = cria_arquivo_dat(ORDENACAO6, tipo_de_vetor);

      // FILE* arquivo_csv_ordenacao1 = cria_arquivo_csv(ORDENACAO1, tipo_de_vetor);
      // FILE* arquivo_csv_ordenacao2 = cria_arquivo_csv(ORDENACAO2, tipo_de_vetor);
      // FILE* arquivo_csv_ordenacao3 = cria_arquivo_csv(ORDENACAO3, tipo_de_vetor);
      // FILE* arquivo_csv_ordenacao4 = cria_arquivo_csv(ORDENACAO4, tipo_de_vetor);
      // FILE* arquivo_csv_ordenacao5 = cria_arquivo_csv(ORDENACAO5, tipo_de_vetor);
      FILE* arquivo_csv_ordenacao6 = cria_arquivo_csv(ORDENACAO6, tipo_de_vetor);
     
      /*!< Variação dos valores de n (quantidade_de_elementos do vetor) */
      for(int quantidade_de_elementos = 25; quantidade_de_elementos <= TAMANHO_DE_VETOR_MAXIMO; quantidade_de_elementos+=5) {
            printf("-------------------------n=%d-------------------------------\n", quantidade_de_elementos);

            int *vetor_original; 
            // int *vetor_ordenacao1 = malloc(quantidade_de_elementos * sizeof(int));
            // int *vetor_ordenacao2 = malloc(quantidade_de_elementos * sizeof(int));
            // int *vetor_ordenacao3 = malloc(quantidade_de_elementos * sizeof(int));
            // int *vetor_ordenacao4 = malloc(quantidade_de_elementos * sizeof(int));
            // int *vetor_ordenacao5 = malloc((quantidade_de_elementos+1) * sizeof(int));
            int *vetor_ordenacao6 = malloc(quantidade_de_elementos * sizeof(int));

            /*!< Definindo os vetores de tamanho n com base no tipo */
            printf("Quantidade de elementos: %d\n", quantidade_de_elementos);
            printf("Tipo de vetor: ");
            switch(tipo_de_vetor) {
                  case 1:
                        printf("aleatório\n"); 
                        vetor_original = gerar_vetor_aleatorio(quantidade_de_elementos, VALOR_MINIMO_ALEATORIO, VALOR_MAXIMO_ALEATORIO);
                        break;
                  case 2:
                        printf("ordenado\n");
                        vetor_original = gerar_vetor_ordenado(quantidade_de_elementos);
                        break;
                  case 3:
                        printf("ordenado invertido\n");
                        vetor_original = gerar_vetor_ordenado_de_forma_invertida(quantidade_de_elementos);
                        break;
                  default:
                        printf("inválido\n");
                        return;
            }

            printf("Quantidade de testes por execução de n: %d\n", QUANTIDADE_DE_TESTES);
            if(DEBUG) printf("Vetor base: \n");
            if(DEBUG) imprimir_vetor(vetor_original, quantidade_de_elementos);

            // long double *tempo_de_execucao_ordenacao1 = malloc(QUANTIDADE_DE_TESTES * sizeof(long double));
            // long double *tempo_de_execucao_ordenacao2 = malloc(QUANTIDADE_DE_TESTES * sizeof(long double));
            // long double *tempo_de_execucao_ordenacao3 = malloc(QUANTIDADE_DE_TESTES * sizeof(long double));
            // long double *tempo_de_execucao_ordenacao4 = malloc(QUANTIDADE_DE_TESTES * sizeof(long double));
            // long double *tempo_de_execucao_ordenacao5 = malloc(QUANTIDADE_DE_TESTES * sizeof(long double));
            long double *tempo_de_execucao_ordenacao6 = malloc(QUANTIDADE_DE_TESTES * sizeof(long double));
            
            // long double soma_ordenacao1 = 0;
            // long double soma_ordenacao2 = 0;
            // long double soma_ordenacao3 = 0;
            // long double soma_ordenacao4 = 0;
            // long double soma_ordenacao5 = 0;
            long double soma_ordenacao6 = 0;

            /*!< Realizando QUANTIDADE_DE_TESTES para cada n */
            for(int teste = 0; teste < QUANTIDADE_DE_TESTES; teste++) {
                  // copiar_vetor(vetor_original, vetor_ordenacao1, quantidade_de_elementos);
                  // copiar_vetor(vetor_original, vetor_ordenacao2, quantidade_de_elementos);
                  // copiar_vetor(vetor_original, vetor_ordenacao3, quantidade_de_elementos);
                  // copiar_vetor(vetor_original, vetor_ordenacao4, quantidade_de_elementos);
                  // copiar_vetor(vetor_original, vetor_ordenacao5+1, quantidade_de_elementos);
                  copiar_vetor(vetor_original, vetor_ordenacao6, quantidade_de_elementos);

                  if(DEBUG) printf("\n---------Teste %d\n\n", teste);

                  // ordenar(ORDENACAO1, teste, vetor_ordenacao1, quantidade_de_elementos, tempo_de_execucao_ordenacao1, &soma_ordenacao1);
                  // if(DEBUG) printf("\n-----\n");

                  // ordenar(ORDENACAO2, teste, vetor_ordenacao2, quantidade_de_elementos, tempo_de_execucao_ordenacao2, &soma_ordenacao2);
                  // if(DEBUG) printf("\n-----\n");

                  // ordenar(ORDENACAO3, teste, vetor_ordenacao3, quantidade_de_elementos, tempo_de_execucao_ordenacao3, &soma_ordenacao3);
                  // if(DEBUG) printf("\n-----\n");

                  // ordenar(ORDENACAO4, teste, vetor_ordenacao4, quantidade_de_elementos, tempo_de_execucao_ordenacao4, &soma_ordenacao4);
                  // if(DEBUG) printf("\n-----\n");

                  // ordenar(ORDENACAO5, teste, vetor_ordenacao5, quantidade_de_elementos, tempo_de_execucao_ordenacao5, &soma_ordenacao5);
                  // if(DEBUG) printf("\n-----\n");

                  ordenar(ORDENACAO6, teste, vetor_ordenacao6, quantidade_de_elementos, tempo_de_execucao_ordenacao6, &soma_ordenacao6);
                  // if(DEBUG) printf("\n-----\n");
            }
            if(DEBUG) printf("\n---------\n\n");

            /*!< Calculando métricas */
            
            // if(DEBUG) printf("Soma - %s: %Lf\n", nome_ordenacao_por_codigo(ORDENACAO1), soma_ordenacao1);
            // if(DEBUG) printf("Soma - %s: %Lf\n", nome_ordenacao_por_codigo(ORDENACAO2), soma_ordenacao2);
            // if(DEBUG) printf("Soma - %s: %Lf\n", nome_ordenacao_por_codigo(ORDENACAO3), soma_ordenacao3);
            // if(DEBUG) printf("Soma - %s: %Lf\n", nome_ordenacao_por_codigo(ORDENACAO4), soma_ordenacao4);
            // if(DEBUG) printf("Soma - %s: %Lf\n", nome_ordenacao_por_codigo(ORDENACAO5), soma_ordenacao5);
            if(DEBUG) printf("Soma - %s: %Lf\n", nome_ordenacao_por_codigo(ORDENACAO6), soma_ordenacao6);
            if(DEBUG) printf("\n");

            /*!< Média */
            // long double media_ordenacao1 = 0;
            // long double media_ordenacao2 = 0;
            // long double media_ordenacao3 = 0;
            // long double media_ordenacao4 = 0;
            // long double media_ordenacao5 = 0;
            long double media_ordenacao6 = 0;

            // media_ordenacao1 = soma_ordenacao1/QUANTIDADE_DE_TESTES;
            // media_ordenacao2 = soma_ordenacao2/QUANTIDADE_DE_TESTES;
            // media_ordenacao3 = soma_ordenacao3/QUANTIDADE_DE_TESTES;
            // media_ordenacao4 = soma_ordenacao4/QUANTIDADE_DE_TESTES;
            // media_ordenacao5 = soma_ordenacao5/QUANTIDADE_DE_TESTES;
            media_ordenacao6 = soma_ordenacao6/QUANTIDADE_DE_TESTES;

            // if(DEBUG) printf("Média - %s: %Lf\n", nome_ordenacao_por_codigo(ORDENACAO1), media_ordenacao1);
            // if(DEBUG) printf("Média - %s: %Lf\n", nome_ordenacao_por_codigo(ORDENACAO2), media_ordenacao2);
            // if(DEBUG) printf("Média - %s: %Lf\n", nome_ordenacao_por_codigo(ORDENACAO3), media_ordenacao3);
            // if(DEBUG) printf("Média - %s: %Lf\n", nome_ordenacao_por_codigo(ORDENACAO4), media_ordenacao4);
            // if(DEBUG) printf("Média - %s: %Lf\n", nome_ordenacao_por_codigo(ORDENACAO5), media_ordenacao5);
            if(DEBUG) printf("Média - %s: %Lf\n", nome_ordenacao_por_codigo(ORDENACAO6), media_ordenacao6);
            if(DEBUG) printf("\n");

            /*!< Desvio Padrão */
            // long double desvio_padrao_ordenacao1 = 0;
            // long double desvio_padrao_ordenacao2 = 0;
            // long double desvio_padrao_ordenacao3 = 0;
            // long double desvio_padrao_ordenacao4 = 0;
            // long double desvio_padrao_ordenacao5 = 0;
            long double desvio_padrao_ordenacao6 = 0;

            for(int teste = 0; teste < QUANTIDADE_DE_TESTES; teste++) {
                  // desvio_padrao_ordenacao1 += pow((tempo_de_execucao_ordenacao1[teste]-media_ordenacao1), 2);
                  // desvio_padrao_ordenacao2 += pow((tempo_de_execucao_ordenacao2[teste]-media_ordenacao2), 2);
                  // desvio_padrao_ordenacao3 += pow((tempo_de_execucao_ordenacao3[teste]-media_ordenacao3), 2);
                  // desvio_padrao_ordenacao4 += pow((tempo_de_execucao_ordenacao4[teste]-media_ordenacao4), 2);
                  // desvio_padrao_ordenacao5 += pow((tempo_de_execucao_ordenacao5[teste]-media_ordenacao5), 2);
                  desvio_padrao_ordenacao6 += pow((tempo_de_execucao_ordenacao6[teste]-media_ordenacao6), 2);
            }

            // desvio_padrao_ordenacao1 = sqrt(desvio_padrao_ordenacao1/QUANTIDADE_DE_TESTES);
            // desvio_padrao_ordenacao2 = sqrt(desvio_padrao_ordenacao2/QUANTIDADE_DE_TESTES);
            // desvio_padrao_ordenacao3 = sqrt(desvio_padrao_ordenacao3/QUANTIDADE_DE_TESTES);
            // desvio_padrao_ordenacao4 = sqrt(desvio_padrao_ordenacao4/QUANTIDADE_DE_TESTES);
            // desvio_padrao_ordenacao5 = sqrt(desvio_padrao_ordenacao5/QUANTIDADE_DE_TESTES);
            desvio_padrao_ordenacao6 = sqrt(desvio_padrao_ordenacao6/QUANTIDADE_DE_TESTES);

            // if(DEBUG) printf("Desvio Padrão - %s: %Lf\n", nome_ordenacao_por_codigo(ORDENACAO1), desvio_padrao_ordenacao1);
            // if(DEBUG) printf("Desvio Padrão - %s: %Lf\n", nome_ordenacao_por_codigo(ORDENACAO2), desvio_padrao_ordenacao2);
            // if(DEBUG) printf("Desvio Padrão - %s: %Lf\n", nome_ordenacao_por_codigo(ORDENACAO3), desvio_padrao_ordenacao3);
            // if(DEBUG) printf("Desvio Padrão - %s: %Lf\n", nome_ordenacao_por_codigo(ORDENACAO4), desvio_padrao_ordenacao4);
            // if(DEBUG) printf("Desvio Padrão - %s: %Lf\n", nome_ordenacao_por_codigo(ORDENACAO5), desvio_padrao_ordenacao5);
            if(DEBUG) printf("Desvio Padrão - %s: %Lf\n", nome_ordenacao_por_codigo(ORDENACAO6), desvio_padrao_ordenacao6);

            /*!< Escrevendo arquivo para o gnuplot (.dat) */
            /*!< 
                  Hierarquia:
                        Método de ordenação
                              Tipo de vetor 
                  
                  É armazenado (n, tempo)
            */
            // escrever_dat(arquivo_dat_ordenacao1, quantidade_de_elementos, media_ordenacao1);
            // escrever_dat(arquivo_dat_ordenacao2, quantidade_de_elementos, media_ordenacao2);
            // escrever_dat(arquivo_dat_ordenacao3, quantidade_de_elementos, media_ordenacao3);
            // escrever_dat(arquivo_dat_ordenacao4, quantidade_de_elementos, media_ordenacao4);
            // escrever_dat(arquivo_dat_ordenacao5, quantidade_de_elementos, media_ordenacao5);
            escrever_dat(arquivo_dat_ordenacao6, quantidade_de_elementos, media_ordenacao6);

            /*!< Escrevendo arquivo de tabela de testes (.csv) para o relatório */
            /*!< 
                  Hierarquia:
                        Método de ordenação
                              Tipo de vetor 
                  
                  É armazenado:             
                                    1  2  3  4  5  6  7  8  9  10 | Média ± Desvio Padrão
                        25          
                        10                 tempo para n no teste t
                        100
                        10000
            */
            switch(quantidade_de_elementos) {
                  case 25:
                  case 100:
                  case 1000:
                  case 10000:
                  case 100000:
                        // escrever_csv(arquivo_csv_ordenacao1, quantidade_de_elementos, 
                        //                   tempo_de_execucao_ordenacao1, QUANTIDADE_DE_TESTES, 
                        //                   media_ordenacao1, desvio_padrao_ordenacao1);
                        // escrever_csv(arquivo_csv_ordenacao2, quantidade_de_elementos, 
                        //                   tempo_de_execucao_ordenacao2, QUANTIDADE_DE_TESTES, 
                        //                   media_ordenacao2, desvio_padrao_ordenacao2);
                        // escrever_csv(arquivo_csv_ordenacao3, quantidade_de_elementos, 
                        //                   tempo_de_execucao_ordenacao3, QUANTIDADE_DE_TESTES, 
                        //                   media_ordenacao3, desvio_padrao_ordenacao3);
                        // escrever_csv(arquivo_csv_ordenacao4, quantidade_de_elementos, 
                                          // tempo_de_execucao_ordenacao4, QUANTIDADE_DE_TESTES, 
                                          // media_ordenacao4, desvio_padrao_ordenacao4);
                        // escrever_csv(arquivo_csv_ordenacao5, quantidade_de_elementos, 
                                          // tempo_de_execucao_ordenacao5, QUANTIDADE_DE_TESTES, 
                                          // media_ordenacao5, desvio_padrao_ordenacao5);
                        escrever_csv(arquivo_csv_ordenacao6, quantidade_de_elementos, 
                                          tempo_de_execucao_ordenacao6, QUANTIDADE_DE_TESTES, 
                                          media_ordenacao6, desvio_padrao_ordenacao6);
                  break;
            }

            // free(tempo_de_execucao_ordenacao1);
            // free(tempo_de_execucao_ordenacao2);
            // free(tempo_de_execucao_ordenacao3);
            // free(tempo_de_execucao_ordenacao4);
            // free(tempo_de_execucao_ordenacao5);
            free(tempo_de_execucao_ordenacao6);

            free(vetor_original);
            // free(vetor_ordenacao1);
            // free(vetor_ordenacao2);
            // free(vetor_ordenacao3);
            // free(vetor_ordenacao4);
            // free(vetor_ordenacao5);
            free(vetor_ordenacao6);

            printf("\n");
      }

      // fclose(arquivo_dat_ordenacao1);
      // fclose(arquivo_dat_ordenacao2);
      // fclose(arquivo_dat_ordenacao3);
      // fclose(arquivo_dat_ordenacao4);
      // fclose(arquivo_dat_ordenacao5);
      fclose(arquivo_dat_ordenacao6);

      // fclose(arquivo_csv_ordenacao1);
      // fclose(arquivo_csv_ordenacao2);
      // fclose(arquivo_csv_ordenacao3);
      // fclose(arquivo_csv_ordenacao4);
      // fclose(arquivo_csv_ordenacao5);
      fclose(arquivo_csv_ordenacao6);
}

/*
*  Recebe como argumento opcional instruções para execução do programa
*     argv[1]: tipo de vetor criado (1 - aleatório, 2 - ordenado, 3 - ordenado de forma invertida)
*/
int main(int argc, char *argv[]) {
      if(argc == 2) { /*!< Usuário informou o tipo especifico de vetor */
            int tipo_de_vetor = atoi(argv[1]);
            printf("> Executando para tipo de vetor específico: %d\n\n", tipo_de_vetor);
            executar_testes(tipo_de_vetor);
      } else { /*!< Usuário não informou o tipo especifico de vetor, os 3 casos serão executados */
            for(int tipo_de_vetor = 1; tipo_de_vetor <= 3; tipo_de_vetor++) {
                  printf("> Tipo de vetor: %d \n\n", tipo_de_vetor);
                  executar_testes(tipo_de_vetor);
            }
      }
      return 0;
}