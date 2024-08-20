/* Disciplina: Programacao Concorrente */
/* Profa.: Silvana Rossetto */
/* Laboratório: 1 */
/* Codigo: "Hello World" usando threads em C e a funcao que espera as threads terminarem */
// Alguns prints que podem ser necessarios para corecao e foram ultizados para ajudar a fazer de forma correta, foram comentados ao longo do codigo


#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>

//cria a estrutura de dados para armazenar os argumentos da thread

typedef struct {
   int tamanhoT;
   int* vetor;
   int tamanhoAcumulado;
} t_Args;

//funcao executada pelas threads
void *CalculaVetorThread (void *arg) {
  t_Args *args = (t_Args *) arg;

  //printf("Tenho tamanho %d para mexer no vetor \n", args->tamanhoT);
  
  for (int i = 0; i < args->tamanhoT ; i++) {
        //printf("tenho o vetor que era %d \n",args->vetor[args->tamanhoAcumulado]);
        args->vetor[args->tamanhoAcumulado]= args->vetor[args->tamanhoAcumulado] + 1;
        args->tamanhoAcumulado+=1;
        //printf("tenho o vetor que virou %d \n",args->vetor[args->tamanhoAcumulado]);
    }
  
  free(arg); //libera a alocacao feita na main

  pthread_exit(NULL);
}


//Funcao que cria vetor
int* criaVetor(int tamanho) { 
    int* vetor = (int*)malloc(tamanho * sizeof(int));
    if (vetor == NULL) {
        printf("erro na alocaçao de memoria\n");
        exit(1);
    }
    // Inicializa o vetor
    for (int i = 0; i < tamanho; i++) {
        vetor[i] = i; 
    }
   // Retorna o ponteiro para o vetor
    return vetor;
}

 int VerificaResultado(int* vetorO, int n){
  int* vetorcorreto = criaVetor(n);
  for (int i = 0; i < n ; i++) {
    if( vetorO[i] != vetorcorreto[i] + 1) {
      printf("erro no vetor na posicao : %d",i);
      return 4;
    }
  return 0;
  }
} 

//funcao principal do programa
int main(int argc, char* argv[]) {
  t_Args *args; //receberá os argumentos para a thread

  int nthreads; //qtde de threads que serao criadas (recebida na linha de comando) M
   
  int tamanhovetor; //tamanho do vetor que sera criado (recebid na linha de comando) N
  int Tamanhoacumulado=0;
  //verifica se o argumento 'qtde de threads' foi passado e armazena seu valor
  if(argc<3) {
      printf("--ERRO: informe a qtde de threads e o tamanho do vetor desejado \n");
      return 1;
  }
  nthreads = atoi(argv[1]); // Primeiro passar o valor de M
  tamanhovetor = atoi(argv[2]); // Depois passar o valor de N
  int tamanho = tamanhovetor / nthreads;
  //printf("tamanho do vetor dentro de cada thread : %d \n", tamanho);
  int resto = tamanhovetor % nthreads;
  //printf("resto : %d \n", resto);
  //teste 
  int* vetor = criaVetor(tamanhovetor);
   //testa se ta vindo o que eu quero no vetor
   /* for (int i = 0; i < tamanhovetor; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n"); */

 /*  printf("numero de threads M : %d \n",nthreads);
  printf("tamanho do vetor N : %d  \n",tamanhovetor); */


  //identificadores das threads no sistema
  pthread_t tid_sistema[nthreads]; // cria idenficadores das threads no sistema

  //cria as threads
  for(int i=1; i<=nthreads; i++) {
    //printf("--Aloca e preenche argumentos para thread %d\n", i);
    args = malloc(sizeof(t_Args)); 
    if (args == NULL) {
      printf("--ERRO: malloc()\n"); 
      return 1;
    }
    args->tamanhoT = tamanho; 
    args->vetor = vetor ;
    args->tamanhoAcumulado = Tamanhoacumulado;
    Tamanhoacumulado= Tamanhoacumulado+ tamanho;  
    if (resto !=0){
      args->tamanhoT = tamanho + 1;
      Tamanhoacumulado= Tamanhoacumulado + 1;
      resto-=1;
    }
     
    //printf("--Cria a thread %d\n", i);
    if (pthread_create(&tid_sistema[i-1], NULL, CalculaVetorThread, (void*) args)) {
      printf("--ERRO: pthread_create()\n"); 
      return 2;
    }
  }

  //Espera todas as threads terminarem
  for (int i=0; i<nthreads; i++) {
    if (pthread_join(tid_sistema[i], NULL)) {
         printf("--ERRO: pthread_join() da thread %d\n", i); 
    } 
  } 

  //log da função principal

  /* for (int i = 0; i < tamanhovetor; i++) {
        printf("%d ", vetor[i]);
    }
   */
  printf("\n");
  printf("--Thread principal terminou\n");
  int resultado =VerificaResultado(vetor,tamanhovetor);
  if (resultado == 0){
    printf("Execucao foi um sucesso \n");
  }
  else{
    printf("Execucao foi uma falha \n");
  }
  // Verificar se Resultado esta correto
  return 0;
 
 
}
