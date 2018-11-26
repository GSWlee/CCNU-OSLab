#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdio>
#include <list>

using namespace std;

int MEMORY_SIZE;


struct test {
    int num;
    int size;
    int start;
    int end;

    test(int a, int b, int c, int d) : num(a), size(b), start(c), end(d) {};

    test() = default;
};

struct space {
    int start_address;
    int end_address;

    space(int a, int b) : start_address(a), end_address(b) {};

    space() = default;
};

string &trim(std::string &s) {
    if (s.empty())
        return s;
    s.erase(0, s.find_first_not_of(' '));
    s.erase(s.find_last_not_of(' ') + 1);
    return s;
}


bool find(int id, vector<test> tests) {
    for (auto temp:tests) {
        if (temp.num == id)
            return true;
    }
    return false;
}

bool find(int id, vector<int> nums) {
    for (auto temp:nums) {
        if (temp == id)
            return true;
    }
    return false;
}

void randtest(vector<test> &tests, list<space> &spaces) {
    vector<int> nums;

    for (int i = 0; i < 20; i++) {
        auto num = rand() % MEMORY_SIZE;
        if(num==67)
            printf("s");
        while (find(num, nums)) {
            num = rand() % MEMORY_SIZE;
        }
        nums.push_back(num);

    }
    sort(nums.begin(), nums.end());
    test temp;
    space toy;
    for (int i = 0; i < 10; i++) {
        temp.num = i;
        temp.size = nums[i * 2 + 1] - nums[i * 2];
        temp.start = nums[i * 2];
        temp.end = nums[i * 2 + 1];
        toy.start_address = (i == 0 ? 0 : nums[i * 2 - 1]);
        toy.end_address = nums[i * 2];
        tests.push_back(temp);
        if (i != 0 && (toy.start_address == spaces.back().end_address)) {
            auto it = spaces.end();
            (it--)->end_address = toy.end_address;
        } else {
            spaces.push_back(toy);
        }
    }
    spaces.emplace_back(space(nums[19], MEMORY_SIZE));
}

void showempty(list<space> spaces) {
    auto temp = spaces.begin();
    printf("show space information:\n");
    printf("space_size   space_saddress  space_eaddress\n");
    for (; temp != spaces.end(); temp++) {
        printf("%10d  %14d  %14d\n", temp->end_address - temp->start_address, temp->start_address,
               temp->end_address);
    }
}

void showtest(vector<test> test) {
    printf("show test information:\n");
    printf("test_id   test_size  test_saddress  test_eaddress\n");
    for (auto temp:test)
        printf("%6d  %8d  %13d  %13d\n", temp.num, temp.size, temp.start, temp.end);

}


bool drop(int id, vector<test> &tests, list<space> &spaces) {
    bool flag = false;
    for (auto temp = tests.begin(); temp != tests.end(); temp++) {
        if (temp->num == id) {
            flag = true;
            auto it = spaces.begin();
            for (; it != spaces.end(); it++) {
                if (it->start_address < temp->start)
                    continue;
                auto itt = it;
                if ((it--)->end_address < temp->start) {
                    if ((itt++)->start_address > temp->end)
                        spaces.insert(itt, space(temp->start, temp->end));
                    else {
                        itt->start_address = temp->start;
                    }
                    tests.erase(temp);
                    break;
                } else {
                    if ((itt++)->start_address == temp->end)
                        it->end_address = temp->end;
                    else {
                        it->end_address = itt->end_address;
                        spaces.erase(itt);
                    }
                    tests.erase(temp);
                    break;
                }
            }
        }
    }
    return flag;
}

int addf(int size, vector<test> &tests, list<space> &spaces) {
    auto it = spaces.begin();
    int id = -1;
    for (; it != spaces.end(); it++) {
        if ((it->end_address - it->start_address) < size)
            continue;
        else {
            id = rand() % MEMORY_SIZE;
            while (find(id, tests))
                id = rand() % MEMORY_SIZE;
            tests.emplace_back(test(id, size, it->start_address, it->start_address + size));
            if (it->start_address == (it->end_address + size))
                spaces.erase(it);
            else
                it->start_address = it->start_address + size;
        }
    }
    return id;
}

