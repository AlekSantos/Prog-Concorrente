/* Multiplicacao de matriz-matriz sequencial */
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include "timer.h"



int main(int argc, char* argv[]) {
    float *matrizA; //matriz que será carregada do arquivo matriz A
   int linhasA, colunasA; //dimensoes da matriz A
   float *matrizB;// matriz que será carregada do arquivo matriz B
    int linhasB, colunasB; //dimensoes da matriz B
   long long int tamA,tamB,tamresultado; //qtde de elementos na matriz A e B
   FILE * arqA, *arqB,*arqS; //descritor do arquivos de entrada e arquivo de saída
   size_t ret; //retorno da funcao de escrita no arquivo de saida
   float *resultado;
   double inicio, fim, delta;// monitoramento de tempo

   size_t retA,retB; //retorno da funcao de leitura no arquivo de entrada para A B
   GET_TIME(inicio);

   //recebe os argumentos de entrada
   if(argc < 4) {
      fprintf(stderr, "Digite: %s <arquivos de entrada> e <arquivo de saída> \n", argv[0]);
      return 1;
   }
   
   //abre o arquivo para leitura binaria de entrada da matriz A
   arqA = fopen(argv[1], "rb");
   if(!arqA) {
      fprintf(stderr, "Erro de abertura do arquivo\n");
      return 2;
   }
   //abre o arquivo para leitura binaria de entrada da matriz B
   arqB = fopen(argv[2], "rb");
   if(!arqB) {
      fprintf(stderr, "Erro de abertura do arquivo\n");
      return 2;
   }


   //le as dimensoes da matriz A
   retA = fread(&linhasA, sizeof(int), 1, arqA);
   if(!retA) {
      fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivo \n");
      return 3;
   }
   retA = fread(&colunasA, sizeof(int), 1, arqA);
   if(!retA) {
      fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivo \n");
      return 3;
   }
   tamA = linhasA * colunasA; //calcula a qtde de elementos da matriz A

   //aloca memoria para a matriz A
   matrizA = (float*) malloc(sizeof(float) * tamA);
   if(!matrizA) {
      fprintf(stderr, "Erro de alocao da memoria da matriz\n");
      return 3;
   }

   //carrega a matriz de elementos do tipo float do arqA
   retA = fread(matrizA, sizeof(float), tamA, arqA);
   if(retA < tamA) {
      fprintf(stderr, "Erro de leitura dos elementos da matriz\n");
      return 4;
   }
   
  
   //le as dimensoes da matriz B
   retB = fread(&linhasB, sizeof(int), 1, arqB);
   if(!retB) {
      fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivo \n");
      return 3;
   }
   retB = fread(&colunasB, sizeof(int), 1, arqB);
   if(!retB) {
      fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivo \n");
      return 3;
   }
   tamB = linhasB * colunasB; //calcula a qtde de elementos da matriz B

   //aloca memoria para a matriz B
   matrizB = (float*) malloc(sizeof(float) * tamB);
   if(!matrizB) {
      fprintf(stderr, "Erro de alocao da memoria da matriz\n");
      return 3;
   }

   //carrega a matriz de elementos do tipo float do arqB
   retB= fread(matrizB, sizeof(float), tamB, arqB);
   if(retB < tamB) {
      fprintf(stderr, "Erro de leitura dos elementos da matriz\n");
      return 4;
   }
      printf("\n");
   tamresultado= linhasA * colunasB;   
   //aloca memoria para a matriz do resultado
   resultado = (float*) malloc(sizeof(float) * tamresultado);
   //finaliza inicialização
   GET_TIME(fim);
   delta = fim - inicio;
   printf("Tempo inicializacao:%lf\n", delta);
   //Inicia tempo de processamento
   GET_TIME(inicio);

   //calcula resultado da matriz(processamento em si)
   if(colunasA != linhasB){
      /*printf("As matrizes não podem ser multiplicadas erro de dimensão.");*/
      return 3;
   }

   for (int i = 0; i < linhasA; i++) {
        for (int j = 0; j < colunasB; j++) {
      
            for (int k = 0; k < colunasA; k++) {
                resultado[i*colunasB+j]+=  matrizA[i*colunasA + k] * matrizB[k*colunasB+j];
            }
        }
    }

   GET_TIME(fim);
   //finaliza tempo de processamento
   delta = fim - inicio;
   printf("Tempo de processamento: %lf \n", delta);
   //inicia tempo de encerramento
   GET_TIME(inicio);
     arqS = fopen(argv[3], "wb");
   if(!arqS) {
      fprintf(stderr, "Erro de abertura do arquivo\n");
      return 3;
   }
   //escreve numero de linhas e de colunas
   ret = fwrite(&linhasA, sizeof(int), 1, arqS);
   ret = fwrite(&colunasB, sizeof(int), 1, arqS);
   //escreve os elementos da matriz
   ret = fwrite(resultado, sizeof(float), tamresultado, arqS);
   fclose(arqA);
   free(matrizA);
   fclose(arqB);
   free(matrizB);
   fclose(arqS);
   free(resultado);
   GET_TIME(fim);
   delta = fim - inicio;
   printf("tempo de finalizacao:%lf\n", delta);
   return 0;
}
