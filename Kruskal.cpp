/*
Программа, реализующая алгоритм Крускала для вычисления минимальной суммарной длины дорожек в парке аттракционов. 
Дорожки должны быть проложены таким образом, чтобы между любыми двумя аттракционами существовал маршрут.

Программа должна считывать со стандартного потока ввода количество аттракционов и их координаты.
При этом координаты каждого аттракциона задаются парой целых чисел (в декартовой системе).

Программа должна выводить в стандартный поток вывода минимальную суммарную длину дорожек с точностью до двух знаков после запятой.
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Edge {
    double weight;
    int u;
    int v;
};

struct CompareEdges {
    bool operator()(const Edge& a, const Edge& b) const {
        return a.weight < b.weight;
    }
};

class MSTInterface {
public:
    virtual void generateEdges() = 0;
    virtual int find(int i) = 0;
    virtual void unionSets(int x, int y) = 0;
    virtual double calculateMST() = 0;
};

class KruskalMST : public MSTInterface {
private:
    int n;
    vector<vector<int> > coords;
    vector<Edge> edges;
    vector<int> parent;
    vector<int> rank;
    double totalWeight;

public:
    KruskalMST(int numVertices, const vector<vector<int> >& coordinates) {
        n = numVertices;
        coords = coordinates;
        parent.resize(n);
        rank.resize(n, 0);
        totalWeight = 0.0;

        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }

        generateEdges();
    }

    virtual void generateEdges() {
        edges.clear();
        for (int u = 0; u < n; ++u) {
            for (int v = u + 1; v < n; ++v) {
                int dx = coords[v][0] - coords[u][0];
                int dy = coords[v][1] - coords[u][1];
                double weight = sqrt(static_cast <double> (dx * dx + dy * dy));
                Edge edge;
                edge.weight = weight;
                edge.u = u;
                edge.v = v;
                edges.push_back(edge);
            }
        }
        sort(edges.begin(), edges.end(), CompareEdges());
    }

    virtual int find(int i) {
        if (parent[i] == i) {
            return i;
        }
        parent[i] = find(parent[i]); 
        return parent[i];
    }

    virtual void unionSets(int x, int y) {
        int xroot = find(x);
        int yroot = find(y);

        if (rank[xroot] < rank[yroot]) {
            parent[xroot] = yroot;
        } else if (rank[xroot] > rank[yroot]) {
            parent[yroot] = xroot;
        } else {
            parent[yroot] = xroot;
            rank[xroot]++;
        }
    }

    virtual double calculateMST() {
        for (vector<Edge> ::iterator it = edges.begin(); it != edges.end(); ++it) {
            int x = find(it->u);
            int y = find(it->v);

            if (x != y) {
                totalWeight += it->weight;
                unionSets(x, y);
            }
        }
        return totalWeight;
    }
};

int main() {
    int n;
    cin >> n;

    vector<vector <int> > coords(n, vector<int>(2));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 2; ++j) {
            cin >> coords[i][j];
        }
    }

    MSTInterface* mst = new KruskalMST(n, coords);
    double minWeight = mst->calculateMST();

    cout << fixed;
    cout.precision(2);
    cout << minWeight << endl;

    delete mst;

    return 0;
}
