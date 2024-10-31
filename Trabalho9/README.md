Respondendo as perguntas do Laboratório 9

Atividade 1

2. Comente a chamada da função Sleep e avalie o resultado da execução.  O que aconteceu e por que?

   Quando comentamos a função sleep o programa principal encerra antes da thread conseguir printar alguma coisa na tela, então o sleep é feito de forma a forçar o programa principal a esperar um tempo antes de finalizar.


Atividade 2

2. Por que não foi necessário fazer uma chamada para a função Sleep no código da função main dessa vez?
   
  Podemos perceber que quando temos a implementação de um canal, ele faz com que o programa principal espere o canal ser prenchido para seguir em frente na execução no caso a thread é a unica que prenche esse canal ou seja, somente depois da execução do prenchimento do canal que o programa principal pode seguir em frente.

4. Comente a linha msg = <-str e avalie o resultado da execução. O que aconteceu e por quê?

   
   Ocorre que o print dentro da thread não é executado pois não temos mais essa "função" de esperar a thread executar para prencher o canal.

6. Código feito nessa pasta!

Atividade 3


1. Qual é a finalidade de cada um dos canais criados?

A finalidade do primeiro canal é ser um canal com um buffer imbutido onde o canal tem indice , no exemplo no indice 0 do canal tem a informação que o valor j[0]=1 e assim em diante até o 3 que é o valor que envei pelo canal atraves do for , e o segundo canal é um canal boleano.

2. O que vai acontecer se comentarmos a linha 32?

   O done ta sendo usado como um canal para aguardar a finalização da thread, pois quando a thread é finalizada o valor de done vira True , e a thread encerra , e como no canal principal é esperado o canal do done ser prenchido para seguir o fluxo principal, logo é usado como uma forma de aguardar a thread principal.


Atividade 4 

1. Altere o código para que a sentença result 1 seja impressa na tela.

Atividade 5 

Código feito nessa pasta!