int addw(int size, vector<test> &tests, list<space> &spaces) {
    auto it = spaces.begin();
    int id = -1;
    auto max = spaces.begin();
    for (; it != spaces.end(); it++) {
        if ((it->end_address - it->start_address) < size)
            continue;
        else {
            if ((it->end_address - it->start_address) > ((max->end_address - max->start_address)))
                max = it;
        }
    }
    if ((max->end_address - max->start_address) >= size) {
        id = rand() % MEMORY_SIZE;
        while (find(id, tests))
            id = rand() % MEMORY_SIZE;
        tests.emplace_back(test(id, size, max->start_address, max->start_address + size));
        if (max->start_address == (max->end_address + size))
            spaces.erase(it);
        else
            max->start_address = max->start_address + size;
    }
    return id;
}

int addb(int size, vector<test> &tests, list<space> &spaces) {
    auto it = spaces.begin();
    int id = -1;
    auto best = spaces.begin();
    for (; it != spaces.end(); it++) {
        if ((it->end_address - it->start_address) < size)
            continue;
        else {
            if ((it->end_address - it->start_address) < ((best->end_address - best->start_address)))
                best = it;
        }
    }
    if ((best->end_address - best->start_address) >= size) {
        id = rand() % MEMORY_SIZE;
        while (find(id, tests))
            id = rand() % MEMORY_SIZE;
        tests.emplace_back(test(id, size, best->start_address, best->start_address + size));
        if (best->start_address == (best->end_address + size))
            spaces.erase(it);
        else
            best->start_address = best->start_address + size;
    }
    return id;
}

int main() {
    cout << "Please enter memory size:";
    cin >> MEMORY_SIZE;
    vector<test> tests;
    list<space> spaces;
    randtest(tests, spaces);
    cout << "enter:--help for help" << endl;
    string order;
    string obtion;
    cin >> order;
    while (order != "quit") {
        if (order == "ls") {
            cin >> obtion;
            if (obtion == "-t") {
                showtest(tests);
            } else if (obtion == "-e") {
                showempty(spaces);
            } else if (obtion == "-a") {
                showempty(spaces);
                showtest(tests);
            } else {
                cout << "command not find" << endl;
            }
        } else if (order == "--help") {
            cout
                    << "ls [-a|-e|-t]: show information; -e empty space information; -t test/using memory information;-a both;"
                    << endl;
            cout << "drop [id]:delete test named id." << endl;
            cout
                    << "add [-f|-b|-w] [size]:set test; -f use first fit method; -b use best fit method; -w use worse fit method"
                    << endl;
        } else if (order == "drop") {
            cin >> order;
            int id = stoi(order);
            bool flag = drop(id, tests, spaces);
            auto message = (flag ? "test has been drop" : "failed drop test:test not find");
            cout << message << endl;
        } else if (order == "add") {
            cin >> obtion;
            if (obtion == "-f") {
                cin >> obtion;
                int size = stoi(obtion);
                int id = addf(size, tests, spaces);
                auto message = (id >= 0 ? "test has been set id is " + to_string(id)
                                        : "failed set test:not enough");
                cout << message << endl;
            } else if (obtion == "-b") {
                cin >> obtion;
                int size = stoi(obtion);
                int id = addb(size, tests, spaces);
                auto message = (id >= 0 ? "test has been set id is " + to_string(id)
                                        : "failed set test:not enough");
                cout << message << endl;
            } else if (obtion == "-w") {
                cin >> obtion;
                int size = stoi(obtion);
                int id = addw(size, tests, spaces);
                auto message = (id >= 0 ? "test has been set id is " + to_string(id)
                                        : "failed set test:not enough");
                cout << message << endl;
            } else {
                cout << "command not find" << endl;
            }


        } else {
            cout << "command not find" << endl;
        }
        cin >> order;
    }
    return 0;
}