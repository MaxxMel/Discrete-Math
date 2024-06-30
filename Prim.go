/*
На строительном участке нужно создать телефонную сеть, 
соединяющую все бытовки. Для того, чтобы телефонные линии не мешали строительству, их решили проводить вдоль дорог. 
Составьте программу, реализующую алгоритм Прима для вычисления минимальной общей длины телефонных линий для указанной конфигурации участка. 
Граф конфигурации участка должен быть представлен в программе в виде списка инцидентности.
*/
input: 
7
10
0 1 200
1 2 150
0 3 100
1 4 170
1 5 180
2 5 100
3 4 240
3 6 380
4 6 210
5 6 260
output:
930 

package main

import (
	"container/list"
	"fmt"
	"math"
)

type Pair struct {
	vertex, weight int
}

func main() {
	var n, m int
	fmt.Scan(&n, &m)

	g := make([][][2]int, n)
	for i := 0; i < m; i++ {
		var u, v, l int
		fmt.Scan(&u, &v, &l)
		g[u] = append(g[u], [2]int{v, l})
		g[v] = append(g[v], [2]int{u, l})
	}

	visited := make([]bool, n)
	key := make([]int, n)
	for i := range key {
		key[i] = math.MaxInt64
	}
	parent := make([]int, n)

	key[0] = 0
	l := list.New()
	l.PushBack(Pair{0, 0})

	totalWeight := 0

	for l.Len() > 0 {
		minPair := l.Front()
		for e := l.Front(); e != nil; e = e.Next() {
			if e.Value.(Pair).weight < minPair.Value.(Pair).weight {
				minPair = e
			}
		}
		l.Remove(minPair)
		u := minPair.Value.(Pair).vertex
		if visited[u] {
			continue
		}
		visited[u] = true
		totalWeight += minPair.Value.(Pair).weight

		for _, edge := range g[u] {
			v, weight := edge[0], edge[1]
			if !visited[v] && weight < key[v] {
				key[v] = weight
				parent[v] = u
				l.PushBack(Pair{v, weight})
			}
		}
	}

	fmt.Println(totalWeight)
}
