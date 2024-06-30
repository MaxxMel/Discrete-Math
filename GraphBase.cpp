/*
База орграфа
Пусть S1, S2, …, Sk — компоненты сильной связности орграфа G. Конденсацией орграфа G называется орграф G⋆ = ⟨V⋆,E⋆⟩, 
множеством вершин V⋆ которого служит множество {S1,S2,…,Sk}, а дуга ⟨Si,Sj⟩ является элементом множества E⋆, если в орграфе G есть по крайней мере одна дуга, исходящая из некоторой вершины компоненты Si и входящая в одну из вершин компоненты Sj.

База — это подмножество вершин орграфа, обладающее следующими свойствами:

каждая вершина орграфа достижима, по крайней мере, из одной вершины базы;
в базе нет вершин, достижимых из других вершин базы.
Очевидно, что в базе не может быть двух вершин, принадлежащих одной и той же компоненте сильной связности.

Также нетрудно доказать, что в ациклическом орграфе существует только одна база. Она состоит из всех вершин с полустепенью захода, равной 0.

С учётом вышесказанного поиск баз в орграфе можно проводить в следующем порядке:

найти все компоненты сильной связности орграфа;
построить его конденсацию;
найти базу конденсации;
из каждой компоненты сильной связности, образующей вершину базы конденсации, взять по одной вершине.
Составьте программу, вычисляющую базу заданного орграфа.

Программа должна считывать со стандартного потока ввода количество вершин орграфа N, количество дуг M и данные о дугах орграфа. При этом каждая дуга кодируется парой чисел u и v, где u — номер вершины, из которой дуга исходит, а v — номер вершины, в которую дуга входит. Вершины нумеруются, начиная с нуля.

Для обеспечения уникальности ответа из компоненты сильной связности, образующей вершину базы конденсации, следует брать вершину с минимальным номером.
*/
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Vertex {
public:
    vector<int> neighbors;
    int discoveryTime, component, lowLink;

    Vertex() : discoveryTime(0), component(0), lowLink(0) {}
};

class Component {
public:
    bool isRoot;
    int minVertex;

    Component() : isRoot(true), minVertex(-1) {}
};

class Tarjan : public Vertex {
public:
    vector<Vertex>& graph;
    stack<int> vertexStack;
    static int time;
    static int componentCount;

    Tarjan(vector<Vertex>& graph) : graph(graph) {}

    void run() {
        for (int i = 0; i < graph.size(); ++i) {
            if (graph[i].discoveryTime == 0) {
                visitVertex(i);
            }
        }
    }

private:
    void visitVertex(int index) {
        Vertex& vertex = graph[index];
        vertex.discoveryTime = vertex.lowLink = time++;
        vertexStack.push(index);

        for (int neighborIndex : vertex.neighbors) {
            Vertex& neighborVertex = graph[neighborIndex];
            if (neighborVertex.discoveryTime == 0) {
                visitVertex(neighborIndex);
                vertex.lowLink = min(vertex.lowLink, neighborVertex.lowLink);
            } else if (neighborVertex.component == 0) {
                vertex.lowLink = min(vertex.lowLink, neighborVertex.lowLink);
            }
        }

        if (vertex.discoveryTime == vertex.lowLink) {
            while (true) {
                int u = vertexStack.top();
                vertexStack.pop();
                graph[u].component = componentCount;
                if (u == index) break;
            }
            componentCount++;
        }
    }
};

int Tarjan::time = 1;
int Tarjan::componentCount = 1;

int main() {
    int numVertices, numEdges;
    cin >> numVertices >> numEdges;
    vector<Vertex> graph(numVertices);

    for (int i = 0; i < numEdges; ++i) {
        int from, to;
        cin >> from >> to;
        graph[from].neighbors.push_back(to);
    }

    Tarjan tarjan(graph);
    tarjan.run();

    vector<Component> components(Tarjan::componentCount);
    for (int i = 0; i < numVertices; ++i) {
        Component& component = components[graph[i].component];
        if (component.minVertex == -1) {
            component.minVertex = i;
        }
    }

    for (const Vertex& vertex : graph) {
        for (int neighborIndex : vertex.neighbors) {
            if (vertex.component != graph[neighborIndex].component) {
                components[graph[neighborIndex].component].isRoot = false;
            }
        }
    }

    for (int i = 1; i < Tarjan::componentCount; ++i) {
        if (components[i].isRoot) {
            cout << components[i].minVertex << " ";
        }
    }

    return 0;
}
