/*
Польская запись — это форма записи арифметических, логических и алгебраических выражений, в которой операция располагается слева от операндов. 
Выражения в польской записи могут обходиться без скобок, однако мы оставим скобки для наглядности.

Например, выражение 5 ⋅ (3 + 4) в польской записи выглядит как
(* 5 (+ 3 4))
Программа polish.go, вычисляющая значение выражения.
*/

package main

import (
	"bufio"
	"fmt"
	"os"
	"unicode"
)

var storage []rune
var current int

func main() {
	//
	input := bufio.NewScanner(os.Stdin)
	input.Scan()
	storage = []rune(input.Text())
	fmt.Printf("%d", eval())
}

func eval() (ans int) {
	if current >= len(storage) {
		ans = 0
		return
	}

	current++

	if unicode.IsDigit(storage[current-1]) {
		ans = int(storage[current-1] - '0')
		return
	}

	if storage[current-1] == '+' {
		ans = eval() + eval()
		return
	}
	if storage[current-1] == '-' {
		ans = eval() - eval()
		return
	}
	if storage[current-1] == '*' {
		ans = eval() * eval()
		return
	}

	ans = eval()
	return
}
