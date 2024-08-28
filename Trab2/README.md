Trabalho 2

Avaliando os resultados podemos obter, através da metrica de variação relativa, sendo calculada pelo valor retornado do produto interno feito de forma sequencial(vs) e pelo produto interno feito pelo nosso programa concorrente(vc).
![image](https://github.com/user-attachments/assets/f725d29a-c34c-4ec2-b214-68c09f9a6fb2)

com a variação relativa, e o uso de alguns testes aumentando e diminuindo o numero de thereads para calcular o produto interno vindo do arquivo com vetor de tamanho 1000 podemos perceber que conforme aumentamos o numero de Thereads para ser igual ao tamanho do vetor(n) essa variação parece aumentar.
Podemos concluir então que a ultilização de thereads não seja boa para esse exemplo de produto interno, sendo o melhor ultilizar a forma sequencial para calcular, isso pode ocorrer devido aos erros de arredondamento vindo das operações.
