/* Disciplina: Programacao Concorrente */
/* Profa.: Silvana Rossetto */
/* Laboratório: 2 */
//Aluno: Alekssander Santos do Carmo Martins
//Programa concorrente



#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h> 

//variaveis globais
//tamanho do vetor
long int n;
//vetor de elementos
float *vetor1;
float *vetor2;
//numero de threads
int nthreads;

//funcao executada pelas threads
//estrategia de divisao de tarefas: blocos de n/nthreads elementos
void *CalculaMultiplicacaoVetores (void *tid) {
  long int id = (long int) tid; //identificador da thread
  int ini, fim, bloco; //auxiliares para divisao do vetor em blocos
  float multi_local, *ret; //somatorio local
  
  bloco = n/nthreads; //tamanho do bloco de dados de cada thread
  ini = id*bloco; //posicao inicial do vetor
  fim = ini + bloco; //posicao final do vetor
  if (id==(nthreads-1)) fim = n; //a ultima thread trata os elementos restantes no caso de divisao nao exata

  //multipicacao vetores
  for(int i=ini; i<fim; i++) {
     multi_local += vetor1[i] * vetor2[i];
  }

  //retorna o resultado da soma
  ret = malloc(sizeof(float));
  if (ret!=NULL) *ret = multi_local;
  else printf("--ERRO: malloc() thread\n");
  pthread_exit((void*) ret);
}
double variacaoRelativa(double vs,double vc){
  double e =(vs-vc)/vs;
  return e;
}

//funcao principal do programa
int main(int argc, char *argv[]) {
  FILE *arq; //arquivo de entrada
  size_t ret; //retorno da funcao de leitura no arquivo de entrada
	      
  double multi_original; //soma registrada no arquivo
  float  produtointerno; //resultados das somas
  //auxiliares para a soma sequencial alternada
  float *multi_retorno_threads; //auxiliar para retorno das threads

  pthread_t *tid_sistema; //vetor de identificadores das threads no sistema

  //valida e recebe os valores de entrada
  if(argc < 3) { printf("Use: %s <arquivo de entrada> <numero de threads> \n", argv[0]); exit(-1); }

  //abre o arquivo de entrada com os valores para serem somados
  arq = fopen(argv[1], "rb");
  if(arq==NULL) { printf("--ERRO: fopen()\n"); exit(-1); }

  //le o tamanho do vetor (primeira linha do arquivo)
  ret = fread(&n, sizeof(long int), 1, arq);
  if(!ret) {
     fprintf(stderr, "Erro de leitura das dimensoes da matriz arquivo \n");
     return 3;
  }

  //aloca espaco de memoria e carrega o vetor de entrada
  vetor1 = malloc (sizeof(float) * n);
  if(vetor1==NULL) { printf("--ERRO: malloc()\n"); exit(-1); }
  ret = fread(vetor1, sizeof(float), n, arq);
  if(ret < n) {
     fprintf(stderr, "Erro de leitura dos elementos do vetor1 \n");
     return 4;
  }
  vetor2 = malloc (sizeof(float) * n);
  if(vetor2==NULL) { printf("--ERRO: malloc()\n"); exit(-1); }
  ret = fread(vetor2, sizeof(float), n, arq);
  if(ret < n) {
     fprintf(stderr, "Erro de leitura dos elementos do vetor2 \n");
     return 4;
  }


  //le o numero de threads da entrada do usuario 
  nthreads = atoi(argv[2]);
  //limita o numero de threads ao tamanho do vetor
  if(nthreads>n) nthreads = n;

  //aloca espaco para o vetor de identificadores das threads no sistema
  tid_sistema = (pthread_t *) malloc(sizeof(pthread_t) * nthreads);
  if(tid_sistema==NULL) { printf("--ERRO: malloc()\n"); exit(-1); }

  //cria as threads
  for(long int i=0; i<nthreads; i++) {
    if (pthread_create(&tid_sistema[i], NULL, CalculaMultiplicacaoVetores, (void*) i)) {
       printf("--ERRO: pthread_create()\n"); exit(-1);
    }
  }


  
 
  //espera todas as threads terminarem e calcula multiplicacao vinda  das threads, para calcular o produto interno
  //retorno = (float*) malloc(sizeof(float));
  produtointerno=0;
  for(int i=0; i<nthreads; i++) {
     if (pthread_join(tid_sistema[i], (void *) &multi_retorno_threads)) {
        printf("--ERRO: pthread_join()\n"); exit(-1);
     }
     produtointerno += *multi_retorno_threads;
     free(multi_retorno_threads);
  }

  //imprime os resultados

  printf("produto interno concorrente = %.26f\n", produtointerno);
 
  //le o produto interno registrado no arquivo
  ret = fread(&multi_original, sizeof(double), 1, arq); 
  printf("\n produto interno sequencial = %.26lf\n", multi_original);

  printf("\nVariacao relativa dos = %.26lf\n",variacaoRelativa(multi_original,produtointerno));

  //desaloca os espacos de memoria
  free(vetor1);
  free(vetor2);
  free(tid_sistema);
  //fecha o arquivo
  fclose(arq);
  return 0;
}

