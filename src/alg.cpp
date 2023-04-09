// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int getPriority(char op) {
  std::pair<char, int> prioritet[6];
  switch (op) {
    case'(':
      prioritet[0].first = '(';
      prioritet[0].second = 0;
    case')':
      prioritet[1].first = ')';
      prioritet[1].second = 1;
    case'+':
      prioritet[2].first = '+';
      prioritet[2].second = 2;
    case'-':
      prioritet[3].first = '-';
      prioritet[3].second = 2;
    case'*':
      prioritet[4].first = '*';
      prioritet[4].second = 3;
    case'/':
      prioritet[5].first = '/';
      prioritet[5].second = 3;
  }
  int priority = -1;
  for (int j = 0; j < 6; ++j) {
    if (op == prioritet[j].first) {
      priority = prioritet[j].second;
      break;
    }
  }
  return priority;
}

std::string mirOne(const std::string& a) {
  if (a.length() <= 2) return a;
  int b = 2 - a.length() % 2;
  std::string d(a, 0, b);
  for (auto it = a.begin() + b; it != a.end();) {
    d += ' '; d += *it++;;
  }
  return d;
}


std::string infx2pstfx(std::string inf) {
  std::string s;
  Tstack<char, 100> stack1;
  for (auto& op : inf) {
    int priority = getPriority(op);
    if (priority == -1) {
      s += op;
    } else {
      if (stack1.get() < priority  priority == 0  stack1.isEmpty()) {
        stack1.push(op);
      } else if (op == ')') {
        char sm = stack1.get();
        while (getPriority(sm) >= priority) {
          s += sm;
          stack1.pop();
          sm = stack1.get();
        }
        stack1.pop();
      } else {
        char sm = stack1.get();
        while (getPriority(sm) >= priority) {
          s += sm;
          stack1.pop();
          sm = stack1.get();
        }
        stack1.push(op);
      }
    }
  }
  while (!stack1.isEmpty()) {
    s += stack1.get();
    stack1.pop();
  }
  s = mirOne(s);
  return s;
}


int count(const int& a, const int& b, const int& operation) {
  switch (operation) {
    default:
      break;
    case'+': return a + b;
    case'-': return a - b;
    case'*': return a * b;
    case'/': return a / b;
  }
  return 0;
}

int eval(std::string pref) {
  Tstack<int, 100> stack1;
  std::string num = "";
  for (size_t i = 0; i < pref.size(); i++) {
    if (getPriority(pref[i]) == -1) {
      if (pref[i] == ' ') {
        continue;
      } else if (isdigit(pref[i + 1])) {
        num += pref[i];
        continue;
      } else {
        num += pref[i];
        stack1.push(atoi(num.c_str()));
        num = "";
      }
    } else {
      int n = stack1.get();
      stack1.pop();
      int k = stack1.get();
      stack1.pop();
      stack1.push(count(k, n, pref[i]));
    }
  }
  return stack1.get();
}
