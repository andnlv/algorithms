#include <iostream>
#include <queue>
#include <list>
#include <vector>

void read_input(std::vector<int> &numbers, std::queue<char> &commands) {
    int commandsNum, numbersNum;
    std::cin >> numbersNum;
    numbers.resize(size_t(numbersNum));
    for (int i = 0; i < numbersNum; ++i) {
        std::cin >> numbers[i];
    }
    std::cin >> commandsNum;
    for (int i = 0; i < commandsNum; ++i) {
        char buff;
        std::cin >> buff;
        commands.push(buff);
    }
}

void solver(std::vector<int> &numbers, std::queue<char> &commands) {
    int right = 0;
    int left = 0;
    std::list<int> maxIndeces;
    maxIndeces.push_front(0);
    while (!commands.empty()) {
        if (commands.front() == 'R') {
            ++right;
            while (!maxIndeces.empty() && numbers[maxIndeces.front()] < numbers[right]) {
                maxIndeces.pop_front();
            }
            maxIndeces.push_front(right);
        } else {
            ++left;
            if (left > maxIndeces.back()) {
                maxIndeces.pop_back();
            }
        }
        commands.pop();
        std::cout << numbers[maxIndeces.back()] << " ";
    }
}

int main() {
    std::vector<int> numbers;
    std::queue<char> commands;
    read_input(numbers, commands);
    solver(numbers, commands);
    return 0;
}
