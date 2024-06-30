/*
Вершинами графа делителей являются все делители числа x.
Ребро соединяет вершины u и v в том случае, 
если u делится на v, и не существует такого w,
что u делится на w, и w делится на v. 
Пример графа делителей изображён на рисунке:
*/

package main

import (
	"fmt"
	"sort"
)

func FindDivisors(x int) []int {
	divisors := []int{}
	for i := 1; i*i <= x; i++ {
		if x%i == 0 {
			divisors = append(divisors, i)
			if i != x/i {
				divisors = append(divisors, x/i)
			}
		}
	}
	//sort.Ints(divisors)
	sort.Sort(sort.Reverse(sort.IntSlice(divisors)))
	return divisors
}
func FindDivs(x int) []int {
	divisors := []int{}
	for i := 1; i*i <= x; i++ {
		if x%i == 0 {
			divisors = append(divisors, i)
		}
		if i != x/i {
			divisors = append(divisors, x/i)
		}
	}
	sort.Sort(sort.Reverse(sort.IntSlice(divisors)))
	return divisors
}

func GRAPH(x int) {
	Storage := FindDivisors(x)
	for _, cur_i := range Storage {
		for _, cur_j := range Storage {
			if cur_i > cur_j && cur_i%cur_j == 0 {
				flag := 0
				for _, w := range Storage {
					if cur_i%w == 0 && w%cur_j == 0 && w != cur_i && w != cur_j {
						flag = 1
					} else {
						continue
					}
				}
				if flag == 0 {
					fmt.Printf("   %d--%d\n", cur_i, cur_j)
				}
			} else {
				continue
			}

		}
	}
}

func main() {
	var x int //**
	fmt.Scanf("%d", &x)
	fmt.Println("graph {")
	for _, cur := range FindDivisors(x) {
		fmt.Printf("   %d\n", cur)
	}
	GRAPH(x)
	fmt.Println("}")
}
