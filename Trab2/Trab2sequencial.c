/* Disciplina: Programacao Concorrente */
/* Profa.: Silvana Rossetto */
/* Laboratório: 2 */
//Aluno: Alekssander Santos do Carmo Martins
// Programa sequencial


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1000 //valor maximo de um elemento do vetor 
//descomentar o define abaixo caso deseje imprimir uma versao do vetor gerado no formato texto
#define TEXTO 

int main(int argc, char*argv[]) {
   float *vetor1; //vetor1 que será geradado
   float *vetor2; //vetor2 que será geradado
   long int n; //qtde de elementos do vetor que serao gerados
   float elem; //valor gerado para incluir no vetor
   double resultadopin=0; //Resultado do produto interno 
   int fator=1; //fator multiplicador para gerar números negativos
   FILE * descritorArquivo; //descritor do arquivo de saida
   size_t ret; //retorno da funcao de escrita no arquivo de saida

   //recebe os argumentos de entrada
   if(argc < 3) {
      fprintf(stderr, "Digite: %s <dimensao> <arquivo saida>\n", argv[0]);
      return 1;
   }
   n = atoi(argv[1]);

   //aloca memoria para o vetor
   vetor1 = (float*) malloc(sizeof(float) * n);
   if(!vetor1) {
      fprintf(stderr, "Erro de alocao da memoria do vetor1\n");
      return 2;
   }
   vetor2 = (float*) malloc(sizeof(float) * n);
   if(!vetor2) {
      fprintf(stderr, "Erro de alocao da memoria do vetor2\n");
      return 2;
   }
   //preenche o vetor com valores float aleatorios
   srand(time(NULL));
   for(long int i=0; i<n; i++) {
        elem = (rand() % MAX)/3.0 * fator;
        vetor1[i] = elem;
        elem = (rand() % MAX)/4.0 * fator;
        vetor2[i] = elem;
        fator*=-1;
   }

   // calcula o valor do produto interno
   for(int i = 0; i < n ; i++) {
        resultadopin += vetor1[i] * vetor2[i];
    }

   //imprimir na saida padrao o vetor gerado
   #ifdef TEXTO
   fprintf(stdout, "%ld\n", n);
   for(long int i=0; i<n; i++) {
      fprintf(stdout, "%f ",vetor1[i]);
   }
   fprintf(stdout, "\n");
   fprintf(stdout, "%ld\n", n);
   for(long int i=0; i<n; i++) {
      fprintf(stdout, "%f ",vetor2[i]);
   }
   fprintf(stdout, "\n");
   fprintf(stdout, "Resultado do produto interno =%lf\n", resultadopin);
   #endif

   //escreve o vetor no arquivo
   //abre o arquivo para escrita binaria
   descritorArquivo = fopen(argv[2], "wb");
   if(!descritorArquivo) {
      fprintf(stderr, "Erro de abertura do arquivo\n");
      return 3;
   }
   //escreve o tamanho n 
   ret = fwrite(&n, sizeof(long int), 1, descritorArquivo);
   //escreve os elementos do vetor
   ret = fwrite(vetor1, sizeof(float), n, descritorArquivo);
   if(ret < n) {
      fprintf(stderr, "Erro de escrita no  arquivo\n");
      return 4;
   }
   ret = fwrite(vetor2, sizeof(float), n, descritorArquivo);
   if(ret < n) {
      fprintf(stderr, "Erro de escrita no  arquivo\n");
      return 4;
   }
   //escreve o produto interno
   ret = fwrite(&resultadopin, sizeof(double), 1, descritorArquivo);

   //finaliza o uso das variaveis
   fclose(descritorArquivo);
   free(vetor1);  //libera o uso da memoria dos vetores 1 e 2
   free(vetor2);
   return 0;
} 
