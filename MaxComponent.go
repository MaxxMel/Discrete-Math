/*
Программа, выполняющая поиск наибольшей компоненты связности в неориентированном мультиграфе. Наибольшей считается компонента, содержащая максимальное количество вершин. 
Если две или более компоненты содержат одинаковое количество вершин, то выбирается та из них, в которой больше рёбер. 
Если же и это не позволяет однозначно выбрать наибольшую компоненту, следует предпочесть компоненту, содержащую минимальную по номеру вершину.

Программа считывает со стандартного потока ввода количество вершин графа N (1 ≤ N ≤ 1000000), количество рёбер M (0 ≤ M ≤ 1000000) и данные о рёбрах графа.
При этом каждое ребро кодируется номерами инцидентных ему вершин u и v такими, что 0 ≤ u, v < N.

Программа формирует в стандартном потоке вывода описание графа в формате DOT. 
При этом вершины графа должны быть помечены своими номерами, и, кроме того, вершины и рёбра наибольшей компоненты должны быть раскрашены красным цветом.
*/

package main

import (
	"bufio"
	"fmt"
	"os"
	"sort"
	"strconv"
	"strings"
)

type Stack struct {
	data []int
}

func (s *Stack) Push(val int) {
	s.data = append(s.data, val)
}

func (s *Stack) Pop() int {
	if len(s.data) == 0 {
		panic(" pustoi ")
	}
	index := len(s.data) - 1
	val := s.data[index]
	s.data = s.data[:index]
	return val
}

func (s *Stack) Size() int {
	return len(s.data)
}

func main() {
	reader := bufio.NewReader(os.Stdin)
	data, _ := reader.ReadString('\n')
	data = strings.TrimSpace(data)
	N, _ := strconv.Atoi(data)

	data, _ = reader.ReadString('\n')
	data = strings.TrimSpace(data)
	M, _ := strconv.Atoi(data)

	edges := make([][2]int, M)
	graph := make(map[int][]int)

	for i := 0; i < M; i++ {
		data, _ := reader.ReadString('\n')
		data = strings.TrimSpace(data)
		parts := strings.Split(data, " ")
		u, _ := strconv.Atoi(parts[0])
		v, _ := strconv.Atoi(parts[1])
		edges[i] = [2]int{u, v}
		graph[u] = append(graph[u], v)
		graph[v] = append(graph[v], u)
	}

	visited := make([]bool, N)

	var DFS func(int) ([]int, int)

	DFS = func(node int) ([]int, int) {
		stack := Stack{}
		stack.Push(node)
		component := []int{}
		componentEdges := 0

		for stack.Size() > 0 {
			v := stack.Pop()

			if !visited[v] {
				visited[v] = true
				component = append(component, v)

				for _, neighbor := range graph[v] {
					componentEdges++
					if !visited[neighbor] {
						stack.Push(neighbor)
					}
				}
			}
		}

		return component, componentEdges / 2
	}

	type CO struct {
		nodes []int
		edges int
	}

	components := []CO{}

	for i := 0; i < N; i++ {
		if !visited[i] {
			nodes, edges := DFS(i)
			components = append(components, CO{nodes, edges})
		}
	}

	sort.Slice(components, func(i, j int) bool {
		if len(components[i].nodes) != len(components[j].nodes) {
			return len(components[i].nodes) > len(components[j].nodes)
		}
		if components[i].edges != components[j].edges {
			return components[i].edges > components[j].edges
		}
		return components[i].nodes[0] < components[j].nodes[0]
	})

	largestComponent := components[0].nodes

	RED := make(map[int]bool)
	for _, node := range largestComponent {
		RED[node] = true
	}

	fmt.Println("graph {")

	for i := 0; i < N; i++ {
		if RED[i] {

			fmt.Printf("%d [color = red]\n", i)
		} else {
			fmt.Printf("%d\n", i)
		}
	}

	for _, edge := range edges {
		u, v := edge[0], edge[1]
		if RED[u] && RED[v] {
			fmt.Printf("%d -- %d [color = red]\n", u, v)
		} else {
			fmt.Printf("%d -- %d;\n", u, v)
		}
	}

	fmt.Println("}")
}
