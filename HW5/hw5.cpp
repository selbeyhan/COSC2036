#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
#include <cmath>
#include <iomanip>

class MyStack
{
private:
    std::vector<char> stack;

public:
    char top()
    {
        return stack.back();
    }

    void pop()
    {
        stack.pop_back();
    }

    void add(char element)
    {
        stack.push_back(element);
    }

    size_t size()
    {
        return stack.size();
    }
};

bool isOperator(char ch)
{
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

int getPrecedence(char op)
{
    if (op == '^')
        return 3;
    if (op == '*' || op == '/')
        return 2;
    if (op == '+' || op == '-')
        return 1;
    return 0; // Assuming '(' has the lowest precedence
}

std::string infixToPostfix(const std::string &infix)
{
    MyStack stack;
    std::string postfix;

    for (char ch : infix)
    {
        if (std::isdigit(ch))
        {
            postfix += ch;
        }
        else if (ch == '(')
        {
            stack.add(ch);
        }
        else if (ch == ')')
        {
            while (stack.size() > 0 && stack.top() != '(')
            {
                postfix += stack.top();
                stack.pop();
            }
            stack.pop(); // Remove '(' from the stack
        }
        else if (isOperator(ch))
        {
            while (stack.size() > 0 && getPrecedence(stack.top()) >= getPrecedence(ch))
            {
                postfix += stack.top();
                stack.pop();
            }
            stack.add(ch);
        }
    }

    while (stack.size() > 0)
    {
        postfix += stack.top();
        stack.pop();
    }

    return postfix;
}

bool isValidOperand(char ch)
{
    return (ch >= '0' && ch <= '9');
}

bool isValidPostfix(const std::string &postfix)
{
    MyStack stack;

    for (char ch : postfix)
    {
        if (isValidOperand(ch))
        {
            stack.add(ch);
        }
        else if (isOperator(ch))
        {
            if (stack.size() < 2)
            {
                return false; // Not enough operands for the operator
            }
            stack.pop();
            stack.pop();
            stack.add(' '); // Placeholder for the result of the operation
        }
    }

    return (stack.size() == 1);
}

float evaluatePostfix(const std::string &postfix)
{
    std::stack<float> evalStack;

    for (char ch : postfix)
    {
        if (isValidOperand(ch))
        {
            evalStack.push(static_cast<float>(ch - '0'));
        }
        else if (isOperator(ch))
        {
            float operand2 = evalStack.top();
            evalStack.pop();
            float operand1 = evalStack.top();
            evalStack.pop();

            switch (ch)
            {
            case '+':
                evalStack.push(operand1 + operand2);
                break;
            case '-':
                evalStack.push(operand1 - operand2);
                break;
            case '*':
                evalStack.push(operand1 * operand2);
                break;
            case '/':
                evalStack.push(operand1 / operand2);
                break;
            case '^':
                evalStack.push(std::pow(operand1, operand2));
                break;
            }
        }
    }

    return evalStack.top();
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        std::cerr << "Usage: " << argv[0] << " <part_number> <expression> <output_file_name>\n";
        return 1;
    }

    int partNumber = std::stoi(argv[1]);
    std::string expression = argv[2];
    std::string outputFileName = argv[3];

    std::ofstream outputFile(outputFileName);

    if (partNumber == 2)
    {
        std::string postfix = infixToPostfix(expression);
        outputFile << postfix << std::endl;
    }
    else if (partNumber == 3)
    {
        if (!isValidPostfix(expression))
        {
            outputFile << "nv" << std::endl;
        }
        else
        {
            float result = evaluatePostfix(expression);
            outputFile << std::fixed << std::setprecision(1) << result << std::endl;
        }
    }
    else
    {
        std::cerr << "Invalid part number. Use 2 for part2 or 3 for part3.\n";
        return 1;
    }
    outputFile.close();
    return 0;
}