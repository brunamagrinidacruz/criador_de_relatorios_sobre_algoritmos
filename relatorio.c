/*!< Compilar e executar 
make
./relatorio > .out
#Ou 
./relatorio tipo_de_vetor > .out #com tipo_de_vetor sendo 1 - aleatório, 2 - ordenado e 3 - ordenado invertido
*/

/*!<
Observação: 
É necessário que exista uma pasta ./resultados e dentro dela uma pasta correspondente para cada método de ordenação
Lá serão salvos os resultados calculados
O nome da pasta para cada método de ordenação deve ser igual definido no arquivo ordenacao.h
*/

/*!< gnuplot (https://www.cs.hmc.edu/~vrable/gnuplot/using-gnuplot.html) */

/*
cd resultados/
cd [metodo de ordenação]

gnuplot
set grid
set title "Metodos de Ordenacao"
set xlabel "Quantidade de elementos (n)"
set ylabel "Tempo de execucao em segundos (t)"
set yrange[0:0.5]
*/

//plot "bubble_sort-aleatorio.dat" title "Aleatorio"
//plot "bubble_sort-ordenado.dat" title "Ordenado"
//plot "bubble_sort-ordenado_inverso.dat" title "Ordenado Invertido"
/*
set title "Bubble Sort"
plot "bubble_sort-aleatorio.dat" title "Aleatorio", "bubble_sort-ordenado.dat" title "Ordenado", "bubble_sort-ordenado_inverso.dat" title "Ordenado Invertido"
*/

//plot "insertion_sort-aleatorio.dat" title "Aleatorio"
//plot "insertion_sort-ordenado.dat" title "Ordenado"
//plot "insertion_sort-ordenado_inverso.dat" title "Ordenado Invertido"
/*
set title "Insertion Sort"
plot "insertion_sort-aleatorio.dat" title "Aleatorio", "insertion_sort-ordenado.dat" title "Ordenado", "insertion_sort-ordenado_inverso.dat" title "Ordenado Invertido"
*/

//plot "merge_sort-aleatorio.dat" title title "Aleatorio"
//plot "merge_sort-ordenado.dat" title title "Ordenado"
//plot "merge_sort-ordenado_inverso.dat" title "Ordenado Invertido"
/*
set title "Merge Sort"
plot "merge_sort-aleatorio.dat" title "Aleatorio", "merge_sort-ordenado.dat" title "Ordenado", "merge_sort-ordenado_inverso.dat" title "Ordenado Invertido"
*/

//plot "bubble.dat" title "Bubble Sort", "insertion.dat" title "Insertion Sort", "merge.dat" title "Merge Sort"
//plot "bubble.dat" title "Bubble Sort" smooth bezier, "insertion.dat" title "Insertion Sort" smooth bezier, "merge.dat" title "Merge Sort" smooth bezier

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#include "ordenacoes.h" /*!< Biblioteca que contém os algoritmos de ordenação */
#include "vetores.h" /*!< Biblioteca responsável por manipulação de vetores */
#include "arquivos.h" /*!< Biblioteca responsável por geração de arquivos .dat (para o gnuplot) e .csv (para o relatório) */

#define DEBUG 1 /*!< Define se printf de debug serão impressos */

#define VALOR_MINIMO_ALEATORIO 1 /*!< Valor minimo para os elementos utilizado na geração do vetor aleatório */
#define VALOR_MAXIMO_ALEATORIO 1000 /*!< Valor máximo para os elementos utilizado na geração do vetor aleatório */

#define TAMANHO_DE_VETOR_MAXIMO 1000 //10000 /*!< O programa irá executar ordenação para n iniciando em 25 com acréscimo de 5 até TAMANHO_DE_VETOR_MAXIMO (ex. 25, 30, 35, ..., TAMANHO_DE_VETOR_MAXIMO) */
#define QUANTIDADE_DE_TESTES 10 /*!< Quantidade de testes a serem realizados por execução de n (o tempo final será a média das QUANTIDADE_DE_TESTES execuções) */

