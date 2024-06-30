/*
Каноническая нумерация состояний автомата
Пусть на множестве входных сигналов инициального автомата Мили определено отношенеие строгого порядка.

Выполним обход диаграммы автомата в глубину от начального стостояния таким образом, что дуги, 
исходящие из каждого состояния, рассматриваются в порядке возрастания входных сигналов, которыми эти дуги помечены.

Если присвоить каждому состоянию автомата номер, равный позиции состояния в полученном в результате обхода предпорядке, 
то мы получим так называемую каноническую нумерацию состояний. При этом будем считать, что состояния нумеруются, начиная с нуля.

Составьте программу, выполняющую каноническую нумерацию состояний инициального автомата Мили.

Программа должна считывать из стандартного потока ввода количество состояний автомата n, размер входного алфавита m, 
номер начального состояния q0 (0 ≤ q0 < n), матрицу переходов Δ и матрицу выходов Φ. Матрицы переходов и выходов имеют размеры n × m. При этом элементами матрицы переходов являются номера состояний, а элементами матрицы выходов — выходные сигналы. Каждый выходной сигнал представляет собой не содержащую пробелов строку.

Программа должны выводить в стандартный поток вывода описание автомата, эквивалентного исходному, в котором состояния пронумерованы канонически. 
Описание должно выводиться в том же формате, в котором исходный автомат поступает на вход программы.
*/

#include <iostream>
#include <vector>
#include <stack>
#include <map>
#include <string>

using namespace std;

class G {
protected:
    int ns, ms, s0;
    vector<vector<int> > d;
    vector<vector<string> > f;

public:
    G(int numStates, int numSymbols, int startState) 
        : ns(numStates), ms(numSymbols), s0(startState) {
        d.resize(ns, vector<int>(ms));
        f.resize(ns, vector<string>(ms));
    }

    void fillD() {
        for (int i = 0; i < ns; ++i) {
            for (int j = 0; j < ms; ++j) {
                cin >> d[i][j];
            }
        }
    }

    void fillF() {
        for (int i = 0; i < ns; ++i) {
            for (int j = 0; j < ms; ++j) {
                cin >> f[i][j];
            }
        }
    }

    const vector<vector<int> >& getD() const {
        return d;
    }

    const vector<vector<string> >& getF() const {
        return f;
    }

    int getNs() const {
        return ns;
    }

    int getMs() const {
        return ms;
    }

    int getS0() const {
        return s0;
    }
};

class C : public G {
private:
    vector<int> c;
    vector<bool> v;

    void dfs(int start) {
        stack<int> st;
        st.push(start);
        while (!st.empty()) {
            int x = st.top();
            st.pop();
            if (!v[x]) {
                v[x] = true;
                c.push_back(x);
                for (int i = d[x].size() - 1; i >= 0; i--) {
                    st.push(d[x][i]);
                }
            }
        }
    }

public:
    C(int numStates, int numSymbols, int startState) 
        : G(numStates, numSymbols, startState), v(numStates, false) {}

    void performDFS() {
        dfs(s0);
    }

    void printC() {
        map<int, int> cm;
        for (int i = 0; i < c.size(); ++i) {
            cm[c[i]] = i;
        }

        cout << ns << endl;
        cout << ms << endl;
        cout << cm[s0] << endl;

        for (int i = 0; i < c.size(); ++i) {
            for (int j = 0; j < ms; ++j) {
                cout << cm[d[c[i]][j]] << " ";
            }
            cout << endl;
        }

        for (int i = 0; i < c.size(); ++i) {
            for (int j = 0; j < ms; ++j) {
                cout << f[c[i]][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    int ns, ms, s0;
    cin >> ns >> ms >> s0;

    C c(ns, ms, s0);
    c.fillD();
    c.fillF();

    c.performDFS();
    c.printC();

    return 0;
}
