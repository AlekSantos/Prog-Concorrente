//Programa concorrente utilizando o padrão leitor e escritor
#include <stdio.h>
#include <stdlib.h>
#include "list_int.h"
#include <pthread.h>
#include "timer.h"


#define QTDE_OPS 100000 //quantidade de operacoes sobre a lista (insercao, remocao, consulta)
#define QTDE_INI 100 //quantidade de insercoes iniciais na lista
#define MAX_VALUE 100 //valor maximo a ser inserido

// estrutura para a lista encadeada
struct list_node_s* head_p = NULL; 

//qtde de threads no programa
int nthreads;
// variáveis de controle para leitura e escrita na fila de leitores e escritores
// controle por exclusão mútua e sincronização da var condicional para leitura e escrita
pthread_mutex_t mutex;
pthread_cond_t cond_escr,cond_leit;
int escr=0;
int leit=0; 
int queroEscrever=0;
int queroLer=0;
// Criando as operações de entrada e saída para leitura e escrita
void EntraLeitura() {
    pthread_mutex_lock(&mutex);
    // Assim que entramos na leitura incrementamos a var queroLer pois há um leitor querendo realizar operação porém precisamos avaliar se podemos ler ou não
    queroLer++;
    // Se existir algum escritor escrevendo no momento ou um escritor querendo entrar para escrever  o leitor deve esperar até que a escrita seja realizada
    while(escr > 0 || queroEscrever!=0 ) {
        printf("existe escritor(es)  escrevendo no momento espere...\n");
        pthread_cond_wait(&cond_leit, &mutex);
        
    }
    // A variável quer ler é decrementada pois o leitor está realizando  a leitura, e assim incrementamos o número de leitores tendo em vista que podem haver leituras simultâneas
    queroLer--;
    printf("Entrou um leitor ...\n");
    leit++;
    pthread_mutex_unlock(&mutex);
}
void SaiLeitura() {
    // Marca a saída do leitor com um log e outro para mostrar a quantidade de leitores que ainda querem ler além disso decrementa a quantidade de leitores. Desbloqueando todas as threads que foram bloqueadas na fila dos escritores
    pthread_mutex_lock(&mutex);
     printf("Saiu um leitor\n");
     leit--;
    printf("existe %d leitor(es) na fila \n", queroLer);
   pthread_cond_broadcast(&cond_escr);
    pthread_mutex_unlock(&mutex);
}
void EntraEscrita () {
    pthread_mutex_lock(&mutex);
     // Assim que entramos na escrita incrementamos a var queroEscrever pois há um escritor querendo realizar operação porém precisamos avaliar se podemos escrever ou não
    queroEscrever++;
     // Se existir algum leitor lendo no momento ou um escritor querendo escrever, o escritor que deseja escrever deve esperar até que as operações sejam realizadas.
    while((leit>0) || (escr>0)) {
    printf("Há leitor(es) %d e escritor(es) %d espere...\n",leit,escr);
    pthread_cond_wait(&cond_escr, &mutex);
} // A variavel queroEscrever  é decrementada pois o escritor está realizando a escrita, e assim incrementamos o número de escritores 
    escr++;
    printf("Entrou um escritor ...\n");
    queroEscrever--;
    pthread_mutex_unlock(&mutex);
}
void SaiEscrita () {
     // Marca a saída de um escritor com um log e outro para mostrar se há escritores que ainda querem escrever.Além disso decrementa a quantidade de escritores pois estamos saindo da escrita
    // Desbloqueia todas as threads que foram bloqueadas na fila dos escritores e da fila de leitores para que o próximo leitor leia ou caso haja escritores na fila os mesmos escrevam antes que 
    // os leitores iniciem sua operação 
    pthread_mutex_lock(&mutex); 
     printf("Escritor saindo.\n");
    printf("Há %d escritor(es) na fila \n", queroEscrever);
    escr--;
    pthread_cond_broadcast(&cond_escr);
    pthread_cond_broadcast(&cond_leit);
    pthread_mutex_unlock(&mutex);
}


//Programa concorrente que cria e faz operacoes sobre uma lista de inteiros utilizando o padrão leitor e escritor



//tarefa das threads
void* tarefa(void* arg) {
   long int id = (long int) arg;
   int op;
   int in, out, read; 
   in=out=read = 0; 

   //realiza operacoes de consulta (98%), insercao (1%) e remocao (1%)
   for(long int i=id; i<QTDE_OPS; i+=nthreads) {
      op = rand() % 100;
      if(op<98) {
	  EntraLeitura(); /* chama a leitura*/    
         Member(i%MAX_VALUE, head_p);   /* Ignore return value */
	 SaiLeitura();    /* sai da  leitura*/   
	 read++;
      } else if(98<=op && op<99) {
	 EntraEscrita(); /* chama a escrita */    
         Insert(i%MAX_VALUE, &head_p);  /* Ignore return value */
	 SaiEscrita();     /* sai da  escrita*/ 
	 in++;
      } else if(op>=99) {
	  EntraEscrita() ; /* chama a escrita */     
         Delete(i%MAX_VALUE, &head_p);  /* Ignore return value */
	 SaiEscrita();    /* sai da  escrita*/ 
	 out++;
      }
   }
   //registra a qtde de operacoes realizadas por tipo
   printf("Thread %ld: in=%d out=%d read=%d\n", id, in, out, read);
   pthread_exit(NULL);
}

/*-----------------------------------------------------------------*/
int main(int argc, char* argv[]) {
   pthread_t *tid;
   double ini, fim, delta;
   
   //verifica se o numero de threads foi passado na linha de comando
   if(argc<2) {
      printf("Digite: %s <numero de threads>\n", argv[0]); return 1;
   }
   nthreads = atoi(argv[1]);

   //insere os primeiros elementos na lista
   for(int i=0; i<QTDE_INI; i++)
      Insert(i%MAX_VALUE, &head_p);  /* Ignore return value */
   

   //aloca espaco de memoria para o vetor de identificadores de threads no sistema
   tid = malloc(sizeof(pthread_t)*nthreads);
   if(tid==NULL) {  
      printf("--ERRO: malloc()\n"); return 2;
   }

   //tomada de tempo inicial
   GET_TIME(ini);
   //inicializa a variavel mutex
   pthread_mutex_init(&mutex, NULL);
   pthread_cond_init(&cond_leit, NULL);
   pthread_cond_init(&cond_escr, NULL);
   
   //cria as threads
   for(long int i=0; i<nthreads; i++) {
      if(pthread_create(tid+i, NULL, tarefa, (void*) i)) {
         printf("--ERRO: pthread_create()\n"); return 3;
      }
   }
   
   //aguarda as threads terminarem
   for(int i=0; i<nthreads; i++) {
      if(pthread_join(*(tid+i), NULL)) {
         printf("--ERRO: pthread_join()\n"); return 4;
      }
   }

   //tomada de tempo final
   GET_TIME(fim);
   delta = fim-ini;
   printf("Tempo: %lf\n", delta);

   //libera o mutex
   pthread_mutex_destroy(&mutex);
   //libera o espaco de memoria do vetor de threads
   free(tid);
   //libera o espaco de memoria da lista
   Free_list(&head_p);

   return 0;
}  /* main */
