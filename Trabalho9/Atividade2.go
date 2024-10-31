// Alekssander santos do carmo martins 121075833
// Atividade2
package main

import (
	"fmt"
	"time"
)

func tarefa(str chan string) {
	// escreve no canal
	var mas = ""
	mas = <-str
	fmt.Println(mas)
	str <- "Oi Main, bom dia, tudo bem?"
	mas = <-str
	fmt.Println(mas)
	str <- "Certo, entendido."
	time.Sleep(time.Second)

	fmt.Printf("Finalizando\n")

}
func main() {
	var msg = "" //string vazia

	// cria um canal de comunicacao nao-bufferizado
	str := make(chan string)
	go tarefa(str)

	str <- "Ola, Goroutine, bom dia!"
	msg = <-str
	// cria um goroutine que executará a função 'tarefa'
	fmt.Println(msg)

	//lê do canal
	str <- "Tudo bem! Vou terminar t ́a?"
	msg = <-str
	fmt.Println(msg)
	time.Sleep(time.Second)

	fmt.Printf("Finalizando\n")

}
