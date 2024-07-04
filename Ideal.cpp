/*
В парке аттракционов построили лабиринт. Лабиринт состоит из n комнат, соединённых с помощью m проходов. Каждый проход покрашен в некоторый цвет ci. 
Посетителей лабиринта забрасывают с вертолёта в комнату номер 1, и их задача — добраться до выхода из лабиринта, расположенного в комнате номер n.

Владельцы лабиринта планируют устроить соревнование. Несколько участников будут заброшены в комнату номер 1. Они должны будут добраться до комнаты номер n,
записывая цвета переходов, через которые им придётся проходить. Участник с самой короткой последовательностью цветов выиграет соревнование. 
Если у нескольких участников длина последовательности окажется одинакова, то победит тот из них, чей путь будет идеальным. Путь считается идеальным, если соответствующая ему последовательность цветов — лексикографически меньшая среди всех возможных кратчайших путей.

Андрей готовится к участию в соревновании. Он пролетел на вертолёте над парком аттракционов и зарисовал лабиринт.
Необходимо составить программу, которая поможет ему найти идеальный путь из комнаты номер 1 в комнату номер n, чтобы выиграть соревнование.

Формат входных данных
Первым делом программа считывает со стандартного потока ввода два целых числа n и m, содержащие количество комнат и переходов, соответственно (2 ≤ n ≤ 100 000, 1 ≤ m ≤ 200 000). 
Далее программа должна считать m описаний переходов, представляющих собой тройки чисел: ai, bi и ci. Каждая тройка задаёт номера комнат, соединяемых переходом, 
и цвет перехода (1 ≤ ai, bi ≤ n, 1 ≤ ci ≤ 109). Каждый переход можно проходить в любом направлении. Две комнаты могут соединяться несколькими переходами. 
Кроме того, могут существовать переходы, ведущие из комнаты в неё же. Гарантируется, что комната номер n достижима из комнаты номер 1.

Формат результата работы программы
Программа должна выводить в стандартный поток вывода длину k идеального пути, за которой должна следовать последовательность из k цветов переходов, 
получаемая в процессе прохода по идеальному пути.
*/

#include <iostream>
#include <vector>
#include <deque>
#include <climits>
#include <algorithm>

using namespace std;

class Graph {
private:
    vector<vector<pair<int, int> > > graph;

public:
    Graph(int countVertex) {
        graph.resize(countVertex);
    }

    void fill(int m) {
        for (int i = 0; i < m; i++) {
            int vertex1, vertex2, color;
            cin >> vertex1 >> vertex2 >> color;
            vertex1--;  
            vertex2--;  
            add(vertex1, vertex2, color);
        }
    }

    void add(int vertex1, int vertex2, int color) {
        graph[vertex1].push_back(make_pair(vertex2, color));
        graph[vertex2].push_back(make_pair(vertex1, color));
    }

    vector<pair<int, int> >& getNeighbors(int vertex) {
        return graph[vertex];
    }

    static int lexComp(const vector<int>& list1, const vector<int>& list2) {
        int size1 = list1.size();
        int size2 = list2.size();
        int minSize = min(size1, size2);
        for (int i = 0; i < minSize; i++) {
            if (list1[i] != list2[i]) {
                return list1[i] - list2[i];
            }
        }
        return size1 - size2;
    }

    void bfs(int start, int finish, vector<int>& d, vector<vector<int> >& path) {
        deque<int> q;
        d[start] = 0;
        q.push_back(start);

        while (!q.empty()) {
            int v = q.front();
            q.pop_front();

            vector<pair<int, int> >& neighbors = getNeighbors(v);

            for (size_t i = 0; i < neighbors.size(); ++i) {
                int u = neighbors[i].first;
                int color = neighbors[i].second;

                if (d[u] == INT_MAX) {
                    d[u] = d[v] + 1;
                    q.push_back(u);
                    path[u] = path[v];
                    path[u].push_back(color);
                } else if (d[u] == d[v] + 1) {
                    vector<int> newPath = path[v];
                    newPath.push_back(color);
                    if (lexComp(newPath, path[u]) < 0) {
                        path[u] = newPath;
                    }
                }
            }
        }
    }
};

int main() {
    int n, m;
    cin >> n >> m;

    Graph graph(n);
    graph.fill(m);

    vector<int> distances(n, INT_MAX);
    vector<vector<int> > paths(n);

    graph.bfs(0, n - 1, distances, paths);

    cout << distances[n - 1] << "\n";
    for (size_t i = 0; i < paths[n - 1].size(); ++i) {
        cout << paths[n - 1][i] << " ";
    }
    cout << "\n";

    return 0;
}
