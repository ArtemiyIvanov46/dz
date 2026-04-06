#include <iostream>
#include <stdexcept>

class Calculator {
public:
    double add(double first, double second) const {
        return first + second;
    }

    double subtract(double first, double second) const {
        return first - second;
    }

    double multiply(double first, double second) const {
        return first * second;
    }

    double divide(double first, double second) const {
        if (second == 0) {
            throw std::runtime_error("Division by zero is not allowed.");
        }

        return first / second;
    }
};

int main() {
    Calculator calculator;
    double first = 0;
    double second = 0;
    char operation = '\0';

    std::cout << "Enter expression: ";
    std::cin >> first >> operation >> second;

    try {
        double result = 0;

        switch (operation) {
            case '+':
                result = calculator.add(first, second);
                break;
            case '-':
                result = calculator.subtract(first, second);
                break;
            case '*':
                result = calculator.multiply(first, second);
                break;
            case '/':
                result = calculator.divide(first, second);
                break;
            default:
                std::cout << "Unknown operation." << std::endl;
                return 1;
        }

        std::cout << "Result: " << result << std::endl;
    } catch (const std::exception& error) {
        std::cout << error.what() << std::endl;
        return 1;
    }

    return 0;
}
