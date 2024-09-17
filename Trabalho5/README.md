Respondendo as  questões propostas

ATIVIDADE 1  
1.Abra o arquivo hellobye.c e identifique qual é o requisito lógico/condicional da aplicação (qual é a ordem de impressão requerida para as expressões "HELLO" e "BYEBYE"). Acompanhe a explicação da professora.  

Resposta:
O programa é simples, ele começa chmando 3 threads, 2 do tipo A e uma do tipo B , na thread do tipo A tem o print na tela de HELLO , e no B tem de BYEBYE, o programa só deixa printar BYEBYE depois de ter 2 HELLO tendo sido executados para isso ela faz uso de variaveis de execução para só permitir o BYEBYE ser printado quando 2 HELLO são printados,ou seja ele para a execução de B até o sinal ser liberado , liberando o sinal para continuar a execução da thread B


ATIVIDADE 2  

Objetivo: Avaliar a implementação de uma aplicação que tem requisitos de ordem de execução das threads.  

Descrição: O programa exemplo.c foi implementado por um colega em uma atividade de laboratório de uma edição anterior da disciplina. O roteiro foi o seguinte:  

Implemente um programa com 5 threads:  

A thread 1 imprime a frase “Oi Maria!”;  
A thread 2 imprime a frase “Oi José!”;  
A thread 3 imprime a frase “Sente-se, por favor.”;  
A thread 4 imprime a frase “Até mais, José!”;  
A thread 5 imprime a frase “Até mais, Maria!”.  
As threads devem ser criadas todas de uma vez na função main. As regras de impressão das mensagens (execução das threads) são:  

A ordem em que as threads 1 e 2 imprimem suas mensagens não importa, mas ambas devem sempre imprimir suas mensagens antes da thread 3.  
A ordem em que as threads 4 e 5 imprimem suas mensagens não importa, mas ambas devem sempre imprimir suas mensagens depois da thread 3.   


1. Leia o programa e verifique se os requisitos foram atendidos.

   Resposta: Sim os requesitos foram atendidos.

ATIVIDADE 3  



2.Execute o programa e verifique seus resultados. As threads estão executando de forma sincronizada, concluindo uma interação para, então, iniciar outra?  

Não, acontece uma bagunça na hora da execução do programa , como por exemplo essa execução :


%./barreira
Thread 0: passo=0
Thread 1: passo=0
Thread 2: passo=0
Thread 0: passo=1
Thread 1: passo=1
Thread 2: passo=1
Thread 0: passo=2
Thread 1: passo=2
Thread 2: passo=2
Thread 0: passo=3
Thread 1: passo=3
Thread 2: passo=3
Thread 0: passo=4
Thread 1: passo=4
Thread 2: passo=4
Thread 3: passo=0
Thread 3: passo=1
Thread 3: passo=2
Thread 3: passo=3
Thread 3: passo=4
Thread 4: passo=0
Thread 4: passo=1
Thread 4: passo=2
Thread 4: passo=3
Thread 4: passo=4
FIM.


3.Descomente a linha 44 (que chama a função "barreira"). Execute novamente o programa e avalie os resultados.  


Agora sim o programa funciona da forma que deveria, ele pode executar as threads em ordem diferente mas sempre seguindo o mesmo passo, ou seja todas as threads executam o passo 0 depois o 1 depois o 2 e em diante diferente do que ocorre antes de ter a barreira implementada.