/*!< 
      Dado o nome da ordenação (nome_ordenacao) e a iteração atual (teste).
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
      FILE* arquivo_ordenacao1 = cria_arquivo_dat(ORDENACAO1, tipo_de_vetor);
      FILE* arquivo_ordenacao2 = cria_arquivo_dat(ORDENACAO2, tipo_de_vetor);
      FILE* arquivo_ordenacao3 = cria_arquivo_dat(ORDENACAO3, tipo_de_vetor);
     
      // //+2 para colocar a média e desvio padrão
      // long double medias_bubble[quantidade_de_testes+2][4];
      // long double medias_insertion[quantidade_de_testes+2][4];
      // long double medias_merge[quantidade_de_testes+2][4];

      /*!< Variação dos valores de n (quantidade_de_elementos do vetor) */
      for(int quantidade_de_elementos = 25; quantidade_de_elementos <= TAMANHO_DE_VETOR_MAXIMO; quantidade_de_elementos+=5) {
            printf("-------------------------n=%d-------------------------------\n", quantidade_de_elementos);

            int *vetor_original = malloc(quantidade_de_elementos * sizeof(int));
            int *vetor_ordenacao1 = malloc(quantidade_de_elementos * sizeof(int));
            int *vetor_ordenacao2 = malloc(quantidade_de_elementos * sizeof(int));
            int *vetor_ordenacao3 = malloc(quantidade_de_elementos * sizeof(int));
            
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
            printf("Vetor base: \n");
            imprimir_vetor(vetor_original, quantidade_de_elementos);

            long double *tempo_de_execucao_ordenacao1 = malloc(QUANTIDADE_DE_TESTES * sizeof(long double));
            long double *tempo_de_execucao_ordenacao2 = malloc(QUANTIDADE_DE_TESTES * sizeof(long double));
            long double *tempo_de_execucao_ordenacao3 = malloc(QUANTIDADE_DE_TESTES * sizeof(long double));
            long double soma_ordenacao1 = 0;
            long double soma_ordenacao2 = 0;
            long double soma_ordenacao3 = 0;

            /*!< Realizando QUANTIDADE_DE_TESTES para cada n */
            for(int teste = 0; teste < QUANTIDADE_DE_TESTES; teste++) {
                  copiar_vetor(vetor_original, vetor_ordenacao1, quantidade_de_elementos);
                  copiar_vetor(vetor_original, vetor_ordenacao2, quantidade_de_elementos);
                  copiar_vetor(vetor_original, vetor_ordenacao3, quantidade_de_elementos);

                  if(DEBUG) printf("\n---------Teste %d\n\n", teste);

                  ordenar(ORDENACAO1, teste, vetor_ordenacao1, quantidade_de_elementos, tempo_de_execucao_ordenacao1, &soma_ordenacao1);
                  if(DEBUG) printf("\n-----\n");
                  ordenar(ORDENACAO2, teste, vetor_ordenacao2, quantidade_de_elementos, tempo_de_execucao_ordenacao2, &soma_ordenacao2);
                  if(DEBUG) printf("\n-----\n");
                  ordenar(ORDENACAO3, teste, vetor_ordenacao3, quantidade_de_elementos, tempo_de_execucao_ordenacao3, &soma_ordenacao3);
            }
            if(DEBUG) printf("\n---------\n\n");

            /*!< Calculando métricas */
            
            if(DEBUG) printf("Soma - %s: %Lf\n", nome_ordenacao_por_codigo(ORDENACAO1), soma_ordenacao1);
            if(DEBUG) printf("Soma - %s: %Lf\n", nome_ordenacao_por_codigo(ORDENACAO2), soma_ordenacao2);
            if(DEBUG) printf("Soma - %s: %Lf\n", nome_ordenacao_por_codigo(ORDENACAO3), soma_ordenacao3);
            if(DEBUG) printf("\n");

            /*!< Média */
            long double media_ordenacao1 = 0;
            long double media_ordenacao2 = 0;
            long double media_ordenacao3 = 0;

            media_ordenacao1 = soma_ordenacao1/QUANTIDADE_DE_TESTES;
            media_ordenacao2 = soma_ordenacao2/QUANTIDADE_DE_TESTES;
            media_ordenacao3 = soma_ordenacao3/QUANTIDADE_DE_TESTES;

            if(DEBUG) printf("Média - %s: %Lf\n", nome_ordenacao_por_codigo(ORDENACAO1), media_ordenacao1);
            if(DEBUG) printf("Média - %s: %Lf\n", nome_ordenacao_por_codigo(ORDENACAO2), media_ordenacao2);
            if(DEBUG) printf("Média - %s: %Lf\n", nome_ordenacao_por_codigo(ORDENACAO3), media_ordenacao3);
            if(DEBUG) printf("\n");

            /*!< Desvio Padrão */
            long double desvio_padrao_ordenacao1 = 0;
            long double desvio_padrao_ordenacao2 = 0;
            long double desvio_padrao_ordenacao3 = 0;

            for(int teste = 0; teste < QUANTIDADE_DE_TESTES; teste++) {
                  desvio_padrao_ordenacao1 += pow((tempo_de_execucao_ordenacao1[teste]-media_ordenacao1), 2);
                  desvio_padrao_ordenacao2 += pow((tempo_de_execucao_ordenacao2[teste]-media_ordenacao2), 2);
                  desvio_padrao_ordenacao3 += pow((tempo_de_execucao_ordenacao3[teste]-media_ordenacao3), 2);
            }

            desvio_padrao_ordenacao1 = sqrt(desvio_padrao_ordenacao1/QUANTIDADE_DE_TESTES);
            desvio_padrao_ordenacao2 = sqrt(desvio_padrao_ordenacao2/QUANTIDADE_DE_TESTES);
            desvio_padrao_ordenacao3 = sqrt(desvio_padrao_ordenacao3/QUANTIDADE_DE_TESTES);

            if(DEBUG) printf("Desvio Padrão - %s: %Lf\n", nome_ordenacao_por_codigo(ORDENACAO1), desvio_padrao_ordenacao1);
            if(DEBUG) printf("Desvio Padrão - %s: %Lf\n", nome_ordenacao_por_codigo(ORDENACAO2), desvio_padrao_ordenacao2);
            if(DEBUG) printf("Desvio Padrão - %s: %Lf\n", nome_ordenacao_por_codigo(ORDENACAO3), desvio_padrao_ordenacao3);

            /*!< 
                  Escrevendo arquivo .dat para gnuplot dentro da seguinte hierarquia:
                        Método de ordenação
                              Tipo de vetor 
                  É armazenado (n, tempo)
            */
            escrever_dat(arquivo_ordenacao1, quantidade_de_elementos, media_ordenacao1);
            escrever_dat(arquivo_ordenacao2, quantidade_de_elementos, media_ordenacao2);
            escrever_dat(arquivo_ordenacao3, quantidade_de_elementos, media_ordenacao3);

            // escrever_csv();

            //Escrevendo as médias para a tabela de 25, 100, 1000 e 10000
            // switch(quantidade_de_elementos) {
            //       case 25:
            //             for(int j = 0; j < quantidade_de_testes; j++) {
            //                   medias_bubble[j][0] = tempo_de_execucao_bubble[j];
            //                   medias_insertion[j][0] = tempo_de_execucao_insertion[j];
            //                   medias_merge[j][0] = tempo_de_execucao_merge[j];
            //             }

            //             medias_bubble[quantidade_de_testes][0] = media_bubble;
            //             medias_insertion[quantidade_de_testes][0] = media_insertion;
            //             medias_merge[quantidade_de_testes][0] = media_merge;

            //             medias_bubble[quantidade_de_testes+1][0] = desvio_padrao_bubble;
            //             medias_insertion[quantidade_de_testes+1][0] = desvio_padrao_insertion;
            //             medias_merge[quantidade_de_testes+1][0] = desvio_padrao_merge;
            //             break;
            //       case 100:
            //             for(int j = 0; j < quantidade_de_testes; j++) {
            //                   medias_bubble[j][1] = tempo_de_execucao_bubble[j];
            //                   medias_insertion[j][1] = tempo_de_execucao_insertion[j];
            //                   medias_merge[j][1] = tempo_de_execucao_merge[j];
            //             }

            //             medias_bubble[quantidade_de_testes][1] = media_bubble;
            //             medias_insertion[quantidade_de_testes][1] = media_insertion;
            //             medias_merge[quantidade_de_testes][1] = media_merge;

            //             medias_bubble[quantidade_de_testes+1][1] = desvio_padrao_bubble;
            //             medias_insertion[quantidade_de_testes+1][1] = desvio_padrao_insertion;
            //             medias_merge[quantidade_de_testes+1][1] = desvio_padrao_merge;
            //             break;
            //       case 1000:
            //             for(int j = 0; j < quantidade_de_testes; j++) {
            //                   medias_bubble[j][2] = tempo_de_execucao_bubble[j];
            //                   medias_insertion[j][2] = tempo_de_execucao_insertion[j];
            //                   medias_merge[j][2] = tempo_de_execucao_merge[j];
            //             }

            //             medias_bubble[quantidade_de_testes][2] = media_bubble;
            //             medias_insertion[quantidade_de_testes][2] = media_insertion;
            //             medias_merge[quantidade_de_testes][2] = media_merge;

            //             medias_bubble[quantidade_de_testes+1][2] = desvio_padrao_bubble;
            //             medias_insertion[quantidade_de_testes+1][2] = desvio_padrao_insertion;
            //             medias_merge[quantidade_de_testes+1][2] = desvio_padrao_merge;
            //             break;
            //       case 10000:
            //             for(int j = 0; j < quantidade_de_testes; j++) {
            //                   medias_bubble[j][3] = tempo_de_execucao_bubble[j];
            //                   medias_insertion[j][3] = tempo_de_execucao_insertion[j];
            //                   medias_merge[j][3] = tempo_de_execucao_merge[j];
            //             }

            //             medias_bubble[quantidade_de_testes][3] = media_bubble;
            //             medias_insertion[quantidade_de_testes][3] = media_insertion;
            //             medias_merge[quantidade_de_testes][3] = media_merge;

            //             medias_bubble[quantidade_de_testes+1][3] = desvio_padrao_bubble;
            //             medias_insertion[quantidade_de_testes+1][3] = desvio_padrao_insertion;
            //             medias_merge[quantidade_de_testes+1][3] = desvio_padrao_merge;

            //             break;
            // }

            free(tempo_de_execucao_ordenacao1);
            free(tempo_de_execucao_ordenacao2);
            free(tempo_de_execucao_ordenacao3);

            free(vetor_original);
            free(vetor_ordenacao1);
            free(vetor_ordenacao2);
            free(vetor_ordenacao3);

            printf("\n");
      }

      // fclose(arquivo_bubble);
      // fclose(arquivo_insertion);
      // fclose(arquivo_merge);
      
      /*
      Fazendo os arquivos .csv para adicionar no relatório
      A ideia é criar 3 arquivos: um para cada algoritmo
      Nota: Também por tipo de vetor (ordenado, ordenado inversamente e aleatório)
      A tabela terá o seguine formato:
      
                                MergeSort ou Bubblesort ou Insertion Sort
       Iteração de teste       25          100         1000        10000
            1
            2
            3
            4
            5
            6
            7
            8
            9
            10
           Média
         Desvio Padrão
      
      */

      // FILE* arquivo_media_bubble = fopen("bubble_media.csv", "w");
      // FILE* arquivo_media_insertion = fopen("insertion_media.csv", "w");
      // FILE* arquivo_media_merge = fopen("merge_media.csv", "w");

      // for(int i = 0; i < quantidade_de_testes+2; i++) {
      //       fprintf(arquivo_media_bubble, "%d,%Lf,%Lf,%Lf,%Lf\n", 
      //             i, medias_bubble[i][0], medias_bubble[i][1], medias_bubble[i][2], medias_bubble[i][3]);     
      // }

      // for(int i = 0; i < quantidade_de_testes+2; i++) {
      //       fprintf(arquivo_media_insertion, "%d,%Lf,%Lf,%Lf,%Lf\n", 
      //             i, medias_insertion[i][0], medias_insertion[i][1], medias_insertion[i][2], medias_insertion[i][3]);     
      // }

      // for(int i = 0; i < quantidade_de_testes+2; i++) {
      //       fprintf(arquivo_media_merge, "%d,%Lf,%Lf,%Lf,%Lf\n", 
      //             i, medias_merge[i][0], medias_merge[i][1], medias_merge[i][2], medias_merge[i][3]);     
      // }

      // imprimir_tabela_media(25, quantidade_de_testes, medias_bubble, medias_insertion, medias_merge);
      // imprimir_tabela_media(100, quantidade_de_testes, medias_bubble, medias_insertion, medias_merge);
      // imprimir_tabela_media(1000, quantidade_de_testes, medias_bubble, medias_insertion, medias_merge);
      // imprimir_tabela_media(10000, quantidade_de_testes, medias_bubble, medias_insertion, medias_merge);

      fclose(arquivo_ordenacao1);
      fclose(arquivo_ordenacao2);
      fclose(arquivo_ordenacao3);
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