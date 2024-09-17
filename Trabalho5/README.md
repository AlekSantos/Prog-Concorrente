Respondendo as  questões propostas

ATIVIDADE 1
1.Abra o arquivo hellobye.c e identifique qual é o requisito lógico/condicional da aplicação (qual é a ordem de impressão requerida para as expressões "HELLO" e "BYEBYE"). Acompanhe a explicação da professora.

Resposta:

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

ATIVIDADE 3



1.Execute o programa e verifique seus resultados. As threads estão executando de forma sincronizada, concluindo uma interação para, então, iniciar outra?

2.Descomente a linha 44 (que chama a função "barreira"). Execute novamente o programa e avalie os resultados.

