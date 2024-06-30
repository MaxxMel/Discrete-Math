/*
Программа должна считывать из стандартного потока ввода сначала описание первого автомата,
а потом — описание второго автомата. Описание каждого автомата представлено в следующем формате: количество состояний автомата n,
размер входного алфавита m, номер начального состояния q0 (0 ≤ q0 < n), матрица переходов Δ и матрица выходов Φ. 
При этом элементами матрицы переходов являются номера состояний, а элементами матрицы выходов — выходные сигналы. Каждый выходной сигнал представляет собой не содержащую пробелов строку.

Программа должны выводить в стандартный поток вывода строку «EQUAL»,
если автоматы эквивалентны, и «NOT EQUAL» — в противном случае.
*/

#include <iostream>
#include <queue>
#include <set>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class MealyMachine {
public:
    int n, m, q0;
    vector< vector<int> > D;
    vector< vector<string> > fi;

    MealyMachine(istream& input) {
        input >> n >> m >> q0;
        D.resize(n, vector<int>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                input >> D[i][j];
            }
        }
        fi.resize(n, vector<string>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                input >> fi[i][j];
            }
        }
    }
};

class MealyMachineComp : public MealyMachine {
public:
    MealyMachineComp(istream& input) : MealyMachine(input) {}

    static bool equalMachine(const MealyMachine& M1, const MealyMachine& M2) {
        if (M1.m != M2.m) {
            return false;
        }
        queue <pair <int, int> > stateQueue;
        set<pair <int, int> > visitedStates;
        stateQueue.push(make_pair(M1.q0, M2.q0));
        visitedStates.insert(make_pair(M1.q0, M2.q0));

        while (!stateQueue.empty()) {
            pair<int, int> currentStatePair = stateQueue.front();
            stateQueue.pop();
            int s1 = currentStatePair.first;
            int s2 = currentStatePair.second;

            for (int i = 0; i < M1.m; ++i) {
                if (!checkAndEnqueue(M1, M2, s1, s2, i, stateQueue, visitedStates)) {
                    return false;
                }
            }
        }
        return true;
    }

private:
    static bool checkAndEnqueue(const MealyMachine& M1, 
    const MealyMachine& M2, int s1, int s2, int input, queue<pair<int, int> >& stateQueue, 
    set<pair<int, int> >& visitedStates) {
        int currentState1 = M1.D[s1][input];
        string output1 = M1.fi[s1][input];
        int currentState2 = M2.D[s2][input];
        string output2 = M2.fi[s2][input];

        if (output1 != output2) {
            return false;
        }

        pair<int, int> statePair = make_pair(currentState1, currentState2);
        if (visitedStates.find(statePair) == visitedStates.end()) {
            stateQueue.push(statePair);
            visitedStates.insert(statePair);
        }

        return true;
    }
};

int main() {
    MealyMachine machine1(cin);
    MealyMachine machine2(cin);
    if (MealyMachineComp::equalMachine(machine1, machine2)) {
        cout << "EQUAL" << endl;
    } else {
        cout << "NOT EQUAL" << endl;
    }
    return 0;
}
