/*
Карта представляет собой целочисленную матрицу размера N × N.

Путь на карте — это последовательность элементов карты с координатами (x1,y1), (x2,y2), …, (xk,yk) такая, что для любых двух 
соседних элементов последовательности справедливо одно утверждение из двух:

x-координаты элементов совпадают, а y-координаты различаются на единицу;
y-координаты элементов совпадают, а x-координаты различаются на единицу.
Длина пути — это сумма его элементов.


программа, вычисляющая минимальную длину пути, соединяющего точки (1,1) и (N,N).

Программа считывает из входного потока размер N карты (1 ≤ N ≤ 1500) и саму карту. Карта содержит целые числа от 0 до 9.

Программа выводит в выходной поток целое число — минимальную длину пути.
*/

package main

import (
	"container/heap"
	"fmt"
)

type Item struct {
	point    Point
	priority int
}

type PriorityQueue []*Item

func (pq PriorityQueue) Len() int { return len(pq) }

func (pq PriorityQueue) Less(i, j int) bool {
	return pq[i].priority < pq[j].priority
}

func (pq PriorityQueue) Swap(i, j int) {
	pq[i], pq[j] = pq[j], pq[i]
}

func (pq *PriorityQueue) Push(x interface{}) {
	item := x.(*Item)
	*pq = append(*pq, item)
}

func (pq *PriorityQueue) Pop() interface{} {
	old := *pq
	n := len(old)
	item := old[n-1]
	*pq = old[0 : n-1]
	return item
}

type Tile struct {
	cost int
	dist int
}

type Point struct {
	x, y int
}


func dijkstra(mat [][]Tile, n int) {
	pq := &PriorityQueue{}
	heap.Init(pq)
	mat[0][0].dist = mat[0][0].cost
	heap.Push(pq, &Item{point: Point{0, 0}, priority: mat[0][0].dist})

	shifts := []Point{
		{0, 1},
		{0, -1},
		{1, 0},
		{-1, 0},
	}

	for pq.Len() > 0 {
		item := heap.Pop(pq).(*Item)
		point := item.point
		for _, shift := range shifts {
			p := Point{
				point.x + shift.x,
				point.y + shift.y,
			}
			if p.x < 0 || p.y < 0 || p.x >= n || p.y >= n {
				continue
			}
			newDist := mat[point.x][point.y].dist + mat[p.x][p.y].cost
			if newDist < mat[p.x][p.y].dist {
				mat[p.x][p.y].dist = newDist
				heap.Push(pq, &Item{point: p, priority: newDist})
			}
		}
	}

	fmt.Println(mat[n-1][n-1].dist)
}

func main() {
	var n int
	fmt.Scan(&n)

	mat := make([][]Tile, n)
	for i := 0; i < n; i++ {
		mat[i] = make([]Tile, n)
		for j := 0; j < n; j++ {
			fmt.Scan(&mat[i][j].cost)
			mat[i][j].dist = 1000000
		}
	}

	
	dijkstra(mat, n)
}
