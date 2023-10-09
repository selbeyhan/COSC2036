#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Stack
{
public:
    int top;
    char arr[1000];
    Stack() { top = -1; };
    void push(char addValue);
    char pop();
    char peek();
    bool isEmpty();
};

void Stack::push(char addValue)
{
    if (top >= 999)
    {
        cout << "There is not enough room for adding new input! \n";
        return;
    }
    arr[++top] = addValue;
}

char Stack::peek()
{
    if (top < 0)
    {
        cout << "There is no element in this stack!\n";
        return 0;
    }
    int topValue = arr[top];
    return topValue;
}

char Stack::pop()
{
    if (top < 0)
    {
        cout << "There is no element in this stack! \n";
        return 0;
    }
    int topValue = arr[top--];
    return topValue;
}

bool Stack::isEmpty()
{
    if (top < 0)
    {
        return true;
    }
    return false;
}

bool isBalanced(string s)
{
    Stack st;

    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '(' || s[i] == '{' || s[i] == '[')
        {
            st.push(s[i]);
        }
        else if (s[i] == ')')
        {
            if (st.isEmpty() || st.pop() != '(')
                return false;
        }
        else if (s[i] == '}')
        {
            if (st.isEmpty() || st.pop() != '{')
                return false;
        }
        else if (s[i] == ']')
        {
            if (st.isEmpty() || st.pop() != '[')
                return false;
        }
    }

    return st.isEmpty();
}

int main(int argc, char *argv[])
{
    string sampleInput = "./lab7 1.txt output.txt";
    if (argc != 3)
    {
        cout << "Invalid Argument, Sample Input Below\n\t" << sampleInput;
        return 0;
    }

    bool bal;
    string inputText;
    ifstream inputFile(argv[1]);
    if (inputFile.is_open())
    {
        inputFile >> inputText;
    }
    else
    {
        cout << "Couldn't Open Input File";
        return 0;
    }
    inputFile.close();
    ofstream outputFile(argv[2]);
    if (outputFile.is_open())
    {
        outputFile << (isBalanced(inputText) ? "True" : "False");
    }
    else
    {
        cout << "Couldn't Open Output File";
        return 0;
    }
    outputFile.close();
    return 0;
}
