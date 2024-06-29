/*
Пусть выражения в польской записи состоят из имён переменных (от a до z), круглых скобок и трёх знаков операций: #, $ и @ (смысл операций мы определять не будем).

Выражения могут содержать повторяющиеся подвыражения. Экономное вычисление таких выражений подразумевает, что повторяющиеся подвыражения вычисляются только один раз.

Программа econom.go, вычисляющая количество операций, которые нужно выполнить для экономного вычисления выражения. 
Примеры работы программы приведены в таблице:

Набор тестов для программы экономного вычисления выражений в польской записи
Выражение
Количество операций
x	0
($xy)	1
($(@ab)c)	2
(#i($jk))	2
(#($ab)($ab))	2
(@(#ab)($ab))	3
(#($a($b($cd)))(@($b($cd))($a($b($cd)))))	5
(#($(#xy)($(#ab)(#ab)))(@z($(#ab)(#ab))))	6
*/
package main

import (
	"bufio"
	"fmt"
	"os"
)

func isOperator(char rune) bool {
	return char == '#' || char == '$' || char == '@'
}

func countOperations(expression string) int {
	stack := make([]string, 0)
	uniqueExpressions := make(map[string]bool)
	operationsCount := 0

	for _, char := range expression {
		s := string(char)
		if s == ")" {
			
			operand2 := stack[len(stack)-1]
			stack = stack[:len(stack)-1] // *
			operand1 := stack[len(stack)-1]
			stack = stack[:len(stack)-1] // *
			operation := stack[len(stack)-1]
			stack = stack[:len(stack)-1] // * 
			stack = stack[:len(stack)-1] // *

			subExpression := operation + operand1 + operand2
			if uniqueExpressions[subExpression] == false {
				uniqueExpressions[subExpression] = true
				operationsCount++
			}

			stack = append(stack, string(subExpression)) 
		} else if !isOperator(char) {
			stack = append(stack, s) 
		} else {
			stack = append(stack, s) 
		}
	}

	return operationsCount
}

func main() {
	var expression string
	input := bufio.NewScanner(os.Stdin)
	input.Scan()
	expression = input.Text()
	fmt.Printf("%d\n", countOperations(expression))
}
