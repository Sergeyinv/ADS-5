// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

bool isOper(char op) {
    return (op == '+' || op == '-' || op == '*' || op == '/');
}
int getPrior(char oper) {
    switch (oper) {
    case '(':
        return 0;
        break;
    case ')':
        return 1;
        break;
    case '+':
        return 2;
        break;
    case '-':
        return 2;
        break;
    case '*':
        return 3;
        break;
    case '/':
        return 3;
        break;
    default:
        return -1;
        break;
    }
}

std::string infx2pstfx(std::string inf) {
    TStack<char, 100> stack1;
    std::string result = "";
    for (int i = 0; i < inf.length(); i++) {
        char n = inf[i];
        if (n >= '0' && n <= '9') {
            result += n;
            result += ' ';
        } else if (n == '(') {
            stack1.push(n);
        } else if (isOper(n)) {
            while (!stack1.isEmpty() && getPrior(stack1.get()) >= getPrior(n)) {
                result += stack1.get();
                result += ' ';
                stack1.pop();
            }
            stack1.push(n);
        } else if (n == ')') {
            while (!stack1.isEmpty() && stack1.get()!= '(') {
                result += stack1.get();
                result += ' ';
                stack1.pop();
            }
            stack1.pop();
        }
    }
    while (!stack1.isEmpty()) {
        result += stack1.get();
        result += ' ';
        stack1.pop();
    }
    result.pop_back();
    return result;
}

int eval(std::string pref) {
    TStack<int, 100> stack2;
    for (int i = 0; i < pref.length(); i++) {
        if (pref[i] <= '9' && pref[i] >= '0') {
            stack2.push(pref[i]-'0');
        } else if (isOper(pref[i])) {
            int operand1 = stack2.get();
            stack2.pop();
            int operand2 = stack2.get();
            stack2.pop();
            int res = 0;
            switch (pref[i]) {
            case '+':
                res = operand2 + operand1;
                break;
            case '-':
                res = operand2 - operand1;
                break;
            case '*':
                res = operand2 * operand1;
                break;
            case '/':
                res = operand2 / operand1;
                break;
            }
            stack2.push(res);
        }
    }
    return stack2.get();
}
