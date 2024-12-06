#include <iostream>

double parseExpression(const char*& expr);
double factorial(int n) {
    if (n < 0) {
        std::cout << "Помилка факторіалу невірне число.\n";
        return 0;
    }
    double result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}
double power(double base, int exp) {
    double result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result *= base;
        }
        base *= base;
        exp /= 2;
    }
    return result;
}
double parseFactor(const char*& expr) {
    double result = 0;
    if (*expr == '(') {
        expr++;
        result = parseExpression(expr);
        if (*expr == ')') expr++;
    } else {
        while (*expr >= '0' && *expr <= '9') {
            result = result * 10 + (*expr - '0');
            expr++;
        }
    }
    if (*expr == '!') { 
        expr++;
        result = factorial((int)result);
    }
    return result;
}
double parseTerm(const char*& expr) {
    double result = parseFactor(expr);
    while (*expr == '^') {
        expr++;
        double exponent = parseFactor(expr);
        result = power(result, (int)exponent);
    }
    return result;
}
double parseFactorOps(const char*& expr) {
    double result = parseTerm(expr);
    while (*expr == '*' || *expr == '/') {
        char op = *expr++;
        double next = parseTerm(expr);
        if (op == '*') result *= next;
        else if (op == '/') {
            if (next == 0) {
                std::cout << "Помилка ділення на 0.\n";
                return 0;
            }
            result /= next;
        }
    }
    return result;
}
double parseExpression(const char*& expr) {
    double result = parseFactorOps(expr);
    while (*expr == '+' || *expr == '-') {
        char op = *expr++;
        double next = parseFactorOps(expr);
        if (op == '+') result += next;
        else if (op == '-') result -= next;
    }
    return result;
}

int main() {
    char input[256];
    std::cout << "Введіть вираження: ";
    std::cin >> input;
    const char* expr = input;
    std::cout << "Результат виводу: " << parseExpression(expr) << "\n";
    return 0;
}

