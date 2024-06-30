/*
Подготовка экспедиции на Марс
N кандидатов готовятся к двум космическим экспедициям на Марс. Поскольку экспедиции будут продолжаться несколько лет, а их участники окажутся в замкнутом пространстве небольшого объёма, то важное значение приобретает психологическая совместимость членов экипажа. Путём тестирования были установлены пары кандидатов, присутствие которых в одной и той же экспедиции было бы нежелательным. Результаты тестирования отражены в таблице размера N × N. Если на пересечении i-той строки и j-го столбца таблицы находится знак «+», то участие i-го и j-го кандидатов в одной экспедиции нежелательно.

Составьте программу, разделяющую кандидатов на две группы для участия в экспедициях. Если такое разделение невозможно, программа должна выводить сообщение «No solution». В противном случае, программа должна выводить номера кандидатов, принадлежащих первой группе. Первой группой мы будем считать группу, в которой меньше кандидатов.

Естественно, хорошо написанная программа должна стремиться к тому, чтобы размеры групп не очень сильно отличались. Поэтому, если возможно несколько разбиений на группы, программа должна выбирать разбиение с минимальной разностью количеств кандидатов в группах. При этом в случае, если разбиений с минимальной разницей всё равно получается несколько, для определённости выбирается разбиение, в котором первая группа лексикографически меньше, чем первые группы остальных разбиений.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class GroupProcessor {
public:
    virtual bool isInSameComponent(const vector<pair<int, int> >& enemies,
     int mask, int index) const {
        return ((mask >> enemies[index].first) & 1) == ((mask >> enemies[index].second) & 1);
    }

    virtual void updBG(vector<int>& bestGroup, int mask, int n) const {
        bestGroup.clear();
        for (int i = 0; i < n; ++i) {
            if ((mask >> i) & 1) {
                bestGroup.push_back(i);
            }
        }
    }

    virtual ~GroupProcessor() {}
};

class GroupFinder : public GroupProcessor {
public:
    vector<int> findBestGroup(const vector<pair<int, int> >& enemies, int n) {
        vector<int> bestGroup;
        findBGR(0, bestGroup, n, 0, 0, enemies);
        return bestGroup;
    }

private:
    void findBGR(int currentIndex, vector<int>& bestGroup, int n,
     int currentLength, int mask, const vector<pair<int, int> >& enemies) {
        if (currentLength >= n / 2 || currentIndex >= n) {
            return;
        }

        mask |= (1 << currentIndex);
        bool isValid = true;

        for (size_t i = 0; i < enemies.size(); ++i) {
            if (isInSameComponent(enemies, mask, static_cast<int>(i))) {
                isValid = false;
                break;
            }
        }

        if (isValid && currentLength + 1 > static_cast<int>(bestGroup.size())) {
            updBG(bestGroup, mask, n);
        }

        findBGR(currentIndex + 1, bestGroup, n, currentLength + 1, mask, enemies);
        mask ^= (1 << currentIndex);
        findBGR(currentIndex + 1, bestGroup, n, currentLength, mask, enemies);
    }
};

void insertionSort(vector<int>& bestGroup) {
    int n = bestGroup.size();
    for (int i = 1; i < n; ++i) {
        int key = bestGroup[i];
        int j = i - 1;

        while (j >= 0 && bestGroup[j] > key) {
            bestGroup[j + 1] = bestGroup[j];
            j = j - 1;
        }
        bestGroup[j + 1] = key;
    }
}

int main() {
    int n;
    cin >> n;

    vector<pair<int, int> > enemies;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            char relationship;
            cin >> relationship;
            if (relationship == '+') {
                enemies.push_back(make_pair(i, j));
            }
        }
    }

    GroupFinder groupFinder;
    vector<int> bestGroup = groupFinder.findBestGroup(enemies, n);

    if (bestGroup.empty()) {
        cout << "No Solution";
    } else {
        insertionSort(bestGroup);
        for (size_t i = 0; i < bestGroup.size(); ++i) {
            cout << bestGroup[i] + 1 << " ";
        }
    }

    return 0;
}
