#include <iostream>
#include <vector>

struct line {
    int id;
    int active;

    line(int num) : id(num), active(1) {};

    line() = default;

    void add() { active++; }

    void zero() { active = 1; }
};

using namespace std;

void LPU(int sizeline, vector<int> tests) {
    int exnums = 0;
    vector<line> lines;
    for (auto test:tests) {
        auto flag = false;
        for (auto &l:lines) {
            if (l.id == test) {
                l.zero();
                flag = true;
            } else
                l.add();
        }
        if (!flag) {
            if (lines.size() < sizeline) {
                lines.push_back(line(test));
            } else {
                auto max = lines.begin();
                auto beg = lines.begin();
                while (beg != lines.end()) {
                    if (beg->active > max->active)
                        max = beg;
                    beg++;
                }
                max->active = 1;
                max->id = test;
            }
            exnums++;

        }
    }
    cout << "lRU的命中率为" << float(((100 * (tests.size() - exnums)) / tests.size())) << "%" << endl;
}

void FIFO(int sizeline, vector<int> tests) {
    int exnums = 0;
    vector<line> lines;
    for (auto test:tests) {
        auto flag = false;
        for (auto &l:lines) {
            if (l.id == test) {
                l.add();
                flag = true;
            }
        }
        if (!flag) {
            if (lines.size() < sizeline) {
                lines.push_back(line(test));
            } else {
                auto min = lines.begin();
                auto beg = lines.begin();
                while (beg != lines.end()) {
                    if (beg->active < min->active)
                        min = beg;
                    beg++;
                }
                min->active = 1;
                min->id = test;
            }
            exnums++;
        }
    }


    cout << "FIFO的命中率为" << float(((100 * (tests.size() - exnums)) / tests.size())) << "%" << endl;
}

int main() {
    int sizeline;
    cin >> sizeline;
    vector<int> tests;

    for (int i = 0; i < 6 * sizeline; i++) {
        auto num = rand() % (2 * sizeline);
        tests.push_back(num);
    }

    FIFO(sizeline, tests);
    LPU(sizeline, tests);
    return 0;
}