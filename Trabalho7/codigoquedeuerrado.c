/* Disciplina: Programacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Aluno:Alekssander Santos do Carmo Martins */

#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>
#include <semaphore.h>

#define NTHREADS 3
#define N 50
// Variaveis globais
sem_t estado1, estado2;      //semaforos para coordenar a ordem de execucao das threads
sem_t estado0;
int positivo = 0;
int contador = 0; 

FILE * arqA; // coloquei como global para eu abrir no problema principal mas acessar na thread
int tamanho;
char buffer1[N];
char buffer2[N*2];
//funcao executada pela thread 1
void *t1 (void *arg) {
   char c; // variavel auxiliar
   while( c !=EOF){
      sem_wait(&estado0);
      for (int i = 0; i < N; i++) {
         c = fgetc(arqA); 
         if (c == EOF) { 
            positivo=1;
            break;
         }
      buffer1[i] = c; 
    }
    
    sem_post(&estado1); // manda sinal para inicio da thread 2 
   }
   pthread_exit(NULL);
}

//funcao executada pela thread 2
void *t2 (void *arg) {

   while(positivo == 0){
   sem_wait(&estado1); //espera sinal da thread 1 para iniciar
   //inicia a logica
    int i = 0;  
    int j = 0;  
    int n = 0;  
    while(buffer1[i] != '\0') {
        buffer2[j] = buffer1[i];
        j++;
        i++;
        contador++;
         // O contador verifica se precisamos inserir os \n para o primeiro caso
        if ((contador == (2 * n + 1)) && (n<=10)) {
            buffer2[j] = '\n';
            j++;
            n++;  
            contador = 0;
        }
        // Contador para inserir de 10 em 10 caracteres
        if((contador == 10) && n>10){
            buffer2[j] = '\n';
            j++;
            n++;  
            contador = 0;
        }
    }
    // final do buffer2
    buffer2[j] = '\0';

   sem_post(&estado2); // manda sinal para iniciar a thread 3
   }
   pthread_exit(NULL);
}

//funcao executada pela thread 3
void *t3 (void *arg) {

   //espera o sinal para iniciar 
   while(positivo==0){
   sem_wait(&estado2); 
   for(int i=0; i<N;i++){
     printf("%c",buffer2[i]);
   }
   sem_post(&estado0);
   }
   //encerra 
   pthread_exit(NULL);
}

//funcao principal
int main(int argc, char *argv[]) {
  pthread_t tid[NTHREADS];
     //recebe os argumentos de entrada
   if(argc < 2) {
      fprintf(stderr, "Digite: %s <arquivo de entrada> \n", argv[0]);
      return 1;
   }
   
   //abre o arquivo para leitura binaria de entrada do arquivo
   arqA = fopen(argv[1], "r");
   if(!arqA) {
      fprintf(stderr, "Erro de abertura do arquivo\n");
      return 2;
   }
   //finaliza abertura do arquivo 



  //inicia os semaforos
  sem_init(&estado0,0,1);
  sem_init(&estado1, 0, 0);
  sem_init(&estado2, 0, 0);

  //cria as tres threads
  if (pthread_create(&tid[2], NULL, t3, NULL)) { 
	  printf("--ERRO: pthread_create()\n"); exit(-1); }
  if (pthread_create(&tid[1], NULL, t2, NULL)) { 
	  printf("--ERRO: pthread_create()\n"); exit(-1); }
  if (pthread_create(&tid[0], NULL, t1, NULL)) { 
	  printf("--ERRO: pthread_create()\n"); exit(-1); }

  //--espera todas as threads terminarem
  for (int t=0; t<NTHREADS; t++) {
    if (pthread_join(tid[t], NULL)) {
         printf("--ERRO: pthread_join() \n"); exit(-1); 
    } 
  }

  sem_destroy(&estado0);
  sem_destroy(&estado1);
  sem_destroy(&estado2);

  fclose(arqA);

  return 0;
}
