/*
Составьте программу, определяющая количество мостов в неориентированном простом графе.

Программа считывает со стандартного потока ввода количество вершин графа N, количество рёбер M и данные о рёбрах графа. 
При этом каждое ребро кодируется номерами инцидентных ему вершин u и v такими, что 0 ≤ u, v < N.

Программа хранит граф в памяти в виде списков инцидентности.


*/

package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	reader := bufio.NewReader(os.Stdin)

	data, _ := reader.ReadString('\n')
	data = strings.TrimSpace(data)
	N, _ := strconv.Atoi(data)

	data, _ = reader.ReadString('\n')
	data = strings.TrimSpace(data)
	M, _ := strconv.Atoi(data)

	graph := make([][]int, N)
	for i := range graph {
		graph[i] = []int{}
	}

	for i := 0; i < M; i++ {
		data, _ := reader.ReadString('\n')
		data = strings.TrimSpace(data)
		parts := strings.Split(data, " ")
		u, _ := strconv.Atoi(parts[0])
		v, _ := strconv.Atoi(parts[1])
		graph[u] = append(graph[u], v)
		graph[v] = append(graph[v], u)
	}

	visited := make([]bool, N)
	TIMEin := make([]int, N)
	low := make([]int, N)
	STEPS := 0
	var bridges int

	DFS(graph, visited, TIMEin, low, &bridges, STEPS)

	fmt.Println(bridges)
}

func DFS(graph [][]int, visited []bool, TIMEin, low []int, bridges *int, STEPS int) {
	var dfs func(cur int, parent int)

	dfs = func(cur int, parent int) {
		visited[cur] = true
		STEPS++
		TIMEin[cur] = STEPS
		low[cur] = STEPS

		for _, to := range graph[cur] {
			if to == parent {
				continue
			}
			if visited[to] {
				if low[cur] >= TIMEin[to] {
					low[cur] = TIMEin[to]
				}

			} else {
				dfs(to, cur)
				if low[cur] >= low[to] {
					low[cur] = low[to]
				}

				if low[to] > TIMEin[cur] {
					*bridges++
				}
			}
		}
	}

	for i := 0; i < len(graph); i++ {
		if !visited[i] {
			dfs(i, -1)
		}
	}
}
