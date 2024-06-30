/*
Программа должна считывать со стандартного потока ввода входной и выходной алфавиты, количество состояний N, матрицу переходов и матрицу выходов автомата Мили.

Входной и выходной алфавиты представлены в стандартном потоке ввода следующим образом: сначала идёт размер алфавита K, а затем следует K не содержащих пробелов строк,
представляющих сигналы алфавита.

Элемент Δij матрицы переходов содержит номер состояния, в которое автомат переходит из состояния i по сигналу j, причём состояния нумеруются, начиная с нуля. 
Элемент Φij матрицы выходов содержит выходной сигнал, который порождается автоматом при переходе из состояния i по сигналу j.

Программа должна выводить в стандартный поток вывода описание автомата Мура в формате DOT.
*/

#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

class State {
public:
    int stateId;
    int outputSignal;

    State(int stateId, int outputSignal) : stateId(stateId), outputSignal(outputSignal) {}

    bool operator==(const State &other) const {
        return stateId == other.stateId && outputSignal == other.outputSignal;
    }

    bool operator<(const State &other) const {
        if (stateId < other.stateId) return true;
        if (stateId > other.stateId) return false;
        return outputSignal < other.outputSignal;
    }
};

class FiniteStateMachine {
public:
    int numInputSymbols;
    int numOutputSymbols;
    int numStates;
    vector<string> inputSymbols;
    vector<string> outputSymbols;
    vector< vector<int> > transitionFunction;
    vector< vector<int> > outputFunction;

    void readInput() {
        cin >> numInputSymbols;
        inputSymbols.resize(numInputSymbols);
        for (int i = 0; i < numInputSymbols; ++i) {
            cin >> inputSymbols[i];
        }

        cin >> numOutputSymbols;
        outputSymbols.resize(numOutputSymbols);
        for (int i = 0; i < numOutputSymbols; ++i) {
            cin >> outputSymbols[i];
        }

        cin >> numStates;
        transitionFunction.resize(numStates, vector<int>(numInputSymbols));
        outputFunction.resize(numStates, vector<int>(numInputSymbols));

        for (int i = 0; i < numStates; ++i) {
            for (int j = 0; j < numInputSymbols; ++j) {
                cin >> transitionFunction[i][j];
            }
        }

        for (int i = 0; i < numStates; ++i) {
            for (int j = 0; j < numInputSymbols; ++j) {
                cin >> outputFunction[i][j];
            }
        }
    }
};

class MooreMachinePrinter : public FiniteStateMachine {
private:
    map<State, int> stateIdMap;
    vector<State> states;
    int stateCounter;

public:
    MooreMachinePrinter() : stateCounter(0) {}

    void buildMooreMachine() {
        for (int i = 0; i < numStates; ++i) {
            for (int j = 0; j < numInputSymbols; ++j) {
                State nextState(transitionFunction[i][j], outputFunction[i][j]);
                if (stateIdMap.find(nextState) == stateIdMap.end()) {
                    stateIdMap[nextState] = stateCounter++;
                    states.push_back(nextState);
                }
            }
        }
    }

    void printDotFormat() {
        cout << "digraph {" << endl;
        cout << "    rankdir = LR" << endl;
        
        for (vector<State>::iterator it = states.begin(); it != states.end(); ++it) {
            int id = stateIdMap[*it];
            cout << "    " << id << " [label = \"(" << it->stateId 
            << "," << outputSymbols[it->outputSignal] << ")\"]" << endl;
        }

        for (vector<State>::iterator it = states.begin(); it != states.end(); ++it) {
            int id = stateIdMap[*it];
            for (int j = 0; j < numInputSymbols; ++j) {
                State next(transitionFunction[it->stateId][j], 
                outputFunction[it->stateId][j]);
                cout << "    " << id << " -> " << stateIdMap[next]
                 << " [label = \"" << inputSymbols[j] << "\"]" << endl;
            }
        }
        
        cout << "}" << endl;
    }
};

int main() {
    MooreMachinePrinter printer;
    printer.readInput();
    printer.buildMooreMachine();
    printer.printDotFormat();

    return 0;
}
