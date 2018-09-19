#include <iostream>
#include<vector>
#include <stack>
#include <string>

void read_input(std::string &sequence, std::istream &in = std::cin) {
  in >> sequence;
}

void write_answer(int answer, std::ostream &out = std::cout) {
  if (answer == -1) {
    out << "CORRECT\n";
    return;
  }
  out << answer << "\n";
}

bool isClosing(char symbol) {
  return symbol == ')' || symbol == ']' || symbol == '}';
}

char getOpening(char symbol) {
  if (symbol == ')') {
    return '(';
  }
  if (symbol == ']') {
    return '[';
  }
  if (symbol == '}') {
    return '{';
  }
  return ' ';
}

void solver(const std::string &sequence, int &answer) {
  std::stack<char> stack;
  for (int i = 0; i < static_cast<int>(sequence.size()); ++i) {
    if (isClosing(sequence[i])) {
      if (!stack.empty() && stack.top() == getOpening(sequence[i])) {
        stack.pop();
      } else {
        answer = i;
        return;
      }
    } else {
      stack.push(sequence[i]);
    }
  }
  if (stack.empty()) {
    answer = -1;
  } else {
    answer = static_cast<int>(sequence.size());
  }
}

int main() {
  std::string seqence;
  int answer;
  read_input(seqence);
  solver(seqence, answer);
  write_answer(answer);
  return 0;
}
