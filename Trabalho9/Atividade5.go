//Atividade 5
//Alekssander santos do carmo martins 121075833

package main

import (
	"fmt"
	"math"
	"time"
)

var primos int = 0

func ehprimo(n int64) bool {
	if n <= 1 {
		return false
	}
	if n == 2 {
		return true
	}
	if n%2 == 0 {
		return false
	}
	for i := int64(3); i <= int64(math.Sqrt(float64(n)))+1; i += 2 {
		if n%i == 0 {
			return false
		}
	}
	return true
}
func tarefa(numeros chan int) {
	for {

		j, more := <-numeros
		if more {
			if ehprimo(int64(j)) {
				primos += 1
			}
		} else {
			fmt.Println("termino")
			return
		}
	}

}

func main() {
	var N int = 100
	var M int = 5
	//usar canal bufferizado
	// fazer um for para passar para cada goroutine um canal bufferizado com N/M elementos
	//usar um canal boleano? para permitir que as goroutines encerrem quando o canal for true?
	numeros := make(chan int, N/M)

	for j := 0; j < N/M; j++ {
		for i := 1; i <= M; i++ {
			numeros <- (j*M + i)
			go tarefa(numeros)
		}

	}
	time.Sleep(3 * time.Second)

	fmt.Println("Existem : ", primos)
}
